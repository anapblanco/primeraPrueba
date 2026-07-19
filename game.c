/***************************************************************************//**
  @file     +game.c+
  @brief    +funciones del juego+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "game.h"
#include "interactions.h"
#include "top10.h"

/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void processInputPlaying(GameState * state, Input input, Frog * frog);
static void processInputPaused(Game * game, Input input);
static void processInputGameOver(Game * game, Input input);
static void processInputVictory(Game * game, Input input);
static void processInputPoints(Game * game, Input input);
static void processInputMenu(Game * game, Input input);

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static int temperaturas_actuales[4];+


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


void updateGame(Game * game, Input input){
    game->timeNow = clock();
    switch ((game->state).id){
        case MENU: 
            processInputMenu(game, input);
        break;
        case PLAYING:
            processInputPlaying(&(game->state),input, &(game->frog));

            updateEntities(game);

            manageInteractions(game);

            checkLevel(game);

        break;
        case PAUSED:
            processInputPaused(game, input);
        break;
        case VICTORY:
            resetFrog(&(game->frog));
            processInputVictory(game, input);
        break;
        case GAME_OVER:
            resetFrog(&(game->frog));
            processInputGameOver(game, input);
        break;
        case POINTS:
            processInputPoints(game, input);
        break;

        case EXIT:
            //no hace nada, main lo lee y termina programa
        break;
    }
 }

 void gameInit(Game* game){
    game->timeNow = clock();
    
    initLevel(game);
    initFrog(&(game->frog));

    game->score=MIN_SCORE;

    //VER BIEN ESTOOO no se si hay que sacar este for o no por los eerrores de archivso, probar
    /*for(int i=0; i<TOP10_SIZE; i++){
        game->scoresTop10[i] = MIN_SCORE;
    }*/
    game->lives=MAX_LIVES;
    game->lastEntityUpdate = clock();
    
    getTop10Status(game->scoresTop10, game->score);

    game->state.id = MENU;
    game->state.menu.selected = MENU_TITLE;
    game->state.menu.optionCount = MENU_COUNT;

    game->state.menu = (MenuState){ MENU_TITLE, MENU_COUNT };
    game->state.paused = (MenuState){ PAUSED_TITLE, PAUSED_COUNT };
    game->state.gameOver = (MenuState){ GAME_OVER_TITLE, GAME_OVER_COUNT };
    game->state.victory = (MenuState){ VICTORY_TITLE, VICTORY_COUNT };
    game->state.points = (MenuState){ POINTS_TITLE, POINTS_COUNT };

}

///////////////////////////////////////////MENUS///////////////
void menuPrevious(MenuState *menu){
    if(menu->selected == 0)
        menu->selected = menu->optionCount - 1;
    else
        menu->selected--;
}

void menuNext(MenuState *menu){
    menu->selected++;

    if(menu->selected >= menu->optionCount)
        menu->selected = 0;
}

/////////////////////////////////////////////////////////////////MENU
static void processInputMenu(Game * game, Input input){
    MenuState *menu = &game->state.menu;
    switch(input){
        case SELECT:
            switch(menu->selected){
                case MENU_PLAY:
                    gameInit(game);
                    game->state.id = PLAYING;
                break;
                case MENU_POINTS:
                    game->state.id = POINTS;
                break;
                case MENU_EXIT:
                    getTop10Status(game->scoresTop10, game->score);
                    game->state.id = EXIT;
                break;
                default:
                break;
            }
            menu->selected = MENU_TITLE;
        break;
        case UP:
            menuPrevious(menu);
        break;
        case DOWN:
            menuNext(menu);
        break;
        case NONE: case RIGHT: case LEFT: default:
        break;
    }
}

