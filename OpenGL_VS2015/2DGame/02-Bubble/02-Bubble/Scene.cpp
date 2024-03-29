#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <windows.h>
#pragma comment(lib,"winmm.lib")


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 23
#define INIT_PLAYER_Y_TILES 21

#define INVULNERABILITY 120


Scene::Scene(Game* game)
{
	map = NULL;
	player = NULL;
	gm = game;
	lives = 3;
	points = 0;
	god = ret =false;
	timerPum = 0;
	mciSendString(L"open \"sounds/Continue.wav\" type mpegvideo alias Continue", NULL, 0, NULL);

}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}

void Scene::initBase() {
	mciSendString(L"stop Ending", NULL, 0, NULL);
	mciSendString(L"stop Continue", NULL, 0, NULL);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, this);
	cadaver = new Cadaver();
	ui = new Interface();
	currentTime = -(1000.0f * 40.0f) / 60.0;
	wrsAllowed = 1;
	multiplier = vector<int>{0, 0, 0, 0};
	startCd = 0;
	timerInvulnerabilty = 0;
	escut = false;
	playerVisible = true;
	viu = true;
	cdStopBubs = 0;
	bubbleStoped = false;
	spritesheet.loadFromFile("images/backgrounds.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backGround = Sprite::createSprite(glm::ivec2(8 * 48, 8 * 26), glm::vec2(1.0 / 3.0, 1.0), &spritesheet, &texProgram);
	backGround->setNumberAnimations(1);
	backGround->setAnimationSpeed(0, 1);
	backGround->setPosition(glm::ivec2(SCREEN_X, SCREEN_X));
	moment = 0;
}

void Scene::retry() {
	ret = false;
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
	case 4:
		PlaySound(NULL, NULL, 0);
		gm->putMainMenu();
		initMm();
		break;
	}
}

void Scene::init1()
{
	
	PlaySound(NULL, NULL, 0);
	PlaySound(TEXT("sounds/mtFuji.wav"), NULL, SND_FILENAME | SND_ASYNC);

	initShaders();
	initBase();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	map->setGbS(&gsBcks);
	ui->init(texProgram, 0);
	ui->setLives(lives);
	ui->setScore(points);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	

	bubble1 = new Bubble();
	bubble1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 3, 2 * map->getTileSize(), true);
	bubble1->setPosition(glm::vec2(5 * map->getTileSize(), 2 * map->getTileSize()));
	bubble1->setJumpx(0);
	bubble1->setTileMap(map);
	bubbles.insert(bubble1);

	backGround->addKeyframe(0, glm::vec2(0.0, 0.0));
	backGround->changeAnimation(0);
	whatScene = 1;

}

void Scene::init2()
{
	PlaySound(NULL, NULL, 0);
	PlaySound(TEXT("sounds/barcelona.wav"), NULL, SND_FILENAME | SND_ASYNC);
	initShaders();
	initBase();
	map = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	ui->init(texProgram, 1);
	ui->setLives(lives);
	ui->setScore(points);

	bubble1 = new Bubble();
	bubble1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 3, 3 * map->getTileSize(), true);
	bubble1->setPosition(glm::vec2(3 * map->getTileSize(), 2 * map->getTileSize()));
	bubble1->setTileMap(map);
	bubbles.insert(bubble1);

	bubble1 = new Bubble();
	bubble1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 3, 1 * map->getTileSize(), true);
	bubble1->setPosition(glm::vec2(23 * map->getTileSize(), 1 * map->getTileSize()));
	bubble1->setTileMap(map);
	bubbles.insert(bubble1);

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
	PlaySound(NULL, NULL, 0);
	PlaySound(TEXT("sounds/london.wav"), NULL, SND_FILENAME | SND_ASYNC);

	initShaders();
	initBase();
	map = TileMap::createTileMap("levels/level03.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	ui->init(texProgram, 2);
	ui->setLives(lives);
	ui->setScore(points);
	
	bubble1 = new Bubble();
	bubble1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 5, 13 * map->getTileSize(), true);
	bubble1->setPosition(glm::vec2(10 * map->getTileSize(), 13 * map->getTileSize()));
	bubble1->setTileMap(map);
	bubbles.insert(bubble1);

	bubble2 = new Bubble();
	bubble2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 5, 13 * map->getTileSize(), true);
	bubble2->setPosition(glm::vec2(16 * map->getTileSize(), 13 * map->getTileSize()));
	bubble2->setTileMap(map);
	bubbles.insert(bubble2);

	bubble3 = new Bubble();
	bubble3->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 5, 13 * map->getTileSize(), true);
	bubble3->setPosition(glm::vec2(39 * map->getTileSize(), 13 * map->getTileSize()));
	bubble3->setTileMap(map);
	bubbles.insert(bubble3);

	bubble4 = new Bubble();
	bubble4->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 7, 2 * map->getTileSize(), true);
	bubble4->setPosition(glm::vec2(31 * map->getTileSize(), 2 * map->getTileSize()));
	bubble4->setTileMap(map);
	bubbles.insert(bubble4);

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

