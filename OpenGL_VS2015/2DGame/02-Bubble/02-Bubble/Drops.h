#pragma once
#include "DynamicObj.h"

class Scene;

class Drops : public DynamicObj
{
public:
	void setTileMap(TileMap* tileMap);
	void setScene(Scene* sc);
	void update(int deltaTime);

protected:
	TileMap* map;
	int whatIsIt;
	Scene* scn;
};

