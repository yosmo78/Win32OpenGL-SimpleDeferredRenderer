 R"(#version 330 core

layout (location = 0) in vec2 aPos;

varying vec2 vTexcoord;

void main()
{
   gl_Position =  vec4( aPos, 0.0, 1.0 );
   vTexcoord =  ( aPos / 2.0 ) + 0.5;
}
)"