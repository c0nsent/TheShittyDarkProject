#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 ourColor;

uniform float offset;

void main()
{
    //vec4 upsideDown = vec4(aPos, 1.f);
    //upsideDown.x -= offset;
    gl_Position = vec4(aPos, 1.f);
    ourColor = aPos;
}