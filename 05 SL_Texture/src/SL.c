#include <SL.h>
#include <stb_image.h>

FILE* fileError = NULL;

void SL_init()
{
	remove("assets/errors.txt");
	fileError = fopen("assets/errors.txt", "w");
	stbi_set_flip_vertically_on_load(true);
}

void SL_quit()
{
	fclose(fileError);
}

char* SL_readFile(const char* path)
{
    FILE* file = fopen(path, "r");
    if (!file)
    {
        SL_printErrors("ERROR: Cannot open file: ", path, "\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer)
    {
        fclose(file);
        SL_printErrors("ERROR: Cannot allocate memory for file: ", path, "\n");
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

void SL_errorBox(const char* error)
{
	SDL_ShowSimpleMessageBox(
    SDL_MESSAGEBOX_INFORMATION,
    "Debug",
    error,
    NULL
    );
}

void SL_printError(const char* error)
{
	fprintf(fileError, error);
}

void SL_printErrors(const char* error1, const char* error2, const char* error3)
{
	fprintf(fileError, error1);
	fprintf(fileError, error2);
	fprintf(fileError, error3);
}
