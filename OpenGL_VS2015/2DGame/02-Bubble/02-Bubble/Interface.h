#ifndef _INTERFACE_INCLUDE
#define _INTERFACE_INCLUDE

#include "Sprite.h"

class Interface
{
public:
	Interface();
	void init(ShaderProgram& shaderProgram);
	//void update(int deltaTime);
	void render();
	void timeAct(int n);
	//void setLives();
	void gameOverText();
	void toggleReadyLabel();

private:
	void setTimeNumber(Sprite* tn, ShaderProgram& shaderProgram);

	int time;
	int lives;
	int bReady;
	Sprite* timeLabel;
	Sprite* gameOverLabel;
	Sprite* timeNumber1;
	Sprite* timeNumber2;
	Sprite* timeNumber3;
	Sprite* readyLabel;
	Texture timeImage, gameOverImage, timeNumbersImage, readyImage;
};

#endif
