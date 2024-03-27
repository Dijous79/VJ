#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 23
#define INIT_PLAYER_Y_TILES 21

#define INVULNERABILITY 120


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

void Scene::initBase() {
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, this);
	cadaver = new Cadaver();
	ui = new Interface();
	currentTime = -(1000.0f * 40.0f) / 60.0;
	wrsAllowed = 1;
	points = 0;
	multiplier = 1;
	startCd = 0;
	lives = 3;
	timerInvulnerabilty = timerTxtInvulnerabilty = 0;
	god = false;
	playerVisible = true;
	viu = true;
	spritesheet.loadFromFile("images/backgrounds.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backGround = Sprite::createSprite(glm::ivec2(8 * 48, 8 * 26), glm::vec2(1.0 / 3.0, 1.0), &spritesheet, &texProgram);
	backGround->setNumberAnimations(1);
	backGround->setAnimationSpeed(0, 1);
	backGround->setPosition(glm::ivec2(SCREEN_X, SCREEN_X));
}

void Scene::init1()
{
	initShaders();
	initBase();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	map->setGbS(&gsBcks);
	ui->init(texProgram, 0);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	

	bubble1 = new Bubble();
	bubble1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 0, 10 * map->getTileSize(), true);
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

	backGround->addKeyframe(0, glm::vec2(0.0, 0.0));
	backGround->changeAnimation(0);
	whatScene = 1;
}

void Scene::init2()
{
	initShaders();
	initBase();
	map = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	ui->init(texProgram, 1);
	GlassBlock* gb1 = new GlassBlock();
	gb1->init(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(8 * 16, 8 * 8), glm::ivec2(32, 8), 1, texProgram);
	gsBcks.insert(gb1);
	GlassBlock* gb2 = new GlassBlock();
	gb2->init(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(8 * 20, 8 * 8), glm::ivec2(32, 8), 1, texProgram);
	gsBcks.insert(gb2);
	GlassBlock* gb3 = new GlassBlock();
	gb3->init(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(8 * 24, 8 * 8), glm::ivec2(32, 8), 1, texProgram);
	gsBcks.insert(gb3);
	GlassBlock* gb4 = new GlassBlock();
	gb4->init(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(8 * 28, 8 * 8), glm::ivec2(32, 8), 1, texProgram);
	gsBcks.insert(gb4);
	map->setGbS(&gsBcks);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	backGround->addKeyframe(0, glm::vec2(2.0 / 3.0, 0.0));
	backGround->changeAnimation(0);
	whatScene = 2;
}

void Scene::init3()
{
	initShaders();
	initBase();
	map = TileMap::createTileMap("levels/level03.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	ui->init(texProgram, 2);
	GlassBlock* gb1 = new GlassBlock();
	gb1->init(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(8 * 11, 8 * 17), glm::ivec2(24, 8), 0, texProgram);
	gsBcks.insert(gb1);
	GlassBlock* gb2 = new GlassBlock();
	gb2->init(glm::ivec2(SCREEN_X, SCREEN_Y), glm::ivec2(8 * 28, 8 * 17), glm::ivec2(24, 8), 0, texProgram);
	gsBcks.insert(gb2);
	map->setGbS(&gsBcks);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	backGround->addKeyframe(0, glm::vec2(1.0 / 3.0, 0.0));
	backGround->changeAnimation(0);
	whatScene = 3;
}

void Scene::flush() {
	delete player;
	gsBcks.clear();
	wrs.clear();
	drops.clear();
	dynObjDestr.clear();
	bubbles.clear();
	delete backGround;
	delete ui;
}

void Scene::update(int deltaTime)
{
	if (startCd <= 45) {
		if (startCd == 25)
			ui->toggleReadyLabel();
		if (startCd == 30)
			ui->toggleReadyLabel();
		if (startCd == 35)
			ui->toggleReadyLabel();
		if (startCd == 40)
			ui->toggleReadyLabel();
		if (startCd == 45)
			ui->toggleReadyLabel();
		if (startCd == 50)
			ui->toggleReadyLabel();
		if (startCd == 55)
			ui->toggleReadyLabel();
		startCd++;
	}
	else {
		currentTime += deltaTime;
		if (currentTime > 100000) {
			ui->timeAct(0);
			moriste();
		}
		else {
			ui->timeAct(100 - (currentTime) / 1000);
			if(viu)player->update(deltaTime);
			else cadaver->update(deltaTime);
			for (std::set<GlassBlock*>::iterator it = gsBcks.begin(); it != gsBcks.end(); ++it) {
				(*it)->update(deltaTime);
			}
			for (std::set<DynamicObj*>::iterator it = dynObjDestr.begin(); it != dynObjDestr.end(); ++it) {
				(*it)->update(deltaTime);
			}
			for (std::set<Wire*>::iterator it = wrs.begin(); it != wrs.end(); ++it) {
				(*it)->update(deltaTime);
			}
			for (std::set<Drops*>::iterator it = drops.begin(); it != drops.end(); ++it) {
				(*it)->update(deltaTime);
			}
			for (std::set<Bubble*>::iterator it = bubbles.begin(); it != bubbles.end(); ++it) {
				(*it)->update(deltaTime);
			}
			wireCollisions();
			dropCollisions();
			if (timerInvulnerabilty == 0 && !god) {
				playerBubbleCollisions();
			}
			else {
				if (!god) {
					timerInvulnerabilty--;
					if (timerInvulnerabilty == 0) {
						playerVisible = true;
					}
				}
				if (timerTxtInvulnerabilty == 0) {
					playerVisible=!playerVisible;
					timerTxtInvulnerabilty = 10;
				}
				else {
					timerTxtInvulnerabilty--;
				}
			}
		}
		if (currentTime > 104000) {
			flush();
			switch (whatScene)
			{
			case 1:
				init1();
				break;
			case 2:
				init2();
				break;
			case 3:
				init3();
				break;
			default:
				break;
			}
		}
	}
}

void Scene::render()
{
	glm::mat4 modelview;
	backGround->render();
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
	for (std::set<DynamicObj*>::iterator it = dynObjDestr.begin(); it != dynObjDestr.end(); ++it) {
		(*it)->render();
	}
	for (std::set<Wire*>::iterator it = wrs.begin(); it != wrs.end(); ++it) {
		(*it)->render();
	}
	for (std::set<Drops*>::iterator it = drops.begin(); it != drops.end(); ++it) {
		(*it)->render();
	}
	for (std::set<Bubble*>::iterator it = bubbles.begin(); it != bubbles.end(); ++it) {
		(*it)->render();
	}
	if (playerVisible && viu) player->render();
	else if(!viu) cadaver-> render();
	ui->render();
	
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
		char contact = map->wahtTile((*it)->topHitBox());
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
				it2 = gsBcks.end();
				--it2;
			}
		}
		if (gb != NULL) {
			glm::ivec2 centreBlock = gb->getCenter();
			instanceDrop(centreBlock);
			dynObjDestr.insert(gb);
			gsBcks.erase(gb);
		}
		std::set<Bubble*>::iterator it2 = bubbles.begin();
		while (it2 != bubbles.end()) {
			if ((*it2)->impacte(pWr,4)) {
				glm::ivec2 pos = (*it2)->getPos();
				int type = (*it2)->getType();
				if (type % 4 != 0) {
					for (int b = 0; b < 2; b++) {
						Bubble* bubble = new Bubble();
						bubble->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, type - 1, pos.y, b);
						bubble->setPosition(glm::vec2(pos.x + b * 10, pos.y + 10));
						bubble->setTileMap(map);
						bubbles.insert(bubble);
					}
				}
				glm::ivec2 centreBlock = (*it2)->getCenter();
				instanceDrop(centreBlock);
				bubbles.erase(it2);
				wr = *it;
				it2 = bubbles.end();
			}
			else
			{
				++it2;
			}
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

