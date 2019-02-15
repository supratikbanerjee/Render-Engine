#version 330 core
out vec4 frag_colour;

in vec2 TexCoords;
in vec3 WorldPosition;
in vec3 Normals;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_metallic1;
uniform sampler2D texture_roughness1;  

uniform vec3 viewPos;
uniform vec3 lightPos = vec3(1.0, 1.0, 1.0);


float metallicParam = 1.0;
float smoothness = 1.0;

//uniform float roughness = 0.15;
const float PI = 3.14159265359;


vec3 getNormals()
{
    vec3 pos_dx = dFdx(WorldPosition);
    vec3 pos_dy = dFdy(WorldPosition);
    vec3 tex_dx = dFdx(vec3(TexCoords, 0.0));
    vec3 tex_dy = dFdy(vec3(TexCoords, 0.0));
    vec3 t = (tex_dy.t * pos_dx - tex_dx.t * pos_dy) / (tex_dx.s * tex_dy.t - tex_dy.s * tex_dx.t);
    vec3 ng = normalize(Normals);
    t = normalize(t - ng * dot(ng, t));
    vec3 b = -normalize(cross(ng, t));
    mat3 tbn = mat3(t, b, ng);

    vec3 n = texture2D(texture_normal1, TexCoords).rgb;
    n = normalize(tbn * ((2.0 * n - 1.0)));
    return n;
}

float DistributionGGX(float NoH, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = NoH;
    float NdotH2 = NdotH*NdotH;
    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;
    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);
    return ggx1 * ggx2;
}


vec3 FresnelShlicks(float VoH, vec3 F0)
{
    vec3 F = F0 + pow(1.0 - VoH, 5.0) * (1.0 - F0);
    return F;
}

void main()
{
    vec3 albedo = pow(texture(texture_diffuse1, TexCoords).rgb, vec3(2.2));
    float metallic  = texture(texture_metallic1, TexCoords).r;
    float roughness = texture(texture_roughness1, TexCoords).r;


    roughness = roughness * smoothness;
    metallic = metallic * metallicParam;

    vec3 F0 = vec3(0.033);
    F0 = mix(F0, albedo, metallic);
    vec3 Lo = vec3(0.0);

    vec3 N = getNormals();
    N = normalize(Normals);
    vec3 L = normalize(lightPos - WorldPosition);
    vec3 V = normalize(viewPos - WorldPosition);
    vec3 H = normalize(L + V);

    float VoN = max(0, dot(V, N));
    float LoN = max(0, dot(L, N));
    float NoH = max(0, dot(H, N));
    float NoV = max(0, dot(V, N));
    float VoH = max(0, dot(V, H));

    float D = DistributionGGX(NoH, roughness);
    vec3 F = FresnelShlicks(VoH, F0);
    float G = GeometrySmith(N, V, L, roughness);

    vec3 nominator    = D * G * F; 
    float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001;
    vec3 specular = nominator / denominator;

    vec3 kS = F;

    vec3 kD = vec3(1.0)-kS;
    kD *= 1.0 - metallic;

    Lo += (kD * albedo * 8.0 / PI + specular) * LoN;

    vec3 color = Lo;
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2)); 
    frag_colour = vec4(color, 1.0);
}