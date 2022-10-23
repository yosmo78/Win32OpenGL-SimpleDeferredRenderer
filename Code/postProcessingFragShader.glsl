R"(#version 330 core

layout (location = 0) out vec4 FragColor;

uniform sampler2D uDiffuseTex;
uniform sampler2D uNormalAndMotionVecTex;
uniform sampler2D uDepthTex;

uniform vec3 uInvLightDir;

varying vec2 vTexcoord;

// For each component of v, returns -1 if the component is < 0, else 1
vec2 sign_not_zero(vec2 v) 
{
    return step(vec2(0.0), v)*vec2(2.0)+vec2(-1.0);
    //return fma(step(vec2(0.0), v),vec2(2.0),vec2(-1.0));
    //return vec2(v.x >= 0 ? 1.0 : -1.0, v.y >= 0 ? 1.0 : -1.0 );
}

// Unpacking from octahedron normals, input is the output from pack_normal_octahedron
vec3 unpack_normal_octahedron(vec2 packed_nrm) 
{
    vec3 v = vec3(packed_nrm.xy, 1.0 - abs(packed_nrm.x) - abs(packed_nrm.y));
    if (v.z < 0) v.xy = (1.0 - abs(v.yx)) * sign_not_zero(v.xy);
    return normalize(v);
}

void main()
{
	vec3 vAlbedo = texture2D(uDiffuseTex,vTexcoord).rgb;
	vec4 vPackedNormalAndMotionVec = texture2D(uNormalAndMotionVecTex,vTexcoord).rgba;
    FragColor = vec4(vAlbedo*max(dot(uInvLightDir,unpack_normal_octahedron((vPackedNormalAndMotionVec.rg-0.5)*2.0)),0.0)+vAlbedo*vec3(0.1,0.1,0.1),1.0);
}
)"