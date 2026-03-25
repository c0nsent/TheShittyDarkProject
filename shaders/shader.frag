#version 460 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float opacity2;

void main()
{
    vec2 reversedObama = vec2(TexCoord.x * -1, TexCoord.y);
    FragColor = mix(texture(texture1, TexCoord) * vec4(ourColor, 1.0), texture(texture2, reversedObama), opacity2);
}