void Scene::initMm() {
	initShaders();
	moment = 4;

	mainMenuWallaperImage.loadFromFile("images/MainMenuWallaper.png", TEXTURE_PIXEL_FORMAT_RGBA);
	mainMenuWallaper = Sprite::createSprite(glm::ivec2(8 * 48, 8 * 30), glm::vec2(1.0, 1.0), &mainMenuWallaperImage, &texProgram);
	mainMenuWallaper->setNumberAnimations(1);
	mainMenuWallaper->setAnimationSpeed(0, 1);
	mainMenuWallaper->setPosition(glm::ivec2(SCREEN_X, SCREEN_Y));
	mainMenuWallaper->addKeyframe(0, glm::vec2(0.0, 0.0));
	mainMenuWallaper->changeAnimation(0);

	insertCoinImage.loadFromFile("images/insertCoinMenu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	insertCoinMenuLabel = Sprite::createSprite(glm::ivec2(8 * 22, 8 * 3), glm::vec2(1.0, 1.0), &insertCoinImage, &texProgram);
	insertCoinMenuLabel->setNumberAnimations(1);
	insertCoinMenuLabel->setAnimationSpeed(0, 1);
	insertCoinMenuLabel->setPosition(glm::ivec2(SCREEN_X + 8 * 13, SCREEN_Y + 8 * 25));
	insertCoinMenuLabel->addKeyframe(0, glm::vec2(0.0, 0.0));
	insertCoinMenuLabel->changeAnimation(0);

	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	counterInsertCoinMainMenu = 0;
}

void Scene::initLevelEnd(int what, int extraScore) {
	initShaders();
	moment = 5;

	winWallaperImage.loadFromFile("images/winWallaper.png", TEXTURE_PIXEL_FORMAT_RGBA);
	winWallaper = Sprite::createSprite(glm::ivec2(8 * 48, 8 * 30), glm::vec2(1.0, 1.0), &winWallaperImage, &texProgram);
	winWallaper->setNumberAnimations(1);
	winWallaper->setAnimationSpeed(0, 1);
	winWallaper->setPosition(glm::ivec2(SCREEN_X, SCREEN_Y));
	winWallaper->addKeyframe(0, glm::vec2(0.0, 0.0));
	winWallaper->changeAnimation(0);

	ptsImage.loadFromFile("images/pts.png", TEXTURE_PIXEL_FORMAT_RGBA);
	ptsLabel = Sprite::createSprite(glm::ivec2(8 * 4, 9), glm::vec2(1.0, 1.0), &ptsImage, &texProgram);
	ptsLabel->setNumberAnimations(1);
	ptsLabel->setAnimationSpeed(0, 1);
	ptsLabel->setPosition(glm::ivec2(8 * 32, 8 * 21));
	ptsLabel->addKeyframe(0, glm::vec2(0.0, 0.0));
	ptsLabel->changeAnimation(0);

	stageImage.loadFromFile("images/whatStage.png", TEXTURE_PIXEL_FORMAT_RGBA);
	stageLabel = Sprite::createSprite(glm::ivec2(8 * 9, 9), glm::vec2(1.0, 1.0 / 3.0), &stageImage, &texProgram);
	stageLabel->setNumberAnimations(3);
	stageLabel->setAnimationSpeed(0, 1);
	stageLabel->addKeyframe(0, glm::vec2(0.0, 0.0));
	stageLabel->setAnimationSpeed(2, 1);
	stageLabel->addKeyframe(2, glm::vec2(0.0, 2.0 / 3.0));
	stageLabel->setAnimationSpeed(1, 1);
	stageLabel->addKeyframe(1, glm::vec2(0.0, 1.0 / 3.0));
	stageLabel->setPosition(glm::ivec2(8 * 19, 8 * 17));
	stageLabel->changeAnimation(what - 2);

	numberScoreImage.loadFromFile("images/scoreNumbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
	scoreLabel = *(new vector<Sprite*>(6));
	for (int i = 0; i < 6; ++i) {
		scoreLabel[i] = Sprite::createSprite(glm::ivec2(8, 9), glm::vec2(1.0 / 11.0, 1.0), &numberScoreImage, &texProgram);
		scoreLabel[i]->setNumberAnimations(11);
		for (int j = 0; j < 11; ++j) {
			scoreLabel[i]->setAnimationSpeed(j, 1);
			scoreLabel[i]->addKeyframe(j, glm::vec2(float(j) / 11.0, 0.0));
		}
		scoreLabel[i]->setPosition(glm::ivec2(8 * (30 - i), 8 * 21));
		scoreLabel[i]->changeAnimation(10);
	}
	for (int i = 0; i < scoreLabel.size(); ++i) {
		if (extraScore > 0) {
			scoreLabel[i]->changeAnimation(extraScore % 10);
			extraScore /= 10;
		}
		else {
			numbs2render = i;
			i = scoreLabel.size();
		}
	}

	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
}

void Scene::initInstructions() {
	initShaders();
	moment = 6;

	instructionsImage.loadFromFile("images/instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	instructionsWallaper = Sprite::createSprite(glm::ivec2(8 * 48, 8 * 30), glm::vec2(1.0, 1.0), &instructionsImage, &texProgram);
	instructionsWallaper->setNumberAnimations(1);
	instructionsWallaper->setAnimationSpeed(0, 1);
	instructionsWallaper->setPosition(glm::ivec2(SCREEN_X, SCREEN_Y));
	instructionsWallaper->addKeyframe(0, glm::vec2(0.0, 0.0));
	instructionsWallaper->changeAnimation(0);

	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
}

void Scene::initCredits() {
	initShaders();
	moment = 7;

	creditsImage.loadFromFile("images/creditWallaper.png", TEXTURE_PIXEL_FORMAT_RGBA);
	creditsWallaper = Sprite::createSprite(glm::ivec2(8 * 48, 8 * 30), glm::vec2(1.0, 1.0), &creditsImage, &texProgram);
	creditsWallaper->setNumberAnimations(1);
	creditsWallaper->setAnimationSpeed(0, 1);
	creditsWallaper->setPosition(glm::ivec2(SCREEN_X, SCREEN_Y));
	creditsWallaper->addKeyframe(0, glm::vec2(0.0, 0.0));
	creditsWallaper->changeAnimation(0);

	numberScoreImage.loadFromFile("images/scoreNumbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
	finalScoreLabel = *(new vector<Sprite*>(7));
	for (int i = 0; i < finalScoreLabel.size(); ++i) {
		finalScoreLabel[i] = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0 / 11.0, 1.0), &numberScoreImage, &texProgram);
		finalScoreLabel[i]->setNumberAnimations(11);
		for (int j = 0; j < 11; ++j) {
			finalScoreLabel[i]->setAnimationSpeed(j, 1);
			finalScoreLabel[i]->addKeyframe(j, glm::vec2(float(j) / 11.0, 0.0));
		}
		finalScoreLabel[i]->setPosition(glm::ivec2(8 * (34 - i*2), 8 * 6));
		finalScoreLabel[i]->changeAnimation(10);
	}
	for (int i = 0; i < finalScoreLabel.size(); ++i) {
		if (points > 0) {
			finalScoreLabel[i]->changeAnimation(points % 10);
			points /= 10;
		}
		else {
			numbs2render = i;
			i = finalScoreLabel.size();
		}
	}

	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
}

void Scene::flush() {
	delete player;
	delete cadaver;
	gsBcks.clear();
	wrs.clear();
	bubbledavers.clear();
	drops.clear();
	dynObjDestr.clear();
	bubbles.clear();
	delete backGround;
	delete ui;
}

void Scene::update(int deltaTime)
{
	
	switch (moment)
	{
	case 0:
		if (startCd == 25)
			ui->toggleReadyLabel();
		if (startCd == 30)
			ui->toggleReadyLabel();
		if (startCd == 35)
			ui->toggleReadyLabel();
		if (startCd == 40)
			ui->toggleReadyLabel();
		if (startCd == 45) {
			ui->toggleReadyLabel();
			moment = 1;
		}
		if (startCd == 50)
			ui->toggleReadyLabel();
		if (startCd == 55)
			ui->toggleReadyLabel();
		startCd++;
		break;
	case 1:
		currentTime += deltaTime;
		if (currentTime > 100000) {
			ui->timeAct(0);
			moriste();
		}
		else {
			ui->timeAct(100 - (currentTime) / 1000);
			player->update(deltaTime);
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
			for (std::set<BubbleDaver*>::iterator it = bubbledavers.begin(); it != bubbledavers.end(); ++it) {
				(*it)->update(deltaTime);
			}
			for (int i = 0; i < 1; i++) {
				std::set<BubbleDaver*>::iterator it4 = bubbledavers.begin();
				while (it4 != bubbledavers.end()) {
					if ((*it4)->check()) {
						bubbledavers.erase(*it4);
						it4 = bubbledavers.end();
					}
					else {
						it4++;
					}
				}
			}
			if (bubbleStoped) {
				if (cdStopBubs > 0) cdStopBubs--;
				else bubbleStoped = false;
			}
			else {
				for (std::set<Bubble*>::iterator it = bubbles.begin(); it != bubbles.end(); ++it) {
					(*it)->update(deltaTime);
				}
			}
			wireCollisions();
			dropCollisions();
			
			if (timerPum == 1) pum();
			else if(timerPum>1) timerPum--;

			if (timerInvulnerabilty <= 0 && !god && !bubbleStoped) {
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
					playerVisible = !playerVisible;
					timerTxtInvulnerabilty = 10;
				}
				else {
					timerTxtInvulnerabilty--;
				}
			}
		}
		if (currentTime > 104000) {
			lives--;
			if (lives != 0) {
				PlaySound(NULL, NULL, 0);
				mciSendString(L"stop GameOver", NULL, 0, NULL);
				mciSendString(L"open \"sounds/GameOver.wav\" type mpegvideo alias GameOver", NULL, 0, NULL);
				mciSendString(L"seek GameOver to start", NULL, 0, NULL);
				mciSendString(L"play GameOver", NULL, 0, NULL);
				ret=true;
			}
			else
				whatScene=4;
				moment = 2;
				timerRetry = 0;
		}
		break;
	case 2:
		player->update(deltaTime);
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
		for (std::set<BubbleDaver*>::iterator it = bubbledavers.begin(); it != bubbledavers.end(); ++it) {
			(*it)->update(deltaTime);
		}
		for (int i = 0; i < 1; i++) {
			std::set<BubbleDaver*>::iterator it4 = bubbledavers.begin();
			while (it4 != bubbledavers.end()) {
				if ((*it4)->check()) {
					printf("entru");
					bubbledavers.erase(*it4);
					it4 = bubbledavers.end();
				}
				else {
					it4++;
				}
			}
		}
		if (bubbleStoped) {
			if (cdStopBubs > 0) cdStopBubs--;
			else bubbleStoped = false;
		}
		else {
			for (std::set<Bubble*>::iterator it = bubbles.begin(); it != bubbles.end(); ++it) {
				(*it)->update(deltaTime);
			}
		}
		wireCollisions();
		dropCollisions();

		if (timerPum == 1) pum();
		else if (timerPum > 1) timerPum--;

		if (timerInvulnerabilty == 0 && !god && !bubbleStoped) {
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
				playerVisible = !playerVisible;
				timerTxtInvulnerabilty = 10;
			}
			else {
				timerTxtInvulnerabilty--;
			}
		}
		timerRetry++;
		if (timerRetry == 180) {
			mciSendString(L"stop Continue", NULL, 0, NULL);
			int aux = 100 - (currentTime / 1000);
			points += aux * 100;
			gm->lvlWin(whatScene, aux * 100);
		}
		break;
	
	case 3:
		cadaver->update(deltaTime);
		timerRetry++;
		if (timerRetry == 180) {
			
			ret=true;
		}
		break;
	case 4:
		counterInsertCoinMainMenu++;
		break;
	}
	if (ret) retry();
}

