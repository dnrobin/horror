#version 330

layout(pixel_center_integer) in vec4 gl_FragCoord;

in vec2 uv;

uniform sampler2D tex_attachment0;
uniform sampler2D tex_attachment1;
uniform sampler2D tex_attachment2;
uniform sampler2D tex_depth;

out vec4 color;

void main()
{
    float w = viewportDimensions.x;
    float h = viewportDimensions.y;

    // draw everything
}