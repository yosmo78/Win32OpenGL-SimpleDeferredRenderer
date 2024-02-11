#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN      
#endif

#include <windows.h> 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL\gl.h>
#include <math.h>
#include <time.h>

#if MAIN_DEBUG
#include <assert.h>
#endif

#include "Models.h"

#define DEFAULT_SCREEN_WIDTH 680
#define DEFAULT_SCREEN_HEIGHT 420

#define PI_F 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f
#define PI_D 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

#define GL_COMPILE_STATUS   	    0x8B81
#define GL_LINK_STATUS      	    0x8B82
#define GL_VERTEX_SHADER    	    0x8B31
#define GL_FRAGMENT_SHADER  	    0x8B30
#define GL_ARRAY_BUFFER     	    0x8892
#define GL_ELEMENT_ARRAY_BUFFER	    0x8893
#define GL_STATIC_DRAW      	    0x88E4
#define GL_TEXTURE0                 0x84C0
#define GL_TEXTURE1                 0x84C1
#define GL_TEXTURE2                 0x84C2
#define GL_TEXTURE3                 0x84C3
#define GL_TEXTURE4                 0x84C4
#define GL_TEXTURE5                 0x84C5
#define GL_TEXTURE6                 0x84C6
#define GL_TEXTURE7                 0x84C7
#define GL_TEXTURE8                 0x84C8
#define GL_TEXTURE9                 0x84C9
#define GL_TEXTURE10                0x84CA
#define GL_TEXTURE11                0x84CB
#define GL_TEXTURE12                0x84CC
#define GL_TEXTURE13                0x84CD
#define GL_TEXTURE14                0x84CE
#define GL_TEXTURE15                0x84CF
#define GL_TEXTURE16                0x84D0
#define GL_TEXTURE17                0x84D1
#define GL_TEXTURE18                0x84D2
#define GL_TEXTURE19                0x84D3
#define GL_TEXTURE20                0x84D4
#define GL_TEXTURE21                0x84D5
#define GL_TEXTURE22                0x84D6
#define GL_TEXTURE23                0x84D7
#define GL_TEXTURE24                0x84D8
#define GL_TEXTURE25                0x84D9
#define GL_TEXTURE26                0x84DA
#define GL_TEXTURE27                0x84DB
#define GL_TEXTURE28                0x84DC
#define GL_TEXTURE29                0x84DD
#define GL_TEXTURE30                0x84DE
#define GL_TEXTURE31                0x84DF
#define GL_ACTIVE_TEXTURE           0x84E0
#define GL_CLAMP_TO_EDGE            0x812F
#define GL_UNSIGNED_INT_24_8        0x84FA
#define GL_DEPTH_COMPONENT16        0x81A5
#define GL_DEPTH_COMPONENT24        0x81A6
#define GL_DEPTH_COMPONENT32        0x81A7
#define GL_DEPTH_COMPONENT32F       0x8CAC
#define GL_DEPTH24_STENCIL8         0x88F0
#define GL_DEPTH_STENCIL            0x84F9
#define GL_MAX_COLOR_ATTACHMENTS    0x8CDF
#define GL_COLOR_ATTACHMENT0        0x8CE0
#define GL_COLOR_ATTACHMENT1        0x8CE1
#define GL_COLOR_ATTACHMENT2        0x8CE2
#define GL_COLOR_ATTACHMENT3        0x8CE3
#define GL_COLOR_ATTACHMENT4        0x8CE4
#define GL_COLOR_ATTACHMENT5        0x8CE5
#define GL_COLOR_ATTACHMENT6        0x8CE6
#define GL_COLOR_ATTACHMENT7        0x8CE7
#define GL_COLOR_ATTACHMENT8        0x8CE8
#define GL_COLOR_ATTACHMENT9        0x8CE9
#define GL_COLOR_ATTACHMENT10       0x8CEA
#define GL_COLOR_ATTACHMENT11       0x8CEB
#define GL_COLOR_ATTACHMENT12       0x8CEC
#define GL_COLOR_ATTACHMENT13       0x8CED
#define GL_COLOR_ATTACHMENT14       0x8CEE
#define GL_COLOR_ATTACHMENT15       0x8CEF
#define GL_COLOR_ATTACHMENT16       0x8CF0
#define GL_COLOR_ATTACHMENT17       0x8CF1
#define GL_COLOR_ATTACHMENT18       0x8CF2
#define GL_COLOR_ATTACHMENT19       0x8CF3
#define GL_COLOR_ATTACHMENT20       0x8CF4
#define GL_COLOR_ATTACHMENT21       0x8CF5
#define GL_COLOR_ATTACHMENT22       0x8CF6
#define GL_COLOR_ATTACHMENT23       0x8CF7
#define GL_COLOR_ATTACHMENT24       0x8CF8
#define GL_COLOR_ATTACHMENT25       0x8CF9
#define GL_COLOR_ATTACHMENT26       0x8CFA
#define GL_COLOR_ATTACHMENT27       0x8CFB
#define GL_COLOR_ATTACHMENT28       0x8CFC
#define GL_COLOR_ATTACHMENT29       0x8CFD
#define GL_COLOR_ATTACHMENT30       0x8CFE
#define GL_COLOR_ATTACHMENT31       0x8CFF
#define GL_DEPTH_ATTACHMENT         0x8D00
#define GL_STENCIL_ATTACHMENT       0x8D20
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821A
#define GL_FRAMEBUFFER              0x8D40
#define GL_FRAMEBUFFER_COMPLETE     0x8CD5
#define GL_READ_FRAMEBUFFER         0x8CA8
#define GL_DRAW_FRAMEBUFFER         0x8CA9

#define WGL_CONTEXT_DEBUG_BIT_ARB                 0x00000001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB    0x00000002
#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB               0x2093
#define WGL_CONTEXT_FLAGS_ARB                     0x2094
#define ERROR_INVALID_VERSION_ARB                 0x2095
#define WGL_CONTEXT_PROFILE_MASK_ARB      	      0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#define ERROR_INVALID_PROFILE_ARB                 0x2096
#define ERROR_INVALID_PIXEL_TYPE_ARB              0x2043
#define ERROR_INCOMPATIBLE_DEVICE_CONTEXTS_ARB    0x2054

#ifdef _WIN64
typedef int64_t khronos_ssize_t;
#else
typedef int32_t khronos_ssize_t;
#endif

typedef khronos_ssize_t GLsizeiptr;
typedef char GLchar;

