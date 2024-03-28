#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Bubble.h"
#include "Game.h"
#include <map>
#include <windows.h>
#pragma comment(lib,"winmm.lib")

#define FALL 10
#define JUMP_HEIGHT 200

enum tamanys
{
	MINI, SMALL, MEDIUM, BIG
};

enum bubbles
{
	MINI_RED, SMALL_RED, MEDIUM_RED, BIG_RED,
	MINI_BLUE, SMALL_BLUE, MEDIUM_BLUE, BIG_BLUE,
	MINI_GREEN, SMALL_GREEN, MEDIUM_GREEN, BIG_GREEN
};

glm::vec2 Bubble::getTextPosBubble(int type) {
	switch (type) {
	case MINI_RED:
		return glm::vec2(0.75, 0);
		break;
	case SMALL_RED:
		return glm::vec2(0.625, 0);
		break;
	case MEDIUM_RED:
		return glm::vec2(0.375, 0);
		break;
	case BIG_RED:
		return glm::vec2(0.0, 0);
		break;
	case MINI_BLUE:
		return glm::vec2(0.75, 1.0 / 24.0);
		break;
	case SMALL_BLUE:
		return glm::vec2(0.625, 1.0 / 12.0);
		break;
	case MEDIUM_BLUE:
		return glm::vec2(0.375, 1.0 / 6.0);
		break;
	case BIG_BLUE:
		return glm::vec2(0.0, 0.25);
		break;
	case MINI_GREEN:
		return glm::vec2(0.75, 2.0 / 24.0);
		break;
	case SMALL_GREEN:
		return glm::vec2(0.625, 2.0 / 12.0);
		break;
	case MEDIUM_GREEN:
		return glm::vec2(0.375, 2.0 / 6.0);
		break;
	case BIG_GREEN:
		return glm::vec2(0.0, 0.5);
		break;
	}
}

void Bubble::infoBubble(glm::ivec2* tam, glm::vec2* part, int type) {
	switch (type) {
	case MINI:
		*tam = glm::ivec2(8, 8);
		*part = glm::vec2(1.0 / 16.0, 1.0 / 24.0);
		break;
	case SMALL:
		*tam = glm::ivec2(16, 16);
		*part = glm::vec2(0.125, 1.0 / 12.0);
		break;
	case MEDIUM:
		*tam = glm::ivec2(32, 32);
		*part = glm::vec2(0.25, 1.0 / 6.0);
		break;
	case BIG:
		*tam = glm::ivec2(48, 48);
		*part = glm::vec2(0.375, 0.25);
		break;
	}
}

void Bubble::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int bubble, int Yini, bool dir)
{

	spritesheet.loadFromFile("images/bubble.png", TEXTURE_PIXEL_FORMAT_RGBA);
	infoBubble(&tam_txt, &part_txt, bubble % 4);
	pos_txt = getTextPosBubble(bubble);
	bub = bubble;
	sprite = Sprite::createSprite(tam_txt, part_txt, &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 1);
	sprite->addKeyframe(0, pos_txt);
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBubble.x), float(tileMapDispl.y + posBubble.y)));
	jumping = true;
	fwd = dir;
	first_jump = true;
	this->Yini = Yini;
	jump_x = 0;
	blocsDown = vector<glm::ivec2>();
	timersDown = vector<int>();
	blocsUp = vector<glm::ivec2>();
	timersUp = vector<int>();
}

