#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "GlassBlock.h"
#include "Wire.h"
#include "Drops.h"
#include "PowerUp.h"
#include "Food.h"
#include "Interface.h"
#include "Bubble.h"
#include "Cadaver.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.

class Game;

class Scene
{

public:
	Scene(Game* gm);
	~Scene();

	void init1();
	void init2();
	void init3();
	void update(int deltaTime);
	void render();
	bool space4Wire();
	void instanceWire(glm::ivec2 pos, int off);
	void setMaxWires(int nnw);
	void addPoints(int pts);
	void flush();
	void godCheat();
	void stopTime();

private:
	void initBase();
	void initShaders();
	void wireCollisions();
	void dropCollisions();
	void playerBubbleCollisions();
	void instanceDrop(glm::ivec2 centerSpawn);
	void moriste();
	void retry();

private:
	int lives;
	TileMap *map;
	Player *player;
	Cadaver* cadaver;
	std::set<GlassBlock*> gsBcks;
	std::set<Wire*> wrs;
	std::set<Drops*> drops;
	std::set<Bubble*> bubbles;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int wrsAllowed;
	int cd2DestroyGlass;
	std::set<DynamicObj*> dynObjDestr;
	bool destroyingGlass;
	int points;
	int multiplier;
	Sprite* backGround;
	Texture spritesheet;
	Interface* ui;
	int whatScene;
	int startCd;
	Bubble* bubble1;
	Bubble* bubble2;
	Bubble* bubble3;
	Bubble* bubble4;
	int timerInvulnerabilty, timerTxtInvulnerabilty,timerRetry, cdStopBubs, moment, counterInsertCoinMainMenu;
	bool god,playerVisible, viu, bubbleStoped;
	Sprite* mainMenuWallaper;
	Sprite* insertCoinMenuLabel;
	Texture mainMenuWallaperImage, insertCoinImage;
	Game* gm;

};


#endif // _SCENE_INCLUDE

