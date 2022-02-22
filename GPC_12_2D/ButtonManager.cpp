#include <Windows.h>
#include "ButtonManager.h"
#include "Engine/Physics.h"
#include "Engine/Input.h"
#include "Engine/Quadrangle.h"
#include "Engine/Point.h"

bool ButtonManager::onClick(Button* button)
{
	Engine::Physics::Component<Quadrangle> quad;
	quad.Center.x = button->image.Location[0];
	quad.Center.y = button->image.Location[1];
	quad.Length.x = button->image.Length[0];
	quad.Length.y = button->image.Length[1];
	Engine::Physics::Component<Point> point;
	point.x = static_cast<float>(Engine::Input::Get::Cursor::X());
	point.y = static_cast<float>(Engine::Input::Get::Cursor::Y());
	if (quad.Collide(point)&&Engine::Input::Get::Key::Down(VK_LBUTTON))
	{
		return true;
	}
	else
	{
		return false;
	}
}