GLuint (__stdcall *glCreateShader)(GLenum shaderType) = NULL;
void   (__stdcall *glShaderSource)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) = NULL;
void   (__stdcall *glCompileShader)(GLuint shader) = NULL;
void   (__stdcall *glGetShaderiv)(GLuint shader, GLenum pname, GLint* params) = NULL;
void   (__stdcall *glGetShaderInfoLog)(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) = NULL;
GLuint (__stdcall *glCreateProgram)(void) = NULL;
void   (__stdcall *glAttachShader)(GLuint program, GLuint shader) = NULL;
void   (__stdcall *glLinkProgram)(GLuint program) = NULL;
void   (__stdcall *glGetProgramiv)(GLuint program, GLenum pname,GLint* params) = NULL;
void   (__stdcall *glGetProgramInfoLog)(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) = NULL;
void   (__stdcall *glDeleteShader)(GLuint shader) = NULL;
void   (__stdcall *glUseProgram)(GLuint program) = NULL;
void   (__stdcall *glGenBuffers)(GLsizei n, GLuint* buffers) = NULL;
void   (__stdcall *glBindBuffer)(GLenum target, GLuint buffer) = NULL;
void   (__stdcall *glBufferData)(GLenum target, GLsizeiptr size, const void* data, GLenum usage) = NULL;
void   (__stdcall *glVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) = NULL;
void   (__stdcall *glEnableVertexAttribArray)(GLuint index) = NULL;
GLint  (__stdcall *glGetUniformLocation)(GLuint program, const GLchar *name) = NULL;
void   (__stdcall *glUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = NULL;
void   (__stdcall *glUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = NULL;
void   (__stdcall *glUniform3fv)( GLint location, GLsizei count, const GLfloat *value) = NULL;
void   (__stdcall *glUniform4fv)( GLint location, GLsizei count, const GLfloat *value) = NULL;
void   (__stdcall *glUniform1i)( GLint location, GLint v0) = NULL;
void   (__stdcall *glActiveTexture)(GLenum texture) = NULL;
void   (__stdcall *glStencilMaskSeparate)(GLenum face,GLuint mask) = NULL;
void   (__stdcall *glGenVertexArrays)(GLsizei n, GLuint* arrays) = NULL;
void   (__stdcall *glBindVertexArray)(GLuint array) = NULL;  
void   (__stdcall *glGenFramebuffers)(GLsizei n, GLuint *ids) = NULL;
void   (__stdcall *glBindFramebuffer)(GLenum target, GLuint framebuffer) = NULL;
void   (__stdcall *glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = NULL;
GLenum (__stdcall *glCheckFramebufferStatus)(GLenum target) = NULL;
void   (__stdcall *glDrawBuffers)(GLsizei n,const GLenum *bufs) = NULL;
void   (__stdcall *glBlitFramebuffer)(	GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) = NULL;

typedef struct Mat3f
{
	union
	{
		float m[3][3];
	};
} Mat3f;

typedef struct Mat4f
{
	union
	{
		float m[4][4];
	};
} Mat4f;

typedef struct Vec2f
{
	union
	{
		float v[2];
		struct
		{
			float x;
			float y;
		};
	};
} Vec2f;

typedef struct Vec3f
{
	union
	{
		float v[3];
		struct
		{
			float x;
			float y;
			float z;
		};
	};
} Vec3f;

typedef struct Vec4f
{
	union
	{
		float v[4];
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};
} Vec4f;

typedef struct Quatf
{
	union
	{
		float q[4];
		struct
		{
			float w; //real
			float x;
			float y;
			float z;
		};
		struct
		{
			float real; //real;
			Vec3f v;
		};
	};
} Quatf;

typedef struct Vertex
{
    Vec3f vPos;
    Vec3f vNormal;
} Vertex;


uint32_t screen_width = DEFAULT_SCREEN_WIDTH;
uint32_t screen_height = DEFAULT_SCREEN_HEIGHT;

//state
uint8_t Running;
uint8_t isPaused;
uint8_t isFullscreen;

//camera
Vec3f position;
float rotHor;
float rotVert;
const float hFov = 60.0f;
const float vFov = 60.0f;

//movement
float speed = 10.0f; //movement speed
float mouseSensitivity = 5.f;

//Window handles
HDC hDC;
HWND WindowHandle;
RECT winRect;
RECT nonFullScreenRect;
RECT snapPosRect;
uint32_t midX;
uint32_t midY;

//GL
GLuint shaderProgramIDs[2]; //0 is material, 1 post processing
GLint modelUniformLoc;
GLint normalUniformLoc;
GLint projViewUniformLoc;
GLint invLightingUniformLoc;
GLuint materialFrameBuffer[1];
GLuint GBufferTextures[3];
GLint GBufferLocs[3];

//meshes
const uint32_t NUM_MODELS = 5;
GLuint modelVAOs[NUM_MODELS];
Mat4f mModelMatrices[NUM_MODELS];
Mat3f mNormalMatrices[NUM_MODELS];
uint32_t modelIndexCount[NUM_MODELS];
GLuint FullScreenVAO;

inline
void InitMat3f( Mat3f *a_pMat )
{
	a_pMat->m[0][0] = 1; a_pMat->m[0][1] = 0; a_pMat->m[0][2] = 0;
	a_pMat->m[1][0] = 0; a_pMat->m[1][1] = 1; a_pMat->m[1][2] = 0;
	a_pMat->m[2][0] = 0; a_pMat->m[2][1] = 0; a_pMat->m[2][2] = 1;
}

//for 2D translations
inline
void InitTransMat3f( Mat3f *a_pMat, float x, float y )
{
	a_pMat->m[0][0] = 1; a_pMat->m[0][1] = 0; a_pMat->m[0][2] = 0;
	a_pMat->m[1][0] = 0; a_pMat->m[1][1] = 1; a_pMat->m[1][2] = 0;
	a_pMat->m[2][0] = x; a_pMat->m[2][1] = y; a_pMat->m[2][2] = 1;
}

//for 2D translations
inline
void InitTransMat3f( Mat3f *a_pMat, Vec2f *a_pTrans )
{
	a_pMat->m[0][0] = 1;           a_pMat->m[0][1] = 0;           a_pMat->m[0][2] = 0;
	a_pMat->m[1][0] = 0;           a_pMat->m[1][1] = 1;           a_pMat->m[1][2] = 0;
	a_pMat->m[2][0] = a_pTrans->x; a_pMat->m[2][1] = a_pTrans->y; a_pMat->m[2][2] = 1;
}

inline
void InitRotXMat3f( Mat3f *a_pMat, float angle )
{
	a_pMat->m[0][0] = 1; a_pMat->m[0][1] = 0;                        a_pMat->m[0][2] = 0;                   
	a_pMat->m[1][0] = 0; a_pMat->m[1][1] = cosf(angle*PI_F/180.0f);  a_pMat->m[1][2] = sinf(angle*PI_F/180.0f); 
	a_pMat->m[2][0] = 0; a_pMat->m[2][1] = -sinf(angle*PI_F/180.0f); a_pMat->m[2][2] = cosf(angle*PI_F/180.0f);
}

inline
void InitRotYMat3f( Mat3f *a_pMat, float angle )
{
	a_pMat->m[0][0] = cosf(angle*PI_F/180.0f);  a_pMat->m[0][1] = 0; a_pMat->m[0][2] = -sinf(angle*PI_F/180.0f);
	a_pMat->m[1][0] = 0;                        a_pMat->m[1][1] = 1; a_pMat->m[1][2] = 0;                    
	a_pMat->m[2][0] = sinf(angle*PI_F/180.0f);  a_pMat->m[2][1] = 0; a_pMat->m[2][2] = cosf(angle*PI_F/180.0f); 
}

inline
void InitRotZMat3f( Mat3f *a_pMat, float angle )
{
	a_pMat->m[0][0] = cosf(angle*PI_F/180.0f);  a_pMat->m[0][1] = sinf(angle*PI_F/180.0f); a_pMat->m[0][2] = 0;
	a_pMat->m[1][0] = -sinf(angle*PI_F/180.0f); a_pMat->m[1][1] = cosf(angle*PI_F/180.0f); a_pMat->m[1][2] = 0;
	a_pMat->m[2][0] = 0;                        a_pMat->m[2][1] = 0; 					   a_pMat->m[2][2] = 1;
}

inline
void InitRotArbAxisMat3f( Mat3f *a_pMat, Vec3f *a_pAxis, float angle )
{
	float c = cosf(angle*PI_F/180.0f);
	float mC = 1.0f-c;
	float s = sinf(angle*PI_F/180.0f);
	a_pMat->m[0][0] = c                          + (a_pAxis->x*a_pAxis->x*mC); a_pMat->m[0][1] = (a_pAxis->y*a_pAxis->x*mC) + (a_pAxis->z*s);             a_pMat->m[0][2] = (a_pAxis->z*a_pAxis->x*mC) - (a_pAxis->y*s);            
	a_pMat->m[1][0] = (a_pAxis->x*a_pAxis->y*mC) - (a_pAxis->z*s);             a_pMat->m[1][1] = c                          + (a_pAxis->y*a_pAxis->y*mC); a_pMat->m[1][2] = (a_pAxis->z*a_pAxis->y*mC) + (a_pAxis->x*s);            
	a_pMat->m[2][0] = (a_pAxis->x*a_pAxis->z*mC) + (a_pAxis->y*s);             a_pMat->m[2][1] = (a_pAxis->y*a_pAxis->z*mC) - (a_pAxis->x*s);             a_pMat->m[2][2] = c                          + (a_pAxis->z*a_pAxis->z*mC);
}

inline
void InitOrientationMat3f( Mat3f *a_pMat, Vec3f *a_pRight, Vec3f *a_pUp, Vec3f*a_pForward )
{
	a_pMat->m[0][0] = a_pRight->x;   a_pMat->m[0][1] = a_pRight->y;   a_pMat->m[0][2] = a_pRight->z;  
	a_pMat->m[1][0] = a_pUp->x;      a_pMat->m[1][1] = a_pUp->y;      a_pMat->m[1][2] = a_pUp->z;     
	a_pMat->m[2][0] = a_pForward->x; a_pMat->m[2][1] = a_pForward->y; a_pMat->m[2][2] = a_pForward->z;
}


//need to verify ordering, may need to be flipped
inline
void Mat3fMult( Mat3f *a, Mat3f *b, Mat3f *out)
{
	out->m[0][0] = a->m[0][0]*b->m[0][0] + a->m[0][1]*b->m[1][0] + a->m[0][2]*b->m[2][0];
	out->m[0][1] = a->m[0][0]*b->m[0][1] + a->m[0][1]*b->m[1][1] + a->m[0][2]*b->m[2][1];
	out->m[0][2] = a->m[0][0]*b->m[0][2] + a->m[0][1]*b->m[1][2] + a->m[0][2]*b->m[2][2];

	out->m[1][0] = a->m[1][0]*b->m[0][0] + a->m[1][1]*b->m[1][0] + a->m[1][2]*b->m[2][0];
	out->m[1][1] = a->m[1][0]*b->m[0][1] + a->m[1][1]*b->m[1][1] + a->m[1][2]*b->m[2][1];
	out->m[1][2] = a->m[1][0]*b->m[0][2] + a->m[1][1]*b->m[1][2] + a->m[1][2]*b->m[2][2];

	out->m[2][0] = a->m[2][0]*b->m[0][0] + a->m[2][1]*b->m[1][0] + a->m[2][2]*b->m[2][0];
	out->m[2][1] = a->m[2][0]*b->m[0][1] + a->m[2][1]*b->m[1][1] + a->m[2][2]*b->m[2][1];
	out->m[2][2] = a->m[2][0]*b->m[0][2] + a->m[2][1]*b->m[1][2] + a->m[2][2]*b->m[2][2];
}

inline
void Mat3fVecMult( Mat3f *a_pMat, Vec3f *a_pIn, Vec3f *a_pOut)
{
	a_pOut->x = a_pMat->m[0][0]*a_pIn->x + a_pMat->m[1][0]*a_pIn->y + a_pMat->m[2][0]*a_pIn->z;
	a_pOut->y = a_pMat->m[0][1]*a_pIn->x + a_pMat->m[1][1]*a_pIn->y + a_pMat->m[2][1]*a_pIn->z;
	a_pOut->z = a_pMat->m[0][2]*a_pIn->x + a_pMat->m[1][2]*a_pIn->y + a_pMat->m[2][2]*a_pIn->z;
}

inline
void InitMat4f( Mat4f *a_pMat )
{
	a_pMat->m[0][0] = 1; a_pMat->m[0][1] = 0; a_pMat->m[0][2] = 0; a_pMat->m[0][3] = 0;
	a_pMat->m[1][0] = 0; a_pMat->m[1][1] = 1; a_pMat->m[1][2] = 0; a_pMat->m[1][3] = 0;
	a_pMat->m[2][0] = 0; a_pMat->m[2][1] = 0; a_pMat->m[2][2] = 1; a_pMat->m[2][3] = 0;
	a_pMat->m[3][0] = 0; a_pMat->m[3][1] = 0; a_pMat->m[3][2] = 0; a_pMat->m[3][3] = 1;
}

inline
void InitTransMat4f( Mat4f *a_pMat, float x, float y, float z )
{
	a_pMat->m[0][0] = 1; a_pMat->m[0][1] = 0; a_pMat->m[0][2] = 0; a_pMat->m[0][3] = 0;
	a_pMat->m[1][0] = 0; a_pMat->m[1][1] = 1; a_pMat->m[1][2] = 0; a_pMat->m[1][3] = 0;
	a_pMat->m[2][0] = 0; a_pMat->m[2][1] = 0; a_pMat->m[2][2] = 1; a_pMat->m[2][3] = 0;
	a_pMat->m[3][0] = x; a_pMat->m[3][1] = y; a_pMat->m[3][2] = z; a_pMat->m[3][3] = 1;
}

inline
void InitTransMat4f( Mat4f *a_pMat, Vec3f *a_pTrans )
{
	a_pMat->m[0][0] = 1;           a_pMat->m[0][1] = 0;           a_pMat->m[0][2] = 0;           a_pMat->m[0][3] = 0;
	a_pMat->m[1][0] = 0;           a_pMat->m[1][1] = 1;           a_pMat->m[1][2] = 0;           a_pMat->m[1][3] = 0;
	a_pMat->m[2][0] = 0;           a_pMat->m[2][1] = 0;           a_pMat->m[2][2] = 1;           a_pMat->m[2][3] = 0;
	a_pMat->m[3][0] = a_pTrans->x; a_pMat->m[3][1] = a_pTrans->y; a_pMat->m[3][2] = a_pTrans->z; a_pMat->m[3][3] = 1;
}

inline
void InitRotXMat4f( Mat4f *a_pMat, float angle )
{
	a_pMat->m[0][0] = 1; a_pMat->m[0][1] = 0;                        a_pMat->m[0][2] = 0;                       a_pMat->m[0][3] = 0;
	a_pMat->m[1][0] = 0; a_pMat->m[1][1] = cosf(angle*PI_F/180.0f);  a_pMat->m[1][2] = sinf(angle*PI_F/180.0f); a_pMat->m[1][3] = 0;
	a_pMat->m[2][0] = 0; a_pMat->m[2][1] = -sinf(angle*PI_F/180.0f); a_pMat->m[2][2] = cosf(angle*PI_F/180.0f); a_pMat->m[2][3] = 0;
	a_pMat->m[3][0] = 0; a_pMat->m[3][1] = 0;                        a_pMat->m[3][2] = 0;                       a_pMat->m[3][3] = 1;
}

inline
void InitRotYMat4f( Mat4f *a_pMat, float angle )
{
	a_pMat->m[0][0] = cosf(angle*PI_F/180.0f);  a_pMat->m[0][1] = 0; a_pMat->m[0][2] = -sinf(angle*PI_F/180.0f); a_pMat->m[0][3] = 0;
	a_pMat->m[1][0] = 0;                        a_pMat->m[1][1] = 1; a_pMat->m[1][2] = 0;                        a_pMat->m[1][3] = 0;
	a_pMat->m[2][0] = sinf(angle*PI_F/180.0f);  a_pMat->m[2][1] = 0; a_pMat->m[2][2] = cosf(angle*PI_F/180.0f);  a_pMat->m[2][3] = 0;
	a_pMat->m[3][0] = 0;                        a_pMat->m[3][1] = 0; a_pMat->m[3][2] = 0;                        a_pMat->m[3][3] = 1;
}

inline
void InitRotZMat4f( Mat4f *a_pMat, float angle )
{
	a_pMat->m[0][0] = cosf(angle*PI_F/180.0f);  a_pMat->m[0][1] = sinf(angle*PI_F/180.0f); a_pMat->m[0][2] = 0; a_pMat->m[0][3] = 0;
	a_pMat->m[1][0] = -sinf(angle*PI_F/180.0f); a_pMat->m[1][1] = cosf(angle*PI_F/180.0f); a_pMat->m[1][2] = 0; a_pMat->m[1][3] = 0;
	a_pMat->m[2][0] = 0;                        a_pMat->m[2][1] = 0; 					   a_pMat->m[2][2] = 1; a_pMat->m[2][3] = 0;
	a_pMat->m[3][0] = 0;                        a_pMat->m[3][1] = 0;                       a_pMat->m[3][2] = 0; a_pMat->m[3][3] = 1;
}

inline
void InitRotArbAxisMat4f( Mat4f *a_pMat, Vec3f *a_pAxis, float angle )
{
	float c = cosf(angle*PI_F/180.0f);
	float mC = 1.0f-c;
	float s = sinf(angle*PI_F/180.0f);
	a_pMat->m[0][0] = c                          + (a_pAxis->x*a_pAxis->x*mC); a_pMat->m[0][1] = (a_pAxis->y*a_pAxis->x*mC) + (a_pAxis->z*s);             a_pMat->m[0][2] = (a_pAxis->z*a_pAxis->x*mC) - (a_pAxis->y*s);             a_pMat->m[0][3] = 0;
	a_pMat->m[1][0] = (a_pAxis->x*a_pAxis->y*mC) - (a_pAxis->z*s);             a_pMat->m[1][1] = c                          + (a_pAxis->y*a_pAxis->y*mC); a_pMat->m[1][2] = (a_pAxis->z*a_pAxis->y*mC) + (a_pAxis->x*s);             a_pMat->m[1][3] = 0;
	a_pMat->m[2][0] = (a_pAxis->x*a_pAxis->z*mC) + (a_pAxis->y*s);             a_pMat->m[2][1] = (a_pAxis->y*a_pAxis->z*mC) - (a_pAxis->x*s);             a_pMat->m[2][2] = c                          + (a_pAxis->z*a_pAxis->z*mC); a_pMat->m[2][3] = 0;
	a_pMat->m[3][0] = 0;                                                       a_pMat->m[3][1] = 0;                                                       a_pMat->m[3][2] = 0;                                                       a_pMat->m[3][3] = 1;
}

inline
void InitPerspectiveProjectionMat4f( Mat4f *a_pMat, uint64_t width, uint64_t height, float a_hFOV, float a_vFOV, float nearPlane, float farPlane )
{
	float thFOV = tanf(a_hFOV*PI_F/360);
	float tvFOV = tanf(a_vFOV*PI_F/360);
	double dNearPlane = (double)nearPlane;
	double dFarPlane = (double)farPlane;
	double nMinF = (dNearPlane-dFarPlane);
  	float aspect = height / (float)width;
	a_pMat->m[0][0] = aspect/(thFOV*thFOV); a_pMat->m[0][1] = 0;                  a_pMat->m[0][2] = 0;                               		   a_pMat->m[0][3] = 0;
	a_pMat->m[1][0] = 0;                    a_pMat->m[1][1] = 1.0f/(tvFOV*tvFOV); a_pMat->m[1][2] = 0;                               		   a_pMat->m[1][3] = 0;
	a_pMat->m[2][0] = 0;                    a_pMat->m[2][1] = 0;                  a_pMat->m[2][2] = (float)((dFarPlane+dNearPlane)/nMinF);     a_pMat->m[2][3] = -1.0f;
	a_pMat->m[3][0] = 0;                    a_pMat->m[3][1] = 0;                  a_pMat->m[3][2] = (float)(2.0*(dFarPlane*dNearPlane)/nMinF); a_pMat->m[3][3] = 0;
}

inline
void InitInvPerspectiveProjectionMat4f( Mat4f *a_pMat, uint64_t width, uint64_t height, float a_hFOV, float a_vFOV, float nearPlane, float farPlane )
{
	float thFOV = tanf(a_hFOV*PI_F/360);
	float tvFOV = tanf(a_vFOV*PI_F/360);
	double dNearPlane = (double)nearPlane;
	double dFarPlane = (double)farPlane;
	double nMinF = (dNearPlane-dFarPlane);
	double fFarNearDoubled = (2.0*(dFarPlane*dNearPlane));
  	float invAspect = (float)width/height;
	a_pMat->m[0][0] = thFOV*thFOV*invAspect; 		   a_pMat->m[0][1] = 0;             a_pMat->m[0][2] = 0;     a_pMat->m[0][3] = 0;
	a_pMat->m[1][0] = 0;                               a_pMat->m[1][1] = tvFOV * tvFOV; a_pMat->m[1][2] = 0;     a_pMat->m[1][3] = 0;
	a_pMat->m[2][0] = 0;                               a_pMat->m[2][1] = 0;             a_pMat->m[2][2] = 0;     a_pMat->m[2][3] = (float)(nMinF/fFarNearDoubled);
	a_pMat->m[3][0] = 0;                               a_pMat->m[3][1] = 0;             a_pMat->m[3][2] = -1.0f; a_pMat->m[3][3] = (float)((dFarPlane+dNearPlane)/fFarNearDoubled);
}

inline
void InitModelMat4ByQuatf( Mat4f *a_pMat, Quatf *a_qRot, Vec3f *a_pPos )
{
	a_pMat->m[0][0] = 1.0f - 2.0f*(a_qRot->y*a_qRot->y + a_qRot->z*a_qRot->z);                            a_pMat->m[0][1] = 2.0f*(a_qRot->x*a_qRot->y + a_qRot->w*a_qRot->z);                                   a_pMat->m[0][2] = 2.0f*(a_qRot->x*a_qRot->z - a_qRot->w*a_qRot->y);        		                      a_pMat->m[0][3] = 0;
	a_pMat->m[1][0] = 2.0f*(a_qRot->x*a_qRot->y - a_qRot->w*a_qRot->z);                                   a_pMat->m[1][1] = 1.0f - 2.0f*(a_qRot->x*a_qRot->x + a_qRot->z*a_qRot->z);                            a_pMat->m[1][2] = 2.0f*(a_qRot->y*a_qRot->z + a_qRot->w*a_qRot->x);        		                      a_pMat->m[1][3] = 0;
	a_pMat->m[2][0] = 2.0f*(a_qRot->x*a_qRot->z + a_qRot->w*a_qRot->y);                                   a_pMat->m[2][1] = 2.0f*(a_qRot->y*a_qRot->z - a_qRot->w*a_qRot->x);                                   a_pMat->m[2][2] = 1.0f - 2.0f*(a_qRot->x*a_qRot->x + a_qRot->y*a_qRot->y); 		                      a_pMat->m[2][3] = 0;
	//a_pMat->m[3][0] = a_pPos->x*a_pMat->m[0][0] + a_pPos->y*a_pMat->m[1][0] + a_pPos->z*a_pMat->m[2][0];  a_pMat->m[3][1] = a_pPos->x*a_pMat->m[0][1] + a_pPos->y*a_pMat->m[1][1] + a_pPos->z*a_pMat->m[2][1]; a_pMat->m[3][2] = a_pPos->x*a_pMat->m[0][2] + a_pPos->y*a_pMat->m[1][2] + a_pPos->z*a_pMat->m[2][2]; a_pMat->m[3][3] = 1;
	a_pMat->m[3][0] = a_pPos->x;  a_pMat->m[3][1] = a_pPos->y; a_pMat->m[3][2] = a_pPos->z; a_pMat->m[3][3] = 1;
}

inline
void Mat4fMult( Mat4f *__restrict a, Mat4f *__restrict b, Mat4f *__restrict out)
{
	out->m[0][0] = a->m[0][0]*b->m[0][0] + a->m[0][1]*b->m[1][0] + a->m[0][2]*b->m[2][0] + a->m[0][3]*b->m[3][0];
	out->m[0][1] = a->m[0][0]*b->m[0][1] + a->m[0][1]*b->m[1][1] + a->m[0][2]*b->m[2][1] + a->m[0][3]*b->m[3][1];
	out->m[0][2] = a->m[0][0]*b->m[0][2] + a->m[0][1]*b->m[1][2] + a->m[0][2]*b->m[2][2] + a->m[0][3]*b->m[3][2];
	out->m[0][3] = a->m[0][0]*b->m[0][3] + a->m[0][1]*b->m[1][3] + a->m[0][2]*b->m[2][3] + a->m[0][3]*b->m[3][3];

	out->m[1][0] = a->m[1][0]*b->m[0][0] + a->m[1][1]*b->m[1][0] + a->m[1][2]*b->m[2][0] + a->m[1][3]*b->m[3][0];
	out->m[1][1] = a->m[1][0]*b->m[0][1] + a->m[1][1]*b->m[1][1] + a->m[1][2]*b->m[2][1] + a->m[1][3]*b->m[3][1];
	out->m[1][2] = a->m[1][0]*b->m[0][2] + a->m[1][1]*b->m[1][2] + a->m[1][2]*b->m[2][2] + a->m[1][3]*b->m[3][2];
	out->m[1][3] = a->m[1][0]*b->m[0][3] + a->m[1][1]*b->m[1][3] + a->m[1][2]*b->m[2][3] + a->m[1][3]*b->m[3][3];

	out->m[2][0] = a->m[2][0]*b->m[0][0] + a->m[2][1]*b->m[1][0] + a->m[2][2]*b->m[2][0] + a->m[2][3]*b->m[3][0];
	out->m[2][1] = a->m[2][0]*b->m[0][1] + a->m[2][1]*b->m[1][1] + a->m[2][2]*b->m[2][1] + a->m[2][3]*b->m[3][1];
	out->m[2][2] = a->m[2][0]*b->m[0][2] + a->m[2][1]*b->m[1][2] + a->m[2][2]*b->m[2][2] + a->m[2][3]*b->m[3][2];
	out->m[2][3] = a->m[2][0]*b->m[0][3] + a->m[2][1]*b->m[1][3] + a->m[2][2]*b->m[2][3] + a->m[2][3]*b->m[3][3];

	out->m[3][0] = a->m[3][0]*b->m[0][0] + a->m[3][1]*b->m[1][0] + a->m[3][2]*b->m[2][0] + a->m[3][3]*b->m[3][0];
	out->m[3][1] = a->m[3][0]*b->m[0][1] + a->m[3][1]*b->m[1][1] + a->m[3][2]*b->m[2][1] + a->m[3][3]*b->m[3][1];
	out->m[3][2] = a->m[3][0]*b->m[0][2] + a->m[3][1]*b->m[1][2] + a->m[3][2]*b->m[2][2] + a->m[3][3]*b->m[3][2];
	out->m[3][3] = a->m[3][0]*b->m[0][3] + a->m[3][1]*b->m[1][3] + a->m[3][2]*b->m[2][3] + a->m[3][3]*b->m[3][3];
}

inline
float DeterminantUpper3x3Mat4f( Mat4f *a_pMat )
{
	return (a_pMat->m[0][0] * ((a_pMat->m[1][1]*a_pMat->m[2][2]) - (a_pMat->m[1][2]*a_pMat->m[2][1]))) + 
		   (a_pMat->m[0][1] * ((a_pMat->m[2][0]*a_pMat->m[1][2]) - (a_pMat->m[1][0]*a_pMat->m[2][2]))) + 
		   (a_pMat->m[0][2] * ((a_pMat->m[1][0]*a_pMat->m[2][1]) - (a_pMat->m[2][0]*a_pMat->m[1][1])));
}

inline
void InverseUpper3x3Mat4f( Mat4f *__restrict a_pMat, Mat4f *__restrict out )
{
	float fDet = DeterminantUpper3x3Mat4f( a_pMat );
#if MAIN_DEBUG
	assert( fDet != 0.f );
#endif
	float fInvDet = 1.0f / fDet;
	out->m[0][0] = fInvDet * ((a_pMat->m[1][1]*a_pMat->m[2][2]) - (a_pMat->m[1][2]*a_pMat->m[2][1]));
	out->m[0][1] = fInvDet * ((a_pMat->m[0][2]*a_pMat->m[2][1]) - (a_pMat->m[0][1]*a_pMat->m[2][2]));
	out->m[0][2] = fInvDet * ((a_pMat->m[0][1]*a_pMat->m[1][2]) - (a_pMat->m[0][2]*a_pMat->m[1][1]));
	out->m[0][3] = 0.0f;

	out->m[1][0] = fInvDet * ((a_pMat->m[2][0]*a_pMat->m[1][2]) - (a_pMat->m[2][2]*a_pMat->m[1][0]));
	out->m[1][1] = fInvDet * ((a_pMat->m[0][0]*a_pMat->m[2][2]) - (a_pMat->m[0][2]*a_pMat->m[2][0])); 
	out->m[1][2] = fInvDet * ((a_pMat->m[0][2]*a_pMat->m[1][0]) - (a_pMat->m[1][2]*a_pMat->m[0][0]));
	out->m[1][3] = 0.0f;

	out->m[2][0] = fInvDet * ((a_pMat->m[1][0]*a_pMat->m[2][1]) - (a_pMat->m[1][1]*a_pMat->m[2][0]));
	out->m[2][1] = fInvDet * ((a_pMat->m[0][1]*a_pMat->m[2][0]) - (a_pMat->m[0][0]*a_pMat->m[2][1]));
	out->m[2][2] = fInvDet * ((a_pMat->m[0][0]*a_pMat->m[1][1]) - (a_pMat->m[1][0]*a_pMat->m[0][1]));
	out->m[2][3] = 0.0f;

	out->m[3][0] = 0.0f;
	out->m[3][1] = 0.0f;
	out->m[3][2] = 0.0f;
	out->m[3][3] = 1.0f;
}

inline
void InverseTransposeUpper3x3Mat4f( Mat4f *__restrict a_pMat, Mat4f *__restrict out )
{
	float fDet = DeterminantUpper3x3Mat4f( a_pMat );
#if MAIN_DEBUG
	assert( fDet != 0.f );
#endif
	float fInvDet = 1.0f / fDet;
	out->m[0][0] = fInvDet * ((a_pMat->m[1][1]*a_pMat->m[2][2]) - (a_pMat->m[1][2]*a_pMat->m[2][1]));
	out->m[0][1] = fInvDet * ((a_pMat->m[2][0]*a_pMat->m[1][2]) - (a_pMat->m[2][2]*a_pMat->m[1][0]));
	out->m[0][2] = fInvDet * ((a_pMat->m[1][0]*a_pMat->m[2][1]) - (a_pMat->m[1][1]*a_pMat->m[2][0]));
	out->m[0][3] = 0.0f;

	out->m[1][0] = fInvDet * ((a_pMat->m[0][2]*a_pMat->m[2][1]) - (a_pMat->m[0][1]*a_pMat->m[2][2]));
	out->m[1][1] = fInvDet * ((a_pMat->m[0][0]*a_pMat->m[2][2]) - (a_pMat->m[0][2]*a_pMat->m[2][0])); 
	out->m[1][2] = fInvDet * ((a_pMat->m[0][1]*a_pMat->m[2][0]) - (a_pMat->m[0][0]*a_pMat->m[2][1]));
	out->m[1][3] = 0.0f;

	out->m[2][0] = fInvDet * ((a_pMat->m[0][1]*a_pMat->m[1][2]) - (a_pMat->m[0][2]*a_pMat->m[1][1]));
	out->m[2][1] = fInvDet * ((a_pMat->m[0][2]*a_pMat->m[1][0]) - (a_pMat->m[1][2]*a_pMat->m[0][0]));
	out->m[2][2] = fInvDet * ((a_pMat->m[0][0]*a_pMat->m[1][1]) - (a_pMat->m[1][0]*a_pMat->m[0][1]));
	out->m[2][3] = 0.0f;

	out->m[3][0] = 0.0f;
	out->m[3][1] = 0.0f;
	out->m[3][2] = 0.0f;
	out->m[3][3] = 1.0f;
}

inline
void InverseTransposeUpper3x3Mat3f( Mat4f *__restrict a_pMat, Mat3f *__restrict out )
{
	float fDet = DeterminantUpper3x3Mat4f( a_pMat );
#if MAIN_DEBUG
	assert( fDet != 0.f );
#endif
	float fInvDet = 1.0f / fDet;
	out->m[0][0] = fInvDet * ((a_pMat->m[1][1]*a_pMat->m[2][2]) - (a_pMat->m[1][2]*a_pMat->m[2][1]));
	out->m[0][1] = fInvDet * ((a_pMat->m[2][0]*a_pMat->m[1][2]) - (a_pMat->m[2][2]*a_pMat->m[1][0]));
	out->m[0][2] = fInvDet * ((a_pMat->m[1][0]*a_pMat->m[2][1]) - (a_pMat->m[1][1]*a_pMat->m[2][0]));

	out->m[1][0] = fInvDet * ((a_pMat->m[0][2]*a_pMat->m[2][1]) - (a_pMat->m[0][1]*a_pMat->m[2][2]));
	out->m[1][1] = fInvDet * ((a_pMat->m[0][0]*a_pMat->m[2][2]) - (a_pMat->m[0][2]*a_pMat->m[2][0])); 
	out->m[1][2] = fInvDet * ((a_pMat->m[0][1]*a_pMat->m[2][0]) - (a_pMat->m[0][0]*a_pMat->m[2][1]));

	out->m[2][0] = fInvDet * ((a_pMat->m[0][1]*a_pMat->m[1][2]) - (a_pMat->m[0][2]*a_pMat->m[1][1]));
	out->m[2][1] = fInvDet * ((a_pMat->m[0][2]*a_pMat->m[1][0]) - (a_pMat->m[1][2]*a_pMat->m[0][0]));
	out->m[2][2] = fInvDet * ((a_pMat->m[0][0]*a_pMat->m[1][1]) - (a_pMat->m[1][0]*a_pMat->m[0][1]));
}

inline
void Vec3fAdd( Vec3f *a, Vec3f *b, Vec3f *out )
{
	out->x = a->x + b->x;
	out->y = a->y + b->y;
	out->z = a->z + b->z;
}

inline
void Vec3fMult( Vec3f *a, Vec3f *b, Vec3f *out )
{
	out->x = a->x * b->x;
	out->y = a->y * b->y;
	out->z = a->z * b->z;
}

inline
void Vec3fCross( Vec3f *a, Vec3f *b, Vec3f *out )
{
	out->x = (a->y * b->z) - (a->z * b->y);
	out->y = (a->z * b->x) - (a->x * b->z);
	out->z = (a->x * b->y) - (a->y * b->x);
}

inline
void Vec3fScale( Vec3f *a, float scale, Vec3f *out )
{
	out->x = a->x * scale;
	out->y = a->y * scale;
	out->z = a->z * scale;
}

inline
float Vec3fDot( Vec3f *a, Vec3f *b )
{
	return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

inline
void Vec3fNormalize( Vec3f *a, Vec3f *out )
{

	float mag = sqrtf((a->x*a->x) + (a->y*a->y) + (a->z*a->z));
	if(mag == 0)
	{
		out->x = 0;
		out->y = 0;
		out->z = 0;
	}
	else
	{
		out->x = a->x/mag;
		out->y = a->y/mag;
		out->z = a->z/mag;
	}
}

inline
void InitUnitQuatf( Quatf *q, float angle, Vec3f *axis )
{
	float s = sinf(angle*PI_F/360.0f);
	q->w = cosf(angle*PI_F/360.0f);
	q->x = axis->x * s;
	q->y = axis->y * s;
	q->z = axis->z * s;
}

inline
void QuatfMult( Quatf *__restrict a, Quatf *__restrict b, Quatf *__restrict out )
{
	out->w = (a->w * b->w) - (a->x* b->x) - (a->y* b->y) - (a->z* b->z);
	out->x = (a->w * b->x) + (a->x* b->w) + (a->y* b->z) - (a->z* b->y);
	out->y = (a->w * b->y) + (a->y* b->w) + (a->z* b->x) - (a->x* b->z);
	out->z = (a->w * b->z) + (a->z* b->w) + (a->x* b->y) - (a->y* b->x);
}

inline
void InitViewMat4ByQuatf( Mat4f *a_pMat, float horizontalAngle, float verticalAngle, Vec3f *a_pPos )
{
	Quatf qRot;
	qRot.w =  cosf(verticalAngle*PI_F/360.0f) * cosf(horizontalAngle*PI_F/360.0f);
	qRot.x = -sinf(verticalAngle*PI_F/360.0f) * cosf(horizontalAngle*PI_F/360.0f);
	qRot.y = -cosf(verticalAngle*PI_F/360.0f) * sinf(horizontalAngle*PI_F/360.0f);
	qRot.z = -sinf(verticalAngle*PI_F/360.0f) * sinf(horizontalAngle*PI_F/360.0f);

	a_pMat->m[0][0] = 1.0f - 2.0f*(qRot.y*qRot.y + qRot.z*qRot.z);                                        a_pMat->m[0][1] = 2.0f*(qRot.x*qRot.y - qRot.w*qRot.z);                                               a_pMat->m[0][2] = 2.0f*(qRot.x*qRot.z + qRot.w*qRot.y);        		                                  a_pMat->m[0][3] = 0;
	a_pMat->m[1][0] = 2.0f*(qRot.x*qRot.y + qRot.w*qRot.z);                                               a_pMat->m[1][1] = 1.0f - 2.0f*(qRot.x*qRot.x + qRot.z*qRot.z);                                        a_pMat->m[1][2] = 2.0f*(qRot.y*qRot.z - qRot.w*qRot.x);        		                                  a_pMat->m[1][3] = 0;
	a_pMat->m[2][0] = 2.0f*(qRot.x*qRot.z - qRot.w*qRot.y);                                               a_pMat->m[2][1] = 2.0f*(qRot.y*qRot.z + qRot.w*qRot.x);                                               a_pMat->m[2][2] = 1.0f - 2.0f*(qRot.x*qRot.x + qRot.y*qRot.y); 		                                  a_pMat->m[2][3] = 0;
	a_pMat->m[3][0] = -a_pPos->x*a_pMat->m[0][0] - a_pPos->y*a_pMat->m[1][0] - a_pPos->z*a_pMat->m[2][0]; a_pMat->m[3][1] = -a_pPos->x*a_pMat->m[0][1] - a_pPos->y*a_pMat->m[1][1] - a_pPos->z*a_pMat->m[2][1]; a_pMat->m[3][2] = -a_pPos->x*a_pMat->m[0][2] - a_pPos->y*a_pMat->m[1][2] - a_pPos->z*a_pMat->m[2][2]; a_pMat->m[3][3] = 1;
}

void PrintMat4f( Mat4f *a_pMat )
{
	for( uint32_t dwIdx = 0; dwIdx < 4; ++dwIdx )
	{
		for( uint32_t dwJdx = 0; dwJdx < 4; ++dwJdx )
		{
			printf("%f ", a_pMat->m[dwIdx][dwJdx] );
		}
		printf("\n");
	}
}

float clamp(float d, float min, float max) {
  const float t = d < min ? min : d;
  return t > max ? max : t;
}

void CloseProgram()
{
	Running = 0;
}

inline
void CenterCursor( HWND Window )
{
    GetWindowRect(Window, &winRect);
    midX = winRect.left + (screen_width / 2);
    midY = winRect.top + (screen_height / 2);
    snapPosRect.left = (int32_t)midX;
    snapPosRect.right = (int32_t)midX;
    snapPosRect.top = (int32_t)midY;
    snapPosRect.bottom = (int32_t)midY;
    if( !isPaused )
    {
        ClipCursor(&snapPosRect);
    }	
}


void Pause()
{
	if( !isPaused )
	{
		isPaused = 1;
    	ClipCursor( NULL );
    	ShowCursor( TRUE );
	}
}

void TogglePause()
{
	isPaused = isPaused ^ 1;
    if( isPaused )
    {
    	ClipCursor( NULL );
    	ShowCursor( TRUE );
    }
    else
    {
    	ClipCursor(&snapPosRect);
    	ShowCursor( FALSE );
    }
}

//look into display modes
//https://stackoverflow.com/questions/7193197/is-there-a-graceful-way-to-handle-toggling-between-fullscreen-and-windowed-mode
void Fullscreen( HWND WindowHandle )
{
	isFullscreen = isFullscreen ^ 1;
	if( isFullscreen )
	{
		nonFullScreenRect.left = winRect.left;
		nonFullScreenRect.right = winRect.right;
		nonFullScreenRect.bottom = winRect.bottom;
		nonFullScreenRect.top = winRect.top;
		SetWindowLong(WindowHandle, GWL_STYLE, WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE );
		HMONITOR hmon = MonitorFromWindow(WindowHandle, MONITOR_DEFAULTTONEAREST);
		MONITORINFO mi = { sizeof(mi) };
        GetMonitorInfo(hmon, &mi);
		screen_width = mi.rcMonitor.right - mi.rcMonitor.left;
    	screen_height = mi.rcMonitor.bottom - mi.rcMonitor.top;
    	MoveWindow(WindowHandle,mi.rcMonitor.left,mi.rcMonitor.top,(int32_t)screen_width,(int32_t)screen_height, FALSE );
        glViewport(0, 0, screen_width, screen_height); 
        CenterCursor( WindowHandle );
	}
	else
	{
		SetWindowLongPtr(WindowHandle, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
		screen_width = nonFullScreenRect.right - nonFullScreenRect.left;
    	screen_height = nonFullScreenRect.bottom - nonFullScreenRect.top;
    	MoveWindow(WindowHandle,nonFullScreenRect.left,nonFullScreenRect.top,(int32_t)screen_width,(int32_t)screen_height, FALSE );
        glViewport(0, 0, screen_width, screen_height); 
        CenterCursor( WindowHandle );
	}
}

void LogGLErrorAndQuit( const char *szMsg)
{
	FILE * file = fopen("GLERROR.txt","w");
    fprintf(file,"%s\n", szMsg);
    fclose(file);
    exit(-1);
}

LRESULT CALLBACK
Win32MainWindowCallback(
    HWND Window,   //HWND a handle to a window
    UINT Message,  //System defined message, Window will call us and ask us to respond it
    WPARAM WParam, //
    LPARAM LParam) //
{
    LRESULT Result = 0;
    switch (Message)
    {
    case WM_SIZE:
    {
    	screen_width = LOWORD(LParam);
    	screen_height = HIWORD(LParam);
        glViewport(0, 0, screen_width, screen_height); //needed for window resizing
        if( materialFrameBuffer[0] )
        {
        	/*
        	glActiveTexture( GL_TEXTURE0 );
			glBindTexture( GL_TEXTURE_2D, NULL );
			glActiveTexture( GL_TEXTURE1 );
    		glBindTexture( GL_TEXTURE_2D, NULL);
    		glActiveTexture( GL_TEXTURE2 );
    		glBindTexture( GL_TEXTURE_2D, NULL);
    		*/
    		glBindFramebuffer( GL_FRAMEBUFFER, NULL );
    		/*
    		glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, NULL, 0 );
    		glFramebufferTexture2D( GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D,NULL,0 );
    		glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D,NULL,0 );
			*/
    		glDeleteTextures( 3, GBufferTextures );
    		glGenTextures( 3, GBufferTextures );
			glBindFramebuffer( GL_FRAMEBUFFER, materialFrameBuffer[0] );
    		glBindTexture( GL_TEXTURE_2D, GBufferTextures[0] );
    		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, screen_width, screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
    		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ); //change to border?
    		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ); //change to border?
    		glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GBufferTextures[0], 0 );
		
    		glBindTexture( GL_TEXTURE_2D, GBufferTextures[1] );
    		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, screen_width, screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
    		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ); //change to border?
    		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ); //change to border?
    		glFramebufferTexture2D( GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D,GBufferTextures[1],0 );
		
    		if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
    		{
				LogGLErrorAndQuit("Failed to init Main Frame Buffer!");
    		    return false;
    		}
		
    		glBindTexture( GL_TEXTURE_2D, GBufferTextures[2]);
    		glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screen_width, screen_height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL ); 
    		//glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_STENCIL, m_width, m_height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT, NULL );
    		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ); //change to border?
    		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    		glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D,GBufferTextures[2],0 );
			//glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,GBufferTextures[2],0 );

    		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    		{
    			LogGLErrorAndQuit("Failed to init RAME BUFFER Depth!");
    		    return false;
    		}
		
    		glBindFramebuffer(GL_FRAMEBUFFER, NULL);
    		glBindTexture(GL_TEXTURE_2D, NULL);
    	}
        CenterCursor( Window );
    }break;

    case WM_MOVE:
    {
    	CenterCursor( Window );
    }break;

    case WM_GETMINMAXINFO:
    {
        LPMINMAXINFO lpMMI = (LPMINMAXINFO)LParam;
        lpMMI->ptMinTrackSize.x = 300;
        lpMMI->ptMinTrackSize.y = 300;
    }break;

    case WM_CLOSE: //when user clicks on the X button on the window
    {
        CloseProgram();
    } break;

    case WM_PAINT: //to allow us to update the window
    {
        //drawScene( shaderProgram, 0.0f );
        PAINTSTRUCT Paint;
        HDC DeviceContext = BeginPaint(Window, &Paint); //will fill out struct with information on where to paint
        EndPaint(Window, &Paint); //closes paint area
    } break;


    case WM_ACTIVATE:
    {
    	switch(WParam)
    	{
    		case WA_ACTIVE:
    		case WA_CLICKACTIVE:
    		{

    		} break;
    		case WA_INACTIVE:
    		{
    			//Pause();
    		} break;
    		default:
    		{
    			//error
    		}
    	}
    } break;

    default:
        Result = DefWindowProc(Window, Message, WParam, LParam); //call windows to handle default behavior of things we don't handle
    }

    return Result;
}

