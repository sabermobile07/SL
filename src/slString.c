#include <SL.h>

void slString_init(slString* me, char* string)
{
    me->count = strlen(string);
    me->data = malloc((me->count + 1) * sizeof(char));

    for(int i=0; i<me->count; i++)
    {
        me->data[i] = string[i];
    }
    if(me->count != 0)
        me->data[me->count] = '\0';
}

void slString_free(slString* me)
{
    free(me->data);
}

char* slString_get(slString* me)
{
    return me->data;
}

void slString_set(slString* me, char* str)
{
    me->count = strlen(str);
    me->data = realloc(me->data, (me->count + 1) * sizeof(char));

    for(int i=0; i<me->count; i++)
    {
        me->data[i] = str[i];
    }
    if(me->count != 0)
        me->data[me->count] = '\0';
}

void slString_add(slString* me, char* string)
{
	int i = 0;
	char c = string[i];
	while(c != '\0' && i < strlen(string))
	{
		slString_addChar(me, c);
		i++;
		c = string[i];
	}
}
/*
void slString_add(slString* me, char* string)
{
    me->data = realloc(me->data, me->count + strlen(string) + 1);
    for(int i=0; i<strlen(string); i++)
    {
        me->data[me->count] = string[i];
        me->count += 1;
    }
    me->data[me->count] = '\0';
}
*/
void slString_addChar(slString* me, char c)
{
    me->data[me->count] = c;
    me->count += 1;
    me->data = realloc(me->data, me->count + 1);
    me->data[me->count] = '\0';
}

void slString_addInt(slString* me, int a)
{
	char s[100] = "";
	sprintf(s, "%d", a);
	slString_add(me, s);
}
/*
void slString_addInt(slString* me, int a)
{
    FILE* file = NULL;
    file = fopen("assets/tmp.txt", "w");
    if(file == NULL)
        printf("Error to add integer");
    fprintf(file, "%d", a);
    fclose(file);
    file = NULL;
    file = fopen("assets/tmp.txt", "r");
    if(file == NULL)
        printf("Error to add integer");
    char c = fgetc(file);
    while(c != EOF)
    {
        slString_addChar(me, c);
        c = fgetc(file);
    }
    fclose(file);
    file = NULL;
}
*/
void slString_addFloat(slString* me, float a)
{
    FILE* file = NULL;
    file = fopen("assets/tmp.txt", "w");
    if(file == NULL)
        printf("Error to add float");
    fprintf(file, "%f", a);
    fclose(file);
    file = NULL;
    file = fopen("assets/tmp.txt", "r");
    if(file == NULL)
        printf("Error to add float");
    char c = fgetc(file);
    while(c != EOF)
    {
        slString_addChar(me, c);
        c = fgetc(file);
    }
    fclose(file);
    file = NULL;
}

void slString_print(slString* me)
{
    printf("%s\n", me->data);
}
