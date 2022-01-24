#pragma once

namespace Engine::Physics
{
    template<typename Shape>
    class Component final : public Shape
    {
    public:
        Component();
        Component(Shape const &);

        template<typename Shape>
        [[nodiscard]] bool Collide(Component<Shape> const &) const;
    };

    //Test.cpp
}