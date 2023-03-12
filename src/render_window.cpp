#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "RenderWindow.hpp"
#include "Sprite.hpp"

#define concat(first, second) first second

RenderWindow::RenderWindow(const char *title, int width, int height, float renderScale_) : window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (window == NULL)
        std::cout << "Window init failed. SDL Error: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    renderScale = renderScale_;
}

SDL_Texture *RenderWindow::loadTexture(const char *filePath)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, filePath);

    if (texture == NULL)
        std::cout << "Texture load failed. SDL Error: " << SDL_GetError() << std::endl;

    return texture;
}

void RenderWindow::destroy()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::render(Sprite &sprite)
{
    SDL_Rect src = sprite.getRect();

    SDL_Rect dest;
    dest.x = sprite.getX() * renderScale;
    dest.y = sprite.getY() * renderScale;
    dest.w = sprite.getRect().w * renderScale;
    dest.h = sprite.getRect().h * renderScale;

    SDL_RenderCopy(renderer, sprite.getTexture(), &src, &dest);
}