#include "SDL.h"
#include "config.h"

int main(int argc, char *argv[])
{
    int exit_status = 0;
    const char *hello_path;
    SDL_RWops *hello_file;
    Sint64 hello_size;
    char *hello_content;
    const char *save_path;
    SDL_RWops *save_file;

    if (SDL_Init(0) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initializing SDL failed: %s\n", SDL_GetError());
        return 1;
    }

    /*
     * Some compilers allow DATA_DIR"hello.txt", but later versions of standard
     * C don't, so always put a space between macros/string literals for
     * compatibility. Also, because DATA_DIR can contain anything, like %
     * characters, it shouldn't be passed directly as part of the format
     * string, it should be passed through a %s specifier, for greater safety.
     */
    hello_path = DATA_DIR "hello.txt";

    hello_file = SDL_RWFromFile(hello_path, "r");
    if (!hello_file) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to open %s: %s\n", hello_path, SDL_GetError());
        exit_status = 1;
        goto quit;
    }

    hello_size = SDL_RWsize(hello_file);
    if (hello_size < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get size of %s: %s\n", hello_path, SDL_GetError());
        exit_status = 1;
        goto quit;
    }
    SDL_Log("Size of %s: %" SDL_PRIs64 "\n", hello_path, hello_size);

    hello_content = SDL_malloc(hello_size + 1);
    if (!hello_content) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to allocate string to read content of %s\n", hello_path);
        SDL_RWclose(hello_file);
        exit_status = 1;
        goto quit;
    }

    if (SDL_RWread(hello_file, hello_content, hello_size, 1) != 1) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to read content of %s: %s\n", hello_path, SDL_GetError());
        SDL_free(hello_content);
        SDL_RWclose(hello_file);
        exit_status = 1;
        goto quit;
    }
    SDL_RWclose(hello_file);
    hello_content[hello_size] = '\0';

    SDL_Log("Content of %s:\n", hello_path);
    SDL_Log("%s\n", hello_content);

    SDL_free(hello_content);

    save_path = SAVE_DIR "save.dat";
    save_file = SDL_RWFromFile(save_path, "wb");
    if (!save_file) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to open %s: %s\n", save_path, SDL_GetError());
        exit_status = 1;
        goto quit;
    }
    SDL_Log("Successfully opened %s for binary writing\n", save_path);
    SDL_RWclose(save_file);

quit:
    SDL_Quit();

    return exit_status;
}

/* vi: set ts=4 sw=4 expandtab: */
