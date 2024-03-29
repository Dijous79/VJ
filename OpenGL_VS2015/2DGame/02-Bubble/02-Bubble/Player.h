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
	Player();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Scene* scene);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	void toggleShield();

	glm::ivec2 getPos();
	glm::ivec2 getSize();

private:
	bool bClimbing;
	bool inAnim;
	bool shield, counting;
	int Bfr;
	bool lastDir;
	bool iOc;
	bool jump, pulsada;
	int cdShoot;
	int cdShieldEnd;
	glm::ivec2 tileMapDispl, posPlayer, size;
	int startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	Scene* scn;
	Sprite* sh;
	Texture shImage;

};


#endif // _PLAYER_INCLUDE


