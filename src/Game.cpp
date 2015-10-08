#include "Game.hpp"

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
#include "InputManager.hpp"
#include "World.hpp"
#include "WorldGenerator.hpp"
#include "Chunk.hpp"
#include "Skybox.hpp"
#include "Block.hpp"
#include "Renderer.hpp"

float	Game::deltaTime = 0.0f;
float	Game::lastFrame = 0.0f;

GLFWwindow* Game::window;

int		Game::windowWidth;
int		Game::windowHeight;

Renderer 		*Game::renderer;
Skybox 			*Game::skybox;
World	 		*Game::world;
Player 			*Game::player;
Camera 			*Game::camera;
InputManager 	*Game::inputManager;

glm::mat4		Game::projection;
glm::mat4		Game::view;

void    Game::init() {
	initGLFW();
	initOGL();
	initRenderer();
	initWorld();
	initProjection();
}

void	Game::initGLFW()
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

	window = glfwCreateWindow(mode->width, mode->height, "OGL", monitor, nullptr);
	glfwMakeContextCurrent(window);

	windowWidth = mode->width;
	windowHeight = mode->height;

	srand(1234);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, windowWidth, windowHeight);

}

void	Game::initOGL() {

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void	Game::initRenderer() {

	renderer = new Renderer();

	camera = new Camera(glm::vec3(20.0f, 20.0f, 20.0f));

	Shader *blockShader = new Shader();
	blockShader->loadFromFile(GL_VERTEX_SHADER,"shaders/block.vs");
	// blockShader->loadFromFile(GL_GEOMETRY_SHADER,"shaders/block.gs");
	blockShader->loadFromFile(GL_FRAGMENT_SHADER,"shaders/block.fs");
	blockShader->createAndLinkProgram();
	renderer->setShader("Block", blockShader);

	Shader *skyboxShader = new Shader();
	skyboxShader->loadFromFile(GL_VERTEX_SHADER,"shaders/skybox.vs");
	skyboxShader->loadFromFile(GL_FRAGMENT_SHADER,"shaders/skybox.fs");
	skyboxShader->createAndLinkProgram();
	renderer->setShader("Skybox", skyboxShader);
}

void	Game::initWorld() {

	skybox = new Skybox();

	float (*perlinNoise)[GENERATOR_SIZE][GENERATOR_SIZE] = NULL;
	WorldGenerator::GenerateMap(&perlinNoise, 7);

	world = new World();
	player = new Player(glm::vec3(10.0f, 20.0f, 10.0f), world);
	inputManager = new InputManager(window, player);

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
									block_type = 3;
								else if (((y1 + (y * Chunk::SIZE)) + 5 < ((*perlinNoise)[x1 + ((x ) * Chunk::SIZE)][z1 + ((z ) * Chunk::SIZE)] * static_cast<float>(Chunk::SIZE * 3.0f) - 32)))
									block_type = 1;
								else
									block_type = 2;
							}
							else if ((y1 + (y * Chunk::SIZE)) < 10)
								block_type = 4;
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
				world->addChunk(chunk);
			}
		}
	}

}

void	Game::initProjection() {

	projection = glm::perspective(45.0f, (GLfloat)windowWidth/(GLfloat)windowHeight, 0.01f, 10000.0f);

}

bool    Game::shouldClose() {
	return glfwWindowShouldClose(window);
}

void	Game::update() {
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glfwPollEvents();
	inputManager->update(deltaTime);
	world->update(deltaTime);
}

void	Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	view = camera->getViewMatrix();

	renderer->getShader("Skybox")->use();
	skybox->render(renderer);
	renderer->getShader("Skybox")->unUse();

	renderer->getShader("Block")->use();
	world->render(renderer);
	renderer->getShader("Block")->unUse();

	// Swap the buffers
	glfwSwapBuffers(window);
}

void	Game::deinit() {
	delete renderer;
	delete skybox;
	delete world;
	delete player;
	delete inputManager;

	//TODO: Properly de-allocate all resources once they've outlived their purpose
	glfwTerminate();
}
