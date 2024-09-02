# Template repo for using SDL2

This is a simple template repo for quickly making a program using SDL and some
satellite libraries (SDL_image, SDL_mixer, SDL_ttf, SDL_net), with basic
support for cross-platform-reliable access to files in the repo. This isn't
intended for serious programs suitable for release distribution, just testing
some code out, like drafting out an idea/feature to be implemented in some
other real application/game.

Access data files in the repo's `data` directory by including `"config.h"`,
**NOT** `<config.h>`, and prepend the `DATA_DIR` macro to a relative path
string literal of the filename, like `DATA_DIR "hello.txt"`. A string
constructed in that way results in an absolute path to that file, which should
always work for loading via `SDL_RWFromFile()`:
```c
#include "SDL.h"
#include "config.h"

SDL_RWops *GetHelloFile(void)
{
    return SDL_RWFromFile(DATA_DIR "hello.txt", "r");
}
```

The same functionality is available for writable files, writing into the repo's
`save` directory; use the `SAVE_DIR` macro for that. The `save` directory has
its contents in its own `.gitignore` file, so that the written files are kept
out of Git commits:
```c
#include "SDL.h"
#include "config.h"

SDL_RWops *GetNewSaveFile(void)
{
    return SDL_RWFromFile(SAVE_DIR "save.dat", "wb");
}
```
