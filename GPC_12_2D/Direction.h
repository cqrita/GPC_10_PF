#pragma once
#include <map>
#include "Engine/Vector.h"
enum class Dir : int
{
	N,
	NE,
	E,
	SE,
	S,
	SW,
	W,
	NW,
	I
};

std::map<Dir, Vector<2>> dMap1
{
	{Dir::N,Normalize(Vector<2>(0,1))},
	{Dir::NE,Normalize(Vector<2>(1,1))},
	{Dir::E,Normalize(Vector<2>(1,0))},
	{Dir::SE,Normalize(Vector<2>(1,-1))},
	{Dir::S,Normalize(Vector<2>(0,-1))},
	{Dir::SW,Normalize(Vector<2>(-1,-1))},
	{Dir::W,Normalize(Vector<2>(-1,0))},
	{Dir::NW,Normalize(Vector<2>(-1,1))},
	{Dir::I,Normalize(Vector<2>(0,0))}
};

std::map<Vector<2>,Dir> dMap2
{
	{{0,1},Dir::N},
	{{1,1},Dir::NE},
	{{1,0},Dir::E},
	{{1,-1},Dir::SE},
	{{0,-1},Dir::S},
	{{-1,-1},Dir::SW},
	{{-1,0},Dir::W},
	{{-1,1},Dir::NW},
	{{0,0},Dir::I},
};

Dir checkDir(Vector<2> v)
{
	if (v[0] > 0)
	{
		if (v[1] > 0)
		{

		}
		else if (v[1] < 0)
		{

		}
		else
		{

		}
	}
	else if (v[0] < 0)
	{
		if (v[1] > 0)
		{

		}
		else if (v[1] < 0)
		{

		}
		else
		{

		}
	}
	else
	{
		if (v[1] > 0)
		{

		}
		else if (v[1] < 0)
		{

		}
		else
		{

		}
	}
}