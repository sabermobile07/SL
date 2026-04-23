#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <SL.h>

struct slTexture
{
	unsigned int id;
};

slTexture* slTexture_init(char* name)
{
	slTexture* me = calloc(1, sizeof(slTexture));
	slStr* path = slStr_new("assets/textures/");
	slStr_add(path, name);
	
	glGenTextures(1, &me->id);
	glBindTexture(GL_TEXTURE_2D, me->id);
	// set the texture wrapping/filtering options (on currently bound texture)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(slStr_get(path), &width, &height, &nrChannels, 0);
	if (data)
	{
		if(nrChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_RGB,
GL_UNSIGNED_BYTE, data);
		}
		else if(nrChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,

GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		slStr_add(error, "Failed to load texture");
		SL_error();
	}
	stbi_image_free(data);
	slStr_free(&path);
	/*
      float texCoords[] = {
    	0.0f, 0.0f, // lower-left corner

    	1.0f, 0.0f, // lower-right corner

    	0.5f, 1.0f // top-center corner

    };
      
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
      
      float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
      
      glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
      
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     
     int width, height, nrChannels;
     unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
     
     unsigned int texture;
     glGenTextures(1, &texture);
     
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
     glGenerateMipmap(GL_TEXTURE_2D);
     
     stbi_image_free(data);
	*/
	return me;
}

void slTexture_free(slTexture** me)
{
	free(*me);
	*me = NULL;
}

void slTexture_use(slTexture* me, int nbr)
{
	glActiveTexture(GL_TEXTURE0 + nbr);
	glBindTexture(GL_TEXTURE_2D, me->id);
}

unsigned int slTexture_getID(slTexture* me)
{
	return me->id;
}