#if MAIN_DEBUG
int CreateOpenGLWindow()
#else
int CreateOpenGLWindow( HINSTANCE Instance )
#endif
{
    WNDCLASSEX WindowClass;
    WindowClass.cbSize = sizeof(WNDCLASSEX);
    WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW; //https://devblogs.microsoft.com/oldnewthing/20060601-06/?p=31003
    WindowClass.lpfnWndProc = Win32MainWindowCallback;
    WindowClass.cbClsExtra = 0;
    WindowClass.cbWndExtra = 0;
#if MAIN_DEBUG
    WindowClass.hInstance = GetModuleHandle(NULL);
#else
    WindowClass.hInstance = Instance;
#endif
    WindowClass.hIcon = LoadIcon(0, IDI_APPLICATION); //IDI_APPLICATION: Default application icon, 0 means use a default Icon
    WindowClass.hCursor = LoadCursor(0, IDC_ARROW); //IDC_ARROW: Standard arrow, 0 means used a predefined Cursor
    WindowClass.hbrBackground = NULL; 
    WindowClass.lpszMenuName = NULL;	// No menu 
    WindowClass.lpszClassName = "TheButtonWindowClass"; //name our class
    WindowClass.hIconSm = NULL; //can also do default Icon here? will NULL be default automatically?
    if ( !RegisterClassEx(&WindowClass) )
    {
    	return -1;
    }
    WindowHandle = CreateWindowEx(0, WindowClass.lpszClassName, "The Button",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
        CW_USEDEFAULT, CW_USEDEFAULT, screen_width, screen_height, //if fullscreen get monitor width and height
        0, 0, WindowClass.hInstance, NULL);
    if( !WindowHandle )
    {
    	return -1;
    }
    
    //Associate OpenGL with out window
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
        PFD_TYPE_RGBA,												// The kind of framebuffer. RGBA or palette.
        32,															// Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0, 0, 0,
        0,
        0, 0, 0, 0,
        24,															// Number of bits for the depthbuffer
        8,															// Number of bits for the stencilbuffer
        0,															// Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };
    hDC = GetDC(WindowHandle);				// Get a DC for our window
    int letWindowsChooseThisPixelFormat = ChoosePixelFormat(hDC, &pfd); // Let windows select an appropriate pixel format
    if( !letWindowsChooseThisPixelFormat )
    {
        return -1;
    }
    if( !SetPixelFormat(hDC, letWindowsChooseThisPixelFormat, &pfd) )
    {
        return -1;
    }
    HGLRC ourOpenGLRC = wglCreateContext(hDC); //wglCreateContextAttribs
    if (!ourOpenGLRC)
    {
        return -1;
    }
    wglMakeCurrent(hDC, ourOpenGLRC); // Make our render context current

    //switch to ARB context if available to allow RenderDoc to work
#if MAIN_DEBUG
    int contextFlags = WGL_CONTEXT_DEBUG_BIT_ARB;
#else
    int contextFlags = 0;
#endif

    // Alright, now for the modernity. First try a 4.4, then 4.3, context, if that fails try 3.3.
    // I can't seem to find a way that lets you simply request the newest version available.
    const int attribs44[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 4,
        WGL_CONTEXT_FLAGS_ARB, contextFlags,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
        0
    };
    const int attribs43[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_FLAGS_ARB, contextFlags,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
        0
    };
    const int attribs33[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_FLAGS_ARB, contextFlags,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
        0
    };

	const char *(__stdcall *wglGetExtensionsString)(void)       = (const char *(__stdcall *)(void))((void*)wglGetProcAddress ( "wglGetExtensionsString" ));
	const char *(__stdcall *wglGetExtensionsStringEXT)(void)    = (const char *(__stdcall *)(void))((void*)wglGetProcAddress ( "wglGetExtensionsStringEXT" ));
	const char *(__stdcall *wglGetExtensionsStringARB)(HDC hdc) = (const char *(__stdcall *)(HDC hdc))((void*)wglGetProcAddress ( "wglGetExtensionsStringARB" ));;
	HGLRC (__stdcall *wglCreateContextAttribsARB) (HDC hDC, HGLRC hShareContext, const int *attribList) = (HGLRC (__stdcall *)(HDC hDC, HGLRC hShareContext, const int *attribList))((void*)wglGetProcAddress ( "wglCreateContextAttribsARB" ));

	if( (wglGetExtensionsStringARB || wglGetExtensionsStringEXT) && wglCreateContextAttribsARB )
	{
		HGLRC ourDebugOpenGLRC;
		if( (wglGetExtensionsStringARB && strstr ( wglGetExtensionsStringARB(hDC), "WGL_ARB_create_context" ) != nullptr)
			|| (wglGetExtensionsStringEXT && strstr ( wglGetExtensionsStringEXT(), "WGL_ARB_create_context" ) != nullptr) )
		{
    		ourDebugOpenGLRC = wglCreateContextAttribsARB(hDC, 0, attribs44);
    		if (!ourDebugOpenGLRC)
    		{
    		    ourDebugOpenGLRC = wglCreateContextAttribsARB(hDC, 0, attribs43);
    		}
    		if (!ourDebugOpenGLRC)
    		{
    		    ourDebugOpenGLRC = wglCreateContextAttribsARB(hDC, 0, attribs33);
    		}

    		if (!ourDebugOpenGLRC) 
    		{
    		    // Fall back
    		    ourDebugOpenGLRC = ourOpenGLRC;
    		} 
    		else 
    		{
    		    // Switch to the new ARB context.
    		    wglMakeCurrent(NULL, NULL);
    		    wglDeleteContext(ourOpenGLRC);
    		    wglMakeCurrent(hDC, ourDebugOpenGLRC);
    		}
		}
		else
		{
			ourDebugOpenGLRC = ourOpenGLRC;
		}
	}

    return 0;
}


