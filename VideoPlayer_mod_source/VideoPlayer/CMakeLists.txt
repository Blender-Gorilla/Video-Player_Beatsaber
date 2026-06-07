cmake_minimum_required(VERSION 3.22)

project(VideoPlayer VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── NDK / Quest toolchain is set by qpm-rust / build.sh ──────────────────────

# ── Source files ─────────────────────────────────────────────────────────────
add_library(VideoPlayer SHARED
    src/main.cpp
    src/VideoPlayerController.cpp
    src/SettingsViewController.cpp
)

target_include_directories(VideoPlayer PRIVATE
    include
    extern/includes
    extern/includes/beatsaber-hook/shared
    extern/includes/custom-types/shared
    extern/includes/bsml/shared
    extern/includes/config-utils/shared
    extern/includes/paper/shared
    extern/includes/modloader/shared
    extern/includes/scotland2/shared
)

# ── QPM dependencies are resolved into extern/ by `qpm restore` ──────────────
# Link order matters: inner-most libs first
target_link_libraries(VideoPlayer
    ${EXTERN_LIB_DIR}/libbeatsaber-hook_3.a
    ${EXTERN_LIB_DIR}/libcustom-types.so
    ${EXTERN_LIB_DIR}/libbsml.so
    ${EXTERN_LIB_DIR}/libconfig-utils.so
    ${EXTERN_LIB_DIR}/libpaper.so
    log
    android
)

# ── Strip debug symbols for release ──────────────────────────────────────────
target_compile_options(VideoPlayer PRIVATE
    -O2
    -fvisibility=hidden
    -DMOD_ID="${PROJECT_NAME}"
    -DMOD_VERSION="${PROJECT_VERSION}"
)