void Scene::setMaxWires(int nnw) {
	wrsAllowed = nnw;
}

void Scene::dropCollisions() {
	Drops* d = NULL;
	for (std::set<Drops*>::iterator it = drops.begin(); it != drops.end(); ++it) {
		glm::ivec2 Dp = (*it)->posObj();
		glm::ivec2 Ds = (*it)->sizeObj();
		glm::ivec2 Pp = player->getPos();
		glm::ivec2 Ps = player->getSize();

		if (Dp.y > Pp.y + Ps.y / 4 && Dp.y < Pp.y + 3*Ps.y / 4 || Dp.y + Ds.y > Pp.y + Ps.y / 4 && Dp.y + Ds.y < Pp.y + 3 * Ps.y / 4) {
			if (Dp.x > Pp.x + Ps.x / 4 && Dp.x < Pp.x + 3 * Ps.x / 4 || Dp.x + Ds.x > Pp.x + Ps.x / 4 && Dp.x + Ds.x < Pp.x + 3 * Ps.x / 4) {
				(*it)->destroy();
				d = (*it);
				it = drops.end();
				--it;
			}
		}
	}
	if (d != NULL)
		drops.erase(d);
}

void Scene::instanceDrop(glm::ivec2 centerSpawn) {
	centerSpawn -= glm::ivec2(8, 8);
	srand(time(NULL));
	if (rand() % 2) {
		Food* aux = new Food();
		aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), centerSpawn, texProgram, rand() % 25);
		aux->setTileMap(map);
		aux->setScene(this);
		drops.insert(aux);
	}
	else {
		PowerUp* aux = new PowerUp();
		aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), centerSpawn, texProgram, rand() % 3);
		aux->setTileMap(map);
		aux->setScene(this);
		drops.insert(aux);
	}
}

void Scene::addPoints(int pts) { 
	points += pts * multiplier; 
	ui->setScore(points);
}

void Scene::playerBubbleCollisions() {
	glm::ivec2 pP = player->getPos();
	std::set<Bubble*>::iterator it2 = bubbles.begin();

	while (it2 != bubbles.end()) {
		if ((*it2)->impacte(pP, 16)) {
			if (lives != 0) {
				lives--;
				timerInvulnerabilty = INVULNERABILITY;
				viu = false;
				cadaver->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, false);
				cadaver->setPosition(player->getPos());
				cadaver->setTileMap(map);
			}
			else
				moriste();

			it2 = bubbles.end();
		}
		else
		{
			++it2;
		}
	}
}


void Scene::moriste() {
	ui->gameOverText();
}

void Scene::godCheat() {
	god = !god;
	timerTxtInvulnerabilty = timerInvulnerabilty= 0;
	playerVisible=true;
}