#version 400 core
#define BURLEY_TRUNCATE     16.0f
#define BURLEY_TRUNCATE_CDF 0.9963790093708328f // cdf(BURLEY_TRUNCATE)
out vec4 frag_colour;

in vec2 TexCoords;
in vec3 WorldPosition;
in vec3 Normals;

vec3 TangentLightPos;
vec3 TangentViewPos;
vec3 TangentWorldPos;
mat3 tbn;
uniform mat4 model;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform sampler2D texture_metallic;
uniform sampler2D texture_specular;
uniform sampler2D texture_roughness;  
uniform sampler2D texture_ambient;
uniform sampler2D texture_depth;

uniform vec3 viewPos = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightPos = vec3(1.0f, 1.0f, 1.0f);

//uniform float roughness = 0.15;
const float PI = 3.14159265359;

float mipmapLevel;
float metallic;
float roughness;
float heightScale = 0.1f;
// CLEAN
uniform float occlusion;

//TEMP
uniform float transmission = 0.0f;

//ADD NEW PARAMS
uniform float light_energy = 1.0f;
uniform vec3 base_color = vec3(0.5,0.2,0.1);
uniform float subsurface = 0.0;
uniform vec3 subsurface_radius = vec3(1.0);
uniform vec3 subsurface_color = vec3(1.0);
uniform float p_metallic = 0.0;
uniform float specular = 0.0;
uniform float p_roughness = 0.5;

uniform float mipmap_level = 1.0;

//SWITCHES
uniform bool paralax_map = false;
uniform bool metallic_tex = false;
uniform bool dipole = false;
uniform bool roughness_tex = false;
uniform bool normalMapping = false;
uniform bool mipmap_auto = true;


float saturate(float a) { return clamp(a, 0.0, 1.0); }

vec3 getBumpNormal(mat3 tbn)
{
    const vec2 size = vec2(2.0,0.0);
    const ivec3 off = ivec3(-1,0,1);

    //vec4 depth = texture(texture_depth, TexCoords);
    //float s11 = depth.x;

    float s01 = textureOffset(texture_depth, TexCoords, off.xy).x;
    float s21 = textureOffset(texture_depth, TexCoords, off.zy).x;
    float s10 = textureOffset(texture_depth, TexCoords, off.yx).x;
    float s12 = textureOffset(texture_depth, TexCoords, off.yz).x;
    vec3 ng = normalize(Normals);
    vec3 va = normalize(vec3(size.xy,s21-s01));
    vec3 vb = normalize(vec3(size.yx,s12-s10));

    vec3 bump = vec3(cross(va,vb));

    

    vec3 n = normalize(bump);

    //return n;
    return n;
}

mat3 calculate_tbn()
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
    return tbn; 
}

