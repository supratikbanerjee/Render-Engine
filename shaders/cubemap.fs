#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 camView;
uniform samplerCube skybox;

float refractive_ratio = 1.0/1.52;
float F0 = ((1.0-refractive_ratio)*(1.0-refractive_ratio))/((1.0+refractive_ratio)*(1.0+refractive_ratio));

vec3 light_position = vec3(1.0,1.0,1.0);

void main()
{    
	vec3 surfaceToLight = normalize(Position-light_position); //L
	vec3 I = normalize(Position-camView);
    vec3 halfDir = normalize(surfaceToLight + I);  //H

    float VoH = max(0, dot(I, halfDir));


	float F = F0 + pow(1.0 - VoH, 5.0) * (1.0 - F0);

    vec3 R1 = reflect(I, normalize(Normal));
    vec3 R2R = refract(I, normalize(Normal), refractive_ratio - 0.03);
    vec3 R2G = refract(I, normalize(Normal), refractive_ratio - 0.02);
    vec3 R2B = refract(I, normalize(Normal), refractive_ratio - 0.01);

    vec3 reflection = vec3(texture(skybox, R1));

    vec3 refractionR = vec3(texture(skybox, R2R));
    vec3 refractionG = vec3(texture(skybox, R2G));
    vec3 refractionB = vec3(texture(skybox, R2B));

    vec3 refractionColor = vec3(refractionR.r, refractionG.g, refractionB.b);

    vec3 R2 = refract(I, normalize(Normal), refractive_ratio);
    vec3 refraction = vec3(texture(skybox, R2));

    //F = 0.2; //Refraction
    //F = 0.8; //Reflection

    //F = 0.0; //Refraction
    //F = 1.0; //Reflection

    vec3 color = mix(refractionColor,reflection, F);

    FragColor = vec4(color, 1.0);
}