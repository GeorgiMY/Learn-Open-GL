//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//
//#include <string>
//#include "Shader.h"
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//
//// glfw: whenever the window size changes this callback function executes
//void processInput(GLFWwindow* window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//int main()
//{
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "I am learning OpenGL", NULL, NULL);
//
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//
//    // Disable VSync (uncap FPS). 0 = off, 1 = on, 2 = every other v-blank (if supported)
//    glfwSwapInterval(0);
//
//    // Load all OpenGL function pointers
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    // Tr 1
//    float vertices[] = {
//        0.0f, -0.5f, 0.0f,
//        0.5f, -0.5f, 0.0f,
//        0.0f,  0.5f, 0.0f,
//    };
//
//    // Tr 2
//    float verticesDos[] = {
//        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
//        1.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
//        0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
//    };
//
//    float verticesTres[] = {
//        -0.5f, -0.5f, 0.0f,
//        0.0f,  0.5f, 0.0f,
//        -1.0f, 0.5f, 0.0f
//    };
//
//    unsigned int VAOs[3], VBOs[3];
//    glGenVertexArrays(3, VAOs);
//    glGenBuffers(3, VBOs);
//
//    // Tr 1
//    glBindVertexArray(VAOs[0]);
//    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // Tr 2
//    glBindVertexArray(VAOs[1]);
//    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesDos), verticesDos, GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    // Configuring the vertex attribute on attribute location 1
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    // Tr 3
//    glBindVertexArray(VAOs[2]);
//    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTres), verticesTres, GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    Shader yellowShader("vertex.glsl", "yellow.frag");
//    Shader orangeShader("vertex.glsl", "orange.frag");
//    Shader uniformShader("vertex.glsl", "uniform.frag");
//
//    double previousTime = glfwGetTime();
//    int frameCount = 0;
//    double timeBetweenCalls = 0.5; // seconds
//
//    // Render loop
//    while (!glfwWindowShouldClose(window))
//    {
//        // input
//        processInput(window);
//
//        // rendering commands here
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // Drawing code
//        // Tr 1
//        orangeShader.use();
//        glBindVertexArray(VAOs[0]);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//
//        // Tr 2
//        yellowShader.use();
//        glBindVertexArray(VAOs[1]);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//
//        // Tr 3 - with uniform color change
//        uniformShader.use();
//        float timeValue = glfwGetTime();
//        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
//        uniformShader.setVec4("ourColor", 0.0f, greenValue, 0.0f, 0.0f);
//        glBindVertexArray(VAOs[2]);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//
//        // check and call events and swap the buffers
//        glfwPollEvents();
//        glfwSwapBuffers(window);
//
//        // Measure FPS
//        double currentTime = glfwGetTime();
//        double timeInterval = currentTime - previousTime;
//
//        frameCount++;
//
//        if (timeInterval >= timeBetweenCalls)
//        {
//            // Display the frame count here any way you want.
//            std::cout << "FPS: " << frameCount << std::endl;
//
//            frameCount = 0;
//            previousTime = currentTime;
//        }
//    }
//
//    // De-allocate all resources once they've outlived their purpose
//    glDeleteVertexArrays(3, VAOs);
//    glDeleteBuffers(3, VBOs);
//    glDeleteProgram(orangeShader.ID);
//    glDeleteProgram(yellowShader.ID);
//    glDeleteProgram(uniformShader.ID);
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    glfwTerminate();
//    return 0;
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
//}
