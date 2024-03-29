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
	void setLives(int v);
	void setScore(int i);
	void gameOverText();
	void toggleReadyLabel();
	void actDoubleShot();

private:
	void setTimeNumber(Sprite* tn, ShaderProgram& shaderProgram);

	int time;
	int lives;
	bool bReady, bInsertCoin, bDoubleShot;
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
	Sprite* stageLabel;
	Sprite* doubleShot;
	vector<Sprite*> scoreLabel;
	vector<Sprite*> liveslabel;
	Texture timeImage, gameOverImage, timeNumbersImage, readyImage, panelBase, insertCoinImage, citiesNameImage, scoreNumbersImage, livesImage, stageImage, doubleShotImage;
};

#endif
