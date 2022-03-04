#pragma once
#include <vector>
#include "Engine/Rendering.h"
#include "Engine/Physics.h"
#include "Engine/Circle.h"
#include "Engine/Sound.h"
#include "Player.h"
#include "Scene.h"
#include "EntityManager.h"
#include "LevelManager.h"
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
    Engine::Sound::Effect::Component battle;
    int enemyCount;
    User* user = nullptr;
    EntityManager* entityManager = nullptr;
    LevelManager* levelManager = nullptr;
    Player* player = nullptr;
    Engine::Rendering::Camera camera;
    bool music;

    int stage;
    float stageConst = 15.0f;
    float stageDuration = stageConst;
};