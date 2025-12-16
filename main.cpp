// SDL VSCODE C/C++
//
// This project is part of a tutorial by The Science of Code:
// - English: https://thescienceofcode.com/sdl-vscode-c-cpp-debug/
// - Español: https://thescienceofcode.com/es/sdl-vscode-c-cpp-debug/
//
// NOTES:
// - This project uses unity build, includes inside secondary files are used only for IDE purpouses (code completition, syntax hl, etc).
// - "IWYU pragma: keep" comments are used to ignore clangd warnings related with unity builds.

#include "SDL_pixels.h"
#define UNITY_BUILD 1
#include <stdio.h>              // IWYU pragma: keep
#include <math.h>               // IWYU pragma: keep
#ifdef _WIN64
 #include <SDL.h>
 #include <SDL_image.h>
#else
 #include <SDL2/SDL.h>
 #include <SDL2/SDL_image.h>
#endif
#include "common.h"
#include "sdl_utils.h"

int
main(int argc, char *args[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    // Init SDL without texture filtering for better pixelart results
    if (sdl_utils_Init("SDL Tutorial", &window, &renderer, 0)) 
    {
        SDL_Texture* texture = IMG_LoadTexture(renderer, "res/characters.png");
        
        // Sprite source rectangle
        SDL_Rect srcRect = {328, 11, 16, 22};
        SDL_Rect srcRect2 = {328, 40, 16, 24};
        SDL_Rect srcRect3 = {328, 72, 16, 24};  
        // Target rectangle (note that we will paint it at x4 its original size)
        SDL_Rect destRect = {0, 0, srcRect.w * 4, srcRect.h * 4};
        SDL_Rect destRect2 = {0, 0, srcRect2.w * 4, srcRect2.h * 4};
        SDL_Rect destRect3 = {0, 0, srcRect3.w * 4, srcRect3.h * 4};
        
        // Animation variables
        float time = 0.0f;
        const float speed = 0.05f;
        const float amplitude = 150.0f;
        const float amplitude2 = 80.0f;
        const float amplitude3 = 220.0f;
        int centerX = 250 + rand() % 10;
        int centerY = 180 + rand() % 10;
        int frame = 0;
        
        while (1)
        {
            // Update sprite position in sine wave pattern
            destRect.x = centerX + (int)(amplitude * sin(time));
            destRect.y = centerY + (int)(amplitude * 0.5f * sin(time * 2.0f));
            destRect2.x = centerX + (int)(amplitude2 * sin(time));
            destRect2.y = centerY + (int)(amplitude2 * 0.5f * sin(time * 2.0f));
            destRect3.x = centerX + (int)(amplitude3 * sin(time));
            destRect3.y = centerY + (int)(amplitude3 * 0.5f * sin(time * 2.0f));
            
            // Increment time for animation
            time += speed;
            
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
            SDL_RenderCopy(renderer, texture, &srcRect2, &destRect2);
            SDL_RenderCopy(renderer, texture, &srcRect3, &destRect3);   
            SDL_RenderPresent(renderer);

            SDL_Event event;
            if (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT) break;
            } 
            if(frame++ > 8){
                srcRect.x += srcRect.w + 16;
                if (srcRect.x >= 17 * (srcRect.w + 16)) srcRect.x = 328;
                srcRect2.x += srcRect2.w + 16;
                if (srcRect2.x >= 17 * (srcRect2.w + 16)) srcRect2.x = 328;
                srcRect3.x += srcRect3.w + 16;
                if (srcRect3.x >= 17 * (srcRect3.w + 16)) srcRect3.x = 328;
                frame = 0;
            }
            SDL_Delay(30);
            
        }

        SDL_DestroyTexture(texture);		
    }
    sdl_utils_Quit(window, renderer);
    return 0;
}
