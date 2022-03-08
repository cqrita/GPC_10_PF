#pragma once
#include <vector>
class ScoreManager
{
public:
	std::vector<int> getScore(int score);
	void setScore(int score);
public:
	std::vector<int> scores;

};