#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Bubble.h"
#include "Game.h"


#define FALL 10
#define JUMP_HEIGHT 200


enum BubbleAnims
{
	TIER1, TIER2, TIER3
};


void Bubble::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	
	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(48, 48), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBubble.x), float(tileMapDispl.y + posBubble.y)));
	jumping = true;
	fwd = true;
	Caiguda_en_y = 0;
	jump_x = 0;
}

void Bubble::update(int deltaTime)
{
	sprite->update(deltaTime);
	int Min_x = -64;
	int Max_x = 64;

	if (fwd) {
		posBubble.x += 3;
		if (map->collisionMoveRight(posBubble, glm::ivec2(48, 48))) {
			fwd = false;
			posBubble.x -= 3;
		}
	}
	else {
		posBubble.x -= 3;
		if (map->collisionMoveLeft(posBubble, glm::ivec2(48, 48))) {
			fwd = true;
			posBubble.x += 3;
		}
	}
	
	posBubble.y = int((jump_x * 0.33) * (jump_x * 0.33)) + 100;
	jump_x += 1;

	glm::ivec2 posBubble2 = posBubble - (posBubble % (8 * 3)) +3;
	if (map->collisionMoveDown(posBubble2, glm::ivec2(45, 48), &posBubble2.y)) {
			jump_x = abs(jump_x) * -1;
			jump_x += 1;
			posBubble.y = posBubble2.y;
	
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




