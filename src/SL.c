#include <SL.h>

// SL --------------------------------------------------------
int SL_init()
{
	srand(time(NULL));
    // Create file for Errors
    SL_createFile((char*)SLerrorPath);
    // SDL Initialisation
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        printf("SDL initialisation error : %s \n", SDL_GetError());
        return -1;
    }
    
    // SDL_image initialisation
    IMG_Init(IMG_INIT_JPG & IMG_INIT_PNG);
    
    // SDL_Mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    // OpenGL ES settings
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    return 1;
}

void SL_quit()
{
	Mix_CloseAudio();
    SDL_Quit();
}
// End SL __________________________________________

// SL Other functions --------------------------------------

void SL_createFile(char* path)
{
    FILE* file = NULL;
    file = fopen(path, "w");
    if(file == NULL)
    {
        printf("Error to create file->%s\n", path);
        SL_errorPrint(STRING, "Error to create file");
    }
    fclose(file);
}

unsigned int SL_getTime()
{
    return SDL_GetTicks();
}

void SL_errorPrint(int type, void* data)
{
	FILE* file = NULL;
    file = fopen(SLerrorPath, "r+");
    if(file == NULL)
        printf("File <%s> not opened\n", SLerrorPath);
    else
    {
        fseek(file, 0, SEEK_END);
        switch(type)
        {
        	case CHAR:
        	{
        		char* d = (char*)data;
        		fprintf(file, "%c\n", *d);
        		break;
        	}
        	case INT:
        	{
        		int* d = (int*)data;
        		fprintf(file, "%d\n", *d);
        		break;
        	}
        	case FLOAT:
        	{
        		float* d = (float*)data;
        		fprintf(file, "%f\n", *d);
        		break;
        	}
        	case VEC3:
        	{
        		vec3 v;
				glm_vec3_copy((vec3*)data, v);
        		fprintf(file, "%f %f %f\n", v[0], v[1], v[2]);
        		break;
        	}
        	case STRING:
        	{
        		char* d = (char*)data;
        		fprintf(file, "%s\n", d);
        		break;
        	}
        	default:
        	{
        		fprintf(file, "Error in reading data type\n");
        		break;
        	}
        }
        fclose(file);
    }
}

void SL_convertMouseTo2D(float* xDest, float* yDest, slWindow* win, int xMouse, int yMouse)
{
	*xDest = (-1 + (2.f * (float) xMouse / (float)win->w)) * win->ratio[0];
    *yDest = (1 - (2 * (float) yMouse / (float) win->h)) * win->ratio[1];
}
/*
void SL_convertMouseTo3D(vec3 dest, slWindow* win)
{
	int xMouse = 0;
	int yMouse = 0;
	SDL_GetMouseState(&xMouse, &yMouse);
	/*
	// Step 1: 3d Normalised Device Coordinates range [-1:1, -1:1, -1:1]
	float x = (2.0f * xMouse) / win->w - 1.0f;
	float y = 1.f - (2.0f * yMouse) / win->h;
	float z = 0.5f;
	vec3 ray_nds;
	glm_vec3_copy((vec3){x, y, z}, ray_nds);
	
	// Step 2: 4d Homogeneous Clip Coordinates range [-1:1, -1:1, -1:1, -1:1]
	vec4 ray_clip;
	glm_vec4_copy((vec4){ray_nds[0], ray_nds[1], -1.f, 1.f}, ray_clip);
	
	// Step 3: 4d Eye (Camera) Coordinates range [-x:x, -y:y, -z:z, -w:w]
	mat4 projInv;
	vec4 ray_eye;
	glm_mat4_inv(win->perspective, projInv);
	glm_mat4_mulv(projInv, ray_clip, ray_eye);
	ray_eye[2] = 1.f;
	ray_eye[3] = 0.f;
	
	// Step 4: 4d World Coordinates range [-x:x, -y:y, -z:z, -w:w]
	mat4 viewInv;
	vec3 ray_wor;
	glm_mat4_inv(win->view, viewInv);
	glm_mat4_mulv3(viewInv, (vec3){ray_eye[0], ray_eye[1], ray_eye[2]}, 1.f, ray_wor);
	// don't forget to normalise the vector at some point
	glm_normalize(ray_wor);
	glm_vec3_copy(ray_wor, dest);
	*/
	/*
	vec4 vPort;
	vPort[0] = 0.f;
	vPort[1] = 0.f;
	vPort[2] = (float)win->w;
	vPort[3] = (float)win->h;
	
	vec3 v;
	v[0] = (float)xMouse;
	v[1] = (float)(win->h - yMouse);
	v[2] = 0.999f;
	
	mat4 pv;
	glm_mat4_mul(win->perspective, win->view, pv);
	glm_unproject(v, pv, vPort, dest);
}

bool SL_testClic3D(slObj* obj, slWindow* win)
{
	vec3 pos, pos2, posCam, dir, dir2;
	SL_convertMouseTo3D(pos, win);
	slObj_getPos(obj, pos2);
	slCamera_getPos(win->cam, posCam);
	glm_vec3_sub(posCam, pos, dir);
	glm_vec3_sub(posCam, pos2, dir2);
	glm_vec3_normalize(dir);
	glm_vec3_normalize(dir2);
	float r = glm_vec3_dot(dir, dir2);
    if( r > 0.999f )
    {
    	return true;
    }
	return false;
}
*/
// Function that checks for ray-sphere intersection and returns true or false
bool SL_raySphere(slObj* obj, vec3 ray_direction_wor, float sphere_radius, slCamera* cam)
{
	//vec3 v = glm::vec3(m_Transformation.GetPos().x, m_Transformation.GetPos().y, 0.5f) - m_Camera.GetCameraPosition();
	vec3 v, objPos, camPos;
	slObj_getPos(obj, objPos);
	objPos[2] = 0.5f;
	slCamera_getPos(cam, camPos);
	glm_vec3_sub(objPos, camPos, v);
	float a = glm_vec3_dot(ray_direction_wor, ray_direction_wor); 
	float b = 2 * glm_vec3_dot(v, ray_direction_wor);
	float c = glm_vec3_dot(v, v) - sphere_radius * sphere_radius;
	float b_squared_minus_4ac = b * b - 4 * a * c;

	if (b_squared_minus_4ac > 0)
	{
		float x1 = (-b - sqrt(b_squared_minus_4ac)) / 2.0f;
		float x2 = (-b + sqrt(b_squared_minus_4ac)) / 2.0f;
		if (x1 >= 0.0f && x2 >= 0.0f)
			return true;
		if (x1 < 0.0f && x2 >= 0.0f)
			return true;
	}
	
	return false;
}

