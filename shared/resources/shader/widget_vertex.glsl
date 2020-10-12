#ifdef GL_ES
precision mediump float;
#endif

attribute vec4 vPosition;
attribute vec2 vTexCoord;

uniform   mat4 vMVP;

varying   vec2 fTexCoord;

void main()
{
    gl_Position = vMVP * vPosition;
    fTexCoord = vTexCoord;
}
