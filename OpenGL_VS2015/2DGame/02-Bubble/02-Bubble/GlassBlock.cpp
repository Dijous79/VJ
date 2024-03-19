#include "GlassBlock.h"

enum GlassAnims {
	SH3, DH3, SH4, DH4
};

GlassAnims decode(glm::ivec2 sz, bool dynamic) {
	if (sz.x / 8 == 3) {
		if (dynamic)
			return DH3;
		else
			return SH3;
	}
	else if (sz.x / 8 == 4) {
		if (dynamic)
			return DH4;
		else
			return SH4;
	}

}

void GlassBlock::init(const glm::ivec2& tileMapPos, glm::ivec2 posiO, glm::ivec2 sizeObj, int col, ShaderProgram& shaderProgram) {
	size = sizeObj;
	posi = posiO;
	destroying = false;
	tileMapDispl = tileMapPos;
	spritesheet.loadFromFile("images/BreakingGlasses.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(size, glm::vec2((sizeObj.x / 8) / 19.0, (sizeObj.y / 8) / 13.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(SH4, 8);
	sprite->addKeyframe(SH4, glm::vec2(10.0 / 19.0, float(4 * col) / 13.0));

	sprite->setAnimationSpeed(SH3, 8);
	sprite->addKeyframe(SH3, glm::vec2(14.0 / 19.0, float(4 * col) / 13.0));

	sprite->setAnimationSpeed(DH4, 15);
	sprite->addKeyframe(DH4, glm::vec2(10.0 / 19.0, float(4.0 * col) / 13.0));
	sprite->addKeyframe(DH4, glm::vec2(10.0 / 19.0, float(4.0 * col + 1.0) / 13.0));
	sprite->addKeyframe(DH4, glm::vec2(10.0 / 19.0, float(4.0 * col + 2.0) / 13.0));
	sprite->addKeyframe(DH4, glm::vec2(10.0 / 19.0, float(4.0 * col + 3.0) / 13.0));
	sprite->addKeyframe(DH4, glm::vec2(4.0 * col / 19.0, 12.0 / 13.0));
	sprite->addKeyframe(DH4, glm::vec2(14.0 / 19.0, 12.0 / 13.0));

	sprite->setAnimationSpeed(DH3, 15);
	sprite->addKeyframe(DH3, glm::vec2(14.0 / 19.0, float(4.0 * col) / 13.0));
	sprite->addKeyframe(DH3, glm::vec2(14.0 / 19.0, float(4.0 * col + 1) / 13.0));
	sprite->addKeyframe(DH3, glm::vec2(14.0 / 19.0, float(4.0 * col + 2) / 13.0));
	sprite->addKeyframe(DH3, glm::vec2(14.0 / 19.0, float(4.0 * col + 3) / 13.0));
	sprite->addKeyframe(DH3, glm::vec2(3.0 * col + 8.0 / 19.0, 12.0 / 13.0));
	sprite->addKeyframe(DH3, glm::vec2(14.0 / 19.0, 12.0 / 13.0));

	sprite->changeAnimation(decode(size, false));
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posi.x), float(tileMapDispl.y + posi.y)));
}
void GlassBlock::update(int deltaTime) {
	sprite->update(deltaTime);
	if (destroying) {
		if (cdDestroy > 0) {
			cdDestroy--;
		}
		else
			sprite->setAnimationSpeed(decode(size, true), 0);
	}
}

void GlassBlock::destroy() {
	sprite->changeAnimation(decode(size, true));
	destroying = true;
	cdDestroy = 21;
}
