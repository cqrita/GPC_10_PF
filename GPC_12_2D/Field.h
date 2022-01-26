#pragma once
#include "Engine/Rendering.h"
#include "Engine/Physics.h"
#include "Engine/Circle.h"
#include "Player.h"
#include "Scene.h"
#include "EntityManager.h"

class Field final : public Scene
{
public:
    void     Start() final override;
    Scene* Update() final override;
    void       End() final override;

private:
    Engine::Rendering::Image::Component background;

    EntityManager* entityManager = nullptr;
    Player* player = nullptr;
};