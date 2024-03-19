#ifndef _DYNAMICOBJ_INCLUDE
#define _DYNAMICOBJ_INCLUDE

#include "Sprite.h"
#include "TileMap.h"


class DynamicObj
{
public:
	virtual void init(const glm::ivec2& tileMapPos, glm::ivec2 posiO, ShaderProgram& shaderProgram);
	virtual void init(const glm::ivec2& tileMapPos, glm::ivec2 posiO, glm::ivec2 sizeObj, int col, ShaderProgram& shaderProgram);
	virtual void update(int deltaTime);
	void render();
	virtual void destroy();

	void setTileMap(TileMap* tileMap);
	glm::ivec2 posObj();
	glm::ivec2 sizeObj();

	glm::ivec2 tileMapDispl, posi, size;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;


protected:
	DynamicObj();
};

#endif