void Bubble::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (fwd) {
		posBubble.x += 8;
		if (map->collisionMoveRight(posBubble, tam_txt)) {
			fwd = false;
			posBubble.x -= 1;
		}
		posBubble.x -= 7;
	}
	else {
		posBubble.x -= 1;
		if (map->collisionMoveLeftBub(posBubble, tam_txt)) {
			fwd = true;
			posBubble.x += 1;
		}
	}

	if (first_jump) {
		switch (tam_txt.x) {
		case 8:
			posBubble.y = int((jump_x * 0.33) * (jump_x * 0.33) + Yini); //64 pixels per salt
			break;
		case 16:
			posBubble.y = int((jump_x * 0.33) * (jump_x * 0.33) + Yini);
			break;
		case 32:
			posBubble.y = int((jump_x * 0.33) * (jump_x * 0.4) + Yini);    //132*3 d'altura
			break;
		case 48:
			posBubble.y = int((jump_x * 0.33) * (jump_x * 0.33) + Yini); //128 pixels per salt
			break;
		}
	}
	else {
		switch (tam_txt.x) {
		case 8:
			posBubble.y = int((jump_x * 0.33) * (jump_x * 0.33)) + 19 * 8; //64 pixels per salt
			break;
		case 16:
			posBubble.y = int((jump_x * 0.33) * (jump_x * 0.33) + 12.9 * 8);
			break;
		case 32:
			posBubble.y = int((jump_x * 0.33) * (jump_x * 0.33) + 7.75 * 8);//132 d'altura
			break;
		case 48:
			posBubble.y = int((jump_x * 0.33) * (jump_x * 0.33)) + 25 / 3; //128 pixels per salt
			break;
		}
	}


	jump_x += 1;


	vector<glm::ivec2> v3 = map->getUpTilePos(posBubble, tam_txt);
	vector<int> v4 = vector<int>(v3.size(), 3);

	timersUp.insert(timersUp.end(), v4.begin(), v4.end());
	blocsUp.insert(blocsUp.end(), v3.begin(), v3.end());

	for (int i = 0; i < blocsUp.size(); i++) {
		glm::ivec2 pos = blocsUp[i];
		if (map->circleRect(posBubble.x + tam_txt.x / 2 + despCentre(tam_txt.x), posBubble.y + tam_txt.y / 2 + despCentre(tam_txt.x), tam_txt.x / 2, pos.x, pos.y, 8, 8, &posBubble.y, true)) {
			
			jump_x = abs(jump_x);
			jump_x += 1;
			posBubble.y += 8+tam_txt.y -despCentre(tam_txt.x);
			blocsUp.erase(blocsUp.begin() + i);
			timersUp.erase(timersUp.begin() + i);
			break;
		}
	}
	for (int i = 0; i < timersUp.size(); i++) {
		if (timersUp[i] == 1) {
			blocsUp.erase(blocsUp.begin() + i);
			timersUp.erase(timersUp.begin() + i);
		}
		else {
			timersUp[i] -= 1;
		}
	}

	vector<glm::ivec2> v1 = map->getDownTilePos(posBubble, tam_txt);
	vector<int> v2 = vector<int>(v1.size(), 3);

	timersDown.insert(timersDown.end(), v2.begin(), v2.end());
	blocsDown.insert(blocsDown.end(), v1.begin(), v1.end());

	for (int i = 0; i < blocsDown.size(); i++) {
		glm::ivec2 pos = blocsDown[i];
		if (map->circleRect(posBubble.x + tam_txt.x / 2, posBubble.y + tam_txt.y / 2, tam_txt.x / 2, pos.x, pos.y, 8, 8, &posBubble.y, true)) {
			if (first_jump && posBubble.y + tam_txt.x > 20 * 8) {
				first_jump = false;
				switch (tam_txt.x) { // canviar en funcó de la amplada de la parabola
				case 8:
					jump_x = 21;
					break;
				case 16:
					jump_x = 29;
					break;
				case 32:
					jump_x = 33;
					break;
				case 48:
					jump_x = 38;
					break;
				}
			}
			jump_x = abs(jump_x) * -1;
			jump_x += 1;
			blocsDown.erase(blocsDown.begin() + i);
			timersDown.erase(timersDown.begin() + i);
			break;
		}
	}
	for (int i = 0; i < timersDown.size(); i++) {
		if (timersDown[i] == 1) {
			blocsDown.erase(blocsDown.begin() + i);
			timersDown.erase(timersDown.begin() + i);
		}
		else {
			timersDown[i] -= 1;
		}
	}



	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBubble.x), float(tileMapDispl.y + posBubble.y)));
}

void Bubble::render()
{
	sprite->render();
}

void Bubble::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Bubble::setPosition(const glm::vec2& pos)
{
	posBubble = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBubble.x), float(tileMapDispl.y + posBubble.y)));
}

bool Bubble::impacte(glm::ivec2 posCable, int superficie) {
	return map->circleRect(posBubble.x + tam_txt.x / 2, posBubble.y + tam_txt.y / 2, tam_txt.x / 2, posCable.x, posCable.y, superficie, 400, &posBubble.y, false);
}

glm::ivec2 Bubble::getPos() {
	return posBubble;
}

int Bubble::getType() {
	return bub;
}

glm::ivec2 Bubble::getCenter() {
	return posBubble + tam_txt / 2;
}

int Bubble::despCentre(int t) {
	switch (t) {
	case 8:
		return 1;
		break;
	case 16:
		return 2;
		break;
	case 32:
		return 6;
		break;
	case 48:
		return 8;
		break;
	}

}

void Bubble::setJumpx(int x) {
	jump_x = x;
}