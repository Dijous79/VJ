#include "PowerUp.h"
#include "Scene.h"

enum PowerUpAnims {
	BASE, DISAPEARING
};

void PowerUp::init(const glm::ivec2& tileMapPos, glm::ivec2 posiO, ShaderProgram& shaderProgram, int pwu) {
	size = glm::ivec2(16, 16);
	posi = posiO;
	tileMapDispl = tileMapPos;
	whatIsIt = pwu;
	spritesheet.loadFromFile("images/PowerUps.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(size, glm::vec2(1.0 / 11.0, 1.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	if (pwu == 0) {
		sprite->setAnimationSpeed(BASE, 1);
		sprite->addKeyframe(BASE, glm::vec2(0.0, 0.0));
		sprite->setAnimationSpeed(DISAPEARING, 4);
		sprite->addKeyframe(DISAPEARING, glm::vec2(0.0, 0.0));
		sprite->addKeyframe(DISAPEARING, glm::vec2(10.0 / 11.0, 0.0));
	}
	else if (pwu == 1) {
		sprite->setAnimationSpeed(BASE, 1);
		sprite->addKeyframe(BASE, glm::vec2(1.0 / 11.0, 0.0));
		sprite->setAnimationSpeed(DISAPEARING, 4);
		sprite->addKeyframe(DISAPEARING, glm::vec2(1.0 / 11.0, 0.0));
		sprite->addKeyframe(DISAPEARING, glm::vec2(10.0 / 11.0, 0.0));
	}
	else if (pwu == 2) {
		sprite->setAnimationSpeed(BASE, 8);
		for (int i = 2; i < 10; ++i)
			sprite->addKeyframe(BASE, glm::vec2(i * (1.0 / 11.0), 0.0));
		sprite->setAnimationSpeed(DISAPEARING, 4);
		sprite->addKeyframe(DISAPEARING, glm::vec2(1.0 / 11.0, 0.0));
		sprite->addKeyframe(DISAPEARING, glm::vec2(10.0 / 11.0, 0.0));
	}
	sprite->changeAnimation(BASE);
	sprite->setPosition((glm::vec2(float(tileMapDispl.x + posi.x), float(tileMapDispl.y + posi.y))));
}

void PowerUp::destroy() {
	switch (whatIsIt)
	{
	case 0:
		scn->setMaxWires(2);
		scn->addPoints(100);
		break;
	case 1:
		scn->addPoints(100);
		break;
	case 2:
		scn->addPoints(100);
		break;
	default:
		break;
	}
}