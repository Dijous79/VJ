#include "Interface.h"

Interface::Interface() {}

void Interface::setTimeNumber(Sprite* tn, ShaderProgram& shaderProgram) {
	tn = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0, 1.0), &timeNumbersImage, &shaderProgram);
	tn->setNumberAnimations(10);
	tn->setAnimationSpeed(0, 1);
	tn->addKeyframe(0, glm::vec2(0.0, 0.0));
}

void Interface::init(ShaderProgram& shaderProgram) {
	timeImage.loadFromFile("images/timeLabel.png", TEXTURE_PIXEL_FORMAT_RGBA);
	timeLabel = Sprite::createSprite(glm::ivec2(8 * 8, 16), glm::vec2(1.0, 1.0), &timeImage, &shaderProgram);
	timeLabel->setNumberAnimations(1);
	timeLabel->setAnimationSpeed(0, 1);
	timeLabel->addKeyframe(0, glm::vec2(0.0, 0.0));
	timeLabel->setPosition(glm::ivec2(8 * 33, 9));
	timeLabel->changeAnimation(0);

	timeNumbersImage.loadFromFile("images/timeNumbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
	timeNumber1 = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.1, 1.0), &timeNumbersImage, &shaderProgram);
	timeNumber1->setNumberAnimations(10);
	timeNumber2 = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.1, 1.0), &timeNumbersImage, &shaderProgram);
	timeNumber2->setNumberAnimations(10);
	timeNumber3 = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.1, 1.0), &timeNumbersImage, &shaderProgram);
	timeNumber3->setNumberAnimations(10);
	for (int i = 0; i < 10; ++i) {
		printf("%d\n", i);
		timeNumber1->setAnimationSpeed(i, 1);
		timeNumber1->addKeyframe(i, glm::vec2(float(i) / 10.0, 0.0));
		timeNumber2->setAnimationSpeed(i, 1);
		timeNumber2->addKeyframe(i, glm::vec2(float(i) / 10.0, 0.0));
		timeNumber3->setAnimationSpeed(i, 1);
		timeNumber3->addKeyframe(i, glm::vec2(float(i) / 10.0, 0.0));
	}

	timeNumber1->setPosition(glm::ivec2(8 * 41, 9));
	timeNumber1->changeAnimation(1);
	timeNumber2->setPosition(glm::ivec2(8 * 43, 9));
	timeNumber2->changeAnimation(0);
	timeNumber3->setPosition(glm::ivec2(8 * 45, 9));
	timeNumber3->changeAnimation(0);

	gameOverImage.loadFromFile("images/gameOverLabel.png", TEXTURE_PIXEL_FORMAT_RGBA);
	gameOverLabel = Sprite::createSprite(glm::ivec2(8 * 17, 16), glm::vec2(1.0, 0.5), &gameOverImage, &shaderProgram);
	gameOverLabel->setNumberAnimations(2);
	gameOverLabel->setAnimationSpeed(0, 1);
	gameOverLabel->addKeyframe(0, glm::vec2(0.0, 0.5));
	gameOverLabel->setAnimationSpeed(1, 1);
	gameOverLabel->addKeyframe(1, glm::vec2(0.0, 0.0));
	gameOverLabel->setPosition(glm::ivec2(8 * 16, 8 * 12));
	gameOverLabel->changeAnimation(0);

	readyImage.loadFromFile("images/readyLabel.png", TEXTURE_PIXEL_FORMAT_RGBA);
	readyLabel = Sprite::createSprite(glm::ivec2(8 * 7, 16), glm::vec2(1.0, 0.5), &readyImage, &shaderProgram);
	readyLabel->setNumberAnimations(2);
	readyLabel->setAnimationSpeed(0, 1);
	readyLabel->addKeyframe(0, glm::vec2(0.0, 0.5));
	readyLabel->setAnimationSpeed(1, 1);
	readyLabel->addKeyframe(1, glm::vec2(0.0, 0.0));
	readyLabel->setPosition(glm::ivec2(8 * 20, 8 * 12));
	readyLabel->changeAnimation(1);
	bReady = true;
}

void Interface::render() {
	timeLabel->render();
	timeNumber1->render();
	timeNumber2->render();
	timeNumber3->render();
	gameOverLabel->render();
	readyLabel->render();
}

void Interface::timeAct(int n) {
	if (n < 100) {
		timeNumber1->changeAnimation(0);
		timeNumber2->changeAnimation(n / 10);
		timeNumber3->changeAnimation(n % 10);
	}
}

void Interface::gameOverText() {
	gameOverLabel->changeAnimation(1);
}

void Interface::toggleReadyLabel() {
	if (bReady) {
		readyLabel->changeAnimation(0);
		bReady = false;
	}
	else {
		readyLabel->changeAnimation(1);
		bReady = true;
	}
}