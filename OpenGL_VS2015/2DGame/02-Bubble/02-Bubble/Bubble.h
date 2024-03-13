#ifndef _BUBBLE_INCLUDE
#define _BUBBLE_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class Bubble
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	bool jumping;
	bool fwd;
	double Caiguda_en_y;
	glm::ivec2 tileMapDispl, posBubble;
	int jump_x,colission_cooldown;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif
