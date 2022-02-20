#include <Windows.h>
#include "GameStart.h"
#include "Global.h"
#include "Field.h"
#include "ButtonManager.h"
void GameStart::Start()
{
	{
		background.Name = "Image/gameMenu";
		background.Length = Vector<2>(camWidth, camHeight) * 2;
		this->camera.Sight = Vector<2>(camWidth, camHeight) * 2;
	}
	{
		startText.Font.Name = "Font/arial";
		startText.Font.Size = 40;
		startText.Length = Vector<2>(200, 80) * 2;
		startText.Location = Vector<2>(camWidth + 90, camHeight - 100);
		startText.Text = "Game Start";
	}
	start = new Button("Image/startIdle", 200, 50, camWidth, camHeight);
	end = new Button("Image/quitIdle", 200, 50, camWidth, camHeight + 100);
	buttonmanager = new ButtonManager();
}

Scene* GameStart::Update()
{
	this->camera.Set();
	background.Render();
	start->onHover("Image/startIdle", "Image/startHover");
	end->onHover("Image/quitIdle", "Image/quitHover");
	start->render();
	end->render();
	startText.Render();
	if (buttonmanager->onClick(start))
	{
		return new Field;
	}
	if (buttonmanager->onClick(end))
	{
		PostQuitMessage(0);
	}
	
	return nullptr;
}

void GameStart::End()
{
	delete start;
	delete end;
	delete buttonmanager;
}
