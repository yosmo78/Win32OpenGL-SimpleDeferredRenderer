R"(#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 NormalsAndMotionVecs;

varying vec3 vNormal;

//https://discourse.panda3d.org/t/glsl-octahedral-normal-packing/15233
/*

Normal packing as described in:
A Survey of Efficient Representations for Independent Unit Vectors
Source: http://jcgt.org/published/0003/02/01/paper.pdf

*/

// For each component of v, returns -1 if the component is < 0, else 1
vec2 sign_not_zero(vec2 v) 
{
    return step(vec2(0.0), v)*vec2(2.0)+vec2(-1.0);
    //return fma(step(vec2(0.0), v),vec2(2.0),vec2(-1.0));
    //return vec2(v.x >= 0 ? 1.0 : -1.0, v.y >= 0 ? 1.0 : -1.0 );
}

// Packs a 3-component normal to 2 channels using octahedron normals
vec2 pack_normal_octahedron(vec3 v) 
{
	v.xy /= dot(abs(v), vec3(1.0));
	//if (v.z <= 0) v.xy = (1.0 - abs(v.yx)) * sign_not_zero(v.xy);
    //return v.xy;
	return mix(v.xy, (1.0 - abs(v.yx)) * sign_not_zero(v.xy), step(v.z, 0.0));
}

void main()
{
    FragColor = vec4(0.0,1.0,0.0,1.0);
    NormalsAndMotionVecs = vec4(pack_normal_octahedron(normalize(vNormal))*0.5+0.5,0.0,0.0);
}
)"