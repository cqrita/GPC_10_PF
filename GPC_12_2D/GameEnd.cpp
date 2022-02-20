#include "GameEnd.h"
#include <Windows.h>
#include "Global.h"
#include "Field.h"
#include <string>
void GameEnd::Start()
{
	{
		background.Name = "Image/gameMenu";
		background.Length = Vector<2>(camWidth, camHeight) * 2;
		this->camera.Sight = Vector<2>(camWidth, camHeight) * 2;
	}
	{
		scoreText.Font.Name = "Font/arial";
		scoreText.Font.Size = 30;
		scoreText.Length = Vector<2>(80, 80) * 2;
		scoreText.Location = Vector<2>(camWidth+20, camHeight-50);
		auto countStr = std::string("score : ").append(std::to_string(score));
		scoreText.Text = countStr.c_str();
	}
	{
		endText.Font.Name = "Font/arial";
		endText.Font.Size = 40;
		endText.Length = Vector<2>(200, 80) * 2;
		endText.Location = Vector<2>(camWidth + 90, camHeight - 100);
		endText.Text = "Game End";
	}
	start = new Button("Image/startIdle", 200, 50, camWidth, camHeight);
	end = new Button("Image/quitIdle", 200, 50, camWidth, camHeight + 100);
	buttonmanager = new ButtonManager();
}

Scene* GameEnd::Update()
{
	this->camera.Set();
	background.Render();
	start->onHover("Image/startIdle", "Image/startHover");
	end->onHover("Image/quitIdle", "Image/quitHover");
	start->render();
	end->render();	
	{
		auto countStr = std::string("score : ").append(std::to_string(score));
		scoreText.Text = countStr.c_str();
		scoreText.Render();
	}	
	endText.Render();
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

void GameEnd::End()
{
	delete start;
	delete end;
	delete buttonmanager;
}

GameEnd::GameEnd(int score)
{
	this->score = score;
}


