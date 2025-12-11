#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform vec4 funnyRectColor;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // FragColor = texture(ourTexture, TexCoord) * vec4(funnyRectColor);

    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(TexCoord.x * -1, TexCoord.y)), 0.2) * vec4(funnyRectColor);
}