#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.

class Scene;

class Player
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Scene* scene);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	bool bClimbing;
	bool inAnim;
	int Bfr;
	bool lastDir;
	bool iOc;
	bool jump;
	glm::ivec2 tileMapDispl, posPlayer, size;
	int startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	Scene* scn;

};


#endif // _PLAYER_INCLUDE


