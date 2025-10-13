#ifdef GL_ES
precision lowp float;
#endif

varying vec2 v_texCoord;
uniform sampler2D u_texture;

void main()
{
	vec4 color=texture2D(u_texture,v_texCoord);

	float gray= 1.2*color.r+1.02*color.g+1.02*color.b;
	gl_FragColor=vec4(1.2*color.r,1.2*color.g,1.2*color.b,color.a);
}