bool SL_testPointIn2D(float xP, float yP, float x, float y, float w, float h)
{
	/*
    if( ( xP > x - (w / 2.f) ) && ( xP < x + (w / 2.f) ) )
    {
        if( ( yP < y + (h / 2.f) ) && ( yP > y - (h / 2.f) ) )
    	{
    		return true;
        }
    }
    */
    if( ( xP > x - (w) ) && ( xP < x + (w) ) )
    {
        if( ( yP < y + (h) ) && ( yP > y - (h) ) )
    	{
    		return true;
        }
    }
    return false;
}

bool SL_testPointIn3D(vec3 p, vec3 tPos, vec3 tScale)
{
    if( ( p[0] > tPos[0] - (tScale[0]/2.f) ) && ( p[0] < tPos[0] + (tScale[0]/2.f) ) )
    {
        if( ( p[1] > tPos[1] - (tScale[1]/2.f) ) && ( p[1] < tPos[1] + (tScale[1]/2.f) ) )
    	{
    		if( ( p[2] > tPos[2] - (tScale[2]/2.f) ) && ( p[2] < tPos[2] + (tScale[2]/2.f) ) )
    		{
    			return true;
    		}
        }
    }
    return false;
}

void SL_mat4Print(mat4 m)
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            printf("%f ", m[i][j]);
            SL_errorPrint(FLOAT, &m[i][j]);
        }
        printf("\n");
        SL_errorPrint(STRING, "");
    }
    printf("\n");
    printf("\n");
    SL_errorPrint(STRING, "\n");
}

void SL_aiMat4ToGlm(const struct aiMatrix4x4 from, mat4 to)
{
    to[0][0] = (float)from.a1;
    to[0][1] = (float)from.b1;
    to[0][2] = (float)from.c1;
    to[0][3] = (float)from.d1;

    to[1][0] = (float)from.a2;
    to[1][1] = (float)from.b2;
    to[1][2] = (float)from.c2;
    to[1][3] = (float)from.d2;

    to[2][0] = (float)from.a3;
    to[2][1] = (float)from.b3;
    to[2][2] = (float)from.c3;
    to[2][3] = (float)from.d3;

    to[3][0] = (float)from.a4;
    to[3][1] = (float)from.b4;
    to[3][2] = (float)from.c4;
    to[3][3] = (float)from.d4;
}

void SL_aiVec3ToGlm(const struct aiVector3D from, vec3 to)
{
    to[0] = from.x;
    to[1] = from.y;
    to[2] = from.z;
}

void SL_aiQuatToGlm(const struct aiQuaternion from, versor to)
{
    glm_quat_identity(to);
    to[0] = from.x;
    to[1] = from.y;
    to[2] = from.z;
    to[3] = from.w;
}

void SL_vec3Mix(vec3 v1, vec3 v2, float factor, vec3 dest)
{
    glm_vec3_zero(dest);
    glm_vec3_muladds(v1, 1.f - factor, dest);
    glm_vec3_muladds(v2, factor, dest);
}
// End SL Other functions ______________________________________________
