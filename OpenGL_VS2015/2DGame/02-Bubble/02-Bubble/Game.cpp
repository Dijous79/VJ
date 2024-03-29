#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include <iostream>


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	scene = new Scene(this);
	scene->initMm();
	moment = 0;
	keyDown = false;
}

bool Game::update(int deltaTime)
{
	scene->update(deltaTime);
	if (moment == 1) {
		if (Game::instance().getKey(GLFW_KEY_1)) {
			if (!keyDown) {
				scene->flush();
				scene->init1();
				keyDown = true;
			}
		}
		else if (Game::instance().getKey(GLFW_KEY_2)) {
			if (!keyDown) {
				scene->flush();
				scene->init2();
				keyDown = true;
			}
		}
		else if (Game::instance().getKey(GLFW_KEY_3)) {
			if (!keyDown) {
				scene->flush();
				scene->init3();
				keyDown = true;
			}
		}
		else if (Game::instance().getKey(GLFW_KEY_G)) {
			if (!keyDown) {
				scene->godCheat();
				keyDown = true;
			}
		}
		else if (Game::instance().getKey(GLFW_KEY_U)) {
			if (!keyDown) {
				scene->addPoints(100);
				scene->stopTime();
				keyDown = true;
			}
		}
		else if (Game::instance().getKey(GLFW_KEY_Y)) {
			if (!keyDown) {
				scene->setMaxWires(2);
				scene->addPoints(100);
				keyDown = true;
			}
		}
		else if (Game::instance().getKey(GLFW_KEY_P)) {
			if (!keyDown) {
				scene->addPoints(100);
				scene->pum();
				keyDown = true;
			}
		}
		else
			keyDown = false;
	}
	else if (moment == 0) {
		if (Game::instance().getKey(GLFW_KEY_ENTER)) {
			if (!keyDown) {
				scene->initInstructions();
				moment = 3;
				keyDown = true;
			}
		}
		else
			keyDown = false;
	}
	else if (moment == 2) {
		if (Game::instance().getKey(GLFW_KEY_ENTER)) {
			switch (nextScene)
			{
			case 2:
				scene->init2();
				moment = 1;
				break;
			case 3:
				scene->init3();
				moment = 1;
				break;
			case 4:
				scene->initCredits();
				moment = 4;
				keyDown = true;
				break;
			default:
				break;
			}
			
		}
	}
	else if (moment == 3) {
		if (Game::instance().getKey(GLFW_KEY_ENTER)) {
			if (!keyDown) {
				scene->init1();
				moment = 1;
			}
		}
		else {
			keyDown = false;
		}
	}
	else if (moment == 4) {
		if (Game::instance().getKey(GLFW_KEY_ENTER)) {
			if (!keyDown) {
				scene->initMm();
				moment = 0;
			}
		}
		else {
			keyDown = false;
		}
	}
	

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (scene != NULL)
		scene->render();
}

void Game::keyPressed(int key)
{
	if(key == GLFW_KEY_ESCAPE) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

void Game::putMainMenu() {
	scene->flush();
	scene->initMm();
	moment = 0;
}

void Game::lvlWin(int what, int score) {
	scene->flush();
	scene->initLevelEnd(what, score);
	moment = 2;
	printf("%d\n", what);
	nextScene = what;
}

