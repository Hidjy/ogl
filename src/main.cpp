#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL/SOIL.h>

#include <vector>

#include "Camera.hpp"
#include "TextManager.hpp"
#include "TextureManager.hpp"
#include "InputManager.hpp"
#include "World.hpp"
#include "WorldGenerator.hpp"
#include "Chunk.hpp"

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

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "OGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    GLuint screenWidth = mode->width, screenHeight = mode->height;

    srand(time(NULL));

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, screenWidth, screenHeight);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

////////////////////////////////////////////////////////////////////////////////

    Shader blockShader("shaders/block.vert", "shaders/block.frag");
    Shader skyboxShader("shaders/skybox.vert", "shaders/skybox.frag");

    TextureManager textureManager("ressources/tileset.png", 8, 4);

    Camera camera(glm::vec3(10.0f, 10.0f, 10.0f));

    InputManager inputManager(window, &camera);

    float noise[GENERATOR_SIZE][GENERATOR_SIZE];
    GenerateWhiteNoise(&noise);
    float perlinNoise[GENERATOR_SIZE][GENERATOR_SIZE];
    GeneratePerlinNoise(&perlinNoise, &noise, 7);

    int cubes[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];


    World world;

    for (int x = -10; x < 10; x++) {
        for (int y = -1; y < 0; y++) {
            for (int z = -10; z < 10; z++) {
                Chunk chunk(glm::vec3(x, y, z), textureManager);

                for (size_t x1 = 0; x1 < CHUNK_SIZE; x1++) {
                    for (size_t y1 = 0; y1 < CHUNK_SIZE; y1++) {
                        for (size_t z1 = 0; z1 < CHUNK_SIZE; z1++) {
                            if (y1 < (perlinNoise[x1 + ((x+10) * CHUNK_SIZE)][z1 + ((z+10) * CHUNK_SIZE)] * static_cast<float>(CHUNK_SIZE)))
                                cubes[x1][y1][z1] = 1 + rand() % 5;
                            else
                                cubes[x1][y1][z1] = 0;
                        }
                    }
                }

                chunk.fill(&cubes);
                world.add(chunk);
            }
        }
    }

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)screenWidth/(GLfloat)screenHeight, 0.1f, 10000.0f);
    glUniformMatrix4fv(glGetUniformLocation(blockShader.getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    blockShader.Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureManager.getTileset());
    glUniform1i(glGetUniformLocation(blockShader.getProgram(), "ourTexture"), 0);

    // Game loop
    while(!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        inputManager.update(deltaTime);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        blockShader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(blockShader.getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));

        world.renderNear(camera._pos, blockShader);

        /*glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_CUBE_MAP, camera._cubemapTexture);

        glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.Use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        // skybox cube
        glBindVertexArray(camera._skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(skyboxShader.getProgram(), "skybox"), 0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, camera._cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // Set depth function back to default
*/
        // Swap the buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glfwTerminate();
    return 0;
}
