#include "Texture.h"

namespace txt
{
  Texture::Texture()
  {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }

  Texture::~Texture()
  {
    clear();
  }

  int Texture::getWidth() const
  {
    return mWidth;
  }

  int Texture::getHeight() const
  {
    return mHeight;
  }

  void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
  {
    SDL_SetTextureColorMod(mTexture, red, green, blue);
  }

  void Texture::setBlendMode(SDL_BlendMode blending)
  {
    SDL_SetTextureBlendMode(mTexture, blending);
  }

  void Texture::setAlpha(Uint8 alpha)
  {
    SDL_SetTextureAlphaMod(mTexture, alpha);
  }

  void Texture::render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
  {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if (clip != NULL)
    {
      renderQuad.w = clip->w;
      renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
  }

  bool Texture::loadFromFile(string path, SDL_Renderer *renderer)
  {
    clear();

    SDL_Texture *newTexture = NULL;

    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
    {
      printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
      SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

      newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

      if (newTexture == NULL)
      {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
      }
      else
      {
        mWidth = loadedSurface->w;
        mHeight = loadedSurface->h;
      }

      SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;
    return mTexture != NULL;
  }

  bool Texture::loadFromRenderedText(string textureText, SDL_Renderer *renderer, TTF_Font *font, SDL_Color textColor)
  {
    clear();

    // Render text surface
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);

    if (textSurface == NULL)
    {
      printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
      // Create texture from surface pixels
      mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
      if (mTexture == NULL)
      {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
      }
      else
      {
        // Get image dimensions
        mWidth = textSurface->w;
        mHeight = textSurface->h;
      }

      // Get rid of old surface
      SDL_FreeSurface(textSurface);
    }

    // Return success
    return mTexture != NULL;
  }

  void Texture::clear()
  {
    if (mTexture != NULL)
    {
      SDL_DestroyTexture(mTexture);
      mTexture = NULL;
    }

    mWidth = 0;
    mHeight = 0;
  }
}