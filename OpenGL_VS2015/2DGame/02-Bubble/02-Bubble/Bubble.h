#ifndef _BUBBLE_INCLUDE
#define _BUBBLE_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include <vector>

class Bubble
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int bubble, int Yini, bool dir);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	bool impacte(glm::ivec2 posCable);
	glm::ivec2 getPos();
	int getType();


private:
	bool jumping, first_jump;
	bool fwd;
	glm::ivec2 tileMapDispl, posBubble;
	int jump_x, colission_cooldown, Yini;
	glm::ivec2 tam_txt;
	glm::vec2 pos_txt, part_txt;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	vector<int> timers;
	vector<glm::ivec2> blocs;
	int bub;

	glm::vec2 getTextPosBubble(int type);
	void infoBubble(glm::ivec2* tam, glm::vec2* part, int type);

};


#endif
