#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"
#include "GlassBlock.h"


using namespace std;


TileMap* TileMap::createTileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program)
{
	TileMap* map = new TileMap(levelFile, minCoords, program);

	return map;
}


TileMap::TileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	if (map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * nTiles);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string& levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);

	map = new char[mapSize.x * mapSize.y];
	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			fin.get(tile);
			if (tile == ' ')
				map[j * mapSize.x + i] = 0;
			else
				map[j * mapSize.x + i] = tile;
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();

	return true;
}



void TileMap::prepareArrays(const glm::vec2& minCoords, ShaderProgram& program)
{
	char tile;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;

	nTiles = 0;
	halfTexel = glm::vec2(0.125f / tilesheet.width(), 0.125f / tilesheet.height());
	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if (tile != '\0')
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				glm::vec2 aux = decodeMap(tile);
				texCoordTile[0] = glm::vec2(aux.y, aux.x);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		char aux = map[y * mapSize.x + x];
		if (aux != '\0' && aux != 'v' && aux != 'b' && aux != 'n' && aux != 'V' && aux != 'B' && aux != 'N')
			return true;
		///////////////mirem si hi ha objectes dinamics solids/////////
		for (auto it = (*objs).begin(); it != (*objs).end(); ++it) {
			glm::ivec2 posA = (*it)->posObj();
			glm::ivec2 sizeA = (*it)->sizeObj();
			int xe = posA.x / tileSize;
			int yt = posA.y / tileSize;
			int yb = yt + sizeA.y / tileSize;
			if (y <= yb && y >= yt && x == xe)
				return true;
		}
	}

	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = (pos.x + size.x) / tileSize - 1;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		char aux = map[y * mapSize.x + x];
		if (aux != '\0' && aux != 'v' && aux != 'b' && aux != 'n' && aux != 'V' && aux != 'B' && aux != 'N')
			return true;
		///////////////mirem si hi ha objectes dinamics solids/////////
		for (auto it = (*objs).begin(); it != (*objs).end(); ++it) {
			glm::ivec2 posA = (*it)->posObj();
			glm::ivec2 sizeA = (*it)->sizeObj();
			int xe = posA.x / tileSize;
			int yt = posA.y / tileSize;
			int yb = yt + sizeA.y / tileSize;
			if (y <= yb && y >= yt && x == xe)
				return true;
		}
	}

	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0, x1, y;

	x0 = (pos.x + (5 *size.x / 16)) / tileSize;
	x1 = x0 + (11 * size.x / 16) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		///////////////mirem si hi ha objectes solids de tilemap/////////
		char aux = map[y * mapSize.x + x];
		if (aux != '\0' && aux != 'v' && aux != 'b' && aux != 'n')
		{
			if (*posY - tileSize * y + size.y <= 4)
			{
				*posY = tileSize * y - size.y;
				return true;
			}
		}
		///////////////mirem si hi ha objectes dinamics solids/////////
		for (auto it = (*objs).begin(); it != (*objs).end(); ++it) {
			glm::ivec2 posA = (*it)->posObj();
			glm::ivec2 sizeA = (*it)->sizeObj();
			int xe = posA.x / tileSize;
			int xd = xe + size.x / tileSize;
			int ya = posA.y / tileSize;
			if (x >= xe && x <= xd && y == ya) {
				if (*posY - tileSize * y + size.y <= 4)
				{
					*posY = tileSize * y - size.y;
					return true;
				}
			}
		}
	}

	return false;
}

bool TileMap::inLadder(const glm::ivec2& pos, const glm::ivec2& size) const {
	int x, y0, y1;
	x = (pos.x + size.x/2) / tileSize;
	float posiO = pos.y / float(tileSize);
	y0 = (pos.y + (size.y / 2))/ tileSize;
	y1 = y0 + 1;
	for (int y = y0; y <= y1; y++)
	{
		char aux = map[y * mapSize.x + x];
		printf("%d -> %c\n", y, aux);
		if (aux == 'b' || aux == 'B' || aux == 'Q')
			return true;
	}
	return false;
}

bool TileMap::onLadder(const glm::ivec2& pos, const glm::ivec2& size) const {
	int x0, x1, y;

	x0 = pos.x / tileSize + 1;
	x1 = x0 + 1;
	y = (pos.y + size.y) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		char aux = map[y * mapSize.x + x];
		if (aux == 'b' || aux == 'B' || aux == 'Q')
		{
			return true;
		}
			
	}
	return false;
}

