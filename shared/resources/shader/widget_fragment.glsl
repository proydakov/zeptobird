#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D fTexture;

varying vec2      fTexCoord;

void main()
{
    gl_FragColor = texture2D( fTexture, fTexCoord );
}
