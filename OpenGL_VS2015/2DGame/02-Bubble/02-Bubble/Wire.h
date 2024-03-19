#pragma once
#include "DynamicObj.h"
class Wire : public DynamicObj
{
public:
	void init(const glm::ivec2& tileMapPos, glm::ivec2 posiO, ShaderProgram& shaderProgram) override;
	void update(int deltaTime) override;
	void destroy() override;
	glm::vec2 topHitBox();
private:
	int boxSize;
	int cd;
};

