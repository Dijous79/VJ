#ifndef _CADAVER_INCLUDE
#define _CADAVER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include <vector>

class Cadaver
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, bool dir);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);


private:
	bool fwd,first_jump;
	glm::ivec2 tileMapDispl, posCadaver;
	int jump_x, Yini;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif // _CADAVER_INCLUDE


