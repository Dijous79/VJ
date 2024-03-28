#include <iostream>
#include "Menu.h"
  
void Menu::init() {
	initShaders();

	wallaperImage.loadFromFile("images/MainMenuWallaper.png", TEXTURE_PIXEL_FORMAT_RGBA);
	screenWallaper = Sprite::createSprite(glm::ivec2(8 * 48, 8 * 30), glm::vec2(1.0, 1.0), &wallaperImage, &texProgram);
	screenWallaper->setNumberAnimations(1);
	screenWallaper->setAnimationSpeed(0, 1);
	screenWallaper->addKeyframe(0, glm::vec2(0.0, 0.0));
	screenWallaper->setPosition(glm::ivec2(0, 0));
	screenWallaper->changeAnimation(0);

	insertCoinImage.loadFromFile("images/BaseImageUi.png", TEXTURE_PIXEL_FORMAT_RGBA);
	insertCoinLabel = Sprite::createSprite(glm::ivec2(8 * 48 + 1, 8 * 4), glm::vec2(1.0, 1.0), &insertCoinImage, &texProgram);
	insertCoinLabel->setNumberAnimations(1);
	insertCoinLabel->setAnimationSpeed(0, 1);
	insertCoinLabel->addKeyframe(0, glm::vec2(0.0, 0.0));
	insertCoinLabel->setPosition(glm::ivec2(-1, 8 * 26));
	insertCoinLabel->changeAnimation(0);
}

void Menu::render() {
	screenWallaper->render();
}

void Menu::update(int deltaTime) {}

void Menu::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	printf("1\n");
	texProgram.init();
	printf("2\n");
	texProgram.addShader(vShader);
	printf("3\n");
	texProgram.addShader(fShader);
	printf("4\n");
	texProgram.link();
	printf("5\n");
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	printf("6\n");
	texProgram.bindFragmentOutput("outColor");
	printf("7\n");
	vShader.free();
	fShader.free();
}