vec3 getNormals(mat3 tbn)
{
    if(mipmap_auto)
        mipmapLevel = textureQueryLod(texture_normal, TexCoords).x;
    else
        mipmapLevel = mipmap_level;

    vec3 n = textureLod(texture_normal, TexCoords, mipmapLevel).rgb;
    n = normalize(tbn * ((2.0 * n - 1.0)));

    if(normalMapping == false)
    {
       n = normalize(Normals);
    }

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

// Blender
vec3 FresnelShlicks(float VoH, vec3 F0)
{
    float fac = 1.0 - VoH;
    float fac2 = fac * fac;
    fac = fac2 * fac2 * fac;

    /* Unreal specular matching : if specular color is below 2% intensity,
     * (using green channel for intensity) treat as shadowning */
    return saturate(50.0 * dot(F0, vec3(0.3, 0.6, 0.1))) * fac + (1.0 - fac) * F0;
}

// Blender
float schlick_fresnel(float u)
{
    float m = clamp(1.0f - u, 0.0f, 1.0f);
    float m2 = m * m;
    return m2 * m2 * m; // pow(m, 5)
}

vec3 principled_brdf(float NoL, float NoV, float LoH, float roughness)
{
    if(NoL < 0 || NoV < 0)
        return vec3(0.0f);
    float FL = schlick_fresnel(NoL);
    float FV = schlick_fresnel(NoV);
    float Fd90 = 0.5f + 2.0f * LoH*LoH * roughness;
    float Fd = (1.0f * (1.0f - FL) + Fd90 * FL) * (1.0f * (1.0f - FV) + Fd90 * FV);
    float brdf = (1.0/PI) * NoL * Fd;
    return vec3(brdf);
}

vec3 burley_mfp_to_d(vec3 radius, vec3 albedo)
{
    vec3 l = 0.25f * (1.0/PI) * radius;
    vec3 s = 1.9f - albedo + 3.5f * ((albedo - 0.8f) * (albedo - 0.8f));
    return l/s;
}

vec3 principled_bssrdf(vec3 radius, float roughness)
{
    vec3 Rm = BURLEY_TRUNCATE * radius;
    if (radius.x > Rm.x)
        return vec3(0.0f, radius.y, radius.z);
    if (radius.y > Rm.y)
        return vec3(radius.x, 0.0f, radius.z);
    if (radius.z > Rm.z)
        return vec3(radius.x, radius.y, 0.0f);
    vec3 exp_r_3_d = exp(-roughness/ (3.0f * radius));
    vec3 exp_r_d = exp_r_3_d * exp_r_3_d * exp_r_3_d;
    vec3 bssrdf = (exp_r_d + exp_r_3_d) / (4.0f * radius);
    return bssrdf * (1.0f/BURLEY_TRUNCATE_CDF);;
}

/*vec3 principled_bssrdf(vec3 radius, float roughness)
{
    vec3 exp_r_3_d = exp(-roughness/ (3.0f * radius));
    vec3 exp_r_d = exp(-roughness/ radius);
    vec3 bssrdf = (exp_r_d + exp_r_3_d) / (8.0f * PI * radius * roughness);
    return bssrdf;
}*/

vec3 dipole_bssrdf()
{
    vec3 r_scatter = vec3(0.74, 0.88, 1.01);
    vec3 absorption = vec3(0.032, 0.17, 0.4);
    float F = 0.444762840;
    vec3 r_extinction = r_scatter + absorption;
    vec3 r_albedo = r_scatter/r_extinction;
    vec3 effective_extinction = sqrt(3*absorption*r_extinction);
    vec3 D = 1.0/(3*r_extinction);
    vec3 dr = abs(1.0/r_extinction);
    float A = (1.0+F)/(1.0-F);
    vec3 dv = 4*D*A;
    vec3 zv = dr + dv;
    vec3 rp1 = ((effective_extinction*dr+1)*(exp(-effective_extinction*dr)/r_extinction*(dr*dr*dr)));
    vec3 rp2 = zv*((effective_extinction*dv+1)*(exp(-effective_extinction*dv)/r_extinction*(dv*dv*dv)));
    vec3 rp = (r_albedo/(4*PI))*(rp1+rp2);
    return rp;
    //vec3(0.44, 0.22, 0.1);
}

void main()
{
    tbn = calculate_tbn();

    vec3 BSDF = vec3(0.0);
    vec3 L = normalize(lightPos - WorldPosition);
    vec3 V = normalize(viewPos - WorldPosition);
    vec3 H = normalize(L + V);
    vec3 N = getNormals(tbn);
    if(paralax_map)
        N = getBumpNormal(tbn);
    
    float NoV = max(0, dot(N, V));
    float NoL = max(0, dot(N, L));
    float NoH = max(0, dot(N, H));
    float VoH = max(0, dot(V, H));
    float LoH = max(0, dot(L, H));


    if(metallic_tex)
    {
        metallic  = texture(texture_metallic, TexCoords).r;
    }
    else
    {
        metallic = p_metallic;
    }

    // TODO
    float diffuse_weight = (1.0 - clamp(metallic, 0.0, 1.0)) * (1.0 - clamp(transmission, 0.0, 1.0));
    //float final_transmission = clamp(transmission, 0.0, 1.0) * (1.0 - clamp(metallic, 0.0, 1.0));
    //float specular_weight = (1.0 - final_transmission);

    if(roughness_tex)
    {
        roughness = texture(texture_roughness, TexCoords).r;
    }
    else
    {
        roughness = p_roughness;
    }

    if(mipmap_auto)
        mipmapLevel = textureQueryLod(texture_diffuse, TexCoords).x;
    else
        mipmapLevel = mipmap_level;

    vec3 albedo = pow(textureLod(texture_diffuse, TexCoords, mipmapLevel).rgb, vec3(2.2));
    if (diffuse_weight > 1e-5) 
    {
        if (subsurface > 1e-5) 
        {
            vec3 mixed_ss_base_color = subsurface_color * subsurface + albedo * base_color * (1.0 - subsurface);
            vec3 radius = burley_mfp_to_d(subsurface_radius, albedo);

            if(dipole)
                BSDF = BSDF + mixed_ss_base_color * dipole_bssrdf() * principled_brdf(NoL, NoV, LoH, roughness);
            else
                BSDF = BSDF + mixed_ss_base_color * principled_bssrdf(radius, roughness) * principled_brdf(NoL, NoV, LoH, roughness);           
        }
        else
        {
            BSDF = BSDF + albedo*base_color*principled_brdf(NoL, NoV, LoH, roughness);
        }
    }
    BSDF = BSDF * diffuse_weight;

    vec3 F0 = vec3(0.033);
    F0 = mix(F0, albedo, metallic);



    float D = DistributionGGX(NoH, roughness);
    vec3 F = FresnelShlicks(VoH, F0);
    float G = GeometrySmith(N, V, L, roughness);

    vec3 nominator    = D * G * F; 
    float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001;
    vec3 specular_val = nominator / denominator;
    //if(specular_tex)
    //{
    //    specular_val = specular_val * vec3(texture(texture_specular, TexCoords));
    //}
    BSDF = BSDF + specular * specular_val;

    float ambient = texture(texture_ambient, TexCoords).r;

    //vec3 kS = F;
    //vec3 kD = vec3(1.0)-kS;
    //kD *= 1.0 - metallic;
    
    //Lo += (kD* base_color * (albedo / PI) + specular);
    BSDF = BSDF * light_energy;
    vec3 color = mix(BSDF, BSDF * ambient, occlusion); // change 1.0 as AO param
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2)); 
    frag_colour = vec4(color, 1.0); //vec4(color, 1.0);
}