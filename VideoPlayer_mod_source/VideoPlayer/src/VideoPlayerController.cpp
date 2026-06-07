#include "VideoPlayerController.hpp"
#include "VideoPlayerConfig.hpp"
#include "main.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/PrimitiveType.hpp"
#include "UnityEngine/Video/VideoPlayer.hpp"
#include "UnityEngine/Video/VideoSource.hpp"
#include "UnityEngine/Video/VideoAudioOutputMode.hpp"
#include "UnityEngine/RenderTextureFormat.hpp"
#include "UnityEngine/RenderTextureDescriptor.hpp"
#include "UnityEngine/RenderTexture.hpp"
#include "UnityEngine/Shader.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Mathf.hpp"
#include "System/Uri.hpp"

DEFINE_TYPE(VideoPlayer, VideoPlayerController);

VideoPlayer::VideoPlayerController* VideoPlayer::VideoPlayerController::_instance = nullptr;

VideoPlayer::VideoPlayerController* VideoPlayer::VideoPlayerController::GetInstance() {
    return _instance;
}

void VideoPlayer::VideoPlayerController::Awake() {
    _instance = this;
    CreateScreen();
    SetupVideoPlayer();
    ApplyConfig();

    if (getVideoPlayerConfig().AutoPlay.GetValue()) {
        LoadVideo(getVideoPlayerConfig().VideoPath.GetValue());
    }
}

void VideoPlayer::VideoPlayerController::OnDestroy() {
    if (_instance == this) _instance = nullptr;
}

// ── Screen ──────────────────────────────────────────────────────────────────

void VideoPlayer::VideoPlayerController::CreateScreen() {
    // Create a Quad as the video surface
    screenObject = UnityEngine::GameObject::CreatePrimitive(
        UnityEngine::PrimitiveType::Quad);
    screenObject->set_name("VideoPlayerScreen");
    UnityEngine::Object::DontDestroyOnLoad(screenObject);

    meshRenderer = screenObject->GetComponent<UnityEngine::MeshRenderer*>();

    // Unlit black material so it looks like a real screen
    auto shader   = UnityEngine::Shader::Find("Unlit/Texture");
    auto material = UnityEngine::Material::New_ctor(shader);
    material->set_color(UnityEngine::Color::get_black());
    meshRenderer->set_material(material);

    // RenderTexture that the VideoPlayer will render into (1920×1080)
    UnityEngine::RenderTextureDescriptor desc(1920, 1080,
        UnityEngine::RenderTextureFormat::Default, 0);
    renderTexture = UnityEngine::RenderTexture::New_ctor(desc);
    renderTexture->Create();
    material->set_mainTexture(renderTexture);
}

// ── VideoPlayer component ────────────────────────────────────────────────────

void VideoPlayer::VideoPlayerController::SetupVideoPlayer() {
    videoPlayer = screenObject->AddComponent<UnityEngine::Video::VideoPlayer*>();
    videoPlayer->set_renderMode(
        UnityEngine::Video::VideoRenderMode::RenderTexture);
    videoPlayer->set_targetTexture(renderTexture);
    videoPlayer->set_audioOutputMode(
        UnityEngine::Video::VideoAudioOutputMode::AudioSource);

    // Add an audio source on the same object
    audioSource = screenObject->AddComponent<UnityEngine::AudioSource*>();
    audioSource->set_spatialBlend(0.0f); // 2-D audio
    videoPlayer->SetTargetAudioSource(0, audioSource);
}

// ── Playback ─────────────────────────────────────────────────────────────────

void VideoPlayer::VideoPlayerController::LoadVideo(StringW path) {
    if (!videoPlayer) return;
    // Build a file:// URI so the VideoPlayer can locate the clip
    auto uri = System::Uri::New_ctor(path);
    videoPlayer->set_url(uri->get_AbsoluteUri());
    videoPlayer->Prepare();
    if (getVideoPlayerConfig().AutoPlay.GetValue()) {
        videoPlayer->Play();
    }
}

void VideoPlayer::VideoPlayerController::Play() {
    if (videoPlayer) videoPlayer->Play();
}

void VideoPlayer::VideoPlayerController::Pause() {
    if (videoPlayer) videoPlayer->Pause();
}

void VideoPlayer::VideoPlayerController::Stop() {
    if (videoPlayer) videoPlayer->Stop();
}

// ── Transform helpers ─────────────────────────────────────────────────────────

void VideoPlayer::VideoPlayerController::SetPosition(float x, float y, float z) {
    if (!screenObject) return;
    screenObject->get_transform()->set_position({x, y, z});
}

void VideoPlayer::VideoPlayerController::SetRotation(float x, float y, float z) {
    if (!screenObject) return;
    screenObject->get_transform()->set_eulerAngles({x, y, z});
}

void VideoPlayer::VideoPlayerController::SetScale(float x, float y) {
    if (!screenObject) return;
    screenObject->get_transform()->set_localScale({x, y, 1.0f});
}

void VideoPlayer::VideoPlayerController::SetVolume(float v) {
    if (audioSource) audioSource->set_volume(v);
}

void VideoPlayer::VideoPlayerController::SetLoop(bool loop) {
    if (videoPlayer) videoPlayer->set_isLooping(loop);
}

// ── ApplyConfig ───────────────────────────────────────────────────────────────

void VideoPlayer::VideoPlayerController::ApplyConfig() {
    auto& cfg = getVideoPlayerConfig();
    SetPosition(cfg.PosX.GetValue(),  cfg.PosY.GetValue(),  cfg.PosZ.GetValue());
    SetRotation(cfg.RotX.GetValue(),  cfg.RotY.GetValue(),  cfg.RotZ.GetValue());
    SetScale   (cfg.ScaleX.GetValue(), cfg.ScaleY.GetValue());
    SetVolume  (cfg.Volume.GetValue());
    SetLoop    (cfg.Loop.GetValue());
}
