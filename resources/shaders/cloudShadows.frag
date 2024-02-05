in vec4 vert_pos;

uniform sampler2D texture;
uniform vec2 cloudPos[20];
uniform vec2 cloudPos2[20];
uniform vec2 cloudPos3[20];
uniform float cloudSize[20];

void main() {
	vec4 ambient = vec4(1, 1, 1, 1);

	bool inShadow = false;

	for(int i = 0; i < 20; i++) {
		vec2 shadowPos = (gl_ModelViewProjectionMatrix * vec4(cloudPos[i], 0, 1)).xy;
		vec2 shadowPos2 = (gl_ModelViewProjectionMatrix * vec4(cloudPos2[i], 0, 1)).xy;
		vec2 shadowPos3 = (gl_ModelViewProjectionMatrix * vec4(cloudPos3[i], 0, 1)).xy;
		if (length(vec2(shadowPos.x - vert_pos.x, (shadowPos.y - vert_pos.y) / 0.7)) < cloudSize[i] || 
			length(vec2(shadowPos2.x - vert_pos.x, (shadowPos2.y - vert_pos.y) / 0.7)) < cloudSize[i] / 1.5 ||
			length(vec2(shadowPos3.x - vert_pos.x, (shadowPos3.y - vert_pos.y) / 0.7)) < cloudSize[i] / 1.5) {
			inShadow = true;
			break;
		}
	}

	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

	if(inShadow) {
		gl_FragColor = gl_Color * pixel * clamp(ambient - vec4(0.85, 0.95, 0.75, 0), 0.f, 1.f);
	} else {
		gl_FragColor = gl_Color * pixel * ambient;
	}
}