/* make sure you are in wgl Context!*/
inline void loadGLFuncPtrs()
{
    //load needed version specific opengl funcs
    int ver = glGetString(GL_VERSION)[0] - '0'; //is opengl 2.0 compatible
    if (ver > 4) ver = 4; //future proofing
    switch (ver)
    {
        case 4: 
        {
            //opengl version 4.0 required
        }
        case 3: 
        {
            //opengl version 3.0 required
            glGenVertexArrays = (void(__stdcall*)(GLsizei n, GLuint * arrays))((void*)wglGetProcAddress("glGenVertexArrays"));
            glBindVertexArray = (void(__stdcall*)(GLuint array))((void*)wglGetProcAddress("glBindVertexArray"));
            glGenFramebuffers = (void(__stdcall*)(GLsizei n, GLuint *ids))((void*)wglGetProcAddress("glGenFramebuffers"));
            glBindFramebuffer = (void(__stdcall*)(GLenum target, GLuint framebuffer))((void*)wglGetProcAddress("glBindFramebuffer"));
            glFramebufferTexture2D = (void(__stdcall*)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level))((void*)wglGetProcAddress("glFramebufferTexture2D"));
            glCheckFramebufferStatus = (GLenum (__stdcall *)(GLenum target))((void*)wglGetProcAddress("glCheckFramebufferStatus"));
            glDrawBuffers = (void(__stdcall *)(GLsizei n,const GLenum *bufs))((void*)wglGetProcAddress("glDrawBuffers"));
            glBlitFramebuffer = (void(__stdcall *)(	GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter))((void*)wglGetProcAddress("glBlitFramebuffer"));
        }
        case 2:
        {
            //opengl version 2.0 required
            glCreateShader = (GLuint(__stdcall *)(GLenum shaderType))((void*)wglGetProcAddress("glCreateShader"));
            glShaderSource = (void (__stdcall*)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length))((void*)wglGetProcAddress("glShaderSource"));
            glCompileShader = (void (__stdcall*)(GLuint shader))((void*)wglGetProcAddress("glCompileShader"));
            glGetShaderiv = (void (__stdcall*)(GLuint shader, GLenum pname, GLint* params))((void*)wglGetProcAddress("glGetShaderiv"));
            glGetShaderInfoLog = (void (__stdcall*)(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog))((void*)wglGetProcAddress("glGetShaderInfoLog"));
            glCreateProgram = (GLuint(__stdcall*)(void))((void*)wglGetProcAddress("glCreateProgram"));
            glAttachShader = (void (__stdcall*)(GLuint program, GLuint shader))((void*)wglGetProcAddress("glAttachShader"));
            glLinkProgram = (void (__stdcall*)(GLuint program))((void*)wglGetProcAddress("glLinkProgram"));
            glGetProgramiv = (void (__stdcall*)(GLuint program, GLenum pname, GLint* params))((void*)wglGetProcAddress("glGetProgramiv"));
            glGetProgramInfoLog = (void (__stdcall*)(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog))((void*)wglGetProcAddress("glGetProgramInfoLog"));
            glDeleteShader = (void (__stdcall*)(GLuint shader))((void*)wglGetProcAddress("glDeleteShader"));
            glUseProgram = (void(__stdcall*)(GLuint program))((void*)wglGetProcAddress("glUseProgram"));
            glGenBuffers = (void(__stdcall*)(GLsizei n, GLuint * buffers))((void*)wglGetProcAddress("glGenBuffers"));
            glBindBuffer = (void(__stdcall*)(GLenum target, GLuint buffer))((void*)wglGetProcAddress("glBindBuffer"));
            glBufferData = (void(__stdcall*)(GLenum target, GLsizeiptr size, const void* data, GLenum usage))((void*)wglGetProcAddress("glBufferData"));
            glVertexAttribPointer = (void(__stdcall*)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer))((void*)wglGetProcAddress("glVertexAttribPointer"));
            glEnableVertexAttribArray = (void(__stdcall*)(GLuint index))((void*)wglGetProcAddress("glEnableVertexAttribArray"));
        	glGetUniformLocation = (GLint(__stdcall *)(GLuint program, const GLchar *name))((void*)wglGetProcAddress("glGetUniformLocation"));
        	glUniformMatrix4fv = (void(__stdcall *)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value))((void*)wglGetProcAddress("glUniformMatrix4fv"));
            glUniformMatrix3fv = (void(__stdcall *)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value))((void*)wglGetProcAddress("glUniformMatrix3fv"));
        	glUniform3fv = (void(__stdcall *)( GLint location, GLsizei count, const GLfloat *value))((void*)wglGetProcAddress("glUniform3fv"));
        	glUniform4fv = (void(__stdcall *)( GLint location, GLsizei count, const GLfloat *value))((void*)wglGetProcAddress("glUniform4fv"));
        	glUniform1i = (void(__stdcall *)( GLint location, GLint v0))((void*)wglGetProcAddress("glUniform1i"));
        	glActiveTexture = (void(__stdcall *)(GLenum texture))((void*)wglGetProcAddress("glActiveTexture"));
        	glStencilMaskSeparate = (void(__stdcall *)(GLenum face,GLuint mask))((void*)wglGetProcAddress("glStencilMaskSeparate"));
        } break;
        case 1:
        	LogGLErrorAndQuit("Compiled Shaders NOT SUPPORTED!");
            break;
        default:
            printf("UNKNOWN OPENGL MAJOR VERSION");
    }
    return;
}

