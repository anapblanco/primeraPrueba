#include "frontend.h"
#include "game.h"
#include <allegro5/allegro.h>

int main(void)
{
    Game game = {0};
    gameInit(&game);
    frontendInit();

    while(game.state.id != EXIT)
    {
        Input input = frontendGetInput();
        updateGame(&game, input);
        frontendRender(&game);
    }

    frontendDestroy();
    return 0;
}
