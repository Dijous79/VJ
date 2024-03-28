#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "Sprite.h"

class Menu
{
public:
	void init();
	void render();
	void update(int deltaTime);

private:
	void initShaders();

	Sprite* screenWallaper;
	Sprite* insertCoinLabel;
	Texture wallaperImage, insertCoinImage;
	ShaderProgram texProgram;
};

#endif