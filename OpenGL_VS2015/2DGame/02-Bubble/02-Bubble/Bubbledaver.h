#ifndef _BUBBLEDAVER_INCLUDE
#define _BUBBLEDAVER_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <vector>

class BubbleDaver {
public:
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int bubble);
	void update(int deltaTime);
	void render();
	void setPosition(const glm::vec2& pos);
	void setTileMap(TileMap* tileMap);
	bool check();

private:
    glm::vec2 getTextPosBubble(int type);
    void infoBubble(glm::ivec2* tam, glm::vec2* part, int type);
	glm::ivec2 tileMapDispl, posBubble;
	glm::ivec2 tam_txt;
	glm::vec2 pos_txt, part_txt;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int bub,cont;

};

#endif
