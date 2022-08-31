#include <slFont.h>

unsigned int MAX(unsigned int a, unsigned int b)
{
	if(a >= b)
		return a;
	else
		return b;
}

void slAtlas_init(slAtlas* me, slShader* shader, FT_Face face, int height)
{
		FT_Set_Pixel_Sizes(face, 0, height);
		FT_GlyphSlot g = face->glyph;

		unsigned int roww = 0;
		unsigned int rowh = 0;

		me->w = 0;
		me->h = 0;

		 //memset(me->c, 0, sizeof Ch);

		/* Find minimum size for a texture holding all visible ASCII characters */
		for (int i = 32; i < MAXCH; i++)
		{
			if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
				fprintf(stderr, "Loading character %c failed!\n", i);
				continue;
			}
			if (roww + g->bitmap.width + 1 >= TEXWIDTH)
			{
				me->w = MAX(me->w, roww);
				me->h += rowh;
				roww = 0;
				rowh = 0;
			}
			roww += g->bitmap.width + 1;
			rowh = MAX(rowh, g->bitmap.rows);
		}

		me->w = MAX(me->w, roww);
		me->h += rowh;

		/* Create a texture that will be used to hold all ASCII glyphs */
		// warning must use shader
		//slShader_use(shader);
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &me->tex);
		glBindTexture(GL_TEXTURE_2D, me->tex);
		//glUniform1i(glGetUniformLocation(slShader_getID(shader), "texture"), 0); warning I don't no if this needed (maybe not needed)

		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, me->w, me->h, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);

		/* We require 1 byte alignment when uploading texture data */
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		/* Clamping to edges is important to prevent artifacts when scaling */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		/* Linear filtering usually looks best for text */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		/* Paste all glyph bitmaps into the texture, remembering the offset */
		int ox = 0;
		int oy = 0;

		rowh = 0;

		for (int i = 32; i < MAXCH; i++)
		{
			if (FT_Load_Char(face, i, FT_LOAD_RENDER))
			{
				fprintf(stderr, "Loading character %c failed!\n", i);
				continue;
			}

			if (ox + g->bitmap.width + 1 >= TEXWIDTH)
			{
				oy += rowh;
				rowh = 0;
				ox = 0;
			}

			glTexSubImage2D(GL_TEXTURE_2D, 0, ox, oy, g->bitmap.width, g->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);
			me->chs[i].ax = g->advance.x >> 6;
			me->chs[i].ay = g->advance.y >> 6;

			me->chs[i].bw = g->bitmap.width;
			me->chs[i].bh = g->bitmap.rows;

			me->chs[i].bl = g->bitmap_left;
			me->chs[i].bt = g->bitmap_top;

			me->chs[i].tx = ox / (float)me->w;
			me->chs[i].ty = oy / (float)me->h;

			rowh = MAX(rowh, g->bitmap.rows);
			ox += g->bitmap.width + 1;
		}
		//glUseProgram(0);

		fprintf(stderr, "Generated a %d x %d (%d kb) texture atlas\n", me->w, me->h, me->w * me->h / TEXWIDTH);
	}

void slAtlas_destroy(slAtlas* me)
{
		glDeleteTextures(1, &me->tex);
}

slFont* slFont_init(char* name)
{
    slFont* me = malloc(sizeof(slFont));
	slString s;
	slString_init(&s, "assets/fonts/");
	slString_add(&s, name);
	me->name = slString_get(&s);
	me->color[0] = 0.f;
	me->color[1] = 0.f;
	me->color[2] = 0.f;
	me->color[3] = 1.f;
	
	me->shader = slShader_init("text2D");
	/* Initialize the FreeType2 library */
	if (FT_Init_FreeType(&me->ft))
	{
		fprintf(stderr, "Could not init freetype library\n");
		return NULL;
	}

	/* Load a font */
	if (FT_New_Face(me->ft, me->name, 0, &me->face)) {
		fprintf(stderr, "Could not open font %s\n", me->name);
		return NULL;
	}

	// Create the vertex buffer object
	glGenBuffers(1, &me->vbo);

	/* Create texture atlasses for several font sizes */
	slAtlas_init(&me->a36, me->shader, me->face, 48);

	return me;
}

