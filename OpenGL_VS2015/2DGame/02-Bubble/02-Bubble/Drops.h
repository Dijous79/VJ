#pragma once
#include "DynamicObj.h"

class Scene;

class Drops : public DynamicObj
{
public:
	void setTileMap(TileMap* tileMap);
	void setScene(Scene* sc);
	void update(int deltaTime);
	bool disapear();

protected:
	TileMap* map;
	int whatIsIt;
	Scene* scn;
	int cd;
	bool dis;
	enum DropsAnims {
		BASE, DISAPEARING
	};
};

