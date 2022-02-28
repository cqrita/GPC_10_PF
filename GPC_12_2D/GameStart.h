#pragma once
#include "Scene.h"
#include "Button.h"
#include "ButtonManager.h"
#include "Engine/Rendering.h"
#include "Engine/Sound.h"

class GameStart final : public Scene
{
public:
    void     Start() final override;
    Scene* Update() final override;
    void       End() final override;
    Button* start;
    Button* end;
    ButtonManager* buttonmanager;
    Engine::Rendering::Camera camera;
    Engine::Rendering::Image::Component background;
    Engine::Rendering::Text::Component startText;
    Engine::Sound::Effect::Component menu;

};