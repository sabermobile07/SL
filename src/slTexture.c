#include <SL.h>

SDL_Surface* inverserPixels(const SDL_Surface *imageSource);

slTexture* slTexture_init()
{
    slTexture* me = malloc(sizeof(slTexture));
    me->id = 0;
    me->fichierImage = "";
    me->w = 0;
    me->h = 0;
    me->format = 0;
    me->formatInterne = 0;
    me->textureVide = false;

    return me;
}

slTexture* slTexture_initFile(char* fichierImage)
{
    slTexture* me = malloc(sizeof(slTexture));
    me->id = 0;
    me->fichierImage = fichierImage;
    me->w = 0;
    me->h = 0;
    me->format = 0;
    me->formatInterne = 0;
    me->textureVide = false;
    
    slTexture_charger(me);

    return me;
}

slTexture* slTexture_initTexture(int w, int h, GLenum format, GLenum formatInterne, bool textureVide)
{
    slTexture* me = malloc(sizeof(slTexture));
    me->id = 0;
    me->fichierImage = "";
    me->w = w;
    me->h = h;
    me->format = format;
    me->formatInterne = formatInterne;
    me->textureVide = textureVide;

    return me;
}

void slTexture_free(slTexture* me)
{
    // Destruction de la texture
    glDeleteTextures(1, &me->id);
}

void slTexture_copy(slTexture* dst, slTexture* const src)
{
    // Copie des attributs
    dst->fichierImage = src->fichierImage;

    dst->w = src->w;
    dst->h = src->h;
    dst->format = src->format;
    dst->formatInterne = src->formatInterne;
    dst->textureVide = src->textureVide;
    // Si la texture est vide, alors on appelle la methode chargerTextureVide()
    if(dst->textureVide && glIsTexture(src->id) == GL_TRUE)
    {
        slTexture_chargerTextureVide(dst);
    }
    // Sinon, on appelle la methode charger() par d�faut
    else if(glIsTexture(src->id) == GL_TRUE)
    {
        slTexture_charger(dst);
    }
}

/*
Texture& Texture::operator=(Texture const &textureACopier)
{
    // Copie des attributs
    m_fichierImage = textureACopier.m_fichierImage;

    m_largeur = textureACopier.m_largeur;
    m_hauteur = textureACopier.m_hauteur;
    m_format = textureACopier.m_format;
    m_formatInterne = textureACopier.m_formatInterne;
    m_textureVide = textureACopier.m_textureVide;
    // Si la texture est vide, alors on appelle la m�thode chargerTextureVide()
    if(m_textureVide && glIsTexture(textureACopier.m_id) == GL_TRUE)
    {
        chargerTextureVide();
    }
    // Sinon, on appelle la m�thode charger() par d�faut
    else if(glIsTexture(textureACopier.m_id) == GL_TRUE)
    {
        charger();
    }
    // Retour du pointeur *this
    return *this;
}
*/

void slTexture_chargerTextureVide(slTexture* me)
{
    // Destruction d'une eventuelle ancienne texture
    if(glIsTexture(me->id) == GL_TRUE)
    {
        glDeleteTextures(1, &me->id);
    }
    // Generation de l'ID
    glGenTextures(1, &me->id);
    // Verrouillage
    glBindTexture(GL_TEXTURE_2D, me->id);
        // D�finition des caract�ristiques de la texture
        glTexImage2D(GL_TEXTURE_2D, 0, me->formatInterne, me->w, me->h, 0, me->format, GL_UNSIGNED_BYTE, 0);
        // Application des filtres
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // D�verrouillage
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool slTexture_charger(slTexture* me)
{
    // Chargement de l'image dans une surface SDL
    SDL_Surface *imageSDL = IMG_Load(me->fichierImage);
    if(imageSDL == 0)
    {
        printf("Erreur : %s\n", SDL_GetError());
        return false;
    }

    // Inversion de l'image
    SDL_Surface *imageInversee = inverserPixels(imageSDL);
    //SDL_FreeSurface(imageSDL);

    // Destruction d'une �ventuelle ancienne texture
    if(glIsTexture(me->id) == GL_TRUE)
    {
        glDeleteTextures(1, &me->id);
    }

    // Generation de l'ID
    glGenTextures(1, &me->id);
    // Verrouillage
    glBindTexture(GL_TEXTURE_2D, me->id);
    // Format de l'image
    GLenum formatInterne = 0;
    GLenum format = 0;
    // Determination du format et du format interne pour les images a 3 composantes
    if(imageInversee->format->BytesPerPixel == 3)
    {
        // Format interne
        formatInterne = GL_RGB;
        // Format
        if(imageInversee->format->Rmask == 0xff)
        {
            format = GL_RGB;
        }
        else
        {
            format = GL_RGB;
        }
    }
    // Determination du format et du format interne pour les images a 4 composantes
    else if(imageInversee->format->BytesPerPixel == 4)
    {
        // Format interne
        formatInterne = GL_RGBA;
        // Format
        if(imageInversee->format->Rmask == 0xff)
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
        printf("Erreur, format interne de l'image inconnu\n");
        SDL_FreeSurface(imageInversee);
        return false;
    }
    // Copie des pixels
    glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, imageInversee->w, imageInversee->h, 0, format, GL_UNSIGNED_BYTE, imageInversee->pixels);
    // Application des filtres
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // Deverrouillage
    glBindTexture(GL_TEXTURE_2D, 0);
    // Fin de la methode
    SDL_FreeSurface(imageInversee);
    return true;
}

const GLuint slTexture_getID(slTexture* me)
{
    return me->id;
}

void slTexture_setFichierImage(slTexture* me, const char* fichierImage)
{
	strcpy(me->fichierImage, fichierImage);
}

SDL_Surface* inverserPixels(const SDL_Surface *imageSource)
{
    // Copie conforme de l'image source sans les pixels
    SDL_Surface *imageInversee = SDL_CreateRGBSurface(0, imageSource->w, imageSource->h, imageSource->format->BitsPerPixel,
            imageSource->format->Rmask, imageSource->format->Gmask, imageSource->format->Bmask, imageSource->format->Amask);

    // Tableau intermediaires permettant de manipuler les pixels
    unsigned char* pixelsSources = (unsigned char*) imageSource->pixels;
    unsigned char* pixelsInverses = (unsigned char*) imageInversee->pixels;

    // Inversion des pixels
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

void slTexture_setID(slTexture* me, GLuint id)
{
	me->id = id;
}
