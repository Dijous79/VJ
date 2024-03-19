#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Player.h"
#include "Game.h"
#include "Scene.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, CLIMBING, OUT_OF_LADDER, SHOOTING_LEFT, SHOOTING_RIGHT
};


void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Scene* scene)
{
	bClimbing = false;
	inAnim = false;
	lastDir = false;
	Bfr = 0;
	scn = scene;
	size = glm::ivec2(96, 96);
	spritesheet.loadFromFile("images/character.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(size, glm::vec2(0.2, 1.0/6.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);

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

	sprite->setAnimationSpeed(CLIMBING, 4);
	sprite->addKeyframe(CLIMBING, glm::vec2(0.2f, 3.0 / 6.0));
	sprite->addKeyframe(CLIMBING, glm::vec2(0.4f, 2.0 / 6.0));
	sprite->addKeyframe(CLIMBING, glm::vec2(0.2f, 3.0 / 6.0));
	sprite->addKeyframe(CLIMBING, glm::vec2(0.6f, 2.0 / 6.0));

	sprite->setAnimationSpeed(OUT_OF_LADDER, 1);
	sprite->addKeyframe(OUT_OF_LADDER, glm::vec2(0.6f, 3.0 / 6.0));

	sprite->setAnimationSpeed(SHOOTING_LEFT, 1);
	sprite->addKeyframe(SHOOTING_LEFT, glm::vec2(0.6f, 4.0 / 6.0));

	sprite->setAnimationSpeed(SHOOTING_RIGHT, 1);
	sprite->addKeyframe(SHOOTING_RIGHT, glm::vec2(0.2f, 4.0 / 6.0));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (inAnim) {
		if (Bfr > 0) Bfr--;
		else {
			inAnim = false;
			if (bClimbing) sprite->changeAnimation(CLIMBING);
			else {
				if (lastDir) sprite->changeAnimation(STAND_LEFT);
				else {
					sprite->changeAnimation(STAND_RIGHT);
				}
			}
		}
	}
	else
	{
		if (bClimbing) {
			if (Game::instance().getKey(GLFW_KEY_UP))
			{
				sprite->setAnimationSpeed(CLIMBING, 4);
				posPlayer.y -= FALL_STEP;
				if (!map->inLadder(posPlayer, size)) {
					bClimbing = false;
					inAnim = true;
					Bfr = 5;
					posPlayer.y -= size.y / 3.3333;
					sprite->changeAnimation(OUT_OF_LADDER);
				}
			}
			else if (Game::instance().getKey(GLFW_KEY_DOWN))
			{
				sprite->setAnimationSpeed(CLIMBING, 4);
				posPlayer.y += FALL_STEP;
				if (map->underLadder(posPlayer, size, &posPlayer.y)) {
					bClimbing = false;
					inAnim = false;
					if (lastDir) sprite->changeAnimation(STAND_LEFT);
					else sprite->changeAnimation(STAND_RIGHT);
				}
			}
			else {
				sprite->setAnimationSpeed(CLIMBING, 0);
			}
		}
		else {
			if (Game::instance().getKey(GLFW_KEY_LEFT))
			{
				lastDir = true;
				if (sprite->animation() != MOVE_LEFT)
					sprite->changeAnimation(MOVE_LEFT);
				posPlayer.x -= 4;
				if (map->collisionMoveLeft(posPlayer, size))
				{
					posPlayer.x += 4;
				}
			}
			else if (Game::instance().getKey(GLFW_KEY_RIGHT))
			{
				lastDir = false;
				if (sprite->animation() != MOVE_RIGHT) {
					sprite->changeAnimation(MOVE_RIGHT);
				}
				posPlayer.x += 4;
				if (map->collisionMoveRight(posPlayer, size))
				{
					posPlayer.x -= 4;
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
				if (map->inLadder(posPlayer, size)) {
					bClimbing = true;
					map->closestLadder(posPlayer, size, &posPlayer.x, &posPlayer.y);
					sprite->changeAnimation(CLIMBING);
				}
			}
			if (Game::instance().getKey(GLFW_KEY_DOWN))
			{
				if (map->onLadder(posPlayer, size)) {
					bClimbing = true;
					printf("%f\n", float(posPlayer.x) / 24.0);
					map->closestLadder(posPlayer, size, &posPlayer.x, &posPlayer.y);
					inAnim = true;
					Bfr = 10;
					sprite->changeAnimation(OUT_OF_LADDER);
				}
			}
			posPlayer.y += FALL_STEP;
			map->collisionMoveDown(posPlayer, size, &posPlayer.y);
		}
		printf("si\n");
		if (Game::instance().getKey(GLFW_KEY_S)) {
			printf("dsfdsfasdfasd\n");
			if (scn->space4Wire()) {
				int off = 24;
				if (!lastDir)
					off += 24;
				scn->instanceWire(posPlayer, off);
				inAnim = true;
				Bfr = 4;
				if (!bClimbing) {
					if (lastDir)
						sprite->changeAnimation(SHOOTING_LEFT);
					else
						sprite->changeAnimation(SHOOTING_RIGHT);
				}
			}
		}
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




