#ifndef __SL_H
#define __SL_H

// Include Mac
#ifdef __APPLE__
    #define GL3_PROTOTYPES 1
    #include <OpenGL/gl3.h>

// Include OpenGL ES iOS
#elif __IPHONE_NA
#include <OpenGLES/ES2/gl.h>

// Include OpenGL ES Android
#elif __ANDROID__
#include <GLES2/gl2.h>

#elif WIN32
    #define GLEW_STATIC
    #define GLEW_BUILD
    #include <GL/glew.h>
    #include <glad/glad.h>
    #include <KHR/khrplatform.h>

#else
#include <GLES2/gl2.h>

#endif

//#pragma pack (1)

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_net.h>
#include <cglm/cglm.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <ft2build.h>
#include FT_FREETYPE_H

//#define MAX(x, y) (((x) > (y)) ? (x) : (y))
//#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define SLerrorPath "log.txt"
#define SLpathShaders "assets/shaders/"
#define SLpathObjs "assets/objs/"

enum { CHAR, INT, FLOAT, STRING, VEC3 };
enum { FALSE, TRUE };
enum { IDLE, DOWN, UP }; // Buttons
typedef enum DIR DIR;
enum DIR { TOP, BUTTOM, LEFT, RIGHT };
enum { PORTRAIT, LANDSCAPE };

typedef struct point point;
typedef struct Ch Ch;
typedef struct slAtlas slAtlas;
typedef struct slFont slFont;
typedef struct slWindow slWindow;

#include <slVector.h>
#include <slList.h>
#include <slString.h>
#include <slInput.h>
#include <slShader.h>
#include <slFont.h>
#include <slCamera.h>
#include <slLight.h>
#include <slTexture.h>
#include <slWindow.h>
#include <slAudio.h>
#include <slGltfAttribute.h>
#include <slGltfIndice.h>
#include <slMesh.h>
#include <slModel.h>
#include <slObj.h>
//#include <slFbo.h>
//#include <slShadow.h>
//#include <slButton.h>
#include <slScene.h>
#include <Enemy.h>
#include <Player.h>
#include <Weapon.h>

// SL --------------------------------------------------------
int SL_init();
void SL_quit();
// End SL _______________________________________

// SL Other functions ------------------------------
int cgltf_load(slMesh* mesh, char* path);
void SL_createFile(char* path);
unsigned int SL_getTime();
void SL_errorPrint(int type, void* data);
void SL_convertMouseTo2D(float* xDest, float* yDest, slWindow* win, int xMouse, int yMouse);
void SL_convertMouseTo3D(vec3 dest, slWindow* win);
bool SL_testClic3D(slObj* obj, slWindow* win);
bool SL_raySphere(slObj* obj, vec3 ray_direction_wor, float sphere_radius, slCamera* cam);
bool SL_testPointIn2D(float xP, float yP, float x, float y, float w, float h);
bool SL_testPointIn3D(vec3 p, vec3 tPos, vec3 tScale);
void SL_mat4Print(mat4 m);
void SL_aiMat4ToGlm(const struct aiMatrix4x4 from, mat4 to);
void SL_aiVec3ToGlm(const struct aiVector3D from, vec3 to);
void SL_aiQuatToGlm(const struct aiQuaternion from, versor to);
void SL_vec3Mix(vec3 v1, vec3 v2, float factor, vec3 dest);
// End SL Other functions ______________________________________________

#endif