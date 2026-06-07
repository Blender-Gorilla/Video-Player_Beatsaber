#!/usr/bin/env bash
set -euo pipefail

# ── Prerequisites ──────────────────────────────────────────────────────────────
# - Android NDK r25c (set NDK env var or place at ~/Android/Sdk/ndk/25.2.*)
# - qpm-rust  (https://github.com/QuestPackageManager/QPM.Rust/releases)
# - cmake 3.22+, ninja

NDK_VER=${NDK_VER:-25.2.9519653}
ANDROID_SDK=${ANDROID_SDK:-$HOME/Android/Sdk}
NDK_PATH="${NDK_PATH:-${ANDROID_SDK}/ndk/${NDK_VER}}"
TOOLCHAIN="${NDK_PATH}/build/cmake/android.toolchain.cmake"

if [ ! -f "$TOOLCHAIN" ]; then
  echo "ERROR: NDK toolchain not found at ${TOOLCHAIN}"
  exit 1
fi

# ── Restore QPM dependencies ───────────────────────────────────────────────────
echo "==> Restoring QPM dependencies..."
qpm restore

# ── Configure ─────────────────────────────────────────────────────────────────
echo "==> Configuring..."
cmake -B build \
  -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE="${TOOLCHAIN}" \
  -DANDROID_ABI=arm64-v8a \
  -DANDROID_PLATFORM=android-31 \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DEXTERN_LIB_DIR="${PWD}/extern/libs"

# ── Build ──────────────────────────────────────────────────────────────────────
echo "==> Building..."
cmake --build build --parallel "$(nproc)"

# ── Package .qmod ──────────────────────────────────────────────────────────────
echo "==> Packaging .qmod..."
cp build/libVideoPlayer.so BMBF/VideoPlayer.so

QMOD_CONTENTS=(
  BMBF/mod.json
  BMBF/VideoPlayer.so
  BMBF/VideoPlayerConfig.json
)

zip -j VideoPlayer.qmod "${QMOD_CONTENTS[@]}"
echo "==> Done! Output: VideoPlayer.qmod"
