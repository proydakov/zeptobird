precision mediump float;

attribute vec4 vPosition;

uniform   mat4 vModelView;
uniform   mat4 vProjection;
uniform   vec3 vColor;

varying   vec3 fColor;

void main()
{
    gl_Position = vProjection * vModelView * vPosition;
    fColor = vColor;
}
