#include "Drops.h"
#include "Scene.h"

void Drops::setTileMap(TileMap* tileMap) {
	map = tileMap;
}

void Drops::setScene(Scene* sc) {
	scn = sc;
}

void Drops::update(int deltaTime) {
	sprite->update(deltaTime);
	posi.y += 2;
	map->collisionMoveDown(posi, size, &posi.y);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posi.x), float(tileMapDispl.y + posi.y)));
	cd--;
	if (cd < 120 && !dis) {
		sprite->changeAnimation(DISAPEARING);
		dis = true;
	}
}

bool Drops::disapear() { return cd < 0; }