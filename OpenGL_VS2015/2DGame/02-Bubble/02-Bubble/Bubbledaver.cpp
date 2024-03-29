#include "Bubbledaver.h"
#include <iostream>

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

glm::vec2 BubbleDaver::getTextPosBubble(int type) {
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

void BubbleDaver::infoBubble(glm::ivec2* tam, glm::vec2* part, int type) {
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

void BubbleDaver::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int bubble)
{
	
	spritesheet.loadFromFile("images/exprosion.png", TEXTURE_PIXEL_FORMAT_RGBA);
	infoBubble(&tam_txt, &part_txt, bubble % 4);
	pos_txt = getTextPosBubble(bubble%4);
	bub = bubble;
	sprite = Sprite::createSprite(tam_txt, part_txt, &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	cont = 0;
	switch (tam_txt.x)
	{
	case 8:
		sprite->setAnimationSpeed(0, 10);
		sprite->addKeyframe(0, glm::vec2(0.75, 0));
		sprite->addKeyframe(0, glm::vec2(0.75, 1.0 / 24.0));
		sprite->addKeyframe(0, glm::vec2(0.75, 2.0 / 24.0));
		sprite->addKeyframe(0, glm::vec2(0.75, 4.0 / 24.0));
		break;
	case 16:
		sprite->setAnimationSpeed(0, 10);
		sprite->addKeyframe(0, glm::vec2(0.625, 0.0 / 12.0));
		sprite->addKeyframe(0, glm::vec2(0.625, 1.0 / 12.0));
		sprite->addKeyframe(0, glm::vec2(0.625, 2.0 / 12.0));
		sprite->addKeyframe(0, glm::vec2(0.625, 3.0 / 12.0));
		break;
	case 32:
		sprite->setAnimationSpeed(0, 10);
		sprite->addKeyframe(0, glm::vec2(0.375, 0.0 / 6.0));
		sprite->addKeyframe(0, glm::vec2(0.375, 1.0 / 6.0));
		sprite->addKeyframe(0, glm::vec2(0.375, 2.0 / 6.0));
		sprite->addKeyframe(0, glm::vec2(0.375, 3.0 / 6.0));
		break;
	case 48:
		sprite->setAnimationSpeed(0, 10);
		sprite->addKeyframe(0, glm::vec2(0.0, 0));
		sprite->addKeyframe(0, glm::vec2(0.0, 0.25));
		sprite->addKeyframe(0, glm::vec2(0.0, 0.5));
		sprite->addKeyframe(0, glm::vec2(0.0, 0.75));
		break;
	}


	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos; 
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBubble.x), float(tileMapDispl.y + posBubble.y)));
}


void BubbleDaver::update(int deltaTime) {
	sprite->update(deltaTime);
	cont++;
	
}


void BubbleDaver::render()
{
	sprite->render();
}

void BubbleDaver::setPosition(const glm::vec2& pos)
{
	posBubble = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBubble.x), float(tileMapDispl.y + posBubble.y)));
}

void BubbleDaver::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

bool BubbleDaver::check() {
	return cont > 20;
}