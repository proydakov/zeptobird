precision mediump float;

attribute vec4 vPosition;
uniform   mat4 vMVP;
uniform   vec3 vColor;
varying   vec3 fColor;

void main()
{
    gl_Position = vMVP * vPosition;
    fColor = vColor;
}
