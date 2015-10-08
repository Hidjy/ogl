#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>

#include "Chunk.hpp"
#include "Renderer.hpp"

Chunk::Chunk() : _pos(glm::vec3(0, 0, 0)), _empty(false), _loaded(false), _setup(false), _needRebuild(false) //FIXME
{
	_blocks = new Block**[SIZE];
	for(int i = 0; i < SIZE; i++)
	{
		_blocks[i] = new Block*[SIZE];

		for(int j = 0; j < SIZE; j++)
		{
			_blocks[i][j] = new Block[SIZE];
		}
	}
	_mesh.setMode(GL_TRIANGLES);
}

Chunk::Chunk(Chunk const &src) : Chunk() {
	_pos = src.getPos();
	_empty = src.empty();
	for (size_t x = 0; x < SIZE; x++) {
		for (size_t y = 0; y < SIZE; y++) {
			for (size_t z = 0; z < SIZE; z++) {
				_blocks[x][y][z] = src.getBlock(x, y, z);
			}
		}
	}
}

Chunk::~Chunk()
{
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			delete [] _blocks[i][j];
		}

		delete [] _blocks[i];
	}
	delete [] _blocks;
}

bool	Chunk::empty() const {
	return _empty;
}

bool		Chunk::isLoaded() const {
	return _loaded;
}

bool		Chunk::isSetup() const {
	return _setup;
}

bool		Chunk::needRebuild() const {
	return _setup;
}

glm::vec3	Chunk::getPos() const {
	return _pos;
}

Block 	Chunk::getBlock(int x, int y, int z) const {
	return _blocks[x][y][z];
}

Block 	&Chunk::getBlock(int x, int y, int z) {
	_needRebuild = true;
	return _blocks[x][y][z];
}

void	Chunk::setPos(glm::vec3 pos) {
	_pos = pos;
}

void	Chunk::setBlock(int x, int y, int z, Block block) {
	if (block.isActive() and not _blocks[x][y][z].isActive())
		_blockCount++;
	else if (not block.isActive() and _blocks[x][y][z].isActive())
		_blockCount--;
	_empty = (_blockCount == 0);
	_needRebuild = true;

	_blocks[x][y][z] = block;
}

GLuint	Chunk::countBlocks()
{
	_blockCount = 0;
	for (int x = 0; x < Chunk::SIZE; x++) {
		for (int y = 0; y < Chunk::SIZE; y++) {
			for (int z = 0; z < Chunk::SIZE; z++) {
				if (_blocks[x][y][z].isActive()) {
					_blockCount++;
				}
			}
		}
	}
	_empty = (_blockCount == 0);
	return _blockCount;
}

static void getRGBA(int type, float &r, float &g, float &b, float &a)
{
	float color[] = {1.0f, 0.5f, 0.2f, 0.0f};
	r = color[type];
	g = 1.0f - color[type];
	b = 0.5f + color[type] * 2.0f;
	a = 1.0f;
}

// template <typename T>
static void multipush(std::vector<float> &target, std::vector<float> src)
{
	for (auto it = src.begin(); it != src.end(); ++it)
		target.push_back(*it);
}

void	Chunk::generateMesh() {
	_needRebuild = false;

	if (_empty)
		return;

	std::vector<GLfloat> vertices;

	for (int x = 0; x < Chunk::SIZE; x++) {
		for (int y = 0; y < Chunk::SIZE; y++) {
			for (int z = 0; z < Chunk::SIZE; z++) {
				Block current = _blocks[x][y][z];
				if (current.isActive()) {
					float vx, vy, vz, r, g, b, a;
					vx = static_cast<float>(x);
					vy = static_cast<float>(y);
					vz = static_cast<float>(z);
					getRGBA(current.getType() - 1, r, g, b, a);
					if (x == 0 or not _blocks[x - 1][y][z].isActive()) {
						multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 0.0f, r, g, b, a});
						multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 1.0f, r, g, b, a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, r, g, b, a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, r, g, b, a});
						multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 1.0f, r, g, b, a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 1.0f, r, g, b, a});
					}
					if (y == 0 or not _blocks[x][y - 1][z].isActive()) {
						multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 0.0f, r, g, b, a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, r, g, b, a});
						multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 1.0f, r, g, b, a});
						multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 0.0f, r, g, b, a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 0.0f, r, g, b, a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, r, g, b, a});
					}
					if (z == 0 or not _blocks[x][y][z - 1].isActive()) {
						multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 0.0f, r, g, b, a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, r, g, b, a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 0.0f, r, g, b, a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 0.0f, r, g, b, a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, r, g, b, a});
						multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 0.0f, r, g, b, a});
					}
					if (x == Chunk::SIZE - 1 or not _blocks[x + 1][y][z].isActive()) {
						multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 1.0f, r, g, b, a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, r, g, b, a});
						multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 0.0f, r, g, b, a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 0.0f, r, g, b, a});
						multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 0.0f, r, g, b, a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, r, g, b, a});
					}
					if (y == Chunk::SIZE - 1 or not _blocks[x][y + 1][z].isActive()) {
						multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 1.0f, r, g, b, a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, r, g, b, a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 1.0f, r, g, b, a});
						multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 1.0f, r, g, b, a});
						multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 0.0f, r, g, b, a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, r, g, b, a});
					}
					if (z == Chunk::SIZE - 1 or not _blocks[x][y][z + 1].isActive()) {
						multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 1.0f, r, g, b, a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 1.0f, r, g, b, a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, r, g, b, a});
						multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 1.0f, r, g, b, a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, r, g, b, a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 1.0f, r, g, b, a});
					}
				}
			}
		}
	}

	GLfloat *tmp = _mesh.getVertexBuffer();
	if (tmp != nullptr)
		delete tmp;

	GLuint vertexBufferSize = vertices.size();
	GLfloat *vertexBuffer = new GLfloat[vertexBufferSize];

	int i = 0;
	for (auto it = vertices.begin() ; it != vertices.end() ; ++it) {
		vertexBuffer[i++] = *it;
	}

	_mesh.setVertexBuffer(vertexBuffer, vertexBufferSize);
}

void	Chunk::render(Renderer *renderer) {
	if (_empty)
		return;
	_mesh.render(renderer);
}

void	Chunk::load() {
	_loaded = true;
}

void	Chunk::unload() {
	_loaded = false;
	_needRebuild = false;
}

void	Chunk::setup() {
	generateMesh();
	_setup = true;
}


Chunk	&Chunk::operator=(Chunk const &src) {
	_pos = src.getPos();
	_empty = src.empty();

	for (size_t x = 0; x < SIZE; x++) {
		for (size_t y = 0; y < SIZE; y++) {
			for (size_t z = 0; z < SIZE; z++) {
				_blocks[x][y][z] = src.getBlock(x, y, z);
			}
		}
	}

	return *this;
}
