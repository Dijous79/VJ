#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 23
#define INIT_PLAYER_Y_TILES 21


Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, this);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	GlassBlock* gb1 = new GlassBlock();
	gb1->init(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(8 * 11, 8 * 17), glm::ivec2(24, 8), 0, texProgram);
	gsBcks.insert(gb1);
	GlassBlock* gb2= new GlassBlock();
	gb2->init(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(8 * 28, 8 * 17), glm::ivec2(24, 8), 0, texProgram);
	gsBcks.insert(gb2);
	map->setGbS(&gsBcks);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	currentTime = 0.0f;
	wrsAllowed = 1;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);

	for (std::set<GlassBlock*>::iterator it = gsBcks.begin(); it != gsBcks.end(); ++it) {
		(*it)->update(deltaTime);
	}
	for (std::set<DynamicObj*>::iterator it = DynObjDestr.begin(); it != DynObjDestr.end(); ++it) {
		(*it)->update(deltaTime);
	}
	for (std::set<Wire*>::iterator it = wrs.begin(); it != wrs.end(); ++it) {
		(*it)->update(deltaTime);
	}
	wireCollisions();
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	for (std::set<GlassBlock*>::iterator it = gsBcks.begin(); it != gsBcks.end(); ++it) {
		(*it)->render();
	}
	for (std::set<DynamicObj*>::iterator it = DynObjDestr.begin(); it != DynObjDestr.end(); ++it) {
		(*it)->render();
	}
	for (std::set<Wire*>::iterator it = wrs.begin(); it != wrs.end(); ++it) {
		(*it)->render();
	}
	player->render();
	
	
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void Scene::wireCollisions() {
	Wire* wr = NULL;
	for (std::set<Wire*>::iterator it = wrs.begin(); it != wrs.end(); ++it) {
		printf("cable\n");
		char contact = map->wahtTile((*it)->topHitBox());
		printf("%c\n", contact);
		if (contact != '\0' && contact != 'v' && contact != 'b' && contact != 'n' && contact != 'V' && contact != 'B' && contact != 'N') {
			wr = *it;
		}
		GlassBlock* gb = NULL;
		for (std::set<GlassBlock*>::iterator it2 = gsBcks.begin(); it2 != gsBcks.end(); ++it2) {
			glm::ivec2 pGB = (*it2)->posObj();
			glm::ivec2 sGB = (*it2)->sizeObj();
			glm::ivec2 pWr = (*it)->posObj();
			if (pGB.y <= pWr.y && pGB.y + sGB.y >= pWr.y && pGB.x <= pWr.x + 4 && pGB.x + sGB.x >= pWr.x + 4) {
				(*it2)->destroy();
				gb = (*it2);
				wr = *it;
			}
		}
		if (gb != NULL) {
			DynObjDestr.insert(gb);
			gsBcks.erase(gb);
		}
	}
	if (wr != NULL) {
		wrs.erase(wr);
	}
}

bool Scene::space4Wire() {
	return wrs.size() < wrsAllowed;
}

void Scene::instanceWire(glm::ivec2 pos, int off) {
	Wire* wr = new Wire();
	glm::ivec2 posA = pos;
	posA.x += off;
	posA.y -= 4;
	wr->init(glm::ivec2(SCREEN_X, SCREEN_Y), posA, texProgram);
	wrs.insert(wr);
}
