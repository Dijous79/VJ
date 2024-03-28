#include "Food.h"
#include "Scene.h"

void Food::init(const glm::ivec2& tileMapPos, glm::ivec2 posiO, ShaderProgram& shaderProgram, int pwu) {
	setPosSize(pwu, posiO);
	tileMapDispl = tileMapPos;
	whatIsIt = pwu;
	cd = 60 * 6;
	dis = false;
	spritesheet.loadFromFile("images/Food.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(size, glm::vec2((size.x / 16) / 6.0, 1.0 / 6.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	if (pwu < 20) {
		sprite->setAnimationSpeed(BASE, 1);
		sprite->addKeyframe(BASE, glm::vec2((pwu % 6) * (1.0 / 6.0), (pwu / 6) * (1.0 / 6.0)));
		sprite->setAnimationSpeed(DISAPEARING, 12);
		sprite->addKeyframe(DISAPEARING, glm::vec2((pwu % 6) * (1.0 / 6.0), (pwu / 6) * (1.0 / 6.0)));
		sprite->addKeyframe(DISAPEARING, glm::vec2(5.0 / 6.0, 5.0 / 6.0));
	}
	else {
		sprite->setAnimationSpeed(BASE, 1);
		sprite->addKeyframe(BASE, glm::vec2(1.0 / 3.0, 5.0 / 6.0));
		sprite->setAnimationSpeed(DISAPEARING, 12);
		sprite->addKeyframe(DISAPEARING, glm::vec2(1.0 / 3.0, 5.0 / 6.0)); 
		sprite->addKeyframe(DISAPEARING, glm::vec2(4.0 / 6.0, 5.0 / 6.0));
	}
	sprite->changeAnimation(BASE);
	sprite->setPosition((glm::vec2(float(tileMapDispl.x + posi.x), float(tileMapDispl.y + posi.y))));
}

void Food::destroy() {
	if (whatIsIt < 20)
		scn->addPoints(500);
	else
		scn->addPoints(1000);
}

void Food::setPosSize(int wht, glm::ivec2 posiO) {
	if (wht < 20) {
		size = glm::ivec2(16, 16);
		posi = posiO;
	}
	else {
		size = glm::ivec2(32, 16);
		posi = posiO - glm::ivec2(8, 0);
	}
}