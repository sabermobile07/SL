#include <SL.h>

struct slShader
{
	unsigned int id;
};

slShader* slShader_init(char* name)
{
	slShader* me = malloc(sizeof(slShader));
	slStr* path = slStr_new("assets/shaders/");
	slStr_add(path, name);
	
	slStr* vPath = slStr_new(slStr_get(path));
	slStr_add(vPath, ".vs");
	
	slStr* fPath = slStr_new(slStr_get(path));
	slStr_add(fPath, ".fs");
	
	char* vCode = SL_readFile(slStr_get(vPath));
	char* fCode = SL_readFile(slStr_get(fPath));
	
	// read file’s buffer contents into streams
	slShader_compile(me, vCode, fCode);
	slStr_free(&vPath);
	slStr_free(&fPath);
	
	slShader_buildTextures(me);
	
	return me;
}

void slShader_free(slShader** me)
{
	glDeleteProgram((*me)->id);
	free(*me);
}

void slShader_compile(slShader* me, const char* vCode, const char* fCode)
{
	// build and compile our shader program
    // ------------------------------------
    
    // Vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertexShader, 1, &vCode, NULL);
    glCompileShader(vertexShader);
    
    // test error
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
    	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    	slStr_add(error, "Error vertex shader : ");
    	slStr_add(error, infoLog);
    	SL_error();
    }
    
    // Fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fCode, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
    	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    	slStr_add(error, "Error fragment shader : ");
    	slStr_add(error, infoLog);
    	SL_error();
    }
    
    // Creating program object
    me->id = glCreateProgram();
    
    // attach shaders to the program
    glAttachShader(me->id, vertexShader);
    glAttachShader(me->id, fragmentShader);
    glLinkProgram(me->id);
    
    // test error
    glGetProgramiv(me->id, GL_LINK_STATUS, &success);
    if(!success)
    {
    	glGetProgramInfoLog(me->id, 512, NULL, infoLog);
    	slStr_add(error, "Error program shader : ");
    	slStr_add(error, infoLog);
    	SL_error();
    }
    
    // delete shaders now they are in the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void slShader_buildTextures(slShader* me)
{
	slShader_use(me);
    
    slShader_setInt(me, "texture1", 0);
    
    slShader_setInt(me, "texture2", 1);
}

void slShader_use(slShader* me)
{
	glUseProgram(me->id);
}

unsigned int slShader_getID(slShader* me)
{
	return me->id;
}

void slShader_setBool(slShader* me, const char* name, bool value)
{
	glUniform1i(glGetUniformLocation(me->id, name), value);
}

void slShader_setInt(slShader* me, const char* name, int value)
{
	glUniform1i(glGetUniformLocation(me->id, name), value);
}

void slShader_setFloat(slShader* me, const char* name, float value)
{
	glUniform1f(glGetUniformLocation(me->id, name), value);
}
