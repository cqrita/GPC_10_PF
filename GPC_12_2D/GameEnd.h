#pragma once
#pragma once
#include "Scene.h"
#include "Button.h"
#include "ButtonManager.h"
#include "Engine/Sound.h"

class GameEnd final : public Scene
{
public:
    void     Start() final override;
    Scene* Update() final override;
    void       End() final override;
    GameEnd()=default;
    GameEnd(int score);
    Button* start=nullptr;
    Button* end = nullptr;
    int score;
    ButtonManager* buttonmanager = nullptr;
    Engine::Rendering::Camera camera;
    Engine::Rendering::Image::Component background;
    Engine::Rendering::Text::Component scoreText;
    Engine::Rendering::Text::Component endText;
    Engine::Sound::Effect::Component menu;

};