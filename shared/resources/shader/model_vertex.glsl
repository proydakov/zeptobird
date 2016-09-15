precision mediump float;

attribute vec4 vPosition;
attribute vec4 vColor;

uniform   mat4 vMVP;

varying   vec4 fColor;

void main()
{
    gl_Position = vMVP * vPosition;
    fColor = vColor;
}
