#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include <iostream>


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init1();
	keyDown = false;
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);
	

	if (Game::instance().getKey(GLFW_KEY_1)) {
		if (!keyDown) {
			scene.flush();
			scene.init1();
			keyDown = true;
		}
	}
	else if (Game::instance().getKey(GLFW_KEY_2)) {
		if (!keyDown) {
			scene.flush();
			scene.init2();
			keyDown = true;
		}
	}
	else if (Game::instance().getKey(GLFW_KEY_3)) {
		if (!keyDown) {
			scene.flush();
			scene.init3();
			keyDown = true;
		}
	}
	else if (Game::instance().getKey(GLFW_KEY_G)) {
		if (!keyDown) {
			scene.godCheat();
			keyDown = true;
		}
	}
	else
		keyDown = false;

	

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.render();
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



