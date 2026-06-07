#pragma once

#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Video/VideoPlayer.hpp"
#include "UnityEngine/Video/VideoClip.hpp"
#include "UnityEngine/RenderTexture.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/MeshFilter.hpp"
#include "UnityEngine/Mesh.hpp"
#include "UnityEngine/AudioSource.hpp"
#include "UnityEngine/Vector3.hpp"
#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(VideoPlayer, VideoPlayerController, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(UnityEngine::Video::VideoPlayer*, videoPlayer);
    DECLARE_INSTANCE_FIELD(UnityEngine::RenderTexture*, renderTexture);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, screenObject);
    DECLARE_INSTANCE_FIELD(UnityEngine::MeshRenderer*, meshRenderer);
    DECLARE_INSTANCE_FIELD(UnityEngine::AudioSource*, audioSource);

    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, OnDestroy);

    DECLARE_INSTANCE_METHOD(void, CreateScreen);
    DECLARE_INSTANCE_METHOD(void, SetupVideoPlayer);
    DECLARE_INSTANCE_METHOD(void, LoadVideo, StringW path);
    DECLARE_INSTANCE_METHOD(void, Play);
    DECLARE_INSTANCE_METHOD(void, Pause);
    DECLARE_INSTANCE_METHOD(void, Stop);
    DECLARE_INSTANCE_METHOD(void, ApplyConfig);

    DECLARE_INSTANCE_METHOD(void, SetPosition,  float x, float y, float z);
    DECLARE_INSTANCE_METHOD(void, SetRotation,  float x, float y, float z);
    DECLARE_INSTANCE_METHOD(void, SetScale,     float x, float y);
    DECLARE_INSTANCE_METHOD(void, SetVolume,    float v);
    DECLARE_INSTANCE_METHOD(void, SetLoop,      bool loop);

    DECLARE_STATIC_FIELD(VideoPlayerController*, _instance);
    DECLARE_STATIC_METHOD(VideoPlayerController*, GetInstance);
)
