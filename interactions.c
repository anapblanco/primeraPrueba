/***************************************************************************//**
  @file     +collision.c+
  @brief    +Descripcion del archivo+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
    #include "interactions.h"
    #include "game.h"
    #include <stddef.h>
/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
    static int runOverFrog(Frog *frog, Entity *obstacles, uint8_t obstacleCount);
    static Entity *frogOnFloater(Frog *frog, Entity *floaters, uint8_t floaterCount);
    static int collided(Frog* frog , Entity* entity);
    static int frogOutOfBounds(Frog *frog);

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/



/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/



/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

   int manageInteractions(Game *game){
     if(game!=NULL){
        int errorType;

        if (frogOutOfBounds(&game->frog)) { //Chequeamos que la rana siga en los limites del juego, sino muere
            frogDies(&(game->frog),&(game->lives), &game->state.id);
            return 0;
        }

        else{ //Si la rana esta dentro de los limites analizamos el resto de interacciones

            Row *currentRow = &(game->level.rows[game->frog.y]); // Tomamos la fila en la que esta la rana

            switch(currentRow->zone){ //Dependiendo la zona en la que esta analizamos como y con que puede interactuar

                case ROAD://Si la rana esta en la calle lo unico que le puede pasar es que sea atropellada por un obstaculo

                    errorType = runOverFrog(&(game->frog), currentRow->firstEntity, currentRow->entityCount);
                    if (errorType == 1){ 
                        frogDies(&(game->frog), &(game->lives), &((game->state).id)); //Si fue atropellada muere
                    }
                    else if(errorType){
                        return errorType;
                    }

                break;

                case WATER://Si la rana esta en el agua lo unico que le puede pasar es que se mueva con un flotador, sino se muere

                    {
                        Entity *floaterP = frogOnFloater(&(game->frog), currentRow->firstEntity, currentRow->entityCount); //Si esta en un flotador necesitamos saber en cual

                        if(floaterP != NULL){
                            // Usar la velocidad/direccion de la fila (row) porque moveRow usa row->speed/row->direction
                            game->frog.speed = currentRow->speed;
                            game->frog.direction = currentRow->direction;
                            // Si prefieren que la entidad mantenga speed/direction, actualizar las entidades al inicializarlas.
                            // moveFrogWithFloater(&(game->frog), floaterP); // opcional si entidades tienen speed/direction válidos
                        }
                        else{
                            frogDies(&(game->frog),&(game->lives), &((game->state).id)); //Si no esta en un flotador, esta en el agua, por ende se muere
                        }
                    }
                
                break;

                case SAFE://Si esta en una zona segura hay que chequear de sumarle puntos
                    if((errorType = updateScore(&(game->frog), &(game->score))) ==1){ 
                        return 0;
                    }
                    else if(errorType){
                        return errorType;
                    }
                    
                break;

            }
        }

     }
     else{
        return ERR_INVALID_GAME_POINTER;
     }
    }

    int updateScore(Frog * frog , uint8_t * score){ //Si es la primera vez que la rana llega a esa zona segura, se le suman puntos 
        if(frog==NULL){
            return ERR_INVALID_FROG_POINTER;
        }
        if(score==NULL){
            return ERR_INVALID_SCORE_POINTER;
        }
        else{
            if(frog->lastSafeSpot != frog->y){
                (*score)+=POINT_WEIGHT;
                frog->lastSafeSpot = frog->y;
            }
            return 0;
        }
    }


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
    static int runOverFrog(Frog *frog, Entity *obstacles, uint8_t obstacleCount){
        if(frog==NULL){
            return ERR_INVALID_FROG_POINTER;
        }
        if(obstacles==NULL){
            return ERR_INVALID_OBSTACLE_POINTER;
        }
        else{
            int i;
            for(i=0; i<obstacleCount; i++){
                if(collided(frog,&(obstacles[i])) ){ //Analizamos los obstaculos de la fila en la que esta la rana, si colisiona con alguno esta atropellada
                    return 1;
                }
            }
            return 0;
        }
    }

    static Entity *frogOnFloater(Frog *frog, Entity *floaters, uint8_t floaterCount){
        //VALIDAR PUNTEROS
        int i;
        for(i=0; i<floaterCount; i++){
            if(collided(frog,&(floaters[i])) ){ //Analizamos los flotadores de la fila en la que esta la rana, si no colisiona con ninguno esta ahogada
                return &(floaters[i]);
            }
        }
        return NULL;
    }


    static int collided(Frog* frog , Entity* entity){
        if( ( (frog->x) >= entity->x ) && ( (frog->x) <= (entity->x + entity->length - 1) )){ //La rana colisiona con una entidad de su fila si esta posicionada entre el espacio inicial de la entidad y el final
            return 1;
        }

        else{
            return 0;
        }
    }


static int frogOutOfBounds(Frog *frog){ //Comparamos las coordenadas de la rana con los limites del juego
        if (frog == NULL){
            return ERR_INVALID_LEVEL_POINTER;
        }   

        if (frog->x < 0){
            return 1;
        }

        if (frog->x >= MAP_WIDTH){
            return 1;
        }

        if (frog->y < 0){
            return 1;
        }

        return 0;
    }




/******************************************************************************/
 