inline GLuint LoadShaderFromString(const char* shaderString, GLenum shaderType, const char* shaderName)
{
	GLuint shaderDescriptor = glCreateShader(shaderType);
    glShaderSource(shaderDescriptor, 1, (const GLchar**) &shaderString, NULL); 
    glCompileShader(shaderDescriptor);
    GLint success;
    glGetShaderiv(shaderDescriptor, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderDescriptor, 1024, NULL, infoLog);
        FILE * file = fopen("GLERROR.txt","w");
        fprintf(file,"ERROR SHADER_COMPILATION_ERROR of type: %s\n%s\n", shaderName, infoLog);
        fclose(file);
        exit(-1);
    }
    return shaderDescriptor;
}

/* don't forget to use after compiling*/
inline GLuint compileShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader); 
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[1024];
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        printf("ERROR PROGRAM_LINKING_ERROR of type: PROGRAM\n%s\n",infoLog);
        exit(-1);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

//https://github.com/yosmo78/Win32OpenGL-FPSCamera
void LoadMeshes()
{
    GLuint VBOs[NUM_MODELS+NUM_MODELS];
    GLuint *EBOs = VBOs + NUM_MODELS;
    glGenVertexArrays(NUM_MODELS, modelVAOs);
    glGenBuffers(NUM_MODELS+NUM_MODELS, VBOs);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(modelVAOs[0]); //can only bind one VAO at a time

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arcadebutton_buttonVerts), arcadebutton_buttonVerts, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // norm attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //FOR EAO's
    // The index buffer binding is stored within the VAO. If no VAO is bound, then you cannot bind a buffer object to GL_ELEMENT_ARRAY_BUFFER (this might not be true, so verify). Meaning GL_ELEMENT_ARRAY_BUFFER is not global like GL_ARRAY_BUFFER 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arcadebutton_buttonIndices), arcadebutton_buttonIndices, GL_STATIC_DRAW);

    modelIndexCount[0] = arcadebutton_buttonIndicesCount;

    InitMat4f( &mModelMatrices[0] );
    InverseTransposeUpper3x3Mat3f(&mModelMatrices[0],&mNormalMatrices[0]);

    glBindVertexArray(modelVAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arcadebutton_buttonbaseVerts), arcadebutton_buttonbaseVerts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arcadebutton_buttonbaseIndices), arcadebutton_buttonbaseIndices, GL_STATIC_DRAW);

    modelIndexCount[1] = arcadebutton_buttonbaseIndicesCount;

    InitMat4f( &mModelMatrices[1] );
    InverseTransposeUpper3x3Mat3f(&mModelMatrices[1],&mNormalMatrices[1]);

    glBindVertexArray(modelVAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arcadebutton_buttondeskVerts), arcadebutton_buttondeskVerts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arcadebutton_buttondeskIndices), arcadebutton_buttondeskIndices, GL_STATIC_DRAW);

    modelIndexCount[2] = arcadebutton_buttondeskIndicesCount;

    InitMat4f( &mModelMatrices[2] );
    InverseTransposeUpper3x3Mat3f(&mModelMatrices[2],&mNormalMatrices[2]);

    glBindVertexArray(modelVAOs[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ButtonBaseVerts), ButtonBaseVerts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ButtonBaseIndices), ButtonBaseIndices, GL_STATIC_DRAW);

    modelIndexCount[3] = ButtonBaseIndicesCount;

    Quatf qModelRot;
    Vec3f vRotAxis = { 0.0f, 1.0f, 0.0f };
    Vec3f vPos = { 5.0f, 0.0f, 5.0f };
    InitUnitQuatf( &qModelRot, 0.0f, &vRotAxis );
	InitModelMat4ByQuatf( &mModelMatrices[3], &qModelRot, &vPos );
    InverseTransposeUpper3x3Mat3f(&mModelMatrices[3],&mNormalMatrices[3]);

    glBindVertexArray(modelVAOs[4]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ButtonTopVerts), ButtonTopVerts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[4]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ButtonTopIndices), ButtonTopIndices, GL_STATIC_DRAW);

    modelIndexCount[4] = ButtonTopIndicesCount;

    mModelMatrices[4] = mModelMatrices[3];
    mNormalMatrices[4] = mNormalMatrices[3];

    const Vec2f GLQuadTextureVerts[4] =
    {
        {  1.0f,  1.0f },
        {  1.0f, -1.0f },
        { -1.0f,  1.0f },
        { -1.0f, -1.0f }
    };

    const uint32_t GLQuadTextureIndices[2 * 3] =
    {
        0, 3, 1,
        0, 2, 3
    };

    //would this be better to do not indexed?
    GLuint FullScreenQuad[2];
    glGenVertexArrays( 1, &FullScreenVAO );
    glBindVertexArray( FullScreenVAO );
    glGenBuffers( 2, FullScreenQuad );
    glBindBuffer( GL_ARRAY_BUFFER, FullScreenQuad[0] );
    glBufferData( GL_ARRAY_BUFFER, 4 * sizeof( Vec2f ), GLQuadTextureVerts, GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, FullScreenQuad[1] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof( uint32_t ), GLQuadTextureIndices, GL_STATIC_DRAW );

    glBindVertexArray(0);
}

