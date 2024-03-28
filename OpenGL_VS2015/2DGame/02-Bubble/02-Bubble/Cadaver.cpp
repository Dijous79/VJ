#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Cadaver.h"
#include "Game.h"
#include <map>


void Cadaver::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram,bool dir)
{

	spritesheet.loadFromFile("images/character.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 1.0 / 6.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);
	sprite->setAnimationSpeed(0, 2);
	sprite->addKeyframe(0, glm::vec2(0.33f, 5.0 / 6.0));
	
	sprite->setAnimationSpeed(1, 2);
	sprite->addKeyframe(1, glm::vec2(0.f, 5.0 / 6.0));

	
	if(dir) sprite->changeAnimation(0);
	else sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCadaver.x), float(tileMapDispl.y + posCadaver.y)));
	fwd = dir;
	first_jump = true;
	jump_x = -10;
}

void Cadaver::update(int deltaTime)
{
	sprite->update(deltaTime);


	if (first_jump) {

		if (map->collisionMoveDown(posCadaver, glm::ivec2(32, 32), &posCadaver.y)) {
			jump_x = abs(jump_x) * -1;
			jump_x += 1;
			first_jump = false;
		}

		if (fwd) {
			sprite->changeAnimation(0);
			posCadaver.x += 1;
			if (map->collisionMoveRight(posCadaver, glm::ivec2(32, 32))) {
				fwd = false;
				posCadaver.x -= 1;
			}
		}
		else {
			sprite->changeAnimation(1);
			posCadaver.x -= 1;
			if (map->collisionMoveLeft(posCadaver, glm::ivec2(32, 32))) {
				fwd = true;
				posCadaver.x += 1;
			}
		}

		posCadaver.y = int((jump_x * 0.33) * (jump_x * 0.33) + Yini); //128 pixels per salt
		
	}
	else {
		posCadaver.y = int((jump_x * 0.33) * (jump_x * 0.33)) + Yini; //128 pixels per salt
		if(fwd) posCadaver.x += 1;
		else posCadaver.x -= 1;
	}


	jump_x += 1;
	
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCadaver.x), float(tileMapDispl.y + posCadaver.y)));
}

void Cadaver::render()
{
	sprite->render();
}

void Cadaver::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Cadaver::setPosition(const glm::vec2& pos)
{
	posCadaver = pos;
	Yini = pos.y - 50;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCadaver.x), float(tileMapDispl.y + posCadaver.y)));
}
