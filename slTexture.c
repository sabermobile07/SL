#include <SL.h>

// Constructeur
void slTexture_init(slTexture * me, char* path)
{
    me->id = 0;
    slString_init(&me->path, path);
    slTexture_charger(me);
}
// Destructeur
void slTexture_free(slTexture * me)
{
    // Destruction de la texture
    glDeleteTextures(1, &me->id);
    slString_destroy(&me->path);
}

// Méthodes
int slTexture_charger(slTexture * me)
{
    // SDL_Surface dans laquelle sera stockée l'image à charger
    SDL_Surface *imageSDL = 0;

    // Chargement de l'image
    imageSDL = IMG_Load(slString_get(&me->path));

    // Vérification du chargement
    if(imageSDL == 0)
    {
        printf("Erreur : %s \n", IMG_GetError());
        return 0;
    }

    // Conversion de l'image en un format unique
    SDL_Surface *imageSDLFormatee = SDL_ConvertSurfaceFormat(imageSDL, SDL_PIXELFORMAT_ABGR8888, 0);
    SDL_FreeSurface(imageSDL);

    // Inversion des pixels
    SDL_Surface *imageSDLInversee = slTexture_inverserPixels(imageSDLFormatee);
    SDL_FreeSurface(imageSDLFormatee);

    // Destruction d'une éventuelle ancienne texture
    if(glIsTexture(me->id) == GL_TRUE)
    {
        glDeleteTextures(1, &me->id);
    }

    GLenum formatInterne = 0;
    GLenum format = 0;
    // Determination du format et du format interne pour les images a 3 composantes
    if(imageSDLInversee->format->BytesPerPixel == 3)
    {
        // Format interne
        formatInterne = GL_RGB;
        // Format
        if(imageSDLInversee->format->Rmask == 0xff)
        {
            format = GL_RGB;
        }
        else
        {
            format = GL_RGB;
        }
    }
    // Determination du format et du format interne pour les images a 4 composantes
    else if(imageSDLInversee->format->BytesPerPixel == 4)
    {
        // Format interne
        formatInterne = GL_RGBA;
        // Format
        if(imageSDLInversee->format->Rmask == 0xff)
        {
            format = GL_RGBA;
        }
        else
        {
            format = GL_RGBA;
        }
    }
    // Dans les autres cas, on arrete le chargement
    else
    {
        printf("Erreur, format interne de l'image inconnu \n");
        SDL_FreeSurface(imageSDLInversee);
        return 0;
    }

    // Génération de l'ID
    glGenTextures(1, &me->id);
    // Verrouillage
    glBindTexture(GL_TEXTURE_2D, me->id);
        // Copie des pixels
        glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, imageSDLInversee->w, imageSDLInversee->h, 0, format, GL_UNSIGNED_BYTE, imageSDLInversee->pixels);
        // Application des filtres
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // Déverrouillage
    glBindTexture(GL_TEXTURE_2D, 0);
    // Libere la surface SDL
    SDL_FreeSurface(imageSDLInversee);
    return 1;
}

GLuint const slTexture_getID(slTexture * me)
{
    return me->id;
}

SDL_Surface* const slTexture_inverserPixels(SDL_Surface *imageSource)
{
    // Copie conforme de l'image source sans les pixels
    SDL_Surface *imageInversee = SDL_CreateRGBSurface(0, imageSource->w, imageSource->h, imageSource->format->BitsPerPixel,
            imageSource->format->Rmask, imageSource->format->Gmask, imageSource->format->Bmask, imageSource->format->Amask);

    // Tableau intermédiaires permettant de manipuler les pixels
    unsigned char* pixelsSources = (unsigned char*) imageSource->pixels;
    unsigned char* pixelsInverses = (unsigned char*) imageInversee->pixels;

    for(int i = 0; i < imageSource->h; i++)
    {
        for(int j = 0; j < imageSource->w * imageSource->format->BytesPerPixel; j++)
        {
            pixelsInverses[(imageSource->w * imageSource->format->BytesPerPixel * (imageSource->h - 1 - i)) + j] =
                                        pixelsSources[(imageSource->w * imageSource->format->BytesPerPixel * i) + j];
        }
    }

    // Retour de l'image inverse
    return imageInversee;
}
