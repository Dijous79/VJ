#pragma once
#include "DynamicObj.h"
class Drops : public DynamicObj
{
public:
	void setTileMap(TileMap* tileMap);

private:
	TileMap* map;
};

