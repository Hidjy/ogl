#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Player.hpp"
#include "Camera.hpp"
#include "TextureManager.hpp"
#include "InputManager.hpp"
#include "World.hpp"
#include "WorldGenerator.hpp"
#include "Chunk.hpp"
#include "Skybox.hpp"
#include "Block.hpp"
#include "Renderer.hpp"

namespace Game {
	extern float	deltaTime;
	extern float	lastFrame;

	extern GLFWwindow* window;

	extern int		windowWidth;
	extern int		windowHeight;

	extern Renderer 		*renderer;
	extern Skybox 			*skybox;
	extern World	 		*world;
	extern Player 			*player;
	extern Camera 			*camera;
	extern InputManager 	*inputManager;

	extern glm::mat4		projection;
	extern glm::mat4		view;

	extern bool		shouldClose();

	extern void		init();
	extern void		initGLFW();
	extern void		initOGL();
	extern void		initRenderer();
	extern void		initWorld();
	extern void		initProjection();
	extern void		initTextures();
	extern void		update();
	extern void		draw();
	extern void		deinit();
}
