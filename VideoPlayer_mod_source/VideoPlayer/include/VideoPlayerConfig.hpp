#pragma once
#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(VideoPlayerConfig,
    CONFIG_VALUE(VideoPath,   std::string, "videoPath",    "/sdcard/ModData/com.beatgames.beatsaber/Mods/VideoPlayer/video.mp4");
    CONFIG_VALUE(PosX,        float,       "posX",         0.0f);
    CONFIG_VALUE(PosY,        float,       "posY",         2.5f);
    CONFIG_VALUE(PosZ,        float,       "posZ",         4.0f);
    CONFIG_VALUE(RotX,        float,       "rotX",         0.0f);
    CONFIG_VALUE(RotY,        float,       "rotY",         0.0f);
    CONFIG_VALUE(RotZ,        float,       "rotZ",         0.0f);
    CONFIG_VALUE(ScaleX,      float,       "scaleX",       4.0f);
    CONFIG_VALUE(ScaleY,      float,       "scaleY",       2.25f);
    CONFIG_VALUE(Loop,        bool,        "loop",         true);
    CONFIG_VALUE(AutoPlay,    bool,        "autoPlay",     true);
    CONFIG_VALUE(Volume,      float,       "volume",       0.5f);
    CONFIG_VALUE(Curvature,   float,       "screenCurvature", 0.0f);
)
