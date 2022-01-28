#pragma once
#include <map>
#include <array>
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

static std::map<Dir, Vector<2>> dMap1
{
	{Dir::N,Vector<2>(0,1)},
	{Dir::NE,Vector<2>(1,1)},
	{Dir::E,Vector<2>(1,0)},
	{Dir::SE,Vector<2>(1,-1)},
	{Dir::S,Vector<2>(0,-1)},
	{Dir::SW,Vector<2>(-1,-1)},
	{Dir::W,Vector<2>(-1,0)},
	{Dir::NW,Vector<2>(-1,1)},
	{Dir::I,Vector<2>(0,0)}
};

static std::map<std::array<float,2>, Dir> dMap2
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

static std::map<Dir, float> dMap3
{
	{Dir::N,90.0f},
	{Dir::NE,45.0f},
	{Dir::E,0.0f},
	{Dir::SE,315.0f},
	{Dir::S,270.0f},
	{Dir::SW,225.0f},
	{Dir::W,180.0f},
	{Dir::NW,135.0f},
	{Dir::I,0.0f}
};



