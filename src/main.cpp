#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL/SOIL.h>

#include <vector>
#include "Player.hpp"
#include "Camera.hpp"
#include "TextManager.hpp"
#include "TextureManager.hpp"
#include "InputManager.hpp"
#include "World.hpp"
#include "WorldGenerator.hpp"
#include "Chunk.hpp"
#include "Skybox.hpp"
#include "Block.hpp"
#include "Renderer.hpp"

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();

	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "OGL", monitor, nullptr);
	glfwMakeContextCurrent(window);

	GLuint screenWidth = mode->width, screenHeight = mode->height;

	srand(1234);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, screenWidth, screenHeight);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

////////////////////////////////////////////////////////////////////////////////

	Renderer *renderer = new Renderer();

	renderer->setBlockShader(new Shader("shaders/block.vert", "shaders/block.frag"));
	renderer->setSkyboxShader(new Shader("shaders/skybox.vert", "shaders/skybox.frag"));
	renderer->setTextShader(new Shader("shaders/text.vert", "shaders/text.frag"));

	renderer->setTextureManager(new TextureManager("ressources/tileset.png", 8, 4));

	Skybox skybox;

	float (*perlinNoise)[GENERATOR_SIZE][GENERATOR_SIZE] = NULL;
	WorldGenerator::GenerateMap(&perlinNoise, 7);

	World world;
	Player player(glm::vec3(10.0f, 20.0f, 10.0f), &world);
	InputManager inputManager(window, &player);

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 2; y++) {
			for (int z = 0; z < 10; z++) {
				Chunk *chunk = new Chunk();
				chunk->setPos(glm::vec3(x, y, z));

				for (size_t x1 = 0; x1 < Chunk::SIZE; x1++) {
					for (size_t y1 = 0; y1 < Chunk::SIZE; y1++) {
						for (size_t z1 = 0; z1 < Chunk::SIZE; z1++) {
							int block_type;
							if ((y1 + (y * Chunk::SIZE)) < ((*perlinNoise)[x1 + ((x ) * Chunk::SIZE)][z1 + ((z ) * Chunk::SIZE)] * static_cast<float>(Chunk::SIZE * 3.0f) - 32)) {
								if ((y1 + (y * Chunk::SIZE)) == 9)
									block_type = 10;
								else if (((y1 + (y * Chunk::SIZE)) + 5 < ((*perlinNoise)[x1 + ((x ) * Chunk::SIZE)][z1 + ((z ) * Chunk::SIZE)] * static_cast<float>(Chunk::SIZE * 3.0f) - 32)))
									block_type = 1;
								else
									block_type = 3;
							}
							else if ((y1 + (y * Chunk::SIZE)) < 10)
								block_type = 25;
							else
								block_type = 0;

							if (block_type != 0) {
								chunk->getBlock(x1, y1, z1).setActive(true);
								chunk->getBlock(x1, y1, z1).setType(block_type);
							}
						}
					}
				}
				chunk->generateMesh();
				world.addChunk(chunk);
			}
		}
	}

	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)screenWidth/(GLfloat)screenHeight, 0.1f, 10000.0f);
	renderer->getBlockShader()->Use();
	glUniformMatrix4fv(glGetUniformLocation(renderer->getBlockShader()->getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	renderer->getBlockShader()->Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, renderer->getTextureManager()->getTileset());
	glUniform1i(glGetUniformLocation(renderer->getBlockShader()->getProgram(), "ourTexture"), 0);

	// Game loop
	while(!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		inputManager.update(deltaTime);
		world.update(deltaTime);

		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = player.GetViewMatrix();

		skybox.render(player._camera, projection);

		renderer->getBlockShader()->Use();
		glUniformMatrix4fv(glGetUniformLocation(renderer->getBlockShader()->getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		world.render(player._pos, renderer);

		// Swap the buffers
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glfwTerminate();
	return 0;
}
