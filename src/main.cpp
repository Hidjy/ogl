#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL/SOIL.h>

#include <string>
#include <iostream>
#include <vector>

#include "Shader.hpp"
#include "Camera.hpp"
#include "CubeRenderer.hpp"

#include "Cube.hpp"

GLuint screenWidth = 800, screenHeight = 450;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();

Camera camera(glm::vec3(3.0f, 10.0f, 3.0f));
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

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "OGL", nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, screenWidth, screenHeight);

    glEnable(GL_DEPTH_TEST);

    Shader blockShader("shader/block.vert", "shader/block.frag");

        //TODO: TextureManager
        // TEXTURE
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
        // Set our texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Set texture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // Load, create texture and generate mipmaps
        int width, height;
        unsigned char* image = SOIL_load_image("ressource/dore.png", &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        SOIL_free_image_data(image);
        glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

    CubeRenderer *cubeRenderer = new CubeRenderer();

    std::vector<Cube> cubes;
    GLuint textures[] = {texture, texture, texture, texture, texture, texture};

    for (GLfloat x = -20; x < 20; x++) {
        for (GLfloat y = 0; y < 1; y++) {
            for (GLfloat z = -20; z < 20; z++) {
                cubes.push_back(Cube(glm::vec3(x, roundf(5 * cos(sqrt(x*x + z*z) * 0.2)), z), textures ));
            }
        }
    }

    // Game loop
    while(!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        Do_Movement();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        blockShader.Use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(blockShader.Program, "ourTexture"), 0);

        glm::mat4 view;
        view = camera.GetViewMatrix();
        glm::mat4 projection;
        projection = glm::perspective(camera.Zoom, (float)screenWidth/(float)screenHeight, 0.1f, 1000.0f);
        // Get the uniform locations
        GLint viewLoc = glGetUniformLocation(blockShader.Program, "view");
        GLint projLoc = glGetUniformLocation(blockShader.Program, "projection");
        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        cubeRenderer->render(cubes, blockShader);
        // Swap the buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    delete cubeRenderer;
    glfwTerminate();
    return 0;
}

// Moves/alters the camera positions based on user input
void Do_Movement()
{
    // Camera controls
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

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //std::cout << key << std::endl;
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


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //camera.ProcessMouseScroll(yoffset);
}