bool movingForward = false;
bool movingLeft = false;
bool movingRight = false;
bool movingBackwards = false;
bool movingUp = false;
bool movingDown = false;


void DrawScene( Mat4f *a_pView, Mat4f *a_pProj )
{
	glViewport(0, 0, screen_width, screen_height);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glDepthMask(GL_FALSE);
	
	glEnable(GL_STENCIL_TEST);
	glStencilMaskSeparate(0xFF,GL_FRONT);//enable those bit slots to be written out of
	glStencilMaskSeparate(0x0,GL_BACK);
	glStencilFunc(GL_ALWAYS, 0x1, 0xFF); //ref&mask op storedVal&mask
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	
	glEnable(GL_CULL_FACE); 
	glCullFace( GL_BACK );
    glFrontFace( GL_CCW );    
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearStencil(0x0);
    //glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

    glBindFramebuffer(GL_FRAMEBUFFER, materialFrameBuffer[0]);

    glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, NULL );
	glActiveTexture( GL_TEXTURE1 );
    glBindTexture( GL_TEXTURE_2D, NULL );
    glActiveTexture( GL_TEXTURE2 );
    glBindTexture( GL_TEXTURE_2D, NULL );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glUseProgram(shaderProgramIDs[0]);
    Mat4f viewProjMatrix;
    Mat4fMult(a_pView, a_pProj, &viewProjMatrix);
	glUniformMatrix4fv(projViewUniformLoc, 1, GL_FALSE,(const GLfloat *)viewProjMatrix.m);

    for( uint32_t mesh = 0; mesh < NUM_MODELS; ++mesh )
    {
        glBindVertexArray(modelVAOs[mesh]);
        glUniformMatrix4fv(modelUniformLoc, 1, GL_FALSE,(const GLfloat *)mModelMatrices[mesh].m);
        glUniformMatrix3fv(normalUniformLoc, 1, GL_FALSE,(const GLfloat *)mNormalMatrices[mesh].m);
        glDrawElements(GL_TRIANGLES, modelIndexCount[mesh], GL_UNSIGNED_INT, 0);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, NULL);

    glClearColor(0.5294f, 0.8078f, 0.9216f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //https://stackoverflow.com/questions/23323860/can-i-avoid-blitting-the-stencil-buffer-from-an-fbo-to-the-back-buffer
    //would be nice to get rid of this for the deferred rendering...
    glBindFramebuffer(GL_READ_FRAMEBUFFER, materialFrameBuffer[0]);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, NULL);
	glBlitFramebuffer(0, 0, screen_width, screen_height, 0, 0, screen_width, screen_height, GL_STENCIL_BUFFER_BIT, GL_NEAREST); //nlit with color buffer works...
	glBindFramebuffer(GL_READ_FRAMEBUFFER, NULL);

    glUseProgram(shaderProgramIDs[1]);

    Vec3f vInvLightDir = { 0.57735026919f, 0.57735026919f, 0.57735026919f };
    glUniform3fv( invLightingUniformLoc, 1, (float*)&vInvLightDir );

    glUniform1i(GBufferLocs[0], 0);
	glUniform1i(GBufferLocs[1], 1);
	glUniform1i(GBufferLocs[2], 2);

    glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, GBufferTextures[0]);
	glActiveTexture( GL_TEXTURE1 );
    glBindTexture( GL_TEXTURE_2D, GBufferTextures[1]);
    glActiveTexture( GL_TEXTURE2 );
    glBindTexture( GL_TEXTURE_2D, GBufferTextures[2]);

	glStencilFunc(GL_EQUAL, 0x1, 0xFF); //ref&mask op storedVal&mask
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glBindVertexArray(FullScreenVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    SwapBuffers(hDC);
}


