#include "Button.h"
#include "Engine/Physics.h"
#include "Engine/Quadrangle.h"
#include "Engine/Point.h"
#include "Engine/Input.h"
Button::Button(const char* string, float width, float height, float x, float y)
{
	image.Name = string;
	image.Length[0] = width;
	image.Length[1] = height;
	image.Location[0] = x;
	image.Location[1] = y;
}

void Button::onHover(const char* idle, const char* hover)
{
	Engine::Physics::Component<Quadrangle> quad;
	quad.Center.x = image.Location[0];
	quad.Center.y = image.Location[1];
	quad.Length.x = image.Length[0];
	quad.Length.y = image.Length[1];
	Engine::Physics::Component<Point> point;
	point.x = static_cast<float>(Engine::Input::Get::Cursor::X());
	point.y = static_cast<float>(Engine::Input::Get::Cursor::Y());
	if (quad.Collide(point))
	{
		image.Name = hover;
	}
	else
	{
		image.Name = idle;
	}
}
void Button::render()
{
	image.Render();
}
