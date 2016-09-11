precision mediump float;

attribute vec4 vPosition;
attribute vec4 vColor;

uniform   mat4 vModelView;
uniform   mat4 vProjection;

varying   vec4 fColor;

void main()
{
    gl_Position = vProjection * vModelView * vPosition;
    fColor = vColor;
}
