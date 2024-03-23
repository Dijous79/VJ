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
	map = TileMap::createTileMap("levels/level00.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, this);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);

	bubble1 = new Bubble();
	bubble1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 0, 10 * map->getTileSize(),true);
	bubble1->setPosition(glm::vec2(10 * map->getTileSize(), 10 * map->getTileSize()));
	bubble1->setTileMap(map);
	bubbles.insert(bubble1);

	bubble2 = new Bubble();
	bubble2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1, 10 * map->getTileSize(), true);
	bubble2->setPosition(glm::vec2(10 * map->getTileSize(), 10 * map->getTileSize()));
	bubble2->setTileMap(map);
	bubbles.insert(bubble2);

	bubble3 = new Bubble();
	bubble3->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 2, 10 * map->getTileSize(), true);
	bubble3->setPosition(glm::vec2(10 * map->getTileSize(), 10 * map->getTileSize()));
	bubble3->setTileMap(map);
	bubbles.insert(bubble3);

	bubble4 = new Bubble();
	bubble4->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 3, 10 * map->getTileSize(), true);
	bubble4->setPosition(glm::vec2(10 * map->getTileSize(), 10 * map->getTileSize()));
	bubble4->setTileMap(map);
	bubbles.insert(bubble4);

	/*GlassBlock* gb1 = new GlassBlock();
	gb1->init(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(8 * 11, 8 * 17), glm::ivec2(24, 8), 0, texProgram);
	gsBcks.insert(gb1);*/
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
	for (std::set<Bubble*>::iterator it = bubbles.begin(); it != bubbles.end(); ++it) {
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
	for (std::set<Bubble*>::iterator it = bubbles.begin(); it != bubbles.end(); ++it) {
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
		glm::ivec2 pWr = (*it)->posObj();
		GlassBlock* gb = NULL;
		for (std::set<GlassBlock*>::iterator it2 = gsBcks.begin(); it2 != gsBcks.end(); ++it2) {
			glm::ivec2 pGB = (*it2)->posObj();
			glm::ivec2 sGB = (*it2)->sizeObj();
			if (pGB.y <= pWr.y && pGB.y + sGB.y >= pWr.y && pGB.x <= pWr.x + 4 && pGB.x + sGB.x >= pWr.x + 4) {
				(*it2)->destroy();
				gb = (*it2);
				wr = *it;
			}
		}

		std::set<Bubble*>::iterator it2 = bubbles.begin();
		while(it2 != bubbles.end()) {
			if ((*it2)->impacte(pWr)) {
				glm::ivec2 pos = (*it2)->getPos();
				int type = (*it2)->getType();
				if (type % 4 != 0) {
					for (int b = 0; b < 2; b++) {
						Bubble* bubble = new Bubble();
						bubble->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, type - 1, pos.y, b);
						bubble->setPosition(glm::vec2(pos.x + b * 10, pos.y + b * 10));
						bubble->setTileMap(map);
						bubbles.insert(bubble);
					}
				}
				std::set<Bubble*>::iterator it3 = it2;
				it2++;
				bubbles.erase(*it3);
				wr = *it;
			}
			else
			{
				++it2;
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
