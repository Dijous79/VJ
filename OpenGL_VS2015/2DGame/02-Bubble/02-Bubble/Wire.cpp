#include "Wire.h"

enum WireAnims {
	Moving, Nothing
};

void Wire::init(const glm::ivec2& tileMapPos, glm::ivec2 posiO, ShaderProgram& shaderProgram) {
	size = glm::ivec2(8, 8 * 24);
	boxSize = 8 * 4;
	posi = posiO;
	cd = 1;
	tileMapDispl = tileMapPos;
	spritesheet.loadFromFile("images/StdWire.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(size, glm::vec2(1.0 / 70, 1.0 / 1.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);


	sprite->setAnimationSpeed(Moving, 60);
	for (int i = 0; i < 70; ++i)
		sprite->addKeyframe(Moving, glm::vec2(float(i) / 70.0, 0));

	sprite->setAnimationSpeed(Nothing, 0);
	sprite->addKeyframe(Nothing, glm::vec2(0, 1.0f / 2.0));

	sprite->changeAnimation(Moving);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posi.x), float(tileMapDispl.y + posi.y)));
}

void Wire::update(int deltaTime) {
	sprite->update(deltaTime);
	if (cd < 4) {
		posi.y -= 2;
		boxSize += 2;
		cd++;
	}
	else {
		cd = 0;
		posi.y -= 3;
		boxSize += 3;
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posi.x), float(tileMapDispl.y + posi.y)));
}

void Wire::destroy() {
	
}

glm::vec2 Wire::topHitBox() {
	glm::vec2 res = glm::vec2(0, 0);
	res.x = posi.x / 8;
	res.y = posi.y / 8;
	return res;
}