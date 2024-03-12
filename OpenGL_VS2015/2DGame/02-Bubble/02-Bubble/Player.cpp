#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	bClimbing = false;
	inLadder = false;
	spritesheet.loadFromFile("images/character.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(0.2, 1.0/6.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.4f, 4.0/6.0));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0f, 4.0/6.0));

	sprite->setAnimationSpeed(MOVE_LEFT, 10);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 1.0/6.0));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.2f, 1.0 / 6.0));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.4f, 1.0 / 6.0));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.6f, 1.0 / 6.0));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.8f, 1.0 / 6.0));

	sprite->setAnimationSpeed(MOVE_RIGHT, 10);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.2f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.4f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.6f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.8f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (bClimbing) {
		if (Game::instance().getKey(GLFW_KEY_UP))
		{
			posPlayer.y -= FALL_STEP;
			if (!map->inLadder(posPlayer, glm::ivec2(92, 92))) {
				bClimbing = false;
				//Posar Sprite de pujant
			}
		}
		else if (Game::instance().getKey(GLFW_KEY_DOWN))
		{
			posPlayer.y += FALL_STEP;
			if (map->underLadder(posPlayer, glm::ivec2(92, 92), &posPlayer.y)) {
				bClimbing = false;
				//Posar Sprite de pujant
			}
		}
	}
	else {
		if (Game::instance().getKey(GLFW_KEY_LEFT))
		{
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			posPlayer.x -= 2;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(92, 92)))
			{
				posPlayer.x += 2;
				sprite->changeAnimation(STAND_LEFT);
			}
		}
		else if (Game::instance().getKey(GLFW_KEY_RIGHT))
		{
			if (sprite->animation() != MOVE_RIGHT) {
				sprite->changeAnimation(MOVE_RIGHT);
			}
			posPlayer.x += 2;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(92, 92)))
			{
				posPlayer.x -= 2;
				sprite->changeAnimation(STAND_RIGHT);
			}
		}
		else
		{
			if (sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
		}

		if (Game::instance().getKey(GLFW_KEY_UP))
		{
			if (map->inLadder(posPlayer, glm::ivec2(92, 92))) {
				bClimbing = true;
				map->closestLadder(posPlayer, glm::ivec2(92, 92), &posPlayer.x);
				//Posar Sprite de pujant
			}
		}
		if (Game::instance().getKey(GLFW_KEY_DOWN))
		{
			if (map->onLadder(posPlayer, glm::ivec2(92, 92))) {
				bClimbing = true;
				map->closestLadder(posPlayer, glm::ivec2(92, 92), &posPlayer.x);
				//Posar Sprite de pujant
			}
		}
		posPlayer.y += FALL_STEP;
		map->collisionMoveDown(posPlayer, glm::ivec2(92, 92), &posPlayer.y);
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




