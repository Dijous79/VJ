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
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	gb1 = new GlassBlock();
	gb1->init(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(24 * 11, 24 * 17), glm::ivec2(72, 24), 0, texProgram);
	gb1->setTileMap(map);
	map->addDObj(gb1);
	gb2 = new GlassBlock();
	gb2->init(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(24 * 28, 24 * 17), glm::ivec2(72, 24), 0, texProgram);
	gb2->setTileMap(map);
	map->addDObj(gb2);
	Wire* wr = new Wire();
	wr->init(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(24 * 20, 24 * 21), texProgram);
	wrs.insert(wr);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	currentTime = 0.0f;
	aux = false;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	for (std::set<Wire*>::iterator it = wrs.begin(); it != wrs.end(); ++it) {
		(*it)->update(deltaTime);
	}
	wireCollisions();
	gb1->update(deltaTime);
	if (Game::instance().getKey(GLFW_KEY_SPACE) && aux == false) {
		map->rmDObj(gb1);
		gb1->destroy();
		aux = true;
	}
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
	player->render();
	gb1->render();
	gb2->render();
	for (std::set<Wire*>::iterator it = wrs.begin(); it != wrs.end(); ++it) {
		(*it)->render();
	}
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
	for (std::set<Wire*>::iterator it = wrs.begin(); it != wrs.end(); ++it) {
		if (map->wahtTile((*it)->topHitBox()) != '\0') {
			(*it)->destroy();
		}
	}
}

