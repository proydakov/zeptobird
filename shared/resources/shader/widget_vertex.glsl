precision mediump float;

attribute vec4 vPosition;
attribute vec2 vTexCoord;

uniform   mat4 vModelView;
uniform   mat4 vProjection;

varying   vec2 fTexCoord;

void main()
{
    gl_Position = vProjection * vModelView * vPosition;
    fTexCoord = vTexCoord;
}
