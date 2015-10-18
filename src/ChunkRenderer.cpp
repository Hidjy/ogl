#include "ChunkRenderer.hpp"

#include "Mesh.hpp"
#include "Chunk.hpp"
#include "IRenderContext.hpp"

ChunkRenderer::ChunkRenderer() {
	_mesh.setMode(GL_TRIANGLES);
}

template <typename T>
static void multipush(std::vector<T> &target, std::vector<T> src)
{
	for (auto it = src.begin(); it != src.end(); ++it)
		target.push_back(*it);
}

void	ChunkRenderer::generateMesh(Chunk *chunk)
{
		std::vector<GLfloat> vertices;

		for (int x = 0; x < Chunk::SizeX; x++) {
			for (int y = 0; y < Chunk::SizeY; y++) {
				for (int z = 0; z < Chunk::SizeZ; z++) {
					Block current = chunk->getBlock(x, y, z);
					if (current.isActive()) {
						float vx, vy, vz;
						vx = static_cast<float>(x);
						vy = static_cast<float>(y);
						vz = static_cast<float>(z);

						float r, g, b, a;
						current.getType()->getRGBA(r, g, b, a);

						GLfloat ao[8] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

						if (y > 0 and z > 0 and chunk->getBlock(x, y - 1, z - 1).isActive()) {
							ao[0] *= AO_COEFF;
							ao[4] *= AO_COEFF;
						}
						if (y > 0 and x < Chunk::SizeX - 1 and chunk->getBlock(x + 1, y - 1, z).isActive()) {
							ao[4] *= AO_COEFF;
							ao[5] *= AO_COEFF;
						}
						if (y > 0 and z < Chunk::SizeY - 1 and chunk->getBlock(x, y - 1, z + 1).isActive()) {
							ao[1] *= AO_COEFF;
							ao[5] *= AO_COEFF;
						}
						if (y > 0 and x > 0 and chunk->getBlock(x - 1, y - 1, z).isActive()) {
							ao[0] *= AO_COEFF;
							ao[1] *= AO_COEFF;
						}

						if (y < Chunk::SizeZ - 1 and z > 0 and chunk->getBlock(x, y + 1, z - 1).isActive()) {
							ao[2] *= AO_COEFF;
							ao[6] *= AO_COEFF;
						}
						if (y < Chunk::SizeX - 1 and x < Chunk::SizeY - 1 and chunk->getBlock(x + 1, y + 1, z).isActive()) {
							ao[6] *= AO_COEFF;
							ao[7] *= AO_COEFF;
						}
						if (y < Chunk::SizeX - 1 and z < Chunk::SizeZ - 1 and chunk->getBlock(x, y + 1, z + 1).isActive()) {
							ao[3] *= AO_COEFF;
							ao[7] *= AO_COEFF;
						}
						if (y < Chunk::SizeX - 1 and x > 0 and chunk->getBlock(x - 1, y + 1, z).isActive()) {
							ao[2] *= AO_COEFF;
							ao[3] *= AO_COEFF;
						}

						if (x > 0 and y > 0 and z > 0 and chunk->getBlock(x - 1, y - 1, z - 1).isActive())
							ao[0] *= AO_COEFF;
						if (x > 0 and y > 0 and z < Chunk::SizeX - 1 and chunk->getBlock(x - 1, y - 1, z + 1).isActive())
							ao[1] *= AO_COEFF;
						if (x > 0 and y < Chunk::SizeY - 1 and z > 0 and chunk->getBlock(x - 1, y + 1, z - 1).isActive())
							ao[2] *= AO_COEFF;
						if (x > 0 and y < Chunk::SizeX - 1 and z < Chunk::SizeY - 1 and chunk->getBlock(x - 1, y + 1, z + 1).isActive())
							ao[3] *= AO_COEFF;
						if (x < Chunk::SizeY - 1 and y > 0 and z > 0 and chunk->getBlock(x + 1, y - 1, z - 1).isActive())
							ao[4] *= AO_COEFF;
						if (x < Chunk::SizeZ - 1 and y > 0 and z < Chunk::SizeY - 1 and chunk->getBlock(x + 1, y - 1, z + 1).isActive())
							ao[5] *= AO_COEFF;
						if (x < Chunk::SizeZ - 1 and y < Chunk::SizeY - 1 and z > 0 and chunk->getBlock(x + 1, y + 1, z - 1).isActive())
							ao[6] *= AO_COEFF;
						if (x < Chunk::SizeY - 1 and y < Chunk::SizeZ - 1 and z < Chunk::SizeZ - 1 and chunk->getBlock(x + 1, y + 1, z + 1).isActive())
							ao[7] *= AO_COEFF;

						if (x == 0 or not chunk->getBlock(x - 1, y, z).isActive()) {
							multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 0.0f, r * ao[0], g * ao[0], b * ao[0], a});
							multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 1.0f, r * ao[1], g * ao[1], b * ao[1], a});
							multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, r * ao[2], g * ao[2], b * ao[2], a});
							multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, r * ao[2], g * ao[2], b * ao[2], a});
							multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 1.0f, r * ao[1], g * ao[1], b * ao[1], a});
							multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 1.0f, r * ao[3], g * ao[3], b * ao[3], a});
						}
						if (y == 0 or not chunk->getBlock(x, y - 1, z).isActive()) {

							multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 0.0f, r * ao[0], g * ao[0], b * ao[0], a});
							multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, r * ao[5], g * ao[5], b * ao[5], a});
							multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 1.0f, r * ao[1], g * ao[1], b * ao[1], a});
							multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 0.0f, r * ao[0], g * ao[0], b * ao[0], a});
							multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 0.0f, r * ao[4], g * ao[4], b * ao[4], a});
							multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, r * ao[5], g * ao[5], b * ao[5], a});
						}
						if (z == 0 or not chunk->getBlock(x, y, z - 1).isActive()) {
							multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 0.0f, r * ao[0], g * ao[0], b * ao[0], a});
							multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, r * ao[2], g * ao[2], b * ao[2], a});
							multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 0.0f, r * ao[4], g * ao[4], b * ao[4], a});
							multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 0.0f, r * ao[4], g * ao[4], b * ao[4], a});
							multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, r * ao[2], g * ao[2], b * ao[2], a});
							multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 0.0f, r * ao[6], g * ao[6], b * ao[6], a});
						}
						if (x == Chunk::SizeX - 1 or not chunk->getBlock(x + 1, y, z).isActive()) {
							multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 1.0f, r * ao[7], g * ao[7], b * ao[7], a});
							multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, r * ao[5], g * ao[5], b * ao[5], a});
							multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 0.0f, r * ao[6], g * ao[6], b * ao[6], a});
							multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 0.0f, r * ao[4], g * ao[4], b * ao[4], a});
							multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 0.0f, r * ao[6], g * ao[6], b * ao[6], a});
							multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, r * ao[5], g * ao[5], b * ao[5], a});
						}
						if (y == Chunk::SizeY - 1 or not chunk->getBlock(x, y + 1, z).isActive()) {
							multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 1.0f, r * ao[7], g * ao[7], b * ao[7], a});
							multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, r * ao[2], g * ao[2], b * ao[2], a});
							multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 1.0f, r * ao[3], g * ao[3], b * ao[3], a});
							multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 1.0f, r * ao[7], g * ao[7], b * ao[7], a});
							multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 0.0f, r * ao[6], g * ao[6], b * ao[6], a});
							multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 0.0f, r * ao[2], g * ao[2], b * ao[2], a});
						}
						if (z == Chunk::SizeZ - 1 or not chunk->getBlock(x, y, z + 1).isActive()) {
							multipush(vertices, {vx + 1.0f, vy + 1.0f, vz + 1.0f, r * ao[7], g * ao[7], b * ao[7], a});
							multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 1.0f, r * ao[3], g * ao[3], b * ao[3], a});
							multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, r * ao[5], g * ao[5], b * ao[5], a});
							multipush(vertices, {vx + 0.0f, vy + 0.0f, vz + 1.0f, r * ao[1], g * ao[1], b * ao[1], a});
							multipush(vertices, {vx + 1.0f, vy + 0.0f, vz + 1.0f, r * ao[5], g * ao[5], b * ao[5], a});
							multipush(vertices, {vx + 0.0f, vy + 1.0f, vz + 1.0f, r * ao[3], g * ao[3], b * ao[3], a});
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

void	ChunkRenderer::render(IRenderContext *renderContext)
{
	_mesh.render(renderContext);
}
