#include "ScoreManager.h"
#include <fstream>
#include <algorithm>
#include <string>
#include <iostream>
std::vector<int> ScoreManager::getScore(int score)
{
	std::ifstream file("score.txt");
	std::string s;
	int i;
	std::vector<int> vec;
	
	if (!file.is_open())
	{
		setScore(score);
		return vec;
	}

	while (std::getline(file, s))
	{
		if (std::isdigit(s[0]))
		{
			i = std::stoi(s);
			scores.push_back(i);
		}
	}
	if (scores.size() == 0)
	{
		setScore(score);
		return vec;
	}
	sort(scores.begin(), scores.end(), std::greater<int>());
	if (scores.size() > 10)
	{
		vec.assign(scores.begin(), scores.begin() + 10);
	}
	else
	{
		vec.assign(scores.begin(), scores.end());
	}
	if (score > vec[0])
	{
		setScore(score);
	}
	file.close();
	return vec;
}

void ScoreManager::setScore(int score)
{
	std::ofstream file("score.txt",std::ios::app);
	std::string s=std::to_string(score);
	std::vector<int> vec;
	if (file.is_open())
	{
		file << s<<std::endl;
		file.close();
	}
}
