in vec4 vert_pos;

uniform sampler2D texture;
uniform vec2 cloudPos[20];
uniform vec2 cloudPos2[20];
uniform float cloudSize[20];

void main() {
	vec4 ambient = vec4(1, 1, 1, 1);
	vec4 shaded = vec4(0.25, 0.15 / 0.68, 0.28 / 0.38, 1/0.7) * 0.7;
	vec4 outline = vec4(0.2, 0.05, 0.3, 1);

	bool inShadow = false;
	bool inOutline = false;

	for(int i = 0; i < 20; i++) {
		vec2 shadowPos = (gl_ModelViewProjectionMatrix * vec4(cloudPos[i], 0, 1)).xy;
		vec2 shadowPos2 = (gl_ModelViewProjectionMatrix * vec4(cloudPos2[i], 0, 1)).xy;
		if (length(vec2(shadowPos.x - vert_pos.x, (shadowPos.y - vert_pos.y) / 0.7)) < cloudSize[i] || 
			length(vec2(shadowPos2.x - vert_pos.x, (shadowPos2.y - vert_pos.y) / 0.7)) < cloudSize[i] / 1.5) {
			inShadow = true;
			break;
		} else if (length(vec2(shadowPos.x - vert_pos.x, (shadowPos.y - vert_pos.y) / 0.7)) < 0.005 + cloudSize[i] ||
				   length(vec2(shadowPos2.x - vert_pos.x, (shadowPos2.y - vert_pos.y) / 0.7)) < 0.005 + cloudSize[i] / 1.5) {
			inOutline = true;
		}
	}

	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

	if(inShadow) {
		gl_FragColor = gl_Color * pixel * shaded;
	} else if (inOutline) {
		gl_FragColor = gl_Color * pixel * outline;
	} else {
		gl_FragColor = gl_Color * pixel * ambient;
	}
}