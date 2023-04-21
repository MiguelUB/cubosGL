#version 330
#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 color;

void main()
{
  gl_Position = vPosition;
  color = vColor;
}
