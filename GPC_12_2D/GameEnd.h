#pragma once
#pragma once
#include "Scene.h"
#include "Button.h"
#include "ButtonManager.h"
#include "Engine/Sound.h"
#include "ScoreManager.h"
#include <vector>
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
    std::vector<int> scores;
    ButtonManager* buttonmanager = nullptr;
    ScoreManager* scoreManager = nullptr;
    Engine::Rendering::Camera camera;
    Engine::Rendering::Image::Component background;
    Engine::Rendering::Text::Component scoreText;
    Engine::Rendering::Text::Component arrayText;
    Engine::Rendering::Text::Component endText;
    Engine::Sound::Effect::Component menu;

};