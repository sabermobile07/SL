#include <SL.h>
#include <stb_image.h>

FILE* fileError = NULL;
slStr* error = NULL;

void SL_init()
{
	remove("assets/errors.txt");
	fileError = fopen("assets/errors.txt", "w");
	error = slStr_new("");
	stbi_set_flip_vertically_on_load(true);
}

void SL_quit()
{
	slStr_free(&error);
	fclose(fileError);
}

char* SL_readFile(const char* path)
{
    FILE* file = fopen(path, "r");
    if (!file)
    {
        slStr_add(error, "ERROR: Cannot open file: ");
        slStr_add(error, path);
        SL_error();
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer)
    {
        fclose(file);
        slStr_add(error, "ERROR: Cannot allocate memory for file: ");
        slStr_add(error, path);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

void SL_error()
{
	slStr_add(error, "\n");
	printf("%s", slStr_get(error));
	fprintf(fileError, slStr_get(error));
	SDL_ShowSimpleMessageBox(
    SDL_MESSAGEBOX_INFORMATION,
    "Debug",
    slStr_get(error),
    NULL
    );
    
    slStr_clean(error);
}
