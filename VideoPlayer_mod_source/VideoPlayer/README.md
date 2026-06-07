# VideoPlayer – Quest Beat Saber Mod

Play local **MP4 videos** on a fully customisable in-game screen while playing or browsing the Beat Saber menu on Meta Quest (1/2/3/Pro).

---

## Features

| Feature | Detail |
|---------|--------|
| MP4 playback | Any H.264/AAC MP4 file stored on the Quest |
| Position | X / Y / Z sliders |
| Rotation | Euler X / Y / Z sliders |
| Scale | Independent Width & Height |
| Volume | 0–100 % |
| Loop | Toggle |
| Auto-play | Toggle (loads & plays on scene start) |
| Curvature | Gentle screen bow (0 = flat, 0.5 = strongly curved) |
| BSML settings UI | In-game panel under **Mods → Video Player** |
| Persistent config | `/sdcard/ModData/.../VideoPlayer/VideoPlayerConfig.json` |
| Play / Pause / Stop / Reload | Buttons in the settings panel |

---

## Installation (pre-built)

1. Download `VideoPlayer.qmod` from Releases.
2. Sideload with **QuestPatcher** or **BMBF**:
   - QuestPatcher: drag-and-drop `VideoPlayer.qmod` onto the *Mods* tab.
   - BMBF: upload through the BMBF web interface.
3. Copy your MP4 to the Quest:
   ```
   /sdcard/ModData/com.beatgames.beatsaber/Mods/VideoPlayer/video.mp4
   ```
4. Launch Beat Saber. The screen appears automatically.
5. Adjust position/scale/etc. via **Mods → Video Player** in the settings menu.

---

## Building from source

### Prerequisites

| Tool | Version |
|------|---------|
| Android NDK | r25c (`25.2.9519653`) |
| CMake | ≥ 3.22 |
| Ninja | any |
| qpm-rust | latest |
| Beat Saber on Quest | 1.37.x |

### Steps

```bash
# 1. Clone
git clone https://github.com/youruser/VideoPlayer
cd VideoPlayer

# 2. Set NDK path (if not default)
export NDK_PATH=/path/to/ndk/25.2.9519653

# 3. Build & package
chmod +x build.sh
./build.sh
# → outputs VideoPlayer.qmod
```

---

## Configuration file

Location on device:
```
/sdcard/ModData/com.beatgames.beatsaber/Mods/VideoPlayer/VideoPlayerConfig.json
```

```json
{
  "videoPath"       : "/sdcard/ModData/com.beatgames.beatsaber/Mods/VideoPlayer/video.mp4",
  "posX"            : 0.0,
  "posY"            : 2.5,
  "posZ"            : 4.0,
  "rotX"            : 0.0,
  "rotY"            : 0.0,
  "rotZ"            : 0.0,
  "scaleX"          : 4.0,
  "scaleY"          : 2.25,
  "loop"            : true,
  "autoPlay"        : true,
  "volume"          : 0.5,
  "screenCurvature" : 0.0
}
```

You can edit this file with `adb shell` or push a pre-made version before first launch.

---

## Project structure

```
VideoPlayer/
├── src/
│   ├── main.cpp                    # Mod entry, hooks, scene lifecycle
│   ├── VideoPlayerController.cpp   # Screen creation & Unity VideoPlayer
│   └── SettingsViewController.cpp  # BSML settings UI logic
├── include/
│   ├── main.hpp
│   ├── VideoPlayerConfig.hpp       # config-utils macro config
│   ├── VideoPlayerController.hpp   # custom-types class declaration
│   ├── SettingsViewController.hpp  # BSML ViewController declaration
│   ├── assets.hpp                  # Embeds BSML XML at compile time
│   ├── settings.bsml               # BSML XML layout
│   └── settings_bsml.inc           # Generated C string include
├── BMBF/
│   ├── mod.json                    # QuestPatcher/BMBF manifest
│   └── VideoPlayerConfig.json      # Default config shipped in .qmod
├── CMakeLists.txt
├── qpm.json
├── build.sh
└── README.md
```

---

## How it works

1. **Scene hook** – A `SceneManager.activeSceneChanged` hook fires on every scene transition. When Beat Saber loads the `GameCore` or `MenuViewControllers` scene the hook spawns a `VideoPlayerHost` GameObject marked `DontDestroyOnLoad`.

2. **VideoPlayerController** – A `MonoBehaviour` attached to that host. On `Awake` it:
   - Creates a `Quad` primitive as the video surface.
   - Attaches a `UnityEngine.Video.VideoPlayer` component pointed at a `RenderTexture`.
   - Reads `VideoPlayerConfig.json` and positions/scales the screen accordingly.
   - Optionally auto-plays the configured MP4.

3. **Settings UI** – A BSML `ViewController` registered with `BSML::Register::RegisterSettingsMenu`. All sliders and toggles bind directly to the config via BSML property macros. "Apply & Save" flushes config to disk and calls `ApplyConfig()` on the live controller.

---

## Dependencies (resolved automatically by QPM)

| Package | Purpose |
|---------|---------|
| `beatsaber-hook` | IL2CPP interop & hooking |
| `custom-types` | Register C++ MonoBehaviour classes with Unity |
| `bsml` | Declarative XML UI for Beat Saber |
| `config-utils` | JSON-backed config with typed accessors |
| `paper` | Logging |
| `scotland2` | Mod loader runtime (peer dependency) |

---

## Licence

MIT – see `LICENSE`.