#if MAIN_DEBUG
int main()
#else
int APIENTRY WinMain(
    _In_ HINSTANCE Instance,
    _In_opt_ HINSTANCE PrevInstance,
    _In_ LPSTR CommandLine,
    _In_ int ShowCode)
#endif
{
#if MAIN_DEBUG
	if( CreateOpenGLWindow() )
#else
    if( CreateOpenGLWindow( Instance ) )
#endif
    {
        return -1;
    }
    loadGLFuncPtrs();

    LoadMeshes();


    LARGE_INTEGER PerfCountFrequencyResult;
    QueryPerformanceFrequency(&PerfCountFrequencyResult);
    int64_t PerfCountFrequency = PerfCountFrequencyResult.QuadPart;
    LARGE_INTEGER LastCounter;
    QueryPerformanceCounter(&LastCounter);

    RAWINPUTDEVICE Rid[1];
	Rid[0].usUsagePage = ((USHORT) 0x01); 
	Rid[0].usUsage = ((USHORT) 0x02); 
	Rid[0].dwFlags = RIDEV_INPUTSINK;   
	Rid[0].hwndTarget = WindowHandle;
	RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

    Running = 1;
    isPaused = 0;
    isFullscreen = 0;

    CenterCursor( WindowHandle );
    ShowCursor( FALSE );

    position = { 0.0f,0.0f,0.0f };
    rotHor = 0.0f;
    rotVert = 0.0f;

    glGenFramebuffers( 1, materialFrameBuffer );
    glBindFramebuffer( GL_FRAMEBUFFER, materialFrameBuffer[0] );

    //https://stackoverflow.com/questions/51030120/concept-what-is-the-use-of-gldrawbuffer-and-gldrawbuffers
    //https://stackoverflow.com/questions/34082243/framebuffer-with-multiple-draw-buffers
    const GLenum buffers[]{ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers( 2, buffers );

    glGenTextures( 3, GBufferTextures );

    glBindTexture( GL_TEXTURE_2D, GBufferTextures[0] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, screen_width, screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ); //change to border?
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ); //change to border?
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GBufferTextures[0], 0 );

    glBindTexture( GL_TEXTURE_2D, GBufferTextures[1] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, screen_width, screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ); //change to border?
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ); //change to border?
    glFramebufferTexture2D( GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D,GBufferTextures[1],0 );


    if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
    {
		LogGLErrorAndQuit("Failed to init Main Frame Buffer!");
        return false;
    }

    glBindTexture( GL_TEXTURE_2D, GBufferTextures[2]);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screen_width, screen_height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL ); 
    //glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_STENCIL, m_width, m_height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT, NULL );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ); //change to border?
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D,GBufferTextures[2],0 );
    //glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,GBufferTextures[2],0 );

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
    	LogGLErrorAndQuit("Failed to init RAME BUFFER Depth!");
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, NULL);
    glBindTexture(GL_TEXTURE_2D, NULL);

    const char materialVertexShader[] =
    #include "materialVertShader.glsl"
    ;

    const char materialFragmentShader[] = 
    #include "materialFragShader.glsl"
    ;

    GLuint materialVertShaderID = LoadShaderFromString(materialVertexShader,GL_VERTEX_SHADER,"Material Vertex Shader");
    GLuint materialFragShaderID = LoadShaderFromString(materialFragmentShader,GL_FRAGMENT_SHADER,"Material Fragment Shader");
    shaderProgramIDs[0] = compileShaderProgram(materialVertShaderID,materialFragShaderID);

    modelUniformLoc = glGetUniformLocation(shaderProgramIDs[0], "mModel");
	normalUniformLoc = glGetUniformLocation(shaderProgramIDs[0], "mNormal");
    projViewUniformLoc = glGetUniformLocation(shaderProgramIDs[0], "mViewProj");

    const char fullscreenVertexShader[] =
    #include "fullscreenVertShader.glsl"
    ;

    const char postProcessingFragmentShader[] = 
    #include "postProcessingFragShader.glsl"
    ;

    GLuint fullScreenVertShaderID = LoadShaderFromString(fullscreenVertexShader,GL_VERTEX_SHADER,"FullScreen Vertex Shader");
    GLuint postProcessingFragShaderID = LoadShaderFromString(postProcessingFragmentShader,GL_FRAGMENT_SHADER,"PostProcessing Fragment Shader");
    shaderProgramIDs[1] = compileShaderProgram(fullScreenVertShaderID,postProcessingFragShaderID);

    invLightingUniformLoc = glGetUniformLocation(shaderProgramIDs[1], "uInvLightDir");

    GBufferLocs[0] = glGetUniformLocation(shaderProgramIDs[1], "uDiffuseTex");
	GBufferLocs[1] = glGetUniformLocation(shaderProgramIDs[1], "uNormalAndMotionVecTex");
	GBufferLocs[2] = glGetUniformLocation(shaderProgramIDs[1], "uDepthTex");


    while( Running )
    {
        uint64_t EndCycleCount = __rdtsc();
    
        LARGE_INTEGER EndCounter;
        QueryPerformanceCounter(&EndCounter);
    
        //Display the value here
        int64_t CounterElapsed = EndCounter.QuadPart - LastCounter.QuadPart;
        float deltaTime = (CounterElapsed / (float)PerfCountFrequency);
        double MSPerFrame = (double) ((1000.0f*CounterElapsed)/ (double)PerfCountFrequency);
        double FPS = PerfCountFrequency/(double)CounterElapsed;
        LastCounter = EndCounter;
    
#if MAIN_DEBUG
        char buf[55];
        sprintf(&buf[0],"The Button: fps %f",FPS);
        SetWindowTextA( WindowHandle, &buf[0]);
#endif

        Vec2f frameRot = { 0, 0 };

        MSG Message;
        while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
        {
        	switch(Message.message)
        	{
        		case WM_QUIT:
        		{
        			CloseProgram();
        			break;
        		}
                case WM_SYSKEYDOWN:
                case WM_SYSKEYUP:
                case WM_KEYDOWN:
                case WM_KEYUP:
                {
                	uint32_t VKCode = (uint32_t) Message.wParam;
                	bool WasDown = (Message.lParam & (1<<30)) != 0;
                	bool IsDown = (Message.lParam & (1<<31)) == 0;
                	bool AltKeyWasDown = (Message.lParam & (1 << 29));
                	switch(VKCode)
                	{
                		case VK_UP:
                		case 'W':
                		{
                			if(WasDown != IsDown)
                			{
                				movingForward = IsDown;
                			}
                			break;
                		}
                		case VK_DOWN:
                		case 'S':
                		{
                			if(WasDown != IsDown)
                			{
                				movingBackwards = IsDown;
                			}
                			break;
                		}
                		case VK_LEFT:
                		case 'A':
                		{
                			if(WasDown != IsDown)
                			{
                				movingLeft = IsDown;
                			}
                			break;
                		}
                		case VK_RIGHT:
                		case 'D':
                		{
                			if(WasDown != IsDown)
                			{
                				movingRight = IsDown;
                			}
                			break;
                		}
                		case 'F':
                		{
                			if(WasDown != 1 && WasDown != IsDown)
                			{
                				Fullscreen( WindowHandle );
                			}
                			break;
                		}
                		case VK_SPACE:
                		{
                			if(WasDown != IsDown)
                			{
                				movingUp = IsDown;
                			}
                			break;
                		}
                		case VK_SHIFT:
                		{
                			if(WasDown != IsDown)
                			{
                				movingDown = IsDown;
                			}
                    		break;
                		}
                		case VK_ESCAPE:
                		{
                			if(WasDown != 1 && WasDown != IsDown)
                			{
                				TogglePause();
                			}
                			break;
                		}
                		case VK_F4:
                		{
                			if(AltKeyWasDown)
                			{
                				CloseProgram();
                			}
                			break;
                		}
                		default:
                		{
                			break;
                		}
                	}
                	break;
                }
                case WM_INPUT:
                {
                	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawmouse
                	UINT dwSize = sizeof(RAWINPUT);
    				static BYTE lpb[sizeof(RAWINPUT)];

    				GetRawInputData((HRAWINPUT)Message.lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
				
    				RAWINPUT* raw = (RAWINPUT*)lpb;
				
    				if (raw->header.dwType == RIM_TYPEMOUSE) 
    				{
    				    frameRot.x += raw->data.mouse.lLastX;
    				    frameRot.y += raw->data.mouse.lLastY;
    				}
                	break;
                }
        		default:
        		{
        			TranslateMessage(&Message);
            		DispatchMessage(&Message);
            		break;
        		}
        	}
        }

        if(!isPaused)
        {
        	Vec2f forwardOrientation = { sinf(rotHor*PI_F/180.0f), cosf(rotHor*PI_F/180.0f) };
        	Vec2f rightOrientation = { sinf((rotHor-90)*PI_F/180.0f), cosf((rotHor-90)*PI_F/180.0f) };
            Vec3f positionChange = {0.0f,0.0f,0.0f};
        	if(movingForward)
        	{
        		positionChange.x += forwardOrientation.x;
              	positionChange.z -= forwardOrientation.y;
        	}
        	if(movingLeft)
        	{
        		positionChange.x += rightOrientation.x;
              	positionChange.z -= rightOrientation.y;
        	}
        	if(movingRight)
        	{
              	positionChange.x -= rightOrientation.x;
              	positionChange.z += rightOrientation.y;
        	}
        	if(movingBackwards)
        	{
        		positionChange.x -= forwardOrientation.x;
              	positionChange.z += forwardOrientation.y;
        	}
        	if(movingUp)
        	{
        		positionChange.y += 1;
        	}
        	if(movingDown)
        	{
        		positionChange.y -= 1;
        	}

        	Vec3f oldPos;
            oldPos.x = position.x;
            oldPos.y = position.y;
            oldPos.z = position.z;
            Vec3f val;
            //normalize positionChange maybe?
            Vec3fScale(&positionChange,speed*deltaTime,&val);
        	Vec3fAdd( &oldPos, &val, &position );
            rotHor  = fmodf(rotHor  + deltaTime*mouseSensitivity*frameRot.x, 360.0f );
            rotVert = clamp(rotVert + deltaTime*mouseSensitivity*frameRot.y, -90.0f, 90.0f);
        }


        Mat4f viewMatrix;
        InitViewMat4ByQuatf( &viewMatrix, rotHor, rotVert, &position );

        Mat4f projectMatrix;
        InitPerspectiveProjectionMat4f(&projectMatrix, screen_width, screen_height, hFov, vFov, 0.04f, 8000.0f );

        DrawScene( &viewMatrix, &projectMatrix );
    }
	return 0;
}