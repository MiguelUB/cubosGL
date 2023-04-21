#version 330
#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

IN vec4 color;
OUT vec4 colorOut;

void main()
{
    colorOut = color;
}

