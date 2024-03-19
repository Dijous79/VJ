#include "DynamicObj.h"

DynamicObj::DynamicObj() {}

void DynamicObj::init(const glm::ivec2& tileMapPos, glm::ivec2 posiO, glm::ivec2 sizeObj, int col, ShaderProgram& shaderProgram) {}

void DynamicObj::init(const glm::ivec2& tileMapPos, glm::ivec2 posiO, ShaderProgram& shaderProgram) {}


void DynamicObj::update(int deltaTime) {}

void DynamicObj::destroy() {}

void DynamicObj::render() {
	sprite->render();
}

void DynamicObj::setTileMap(TileMap* tileMap) {
	map = tileMap;
}

glm::ivec2 DynamicObj::posObj() {
	return posi;
}

glm::ivec2 DynamicObj::sizeObj() {
	return size;
}
