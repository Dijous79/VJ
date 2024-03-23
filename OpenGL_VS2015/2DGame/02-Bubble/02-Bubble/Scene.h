#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "GlassBlock.h"
#include "Wire.h"
#include "Drops.h"
#include "Bubble.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	bool space4Wire();
	void instanceWire(glm::ivec2 pos, int off);

private:
	void initShaders();
	void wireCollisions();

private:
	TileMap *map;
	Player *player;
	Bubble* bubble1, * bubble2, * bubble3, * bubble4;
	std::set<GlassBlock*> gsBcks;
	std::set<Wire*> wrs;
	std::set<Drops*> drops;
	std::set<Bubble*> bubbles;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int wrsAllowed;
	int cd2DestroyGlass;
	std::set<DynamicObj*> DynObjDestr;
	bool destroyingGlass;

};


#endif // _SCENE_INCLUDE