void Scene::render()
{
	if (moment == 4) {
		glm::mat4 modelview;
		texProgram.use();
		texProgram.setUniformMatrix4f("projection", projection);
		texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
		modelview = glm::mat4(1.0f);
		texProgram.setUniformMatrix4f("modelview", modelview);
		texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
		mainMenuWallaper->render();
		if ((counterInsertCoinMainMenu / 30) % 2 == 0)
			insertCoinMenuLabel->render();
	}
	else if (moment == 5) {
		glm::mat4 modelview;
		texProgram.use();
		texProgram.setUniformMatrix4f("projection", projection);
		texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
		modelview = glm::mat4(1.0f);
		texProgram.setUniformMatrix4f("modelview", modelview);
		texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
		winWallaper->render();
		stageLabel->render();
		ptsLabel->render();
		for (int i = 0; i < numbs2render; ++i)
			scoreLabel[i]->render();
	}
	else if (moment == 6) {
		glm::mat4 modelview;
		texProgram.use();
		texProgram.setUniformMatrix4f("projection", projection);
		texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
		modelview = glm::mat4(1.0f);
		texProgram.setUniformMatrix4f("modelview", modelview);
		texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
		instructionsWallaper->render();
	}
	else if (moment == 7) {
		glm::mat4 modelview;
		texProgram.use();
		texProgram.setUniformMatrix4f("projection", projection);
		texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
		modelview = glm::mat4(1.0f);
		texProgram.setUniformMatrix4f("modelview", modelview);
		texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
		creditsWallaper->render();
		for (int i = 0; i < numbs2render; ++i)
			finalScoreLabel[i]->render();
	}
	else {
		glm::mat4 modelview;
		texProgram.use();
		backGround->render();
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
		if (!(bubbleStoped && cdStopBubs < 60 * 2 && (cdStopBubs / 15) % 2 == 0)) {
			for (std::set<Bubble*>::iterator it = bubbles.begin(); it != bubbles.end(); ++it) {
				(*it)->render();
			}
		}
		for (std::set<BubbleDaver*>::iterator it = bubbledavers.begin(); it != bubbledavers.end(); ++it) {
			(*it)->render();
		}
		if (playerVisible && viu) player->render();
		else if (!viu) cadaver->render();
		ui->render();
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
			mciSendString(L"stop glass", NULL, 0, NULL);
			mciSendString(L"open \"sounds/glass.wav\" type mpegvideo alias glass", NULL, 0, NULL);
			mciSendString(L"seek glass to start", NULL, 0, NULL);
			mciSendString(L"play glass", NULL, 0, NULL);
			glm::ivec2 centreBlock = gb->getCenter();
			points += 500;
			ui->setScore(points);
			dynObjDestr.insert(gb);
			gsBcks.erase(gb);
		}
		std::set<Bubble*>::iterator it2 = bubbles.begin();
		while (it2 != bubbles.end()) {
			if ((*it2)->impacte(pWr, 4)) {
				
				mciSendString(L"stop pang", NULL, 0, NULL);
				mciSendString(L"open \"sounds/pang.wav\" type mpegvideo alias pang", NULL, 0, NULL);
				mciSendString(L"seek pang to start", NULL, 0, NULL);
				mciSendString(L"play pang", NULL, 0, NULL);

				
				glm::ivec2 pos = (*it2)->getPos();
				int type = (*it2)->getType();
				if (type % 4 != 0) {
					for (int b = 0; b < 2; b++) {
						Bubble* bubble = new Bubble();
						bubble->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, type - 1, pos.y - (type % 4) * 4, b);
						bubble->setPosition(glm::vec2(pos.x + b * (type % 4) * 8, pos.y + (type % 4) + 1 * 8));
						bubble->setJumpx(-10);
						bubble->setTileMap(map);
						bubbles.insert(bubble);
					}
				}
				glm::ivec2 centreBlock = (*it2)->getCenter();
				srand(time(NULL));
				if (rand() % 5 == 0)
					instanceDrop(centreBlock);
				addPoints(0, type, centreBlock);
				BubbleDaver* bubbledaver = new BubbleDaver();
				bubbledaver->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, type);
				bubbledaver->setPosition(pos);
				bubbledaver->setTileMap(map);
				bubbledavers.insert(bubbledaver);
				bubbles.erase(it2);
				wr = *it;
				it2 = bubbles.end();
				if (bubbles.empty()) {
					if (whatScene != 3) {
						PlaySound(NULL, NULL, 0);
						mciSendString(L"stop Continue", NULL, 0, NULL);
						mciSendString(L"seek Continue to start", NULL, 0, NULL);
						mciSendString(L"play Continue", NULL, 0, NULL);
					}
					else {
						PlaySound(NULL, NULL, 0);
						mciSendString(L"stop Ending", NULL, 0, NULL);
						mciSendString(L"open \"sounds/Ending.wav\" type mpegvideo alias Ending", NULL, 0, NULL);
						mciSendString(L"seek Ending to start", NULL, 0, NULL);
						mciSendString(L"play Ending", NULL, 0, NULL);
					}
					whatScene++;
					moment = 2;
					timerRetry = 0;
					
				}
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
	mciSendString(L"stop shoot", NULL, 0, NULL);
	mciSendString(L"open \"sounds/shoot.wav\" type mpegvideo alias shoot", NULL, 0, NULL);
	mciSendString(L"seek shoot to start", NULL, 0, NULL);
	mciSendString(L"play shoot", NULL, 0, NULL);

	Wire* wr = new Wire();
	glm::ivec2 posA = pos;
	posA.x += off;
	posA.y -= 4;
	wr->init(glm::ivec2(SCREEN_X, SCREEN_Y), posA, texProgram);
	wrs.insert(wr);
}

