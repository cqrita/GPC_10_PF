#pragma once
#include "Engine/Rendering.h"
#include "Engine/Physics.h"
#include "Engine/Circle.h"
#include "Player.h"
#include "Scene.h"
#include "EntityManager.h"
#include "User.h"

class Field final : public Scene
{
public:
    void     Start() final override;
    Scene* Update() final override;
    void       End() final override;

private:
   


    Engine::Rendering::Image::Component background;
    User* user = nullptr;
    EntityManager* entityManager = nullptr;
    Player* player = nullptr;
    Engine::Rendering::Camera camera;
};