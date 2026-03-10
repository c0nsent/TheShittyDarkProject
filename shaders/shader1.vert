#version 460 core
layout (location=0) in vec3 aPos;

out vec4 vertexColor;

float getModule(float pos ) {
    if (pos > 0)
        pos = pos * -1;

    return pos;
}

void main()
{
    gl_Position = vec4(aPos, 1.0);
    vertexColor = vec4(getModule(aPos.x), getModule(aPos.y), 0.0, 1.0);
}