void Scene::setMaxWires(int nnw) {
	wrsAllowed = nnw;
	ui->actDoubleShot();
}

void Scene::dropCollisions() {
	Drops* d = NULL;
	for (std::set<Drops*>::iterator it = drops.begin(); it != drops.end(); ++it) {
		if ((*it)->disapear()) {
			d = (*it);
		}
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
				mciSendString(L"stop item", NULL, 0, NULL);
				mciSendString(L"open \"sounds/item.wav\" type mpegvideo alias item", NULL, 0, NULL);
				mciSendString(L"seek item to start", NULL, 0, NULL);
				mciSendString(L"play item", NULL, 0, NULL);
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

void Scene::addPoints(int pts, int whatType, glm::ivec2 centreBlock) {
	if (whatType == -1)
		points += pts;
	else {
		int type = whatType % 4;
		for (int i = 0; i < 4; ++i) {
			if (type == i) {
				if (multiplier[i] < 8 && multiplier[i] > 0) multiplier[i] *= 2;
				else if (multiplier[i] == 0) multiplier[i]++;
			}
			else {
				multiplier[i] = 0;
			}
		}
		points += 50 * (4 - type) * multiplier[type];
	}
	ui->setScore(points);
}

void Scene::playerBubbleCollisions() {
	glm::ivec2 pP = player->getPos();
	pP.x += 8;
	std::set<Bubble*>::iterator it2 = bubbles.begin();

	while (it2 != bubbles.end()) {
		
		if ((*it2)->impacte(pP, 16)) {
			if (escut) {
				escut = false;
				printf("he sortit\n");
				timerInvulnerabilty = 60 * 1;
			}
			else {
				bool direccio = (*it2)->impacte(pP, 8);
				if (lives != 0) {

					mciSendString(L"stop Missed", NULL, 0, NULL);
					mciSendString(L"open \"sounds/Missed.wav\" type mpegvideo alias missed", NULL, 0, NULL);
					mciSendString(L"seek Missed to start", NULL, 0, NULL);
					mciSendString(L"play Missed", NULL, 0, NULL);

					lives--;
					ui->setLives(lives);
					viu = false;
					moment = 3;
					timerRetry = 0;
					cadaver->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, direccio);
					cadaver->setPosition(player->getPos());
					cadaver->setTileMap(map);
				}
				else {
					PlaySound(NULL, NULL, 0);
					mciSendString(L"stop GameOver", NULL, 0, NULL);
					mciSendString(L"open \"sounds/GameOver.wav\" type mpegvideo alias GameOver", NULL, 0, NULL);
					mciSendString(L"seek GameOver to start", NULL, 0, NULL);
					mciSendString(L"play GameOver", NULL, 0, NULL);

					cadaver->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, direccio);
					cadaver->setPosition(player->getPos());
					cadaver->setTileMap(map);
					viu = false;
					whatScene=4;
					moment = 3;
					timerRetry = 0;
				}
				it2 = bubbles.end();
			}
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

void Scene::stopTime() {
	bubbleStoped = true;
	cdStopBubs = 6 * 60;
	timerInvulnerabilty = 6 * 60;
}

void Scene::shield() {
	escut = true;
}

void Scene::pum() {
	std::set<Bubble*>::iterator it2 = bubbles.begin();
	while (it2 != bubbles.end()) {
		if ((*it2)->getType() % 4 != 0) {

			mciSendString(L"stop pang", NULL, 0, NULL);
			mciSendString(L"open \"sounds/pang.wav\" type mpegvideo alias pang", NULL, 0, NULL);
			mciSendString(L"seek pang to start", NULL, 0, NULL);
			mciSendString(L"play pang", NULL, 0, NULL);


			glm::ivec2 pos = (*it2)->getPos();
			int type = (*it2)->getType();
			for (int b = 0; b < 2; b++) {
				Bubble* bubble = new Bubble();
				bubble->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, type - 1, pos.y - (type % 4) * 4, b);
				bubble->setPosition(glm::vec2(pos.x + b * (type % 4) * 8, pos.y + (type % 4) + 1 * 8));
				bubble->setJumpx(-10);
				bubble->setTileMap(map);
				bubbles.insert(bubble);
			}
			glm::ivec2 centreBlock = (*it2)->getCenter();
			instanceDrop(centreBlock);
			BubbleDaver* bubbledaver = new BubbleDaver();
			bubbledaver->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, type);
			bubbledaver->setPosition(pos);
			bubbledaver->setTileMap(map);
			bubbledavers.insert(bubbledaver);
			bubbles.erase(it2);
			it2 = bubbles.begin();
			timerPum=10;
			break;
		}
		else
		{
			++it2;
			if(it2 == bubbles.end()) 
				timerPum = 0;
		}
	}
}

void Scene::gameReset() {
	points = 0;
	lives = 3;
}