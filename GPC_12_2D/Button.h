#pragma once
#include "Engine/Rendering.h"
class Button
{
public:
	Button(const char* string, float width, float height, float x, float y);
	void render();
	Engine::Rendering::Image::Test image;
	void onHover(const char* idle, const char* hover);
};