bool TileMap::underLadder(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const {
	int x, y;

	x = (pos.x + size.x/2) / tileSize;
	float posiO = pos.y / float(tileSize) + 2;
	y = (pos.y + size.y) / tileSize;
	
	char aux = map[y * mapSize.x + x];

	printf("%c\n", aux);
	if (aux != 'b' && aux != '\0')
	{
		*posY = tileSize * y - size.y;
		return true;
	}
	return false;
}

void TileMap::closestLadder(const glm::ivec2& pos, const glm::ivec2& size, int* posX, int* posY) const {
	int x0, x1, y0, y1;
	bool mogut = false;
	x0 = pos.x / tileSize + 1;
	x1 = x0 + 1;
	float posiO = pos.y / float(tileSize);
	y0 = pos.y / tileSize;
	if (floor(posiO) != posiO)
		y0 += 1;
	y1 = y0 + size.y / tileSize;
	for (int x = x0; x <= x1; ++x) {
		for (int y = y0; y <= y1; y++)
		{
			
			char aux = map[y * mapSize.x + x];
			if (aux == 'b' || aux == 'B' || aux == 'Q') { // centre d'escala
				*posX = tileSize * (float(x) - 1.5f);
				mogut = true;
			}
			if (aux == 'B' || aux == 'Q') { // centre de top ladder
				//*posY = tileSize * y - size.y / 2;
				mogut = true;
			}
			if (mogut)
				return;
		}
	}
}

void TileMap::setGbS(std::set<GlassBlock*>* dObj) {
	objs = dObj;
}


char TileMap::wahtTile(glm::vec2 tile) {
	char aux = map[static_cast<int>(tile.y) * static_cast<int>(mapSize.x) + static_cast<int>(tile.x)];
	return aux;
}

glm::vec2 TileMap::decodeMap(char l) {
	switch (l) {
	case '1':
		return glm::vec2(0.0, 0.0);
		break;
	case '2':
		return glm::vec2(0.0, 0.125);
		break;
	case '3':
		return glm::vec2(0.0, 0.25);
		break;
	case '4':
		return glm::vec2(0.0, 0.375);
		break;
	case '5':
		return glm::vec2(0.0, 0.5);
		break;
	case '6':
		return glm::vec2(0.0, 0.625);
		break;
	case '7':
		return glm::vec2(0.0, 0.75);
		break;
	case '8':
		return glm::vec2(0.0, 0.875);
		break;
	case 'M':
		return glm::vec2(0.5, 0.75);
		break;
	case 'Q':
		return glm::vec2(0.625, 0.75);
		break;
	case 'W':
		return glm::vec2(0.5, 0.875);
		break;
	case 'r':
		return glm::vec2(0.125, 0.5);
		break;
	case 't':
		return glm::vec2(0.125, 0.625);
		break;
	case 'y':
		return glm::vec2(0.125, 0.75);
		break;
	case 'u':
		return glm::vec2(0.125, 0.875);
		break;
	case 'R':
		return glm::vec2(0.0, 0.5);
		break;
	case 'T':
		return glm::vec2(0.0, 0.625);
		break;
	case 'Y':
		return glm::vec2(0.0, 0.75);
		break;
	case 'U':
		return glm::vec2(0.0, 0.875);
		break;
	case 'i':
		return glm::vec2(0.25, 0.0);
		break;
	case 'o':
		return glm::vec2(0.25, 0.125);
		break;
	case 'p':
		return glm::vec2(0.25, 0.25);
		break;
	case 'a':
		return glm::vec2(0.25, 0.375);
		break;
	case 'I':
		return glm::vec2(0.5, 0.5);
		break;
	case 'O':
		return glm::vec2(0.5, 0.625);
		break;
	case 'P':
		return glm::vec2(0.5, 0.75);
		break;
	case 'A':
		return glm::vec2(0.5, 0.875);
		break;
	case 's':
		return glm::vec2(0.25, 0.5);
		break;
	case 'd':
		return glm::vec2(0.25, 0.625);
		break;
	case 'f':
		return glm::vec2(0.25, 0.75);
		break;
	case 'g':
		return glm::vec2(0.25, 0.875);
		break;
	case 'S':
		return glm::vec2(0.125, 0.5);
		break;
	case 'D':
		return glm::vec2(0.125, 0.625);
		break;
	case 'F':
		return glm::vec2(0.125, 0.75);
		break;
	case 'G':
		return glm::vec2(0.125, 0.875);
		break;
	case 'h':
		return glm::vec2(0.375, 0.0);
		break;
	case 'j':
		return glm::vec2(0.375, 0.125);
		break;
	case 'k':
		return glm::vec2(0.375, 0.25);
		break;
	case 'l':
		return glm::vec2(0.375, 0.375);
		break;
	case 'H':
		return glm::vec2(0.625, 0.5);
		break;
	case 'J':
		return glm::vec2(0.625, 0.625);
		break;
	case 'K':
		return glm::vec2(0.625, 0.75);
		break;
	case 'L':
		return glm::vec2(0.625, 0.875);
		break;
	case 'ñ':
		return glm::vec2(0.375, 0.5);
		break;
	case 'z':
		return glm::vec2(0.375, 0.625);
		break;
	case 'x':
		return glm::vec2(0.375, 0.75);
		break;
	case 'c':
		return glm::vec2(0.375, 0.875);
		break;
	case 'Ñ':
		return glm::vec2(0.25, 0.5);
		break;
	case 'Z':
		return glm::vec2(0.25, 0.625);
		break;
	case 'X':
		return glm::vec2(0.25, 0.75);
		break;
	case 'C':
		return glm::vec2(0.25, 0.875);
		break;
	case 'b':
		return glm::vec2(0.625, 0.875);
		break;
	case 'v':
		return glm::vec2(0.75, 0.875);
		break;
	case 'n':
		return glm::vec2(0.875, 0.875);
		break;
	case 'V':
		return glm::vec2(0.75, 0.875);
		break;
	case 'B':
		return glm::vec2(0.625, 0.875);
		break;
	case 'N':
		return glm::vec2(0.875, 0.875);
		break;

	}
}