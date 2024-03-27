#pragma once
#include "Drops.h"
class PowerUp : public Drops
{
public:
	void init(const glm::ivec2& tileMapPos, glm::ivec2 posiO, ShaderProgram& shaderProgram, int pwu) override;
	void destroy();
};

