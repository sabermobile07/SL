#ifndef __SL_FONT_H
#define __SL_FONT_H

// Maximum texture width
#define TEXWIDTH 1024
// Max characters in font
#define MAXCH 128

#include <SL.h>

struct point
{
	GLfloat x;
	GLfloat y;
	GLfloat s;
	GLfloat t;
};

struct Ch
{
		float ax;	// advance.x
		float ay;	// advance.y

		float bw;	// bitmap.width;
		float bh;	// bitmap.height;

		float bl;	// bitmap_left;
		float bt;	// bitmap_top;

		float tx;	// x offset of glyph in texture coordinates
		float ty;	// y offset of glyph in texture coordinates
};

struct slAtlas
{
	GLuint tex;		// texture object

	unsigned int w;			// width of texture in pixels
	unsigned int h;			// height of texture in pixels

	Ch chs[MAXCH];		// character information
};

struct slFont
{
	const char* name;
	slShader* shader;
	FT_Library ft;
	FT_Face face;
	GLuint vbo;
	GLfloat color[4];
	slAtlas a36;
};

/**
 * The atlas struct holds a texture that contains the visible US-ASCII characters
 * of a certain font rendered with a certain character height.
 * It also contains an array that contains all the information necessary to
 * generate the appropriate vertex and texture coordinates for each character.
 *
 * After the constructor is run, you don't need to use any FreeType functions anymore.
 */

void slAtlas_init(slAtlas* me, slShader* shader, FT_Face face, int height);
void slAtlas_destroy(slAtlas* me);

slFont* slFont_init(char* name);
void slFont_free(slFont** me);
void slFont_draw(slFont* me, slWindow* win, const char *text, float x, float y);
//void slFont_draw(slFont* me, slWindow win, const char *text, GLfloat* color,  float x, float y, float sx, float sy);

#endif
