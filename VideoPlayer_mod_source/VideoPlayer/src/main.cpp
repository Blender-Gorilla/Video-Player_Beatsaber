#include "main.hpp"
#include "VideoPlayerController.hpp"
#include "SettingsViewController.hpp"
#include "VideoPlayerConfig.hpp"

#include "modloader/shared/modloader.hpp"
#include "custom-types/shared/register.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSMLDataCache.hpp"

#include "GlobalNamespace/MainMenuViewController.hpp"
#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "UnityEngine/SceneManagement/SceneManager.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"
#include "UnityEngine/GameObject.hpp"

#include "scotland2/shared/modloader.h"
#include "beatsaber-hook/shared/utils/hooking.hpp"

// ── Config singleton ──────────────────────────────────────────────────────────

static VideoPlayerConfig _cfg;
VideoPlayerConfig& getVideoPlayerConfig() { return _cfg; }

// ── Scene lifecycle hook ──────────────────────────────────────────────────────
//
//  We create the VideoPlayerController when the game scene loads (i.e.
//  GameplayCore or MenuCore) and destroy the old one between scenes so the
//  screen follows the player into gameplay.

MAKE_HOOK_MATCH(SceneManager_activeSceneChanged,
    &UnityEngine::SceneManagement::SceneManager::activeSceneChanged,
    void,
    UnityEngine::SceneManagement::Scene from,
    UnityEngine::SceneManagement::Scene to)
{
    SceneManager_activeSceneChanged(from, to);

    std::string name = static_cast<std::string>(to.get_name());

    // Destroy existing controller so we don't duplicate across scene loads
    auto* old = VideoPlayer::VideoPlayerController::GetInstance();
    if (old) UnityEngine::Object::Destroy(old->get_gameObject());

    // Spawn fresh controller in gameplay and menu scenes
    if (name == "GameCore" || name == "MenuViewControllers") {
        auto* go = UnityEngine::GameObject::New_ctor("VideoPlayerHost");
        UnityEngine::Object::DontDestroyOnLoad(go);
        go->AddComponent<VideoPlayer::VideoPlayerController*>();
    }
}

// ── Mod setup ─────────────────────────────────────────────────────────────────

extern "C" void setup(CModInfo* info) {
    info->id      = MOD_ID;
    info->version = MOD_VER;
    info->version_long = 0;

    _cfg.Init(modloader::get_files_dir());
    Paper::Logger::RegisterFileContextId(MOD_ID);
    Logger.info("VideoPlayer setup complete");
}

extern "C" void late_load() {
    il2cpp_functions::Init();

    // Register custom types
    custom_types::Register::AutoRegister();

    // Install scene hook
    INSTALL_HOOK(Logger, SceneManager_activeSceneChanged);

    // Register mod settings menu via BSML
    BSML::Register::RegisterSettingsMenu<VideoPlayer::SettingsViewController*>(
        "Video Player",   // name shown in Mods settings list
        "settings",       // BSML resource key
        false             // don't show in-game pause menu
    );

    Logger.info("VideoPlayer late_load complete");
}
