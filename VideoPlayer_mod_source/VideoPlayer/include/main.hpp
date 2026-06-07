#pragma once
#include "VideoPlayerConfig.hpp"
#include "modloader/shared/modinfo.hpp"
#include "paper/shared/logger.hpp"

#define MOD_ID   "VideoPlayer"
#define MOD_VER  "1.0.0"

// Logger helper
static constexpr auto Logger = Paper::ConstLoggerContext(MOD_ID);

// Config accessor
VideoPlayerConfig& getVideoPlayerConfig();
