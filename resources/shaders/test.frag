in vec4 vert_pos;

uniform sampler2D texture;
uniform bool hasTexture;
uniform vec2 lightPos;

void main() {
	vec4 ambient = vec4(0.5, 0.5, 0.5, 1);

	vec2 light = (gl_ModelViewProjectionMatrix * vec4(lightPos, 0, 1)).xy;

	vec2 lightToFrag = light - vert_pos.xy;
	lightToFrag.y = lightToFrag.y / 1.7;

	float vecLength = length(lightToFrag);
	vecLength = vecLength * 4;
	vecLength = clamp(vecLength, 0.f, 1.f);

	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

	if(hasTexture == true)
	{
		gl_FragColor = gl_Color * pixel * (clamp(ambient + vec4(1-vecLength, 1-vecLength, 1-vecLength, 1), 0.f, 1.f));
	}
	else
	{
		gl_FragColor = gl_Color * pixel * (vec4(1-vecLength, 1-vecLength, 1-vecLength, 1) + ambient);
	}
}