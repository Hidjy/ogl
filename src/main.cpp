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
#include "Cube.hpp"
#include "Chunk.hpp"

GLuint screenWidth = 1600, screenHeight = 900;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();
GLuint LoadTexture(std::string path);

Camera camera(glm::vec3(10.0f, 10.0f, 10.0f));

bool keys[1024];
GLfloat lastX = screenWidth / 2, lastY = screenHeight / 2;
bool firstMouse = true;

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

    srand(glfwGetTime());

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, screenWidth, screenHeight);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE); //TODO Benchmark with/without GL_CULL_FACE
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

////////////////////////////////////////////////////////////////////////////////

    Shader blockShader("shaders/block.vert", "shaders/block.frag");

    TextManager *textManager = new TextManager();

    int cubes[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    for (size_t x = 0; x < CHUNK_SIZE; x++) {
		for (size_t y = 0; y < CHUNK_SIZE; y++) {
			for (size_t z = 0; z < CHUNK_SIZE; z++) {
                if ((x - (CHUNK_SIZE / 2)) * (x - (CHUNK_SIZE / 2)) + (y - (CHUNK_SIZE / 2)) * (y - (CHUNK_SIZE / 2)) + (z - (CHUNK_SIZE / 2)) * (z - (CHUNK_SIZE / 2)) <= (CHUNK_SIZE / 2) * (CHUNK_SIZE / 2))
                // if (true)
                    cubes[x][y][z] = 1;
                else
                    cubes[x][y][z] = 0;
			}
		}
	}

    Chunk *chunks[3*2*5];
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 2; y++) {
            for (int z = 0; z < 5; z++) {
                chunks[x + y * 3 + z * 3 * 2] = new Chunk(glm::vec3(x, y, z));
                chunks[x + y * 3 + z * 3 * 2]->fill(&cubes);
                chunks[x + y * 3 + z * 3 * 2]->generateSections();
            }
        }
    }

    GLuint texture = LoadTexture("ressources/0.png");

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)screenWidth/(GLfloat)screenHeight, 0.1f, 10000.0f);
    blockShader.Use();
    glUniformMatrix4fv(glGetUniformLocation(blockShader.getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Game loop
    GLuint frames = 0;
    GLuint fps = 0;
    GLfloat fps_periode = 2;
    GLfloat fps_time = 0;
    while(!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        fps_time += deltaTime;

        glfwPollEvents();
        Do_Movement();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        blockShader.Use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(blockShader.getProgram(), "ourTexture"), 0);

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(blockShader.getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));

        // chunk.render(blockShader);
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 2; y++) {
                for (int z = 0; z < 5; z++) {
                    chunks[x + y * 3 + z * 3 * 2]->render(blockShader);
                }
            }
        }

        if (fps_time > fps_periode) {
            fps = frames / fps_periode;
            frames = 0;
            fps_time = 0;
        }
        frames++;
        textManager->RenderText(std::to_string(fps), 25.0f, 425.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        // Swap the buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glfwTerminate();
    return 0;
}

//////////////////////////////////////////////////////////////////////////////

// Moves/alters the camera positions based on user input
void Do_Movement()
{
    if(keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if(keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if(keys[GLFW_KEY_SPACE])
        camera.ProcessKeyboard(UP, deltaTime);
    if(keys[GLFW_KEY_LEFT_SHIFT])
        camera.ProcessKeyboard(DOWN, deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if(action == GLFW_PRESS)
            keys[key] = true;
        else if(action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

GLuint LoadTexture(std::string path) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height;
    unsigned char* image = SOIL_load_image(path.data(), &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}
