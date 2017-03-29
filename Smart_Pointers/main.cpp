#include <iostream>
#include <string>
#include <iterator>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;

GLFWwindow* window;

GLuint loadShader(const std::string& filepath, GLuint type)
{
    GLuint shaderId = glCreateShader(type);

    std::ifstream shaderStream(filepath);
    std::string shaderCode(std::istreambuf_iterator<char>{shaderStream}, {});

    GLint result = GL_FALSE;
    int logLength;

    const char* code = shaderCode.c_str();
    glShaderSource(shaderId, 1, &code, NULL);
    glCompileShader(shaderId);

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
    if ( logLength > 0 ){
      std::vector<char> shaderErrorMessage(logLength + 1);
      glGetShaderInfoLog(shaderId, logLength, NULL, &shaderErrorMessage[0]);
      cout << &shaderErrorMessage[0] << endl;
    }

    return shaderId;
}

int main()
{
    if (!glfwInit())
    {
        cout << "Error GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow( 1024, 768, "OpenGL test", NULL, NULL);
    if( window == nullptr )
    {
        cout << "Cannot open window with GLFW." << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental=true;
    if (glewInit() != GLEW_OK)
    {
        cout << "Cannot init GLEW" << endl;
        return -1;
    }

    loadShader("data/vertex.glsl", GL_VERTEX_SHADER);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while (glfwWindowShouldClose(window) == 0);

    return 0;
}