void slFont_free(slFont** me)
{
	slShader_free(&(*me)->shader);
	slAtlas_destroy(&(*me)->a36);
	free(*me);
	*me = NULL;
}

/**
 * Render text using the currently loaded font and currently set font size.
 * Rendering starts at coordinates (x, y), z is always 0.
 * The pixel coordinates that the FreeType2 library uses are scaled by (sx, sy).
 */
void slFont_draw(slFont* me, slWindow* win, const char *text, float x, float y)
{
	point coords[6 * strlen(text)];
	int c = 0;
	
	const uint8_t *p;

	// Loop through all characters 
	for (p = (const uint8_t *)text; *p; p++)
	{
		// Calculate the vertex and texture coordinates 
		float x2 = x + me->a36.chs[*p].bl * win->px[0];
		float y2 = y + me->a36.chs[*p].bt * win->px[1];
		float w = me->a36.chs[*p].bw * win->px[0];
		float h = me->a36.chs[*p].bh * win->px[1];

		// Advance the cursor to the start of the next character 
		x += me->a36.chs[*p].ax * win->px[0];
		y += me->a36.chs[*p].ay * win->px[1];
		
		/*
		// Calculate the vertex and texture coordinates
		float bl = ((float) me->a36.chs[*p].bl / (float)win->w);
    	float bt = ((float) me->a36.chs[*p].bt / (float) win->h);
    	float bw = ((float) me->a36.chs[*p].bw / (float)win->w);
    	float bh = ((float) me->a36.chs[*p].bh / (float) win->h);
    	float ax = ((float) me->a36.chs[*p].ax / (float)win->w);
    	float ay = ((float) me->a36.chs[*p].ay / (float) win->h);
		
		float x2 = x - bl;
		float y2 = y + bt;
		float w = bw;
		float h = bh;

		// Advance the cursor to the start of the next character 
		x += ax;
		y += ay;
		*/

		// Skip glyphs that have no pixels 
		if (!w || !h)
			continue;

		coords[c++] = (point) { x2, y2, me->a36.chs[*p].tx, me->a36.chs[*p].ty };
		coords[c++] = (point) { x2 + w, y2, me->a36.chs[*p].tx + me->a36.chs[*p].bw / me->a36.w, me->a36.chs[*p].ty };
		coords[c++] = (point) { x2, y2 - h, me->a36.chs[*p].tx, me->a36.chs[*p].ty + me->a36.chs[*p].bh / me->a36.h };
		coords[c++] = (point) { x2 + w, y2, me->a36.chs[*p].tx + me->a36.chs[*p].bw / me->a36.w, me->a36.chs[*p].ty };
		coords[c++] = (point) { x2, y2 - h, me->a36.chs[*p].tx, me->a36.chs[*p].ty + me->a36.chs[*p].bh / me->a36.h };
		coords[c++] = (point) { x2 + w, y2 - h, me->a36.chs[*p].tx + me->a36.chs[*p].bw / me->a36.w, me->a36.chs[*p].ty + me->a36.chs[*p].bh / me->a36.h };
	}

	slShader_use(me->shader);
	
	// Set color
	
	//glUniformMatrix4fv(glGetUniformLocation(slShader_getID(me->shader), "projection"), 1, GL_FALSE, *(win->ortho));
	glUniform4fv(glGetUniformLocation(slShader_getID(me->shader), "color"), 1, me->color);

	// Use the texture containing the atlas
	glBindTexture(GL_TEXTURE_2D, me->a36.tex);
	glUniform1i(glGetUniformLocation(slShader_getID(me->shader), "texture"), 0);
	
	/* Draw all the character on the screen in one go */
	/* Set up the VBO for our vertex data */
	glBindBuffer(GL_ARRAY_BUFFER, me->vbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * 4 * strlen(text) * sizeof(GLfloat), coords, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
	glDrawArrays(GL_TRIANGLES, 0, c);

	glDisableVertexAttribArray(0);
	glUseProgram(0);
}
