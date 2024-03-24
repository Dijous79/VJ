#pragma once
#include "Drops.h"
class Food : public Drops
{
public:
	void init(const glm::ivec2& tileMapPos, glm::ivec2 posiO, ShaderProgram& shaderProgram, int pwu) override;
	void destroy();

private:
	void setPosSize(int wht, glm::ivec2 posiO);
};

