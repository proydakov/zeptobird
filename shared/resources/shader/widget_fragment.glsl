#version 130

precision mediump float;

uniform sampler2D fTexture;

varying vec2      fTexCoord;

void main()
{
    gl_FragColor = texture2D( fTexture, fTexCoord );
}
