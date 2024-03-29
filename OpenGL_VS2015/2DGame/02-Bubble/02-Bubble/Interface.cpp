#include "Interface.h"

Interface::Interface() {}

void Interface::setTimeNumber(Sprite* tn, ShaderProgram& shaderProgram) {
	tn = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0, 1.0), &timeNumbersImage, &shaderProgram);
	tn->setNumberAnimations(10);
	tn->setAnimationSpeed(0, 1);
	tn->addKeyframe(0, glm::vec2(0.0, 0.0));
}

void Interface::init(ShaderProgram& shaderProgram, int city) {
	cdAnimInsertCoin = 20;
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

	panelBase.loadFromFile("images/BaseImageUi.png", TEXTURE_PIXEL_FORMAT_RGBA);
	baseInfoPanel = Sprite::createSprite(glm::ivec2(8 * 48 + 1, 8 * 4), glm::vec2(1.0, 1.0), &panelBase, &shaderProgram);
	baseInfoPanel->setNumberAnimations(1);
	baseInfoPanel->setAnimationSpeed(0, 1);
	baseInfoPanel->addKeyframe(0, glm::vec2(0.0, 0.0));
	baseInfoPanel->setPosition(glm::ivec2(-1, 8 * 26));
	baseInfoPanel->changeAnimation(0);

	insertCoinImage.loadFromFile("images/insertCoin.png", TEXTURE_PIXEL_FORMAT_RGBA);
	insertCoinLabel = Sprite::createSprite(glm::ivec2(8 * 12, 8), glm::vec2(1.0, 0.5), &insertCoinImage, &shaderProgram);
	insertCoinLabel->setNumberAnimations(2);
	insertCoinLabel->setAnimationSpeed(0, 1);
	insertCoinLabel->addKeyframe(0, glm::vec2(0.0, 0.5));
	insertCoinLabel->setAnimationSpeed(1, 1);
	insertCoinLabel->addKeyframe(1, glm::vec2(0.0, 0.0));
	insertCoinLabel->setPosition(glm::ivec2(8 * 34, 8 * 28));
	insertCoinLabel->changeAnimation(1);
	bInsertCoin = true;

	citiesNameImage.loadFromFile("images/cities.png", TEXTURE_PIXEL_FORMAT_RGBA);
	cityLabel = Sprite::createSprite(glm::ivec2(8 * 10, 9), glm::vec2(1.0, 1.0 / 3.0), &citiesNameImage, &shaderProgram);
	cityLabel->setNumberAnimations(3);
	cityLabel->setAnimationSpeed(0, 1);
	cityLabel->addKeyframe(0, glm::vec2(0.0, 0.0));
	cityLabel->setAnimationSpeed(2, 1);
	cityLabel->addKeyframe(2, glm::vec2(0.0, 1.0 / 3.0));
	cityLabel->setAnimationSpeed(1, 1);
	cityLabel->addKeyframe(1, glm::vec2(0.0, 2.0 / 3.0));
	cityLabel->setPosition(glm::ivec2(8 * 19, 8 * 26));
	cityLabel->changeAnimation(city);

	stageImage.loadFromFile("images/whatStage.png", TEXTURE_PIXEL_FORMAT_RGBA);
	stageLabel = Sprite::createSprite(glm::ivec2(8 * 9, 9), glm::vec2(1.0, 1.0 / 3.0), &stageImage, &shaderProgram);
	stageLabel->setNumberAnimations(3);
	stageLabel->setAnimationSpeed(0, 1);
	stageLabel->addKeyframe(0, glm::vec2(0.0, 0.0));
	stageLabel->setAnimationSpeed(2, 1);
	stageLabel->addKeyframe(2, glm::vec2(0.0, 2.0 / 3.0));
	stageLabel->setAnimationSpeed(1, 1);
	stageLabel->addKeyframe(1, glm::vec2(0.0, 1.0 / 3.0));
	stageLabel->setPosition(glm::ivec2(8 * 19, 8 * 28));
	stageLabel->changeAnimation(city);

	scoreNumbersImage.loadFromFile("images/scoreNumbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
	scoreLabel = *(new vector<Sprite*>(8));
	for (int i = 0; i < 8; ++i) {
		scoreLabel[i] = Sprite::createSprite(glm::ivec2(8, 9), glm::vec2(1.0 / 11.0, 1.0), &scoreNumbersImage, &shaderProgram);
		scoreLabel[i]->setNumberAnimations(11);
		for (int j = 0; j < 11; ++j) {
			scoreLabel[i]->setAnimationSpeed(j, 1);
			scoreLabel[i]->addKeyframe(j, glm::vec2(float(j) / 11.0, 0.0));
		}
		scoreLabel[i]->setPosition(glm::ivec2(8 * (15 - i), 8 * 27));
		scoreLabel[i]->changeAnimation(10);
	}
	scoreLabel[0]->changeAnimation(0);

	livesImage.loadFromFile("images/character.png", TEXTURE_PIXEL_FORMAT_RGBA);
	liveslabel = *(new vector<Sprite*>(3));
	for (int i = 0; i < 3; ++i) {
		liveslabel[i] = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.1, 1.0 / 12.0), &livesImage, &shaderProgram);
		liveslabel[i]->setNumberAnimations(1);
		liveslabel[i]->addKeyframe(0, glm::vec2(0.8, 8.0 / 12.0));
		liveslabel[i]->setPosition(glm::ivec2(16 * (1 + i), 8 * 28));
		liveslabel[i]->changeAnimation(0);
	}

	doubleShotImage.loadFromFile("images/doubleShotUi.png", TEXTURE_PIXEL_FORMAT_RGBA);
	doubleShot = Sprite::createSprite(glm::ivec2(8 * 2, 8 * 2), glm::vec2(1.0, 1.0), &doubleShotImage, &shaderProgram);
	doubleShot->setNumberAnimations(1);
	doubleShot->setAnimationSpeed(0, 1);
	doubleShot->addKeyframe(0, glm::vec2(0.0, 0.0));
	doubleShot->setPosition(glm::ivec2(8 * 14, 8 * 28));
	doubleShot->changeAnimation(0);

	bDoubleShot = false;

}

void Interface::update(int deltaTime) {
	if (cdAnimInsertCoin > 0)
		cdAnimInsertCoin--;
	else {
		cdAnimInsertCoin = 20;
		if (bInsertCoin) {
			bInsertCoin = false;
			insertCoinLabel->changeAnimation(0);
		}
		else {
			bInsertCoin = true;
			insertCoinLabel->changeAnimation(1);
		}
	}
}

void Interface::render() {
	baseInfoPanel->render();
	insertCoinLabel->render();
	cityLabel->render();
	stageLabel->render();
	if (bDoubleShot)
		doubleShot->render();
	for (int i = 0; i < 6; ++i)
		scoreLabel[i]->render();
	for (int i = 0; i < lives; ++i)
		liveslabel[i]->render();
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

void Interface::setScore(int n) {
	for (int i = 0; i < scoreLabel.size(); ++i) {
		if (n > 0) {
			scoreLabel[i]->changeAnimation(n % 10);
			n /= 10;
		}
		else
			scoreLabel[i]->changeAnimation(10);
	}
}

void Interface::setLives(int v) {
	lives = v;
}

void Interface::actDoubleShot() {
	bDoubleShot = true;
}