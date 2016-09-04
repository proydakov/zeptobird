precision mediump float;

attribute vec4 vPosition;
uniform   vec3 vColor;
varying   vec3 fColor;

void main()
{
    gl_Position = vPosition;
    fColor = vColor;
}