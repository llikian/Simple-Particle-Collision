#include "src/particles.hpp"

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[])
{
    // Initializes SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Initializes the window and the renderer
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(DX, DY, 0, &window, &renderer);

    bool stop = false;
    SDL_Event event;
    const Uint8* keyboard;

    World world;
    makeWorld(world, 20);

    // Other variables

    // Main Loop
    while(!stop)
    {
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);
        ////

        drawWorld(renderer, world);
        updateWorld(world);

        ////
        keyboard = SDL_GetKeyboardState(nullptr);

        // Updates the changes
        SDL_RenderPresent(renderer);

        // Handles closing the window
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT || keyboard[SDL_SCANCODE_ESCAPE])
            {
                stop = true;
            }
        }
    }

    // Cleans up SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}