////////////////////////////////////////////////////////////////////////PAUSED
void processInputPaused(Game *game, Input input){
    switch(input){
        case SELECT:
            switch ( (game->state.paused).selected ){
                case PAUSED_MENU: 
                    getTop10Status(game->scoresTop10, game->score);
                    game->state.id = MENU;
                break;
                case PAUSED_PLAY:
                    game->state.id = PLAYING; //////////////ANALIZAR TEMA VIDAS REPLAY
                break;
                case PAUSED_EXIT:
                    getTop10Status(game->scoresTop10, game->score);
                    game->state.id = EXIT;
                break;
            }
            (game->state.paused).selected = PAUSED_TITLE; //resteo menu
        break;
        case UP:
            menuPrevious(&(game->state.paused));
        break;

        case DOWN:
            menuNext(&(game->state.paused));
        break;

        case NONE: case RIGHT: case LEFT: default:
            //se queda en el mismo menu, no hace nada
            break;
    }
}

///////////////////////////////////////////////////////////GAME OVER
void processInputGameOver(Game *game, Input input){
        switch(input){
            case SELECT:
                switch ( game->state.gameOver.selected ){
                    case GAME_OVER_MENU: 
                        getTop10Status(game->scoresTop10, game->score);
                        game->state.id = MENU;
                    break;
                    case GAME_OVER_EXIT:
                        getTop10Status(game->scoresTop10, game->score);
                        game->state.id = EXIT;
                    break;
                }
                (game->state.gameOver).selected = GAME_OVER_TITLE; //reset menu
            break;
            case UP:
                menuPrevious(&(game->state.gameOver));
            break;

            case DOWN:
                menuNext(&(game->state.gameOver));
            break;

            case NONE: case RIGHT: case LEFT: default:
            //se queda en el mismo menu, no hace nada
            break;
    }
}

///////////////////////////////////////////////////////////VICTORY
void processInputVictory(Game *game, Input input){
        switch(input){
            case SELECT:
                switch ( (game->state.victory).selected ){
                    case VICTORY_MENU: 
                        getTop10Status(game->scoresTop10, game->score);
                        game->state.id = MENU;
                    break;
                    case VICTORY_EXIT:
                        getTop10Status(game->scoresTop10, game->score);
                        game->state.id = EXIT;
                    break;
                }
                (game->state.victory).selected = VICTORY_TITLE; //reset menu
            break;
            case UP:
                menuPrevious(&(game->state.victory));
            break;

            case DOWN:
                menuNext(&(game->state.victory));
            break;

            case NONE: case RIGHT: case LEFT: default:
            //se queda en el mismo menu, no hace nada
            break;
    }
}
//////////////////////////////////////////////////////////POINTS
void processInputPoints(Game * game, Input input){
        switch(input){
            case SELECT:
                switch ( (game->state.points).selected ){
                    case POINTS_MENU: 
                        game->state.id = MENU;
                    break;

                    case POINT_1: case POINT_2: case POINT_3: case POINT_4: case POINT_5:
                    case POINT_6: case POINT_7: case POINT_8: case POINT_9: case POINT_10:
                        //todavia nada 
                    break;

                    case POINTS_EXIT:
                    getTop10Status(game->scoresTop10, game->score);
                        game->state.id = EXIT;
                    break;
                }
                (game->state.points).selected = POINTS_TITLE; //para que no se pueda seleccionar nada mas
            break;
            case UP:
                menuPrevious(&(game->state.points));
            break;

            case DOWN:
                menuNext(&(game->state.points));
            break;

            case NONE: case RIGHT: case LEFT: default:
            //se queda en el mismo menu, no hace nada
            break;
    }
}
/////////////////////////////GAME LOGIC///////////////////////
void processInputPlaying(GameState * state, Input input, Frog * frog){
    switch(input){
                case SELECT:
                    state->id = PAUSED;
                break;

                case UP:
                    moveFrog(frog,UP);
                break;

                case DOWN:
                    moveFrog(frog,DOWN);
                break;

                case RIGHT:
                    moveFrog(frog,RIGHT);
                break;

                case LEFT:
                    moveFrog(frog,LEFT);
                break;

                case NONE: default:
                //se queda en el mismo menu, no hace nada
                break;
    }
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/******************************************************************************/
 