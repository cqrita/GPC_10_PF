#pragma once
#include <vector>
#include "Engine/Rendering.h"
#include "Engine/Physics.h"
#include "Engine/Circle.h"
#include "Player.h"
#include "Scene.h"
#include "EntityManager.h"
#include "User.h"
#include "Enemy.h"
class Field final : public Scene
{
public:
    void     Start() final override;
    Scene* Update() final override;
    void       End() final override;

private:
   

    std::vector<Enemy*> enemies;
    Engine::Rendering::Image::Component background;
    Engine::Rendering::Text::Component UI;
    int enemyCount;
    User* user = nullptr;
    EntityManager* entityManager = nullptr;
    Player* player = nullptr;
    Engine::Rendering::Camera camera;
};