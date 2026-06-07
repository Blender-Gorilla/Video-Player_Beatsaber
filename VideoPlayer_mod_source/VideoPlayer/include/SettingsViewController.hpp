#pragma once

#include "custom-types/shared/macros.hpp"
#include "bsml/shared/BSML/ViewControllers/HotReloadViewController.hpp"
#include "bsml/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(VideoPlayer, SettingsViewController, BSML::ViewController,
    DECLARE_BSML_PROPERTY(float, posX);
    DECLARE_BSML_PROPERTY(float, posY);
    DECLARE_BSML_PROPERTY(float, posZ);
    DECLARE_BSML_PROPERTY(float, rotX);
    DECLARE_BSML_PROPERTY(float, rotY);
    DECLARE_BSML_PROPERTY(float, rotZ);
    DECLARE_BSML_PROPERTY(float, scaleX);
    DECLARE_BSML_PROPERTY(float, scaleY);
    DECLARE_BSML_PROPERTY(float, volume);
    DECLARE_BSML_PROPERTY(bool,  loop);
    DECLARE_BSML_PROPERTY(bool,  autoPlay);
    DECLARE_BSML_PROPERTY(float, curvature);

    DECLARE_BSML_PROPERTY(StringW, videoPath);

    DECLARE_INSTANCE_METHOD(void, DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    DECLARE_INSTANCE_METHOD(void, OnApplyClicked);
    DECLARE_INSTANCE_METHOD(void, OnPlayClicked);
    DECLARE_INSTANCE_METHOD(void, OnPauseClicked);
    DECLARE_INSTANCE_METHOD(void, OnStopClicked);
    DECLARE_INSTANCE_METHOD(void, OnReloadClicked);
)
