#ifndef _INTERFACE_INCLUDE
#define _INTERFACE_INCLUDE

#include "Sprite.h"
#include <vector>

class Interface
{
public:
	Interface();
	void init(ShaderProgram& shaderProgram, int city);
	void update(int deltaTime);
	void render();
	void timeAct(int n);
	//void setLives();
	void setScore(int i);
	void gameOverText();
	void toggleReadyLabel();

private:
	void setTimeNumber(Sprite* tn, ShaderProgram& shaderProgram);

	int time;
	int lives;
	bool bReady, bInsertCoin;
	int cdAnimInsertCoin;
	Sprite* timeLabel;
	Sprite* gameOverLabel;
	Sprite* timeNumber1;
	Sprite* timeNumber2;
	Sprite* timeNumber3;
	Sprite* readyLabel;
	Sprite* baseInfoPanel;
	Sprite* insertCoinLabel;
	Sprite* cityLabel;
	vector<Sprite*> scoreLabel;
	Texture timeImage, gameOverImage, timeNumbersImage, readyImage, panelBase, insertCoinImage, citiesNameImage, scoreNumbersImage;
};

#endif
