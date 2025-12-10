#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <fstream>
#include <sstream>
#include <string>

std::string loadShaderFromFile(const char* path);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// glfw: whenever the window size changes this callback function executes
void processInput(GLFWwindow* window);
int* shadersLockAndLoad();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "I am learning OpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Disable VSync (uncap FPS). 0 = off, 1 = on, 2 = every other v-blank (if supported)
    glfwSwapInterval(0);

    // Load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Tr 1
    float vertices[] = {
        0.0f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
    };

    // Tr 2
    float verticesDos[] = {
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    float verticesTres[] = {
        -0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
        -1.0f, 0.5f, 0.0f
	};

    unsigned int VAOs[3], VBOs[3];
    glGenVertexArrays(3, VAOs);
    glGenBuffers(3, VBOs);

	// Tr 1
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Tr 2
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesDos), verticesDos, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Configuring the vertex attribute on attribute location 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

	// Tr 3
    glBindVertexArray(VAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTres), verticesTres, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    int* shaders = shadersLockAndLoad();

    double previousTime = glfwGetTime();
    int frameCount = 0;
    double timeBetweenCalls = 0.5; // seconds

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Drawing code
		// Tr 1
        glUseProgram(shaders[0]);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Tr 2
		glUseProgram(shaders[1]);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

		// Tr 3 - with uniform color change
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaders[2], "ourColor");

        if (vertexColorLocation == -1)
        {
            std::cout << "Failed to get uniform location!" << std::endl;
		}

        glUseProgram(shaders[2]);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        glBindVertexArray(VAOs[2]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);

        // Measure FPS
        double currentTime = glfwGetTime();
        double timeInterval = currentTime - previousTime;
        
        frameCount++;

        if (timeInterval >= timeBetweenCalls)
        {
            // Display the frame count here any way you want.
            std::cout << "FPS: " << frameCount << std::endl;

            frameCount = 0;
            previousTime = currentTime;
        }
    }

    // De-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(3, VAOs);
    glDeleteBuffers(3, VBOs);
    glDeleteProgram(shaders[0]);
    glDeleteProgram(shaders[1]);
    glDeleteProgram(shaders[2]);
    delete[] shaders;

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

int* shadersLockAndLoad()
{
    int* shaders = new int[3];

    std::string vertexCode = loadShaderFromFile("vertex.glsl");
    std::string orangeCode = loadShaderFromFile("orange.frag");
    std::string yellowCode = loadShaderFromFile("yellow.frag");
	std::string uniformCode = loadShaderFromFile("uniform.frag");

    const char* vertexShaderSource = vertexCode.c_str();
    const char* orangeFragmentSource = orangeCode.c_str();
    const char* yellowFragmentSource = yellowCode.c_str();
	const char* uniformFragmentSource = uniformCode.c_str();

    // // VERTEX SHADER
    // Creating a vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for vertex shader compile errors
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // // FRAGMENT SHADER
    // Creating a fragment shader
    unsigned int fragmentShaderOrange;
    fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderOrange, 1, &orangeFragmentSource, NULL);
    glCompileShader(fragmentShaderOrange);

    unsigned int fragmentShaderYellow;
    fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &yellowFragmentSource, NULL);
    glCompileShader(fragmentShaderYellow);

    unsigned int fragmentShaderUniform;
	fragmentShaderUniform = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderUniform, 1, &uniformFragmentSource, NULL);
	glCompileShader(fragmentShaderUniform);

    // Check for fragment shader compile errors
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		glGetShaderInfoLog(fragmentShaderUniform, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // // SHADER PROGRAM
    // Creating a shader program
    unsigned int shaderProgramOrange = glCreateProgram();

    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);

    glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success);

    unsigned int shaderProgramYellow = glCreateProgram();

    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

    unsigned int shaderProgramUniform = glCreateProgram();

    glAttachShader(shaderProgramUniform, vertexShader);
    glAttachShader(shaderProgramUniform, fragmentShaderUniform);
    glLinkProgram(shaderProgramUniform);

	// Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);
	glDeleteShader(fragmentShaderYellow);
	glDeleteShader(fragmentShaderUniform);

    // Check for linking errors
    if (!success) {
        glGetProgramInfoLog(shaderProgramOrange, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

		glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

		glGetProgramInfoLog(shaderProgramUniform, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

	shaders[0] = shaderProgramOrange;
	shaders[1] = shaderProgramYellow;
	shaders[2] = shaderProgramUniform;

    return shaders;
}

std::string loadShaderFromFile(const char* path)
{
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
