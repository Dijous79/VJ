#pragma once
#include "Drops.h"
class PowerUp : public Drops
{
	void init(const glm::ivec2& tileMapPos, glm::ivec2 posiO, ShaderProgram& shaderProgram) override;
};

