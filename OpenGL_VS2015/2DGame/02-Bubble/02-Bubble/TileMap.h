#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include <set>
#include <vector>
#include "Texture.h"
#include "ShaderProgram.h"


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.

class GlassBlock;

class TileMap
{

private:
	TileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program);

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap* createTileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program);

	~TileMap();

	void render() const;
	void free();

	int getTileSize() const { return tileSize; }

	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	bool inLadder(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool onLadder(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool underLadder(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	void closestLadder(const glm::ivec2& pos, const glm::ivec2& size, int* posX, int* posY) const;
	void setGbS(std::set<GlassBlock*>* dObj);
	char wahtTile(glm::vec2 tile);
	vector<glm::ivec2> getDownTilePos(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool circleRect(int cx, int cy, int radius, int rx, int ry, int rw, int rh, int* posY, bool move);

private:
	bool loadLevel(const string& levelFile);
	void prepareArrays(const glm::vec2& minCoords, ShaderProgram& program);
	glm::vec2 decodeMap(char l);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	int nTiles;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	char* map;
	std::set<GlassBlock*>* objs;

};


#endif // _TILE_MAP_INCLUDE


