#pragma once
#include <vector>
#include "Engine/Rendering.h"
#include "Engine/Physics.h"
#include "Engine/Circle.h"
#include "Engine/Sound.h"
#include "Player.h"
#include "Scene.h"
#include "EntityManager.h"
#include "User.h"
#include "Enemy.h"
#include "Item.h"
class Field final : public Scene
{
public:
    void     Start() final override;
    Scene* Update() final override;
    void       End() final override;

private:
   
    std::vector<Item*> items;
    std::vector<Enemy*> enemies;
    Engine::Rendering::Image::Component background;
    Engine::Rendering::Text::Component UI;
    Engine::Rendering::Image::Component textBackground;
    Engine::Sound::Effect::Component battle;
    int enemyCount;
    User* user = nullptr;
    EntityManager* entityManager = nullptr;
    Player* player = nullptr;
    Engine::Rendering::Camera camera;
    bool music;

    int stage;
    float stageConst = 10.0f;
    float stageDuration = stageConst;

    Engine::Rendering::Text::Component stageText;
    float stageTextConst = 2.0f;
    float stageTextDuration = stageTextConst;
    bool stageTextFlag;
};