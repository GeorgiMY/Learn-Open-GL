#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord;

out vec4 vertexColor;
out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;

    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
    TexCoord = aTexCoord;
}
