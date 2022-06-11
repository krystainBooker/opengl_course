// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <iostream>
#include <cmath>

const int mWidth = 800;
const int mHeight = 600;

void processInput(GLFWwindow* window);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

/**
 * GLSL supports basic types int, float, double, uint, and bool.
 * Additionally it features two containers, vectors, and matrices.
 *
 * Vectors in GLSL is a 2,3, or 4 component container for any basic type.
 * vecn: the default vector of n floats
 * bvecn: a vector of n booleans
 * ivecn: a vector of n integers.
 * uvecn: a vector of n unsigned integers.
 * dvecn: a vector of n double components.
 *
 * Uniforms: Another way to pass data from our application on the CPU to the shaders on the GPU.
 * Uniforms are global, though uniforms will keep their value until they're either reset or updated.
 * **If a uniform is declared but not used in GLSL, it will be removed via the compiler.
 */

/**
 * Vertex shaders input variables are known as a vertex attribute
 * Inputs limited to 16 4-component vertex attributes (Some hardware may allow for more, query by GL_MAX_VERTEX_ATTRIBS)
 *
 * On the vertex shader we need to specify the location of the input data with location metadata,
 * which allows us to pass in multiple inputs.
 *
 * The location metadata refers to the size of input variable
 *      layout(location = 0) out vec3 vals[4];    // Consumes 4 locations
 *      layout(location = 4) out OutData myOut;   // Consumes 6 locations. dvec4 uses 2, and `val[3]` uses 3 total
 *      layout(location = 10) out vec2 texCoord;  // Consumes 1 location
 * Additional details: https://www.khronos.org/opengl/wiki/Layout_Qualifier_(GLSL)
 *
 * When types and names are equal on both sides OpenGL will link those variables together automatically to send
 * data between shaders.
 */
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColour;\n"
                                 "out vec3 vertexColor; " //Specify a color output to the fragment shader
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "   vertexColor = aColour;\n"
                                 //" vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n" //Set the output variable to dark-red
                                 "}\0";


/**
 * The fragment shader requires a vec4 color output variable
 */
const char *fragmentShaderSource = "#version 330 core\n"
                                 "out vec4 FragColor;\n"
                                 "in vec3 vertexColor; \n" //The input variable from the vertex shader
                                 //"uniform vec4 ourColour;\n" //We set this variable in the OpenGL code on CPU
                                 "void main()\n"
                                 "{\n"
                                 //"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                 //"   FragColor = vertexColor;\n"
                                 "     FragColor = vec4(vertexColor, 1.0);\n"
                                 "}\0";
int  success;
char infoLog[512];

int main(int argc, char * argv[])
{

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* mWindow = glfwCreateWindow(mWidth, mHeight, "LearnOpenGL", nullptr, nullptr);
    if (mWindow == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    glfwSetFramebufferSizeCallback(mWindow, framebufferSizeCallback); // Resize the viewport on window resize
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return EXIT_FAILURE;
    }

    //Maximum number of vertex attributes
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum number of vertex attributes supported: " << nrAttributes << std::endl;

    // Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create shader reference
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Assign shader source to reference id
    glCompileShader(vertexShader); // Compile shader

    // Shader compilation check
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Shader compilation check
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Shader program linking error check
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    // Delete shader objects after linked
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Setup vertex data
    float vertices[] = {
            // positions         // colors
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    };

    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Link vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float))); //Colour
    glEnableVertexAttribArray(1);

    // The call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Activate the shader
    glUseProgram(shaderProgram);

    // Rendering Loop
    while (!glfwWindowShouldClose(mWindow))
    {
        // Input
        processInput(mWindow);

        // Background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Update the uniform colour
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColour");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // Render the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }

    // De-allocate all resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return EXIT_SUCCESS;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width, height);
}
