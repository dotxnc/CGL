#version 330 core
in vec3 outColor;
in vec2 TexCoord;

out vec4 color;

// uniform sampler2D ourTexture;

void main()
{
    color = vec4(outColor, 1.0);
}
