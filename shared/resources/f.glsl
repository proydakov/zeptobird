precision mediump float;

varying vec3 fColor;

void main()
{
    gl_FragColor = vec4(fColor.x, fColor.y, fColor.z, 1.0);
}
