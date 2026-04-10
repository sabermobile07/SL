#include <SL.h>

struct slShader
{
	unsigned int id;
};

slShader* slShader_init(char* name)
{
	slShader* me = calloc(1, sizeof(slShader));
	char path[256];
	snprintf(path, sizeof(path), "assets/shaders/%s", name);
	
	char vPath[256];
	snprintf(vPath, sizeof(vPath), "%s.vs", path);
	
	char fPath[256];
	snprintf(fPath, sizeof(fPath), "%s.fs", path);
	
	char* vCode = SL_readFile(vPath);
	char* fCode = SL_readFile(fPath);
	
	// read file’s buffer contents into streams
	slShader_compile(me, vCode, fCode);
	free(vCode);
	free(fCode);
	
	return me;
}

void slShader_free(slShader* me)
{
	glDeleteProgram(me->id);
	free(me);
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
    	SL_printErrors("\nERROR SHADER VERTEX COMPILATION FAILED : ", infoLog, "\n");
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
    	SL_printErrors("\nERROR SHADER FRAGMENT COMPILATION FAILED : ", infoLog, "\n");
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
    	SL_printErrors("\nError link shaderProgram : ", infoLog, "\n");
    }
    
    // delete shaders now they are in the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void slShader_use(slShader* me)
{
	glUseProgram(me->id);
}

void slShader_setBool(slShader* me, const char* name, bool value)
{
	glUniform1i(glGetUniformLocation(me->id, name), (int)value);
}

void slShader_setInt(slShader* me, const char* name, int value)
{
	glUniform1i(glGetUniformLocation(me->id, name), value);
}

void slShader_setFloat(slShader* me, const char* name, float value)
{
	glUniform1f(glGetUniformLocation(me->id, name), value);
}
