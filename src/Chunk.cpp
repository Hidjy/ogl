#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>

#include "Chunk.hpp"
#include "Renderer.hpp"
#include "BlockType.hpp"
#include "Color.hpp"

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

template <typename T>
static void multipush(std::vector<T> &target, std::vector<T> src)
{
	for (auto it = src.begin(); it != src.end(); ++it)
		target.push_back(*it);
}

#define AO_COEFF 0.9f

void	Chunk::generateMesh() {
	_needRebuild = false;

	if (_empty)
		return;

	// Glfloat points[][] = {
	// 	{.0f, .0f, .0f},
	// 	{.0f, .0f, .0f},
	// 	{.0f, .0f, .0f},
	// 	{.0f, .0f, .0f},
	// 	{.0f, .0f, .0f},
	// 	{.0f, .0f, .0f},
	// 	{.0f, .0f, .0f},
	// 	{.0f, .0f, .0f}
	// };

	std::vector<GLfloat> vertices;

	for (int x = 0; x < Chunk::SIZE; x++) {
		for (int y = 0; y < Chunk::SIZE; y++) {
			for (int z = 0; z < Chunk::SIZE; z++) {
				Block current = _blocks[x][y][z];
				if (current.isActive()) {
					float vx, vy, vz;
					vx = static_cast<float>(x);
					vy = static_cast<float>(y);
					vz = static_cast<float>(z);
					Color c = current.getType()->getColor();

					GLfloat ao[8] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

					if (y > 0 and z > 0 and _blocks[x][y - 1][z - 1].isActive()) {
						ao[0] *= AO_COEFF;
						ao[4] *= AO_COEFF;
					}
					if (y > 0 and x < Chunk::SIZE - 1 and _blocks[x + 1][y - 1][z].isActive()) {
						ao[4] *= AO_COEFF;
						ao[5] *= AO_COEFF;
					}
					if (y > 0 and z < Chunk::SIZE - 1 and _blocks[x][y - 1][z + 1].isActive()) {
						ao[1] *= AO_COEFF;
						ao[5] *= AO_COEFF;
					}
					if (y > 0 and x > 0 and _blocks[x - 1][y - 1][z].isActive()) {
						ao[0] *= AO_COEFF;
						ao[1] *= AO_COEFF;
					}

					if (y < Chunk::SIZE - 1 and z > 0 and _blocks[x][y + 1][z - 1].isActive()) {
						ao[2] *= AO_COEFF;
						ao[6] *= AO_COEFF;
					}
					if (y < Chunk::SIZE - 1 and x < Chunk::SIZE - 1 and _blocks[x + 1][y + 1][z].isActive()) {
						ao[6] *= AO_COEFF;
						ao[7] *= AO_COEFF;
					}
					if (y < Chunk::SIZE - 1 and z < Chunk::SIZE - 1 and _blocks[x][y + 1][z + 1].isActive()) {
						ao[3] *= AO_COEFF;
						ao[7] *= AO_COEFF;
					}
					if (y < Chunk::SIZE - 1 and x > 0 and _blocks[x - 1][y + 1][z].isActive()) {
						ao[2] *= AO_COEFF;
						ao[3] *= AO_COEFF;
					}

					if (x > 0 and y > 0 and z > 0 and _blocks[x - 1][y - 1][z - 1].isActive())
						ao[0] *= AO_COEFF;
					if (x > 0 and y > 0 and z < Chunk::SIZE - 1 and _blocks[x - 1][y - 1][z + 1].isActive())
						ao[1] *= AO_COEFF;
					if (x > 0 and y < Chunk::SIZE - 1 and z > 0 and _blocks[x - 1][y + 1][z - 1].isActive())
						ao[2] *= AO_COEFF;
					if (x > 0 and y < Chunk::SIZE - 1 and z < Chunk::SIZE - 1 and _blocks[x - 1][y + 1][z + 1].isActive())
						ao[3] *= AO_COEFF;
					if (x < Chunk::SIZE - 1 and y > 0 and z > 0 and _blocks[x + 1][y - 1][z - 1].isActive())
						ao[4] *= AO_COEFF;
					if (x < Chunk::SIZE - 1 and y > 0 and z < Chunk::SIZE - 1 and _blocks[x + 1][y - 1][z + 1].isActive())
						ao[5] *= AO_COEFF;
					if (x < Chunk::SIZE - 1 and y < Chunk::SIZE - 1 and z > 0 and _blocks[x + 1][y + 1][z - 1].isActive())
						ao[6] *= AO_COEFF;
					if (x < Chunk::SIZE - 1 and y < Chunk::SIZE - 1 and z < Chunk::SIZE - 1 and _blocks[x + 1][y + 1][z + 1].isActive())
						ao[7] *= AO_COEFF;

					if (x == 0 or not _blocks[x - 1][y][z].isActive()) {
						multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 0.0f, c.r * ao[0], c.g * ao[0], c.b * ao[0], c.a});
						multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 1.0f, c.r * ao[1], c.g * ao[1], c.b * ao[1], c.a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, c.r * ao[2], c.g * ao[2], c.b * ao[2], c.a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, c.r * ao[2], c.g * ao[2], c.b * ao[2], c.a});
						multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 1.0f, c.r * ao[1], c.g * ao[1], c.b * ao[1], c.a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 1.0f, c.r * ao[3], c.g * ao[3], c.b * ao[3], c.a});
					}
					if (y == 0 or not _blocks[x][y - 1][z].isActive()) {

						multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 0.0f, c.r * ao[0], c.g * ao[0], c.b * ao[0], c.a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, c.r * ao[5], c.g * ao[5], c.b * ao[5], c.a});
						multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 1.0f, c.r * ao[1], c.g * ao[1], c.b * ao[1], c.a});
						multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 0.0f, c.r * ao[0], c.g * ao[0], c.b * ao[0], c.a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 0.0f, c.r * ao[4], c.g * ao[4], c.b * ao[4], c.a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, c.r * ao[5], c.g * ao[5], c.b * ao[5], c.a});
					}
					if (z == 0 or not _blocks[x][y][z - 1].isActive()) {
						multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 0.0f, c.r * ao[0], c.g * ao[0], c.b * ao[0], c.a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, c.r * ao[2], c.g * ao[2], c.b * ao[2], c.a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 0.0f, c.r * ao[4], c.g * ao[4], c.b * ao[4], c.a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 0.0f, c.r * ao[4], c.g * ao[4], c.b * ao[4], c.a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, c.r * ao[2], c.g * ao[2], c.b * ao[2], c.a});
						multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 0.0f, c.r * ao[6], c.g * ao[6], c.b * ao[6], c.a});
					}
					if (x == Chunk::SIZE - 1 or not _blocks[x + 1][y][z].isActive()) {
						multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 1.0f, c.r * ao[7], c.g * ao[7], c.b * ao[7], c.a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, c.r * ao[5], c.g * ao[5], c.b * ao[5], c.a});
						multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 0.0f, c.r * ao[6], c.g * ao[6], c.b * ao[6], c.a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 0.0f, c.r * ao[4], c.g * ao[4], c.b * ao[4], c.a});
						multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 0.0f, c.r * ao[6], c.g * ao[6], c.b * ao[6], c.a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, c.r * ao[5], c.g * ao[5], c.b * ao[5], c.a});
					}
					if (y == Chunk::SIZE - 1 or not _blocks[x][y + 1][z].isActive()) {
						multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 1.0f, c.r * ao[7], c.g * ao[7], c.b * ao[7], c.a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, c.r * ao[2], c.g * ao[2], c.b * ao[2], c.a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 1.0f, c.r * ao[3], c.g * ao[3], c.b * ao[3], c.a});
						multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 1.0f, c.r * ao[7], c.g * ao[7], c.b * ao[7], c.a});
						multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 0.0f, c.r * ao[6], c.g * ao[6], c.b * ao[6], c.a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, c.r * ao[2], c.g * ao[2], c.b * ao[2], c.a});
					}
					if (z == Chunk::SIZE - 1 or not _blocks[x][y][z + 1].isActive()) {
						multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 1.0f, c.r * ao[7], c.g * ao[7], c.b * ao[7], c.a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 1.0f, c.r * ao[3], c.g * ao[3], c.b * ao[3], c.a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, c.r * ao[5], c.g * ao[5], c.b * ao[5], c.a});
						multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 1.0f, c.r * ao[1], c.g * ao[1], c.b * ao[1], c.a});
						multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, c.r * ao[5], c.g * ao[5], c.b * ao[5], c.a});
						multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 1.0f, c.r * ao[3], c.g * ao[3], c.b * ao[3], c.a});
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
