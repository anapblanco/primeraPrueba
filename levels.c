/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "levels.h"
#include "game.h"
#include <stddef.h>
#include <string.h>

/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/

 static Level level1={
    LEVEL_1,
    NULL, 
    {
        {NO_CHECKPOINT, NULL, START, 0, 0, 0, 0, DIR_LEFT},
        {NO_CHECKPOINT, NULL, START, 0, 0, 0, 0, DIR_LEFT},

        {NO_CHECKPOINT, NULL, ROAD, 2, TRUCK_LENGTH, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, ROAD, 4, CAR_LENGTH, MEDIUM_GAP, SLOW, DIR_LEFT},
        {NO_CHECKPOINT, NULL, ROAD, 2, CAR_LENGTH, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, ROAD, 3, TRUCK_LENGTH, MEDIUM_GAP, SLOW, DIR_LEFT},
        {NO_CHECKPOINT, NULL, ROAD, 2, CAR_LENGTH, MAX_GAP, SLOW, DIR_RIGHT},

        {CHECKPOINT_1, NULL, SAFE, 0, 0, 0, 0, DIR_LEFT},
        {CHECKPOINT_1, NULL, SAFE, 0, 0, 0, 0, DIR_LEFT},

        {NO_CHECKPOINT, NULL, WATER, 2, MEDIUM, MAX_GAP, SLOW, DIR_LEFT},
        {NO_CHECKPOINT, NULL, WATER, 3, SMALL, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, WATER, 2, LARGE, MEDIUM_GAP, SLOW, DIR_LEFT},
        {NO_CHECKPOINT, NULL, WATER, 2, MEDIUM, MEDIUM_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, WATER, 2, LARGE, MAX_GAP, SLOW, DIR_LEFT},

        {CHECKPOINT_2, NULL, SAFE, 0, 0, 0, 0, DIR_LEFT},
        {CHECKPOINT_2, NULL, SAFE, 0, 0, 0, 0, DIR_LEFT}
    }
};

static Level level2={
    LEVEL_2,
    NULL, 
     {
        {NO_CHECKPOINT, NULL, START, 0, 0, 0, 0, DIR_LEFT},
        {NO_CHECKPOINT, NULL, START, 0, 0, 0, 0, DIR_LEFT},

        {NO_CHECKPOINT, NULL, ROAD, 3, TRUCK_LENGTH, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, ROAD, 3, CAR_LENGTH, MEDIUM_GAP, SLOW, DIR_LEFT},
        {NO_CHECKPOINT, NULL, ROAD, 3, CAR_LENGTH, MEDIUM_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, ROAD, 3, TRUCK_LENGTH, MEDIUM_GAP, SLOW, DIR_LEFT},
        {NO_CHECKPOINT, NULL, ROAD, 2, TRUCK_LENGTH, MAX_GAP, MEDIUM_SPEED, DIR_RIGHT},

        {CHECKPOINT_1, NULL, SAFE, 0, 0, 0, 0, DIR_LEFT},
        {CHECKPOINT_1, NULL, SAFE, 0, 0, 0, 0, DIR_LEFT},

        {NO_CHECKPOINT, NULL, WATER, 3, LARGE, MIN_GAP, MEDIUM_SPEED, DIR_LEFT},
        {NO_CHECKPOINT, NULL, WATER, 3, MEDIUM, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, WATER, 3, MEDIUM, MEDIUM_GAP, SLOW, DIR_LEFT},
        {NO_CHECKPOINT, NULL, WATER, 3, SMALL, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, WATER, 2, LARGE, MAX_GAP, SLOW, DIR_LEFT},

        {CHECKPOINT_2, NULL, SAFE, 0, 0, 0, 0, DIR_LEFT},
        {CHECKPOINT_2, NULL, SAFE, 0, 0, 0, 0, DIR_LEFT}
    }
};

static Level level3={
    LEVEL_3,
    NULL, 
    {
        {NO_CHECKPOINT, NULL, START, 0, 0, 0, 0, DIR_LEFT},
        {NO_CHECKPOINT, NULL, START, 0, 0, 0, 0, DIR_LEFT},

        {NO_CHECKPOINT, NULL, ROAD, 3, TRUCK_LENGTH, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, ROAD, 3, CAR_LENGTH, MEDIUM_GAP, MEDIUM_SPEED, DIR_LEFT},
        {NO_CHECKPOINT, NULL, ROAD, 2, CAR_LENGTH, MAX_GAP, FAST, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, ROAD, 3, TRUCK_LENGTH, MEDIUM_GAP, SLOW, DIR_LEFT},
        {NO_CHECKPOINT, NULL, ROAD, 2, TRUCK_LENGTH, MAX_GAP, MEDIUM_SPEED, DIR_RIGHT},

        {CHECKPOINT_1, NULL, SAFE, 0, 0, 0, 0, DIR_LEFT},
        {CHECKPOINT_1, NULL, SAFE, 0, 0, 0, 0, DIR_LEFT},

        {NO_CHECKPOINT, NULL, WATER, 3, MEDIUM, MAX_GAP, MEDIUM_SPEED, DIR_LEFT},
        {NO_CHECKPOINT, NULL, WATER, 3, SMALL, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, WATER, 2, LARGE, MEDIUM_GAP, MEDIUM_SPEED, DIR_LEFT},
        {NO_CHECKPOINT, NULL, WATER, 3, SMALL, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, WATER, 2, LARGE, MAX_GAP, SLOW, DIR_LEFT},

        {CHECKPOINT_2, NULL, SAFE, 0, 0, 0, 0, DIR_LEFT},
        {CHECKPOINT_2, NULL, SAFE, 0, 0, 0, 0, DIR_LEFT}
    }
};

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static int loadLevel(Level * level);
static void loadLevelEntities(Level* level);
static void loadZoneEntities(Row* rows, uint8_t  zoneStart, Entity* firstEntity);
static void loadRowEntities(Row* row, uint8_t  rowNumber);
static int checkLevelEntities(Level* level);

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
  int arrivedAtFinishLine(uint8_t  y){
        if (y==FINISH_LINE){ //Detectamos si la rana llego a la linea de meta 
            return 1;
        }
        return 0;
  }

  int checkLevel(Game * game){ //Si llego a la linea de meta avanza al siguiente nivel
      if (arrivedAtFinishLine((game->frog).y)){
            goToNextLevel(game);
            (game ->frog).lastCheckpoint = NO_CHECKPOINT;
            resetFrog(&(game->frog));
      }
      return 0;
  }

  int goToNextLevel(Game * game){ //Avanzamos al siguiente nivel dependiendo del nivel en el que estamos 
    int errorType;
    if(game != NULL){ 
        game->lastEntityUpdate = clock();
        switch((game->level).id){
            case LEVEL_1:
                game->level = level2; //Igualamos el nivel a la estrucutra predeterminada del nivel correspondiente
                game->level.entities = &game->entities; //Apuntamos el puntero de entidades a las entidades del juego
                if((errorType = loadLevel(&game->level))){ //Se inicializan las entidades del juego con las caracteristicas del nivel
                    return errorType;
                }
                return 0;
            break;

            case LEVEL_2:
                game->level = level3;
                game->level.entities = &game->entities;
                if((errorType = loadLevel(&game->level))){ //Se inicializan las entidades del juego con las caracteristicas del nivel
                    return errorType;
                }
                return 0;
            break;

            default:
                return 0;
        }
    }
    else {
        return ERR_INVALID_GAME_POINTER;
    }
}

int initLevel(Game * game){
    int errorType;
    if(game != NULL){ //Validacion de puntero
        initFrog(&game->frog);
        game->level = level1;//Igualamos el nivel a la estrucutra predeterminada del nivel correspondiente
        game->level.entities = &game->entities; //Apuntamos las entidades del nivel a las entidades del juego
        if((errorType = loadLevel(&game->level))){ //Se inicializan las entidades del juego con las caracteristicas del nivel
            return errorType;
        }
        return 0;
    }
    else {
        return ERR_INVALID_GAME_POINTER;
    }
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static int loadLevel(Level * level){
 if(level != NULL){ 
    int errorType;
    loadLevelEntities(level); //Cargamos las entidades con las caracteristicas del nivel
    if((errorType = checkLevelEntities(level))){ //Chequeamos que no excedamos el maximo de entidades
        return errorType;
    }

    else {
        return 0;
    }
 }
 else {
    return ERR_INVALID_LEVEL_POINTER;
 }
}


static void loadLevelEntities(Level* level){
    uint8_t  i;
    Entity * firstObstacle;
    Entity * firstFloater;
    *(level->entities) = (GameEntities){0}; //inicializa en cero para sacar basura
    firstObstacle = level->entities->obstacles;
    firstFloater = level->entities->floaters;
    for(i=0; i<MAP_HEIGHT; i++){ //Recorremos las filas del mapa 
        switch(level->rows[i].zone){
            case ROAD: //Si estamos en la calle cargamos los obstaculos 
                loadZoneEntities(level->rows, i, firstObstacle);
                i+=MAX_PLAYING_ZONE_HEIGHT-1;
            break;
            case WATER: //Si estamos en la calle cargamos los obstaculos 
                loadZoneEntities(level->rows, i, firstFloater);
                i+=MAX_PLAYING_ZONE_HEIGHT-1;
            break;
            case SAFE:
            case START:
            case DEFAULT:
            default:
                break;
        }
    }
}


static void loadRowEntities(Row* row, uint8_t rowNumber){
    uint8_t  k;
    int x0 = 0;
    for(k = 0; k<(row->entityCount); k++){ //Inicializamos cada entidad de la fila con las caracteristicas del nivel
        ((row->firstEntity)[k]).x = x0 + (row->entityLength+row->gap)*k;
        ((row->firstEntity)[k]).y = rowNumber;
        ((row->firstEntity)[k]).speed = row->speed;
        ((row->firstEntity)[k]).direction = row->direction;
        ((row->firstEntity)[k]).length = row->entityLength;
        ((row->firstEntity)[k]).active = true;
    }
}

static void loadZoneEntities(Row* rows, uint8_t  zoneStart, Entity* firstEntity){
    uint8_t  j;
    Entity *current = firstEntity;
    for(j=0; j<MAX_PLAYING_ZONE_HEIGHT; j++ ){ 
        rows[zoneStart + j].firstEntity = current; //Apuntamos el primer elemento de la fila segun los ultimos de las otras 
        current += rows[zoneStart + j].entityCount;
        loadRowEntities(&(rows[zoneStart+j]), zoneStart+j); //Cargamos los elementos de la fila
    }
}

static int checkLevelEntities(Level* level){ //Chequeamos que no nos excedimos del maximo de cada tipo de entidad al disenar el nivel 

    if(level != NULL){
            uint8_t  i; 
            uint8_t  obstacleCount = 0;
            uint8_t  floaterCount = 0;

            for ( i = 0; i < MAP_HEIGHT; i++) {

                if (level->rows[i].zone == ROAD){
                    obstacleCount += level->rows[i].entityCount;
                }

                if (level->rows[i].zone == WATER){
                    floaterCount += level->rows[i].entityCount;
                }
            }

            if(obstacleCount>MAX_OBSTACLES){
                return  ERR_MAX_OBSTACLES_EXCEEDED;
            }
            if(floaterCount>MAX_FLOATERS){
                return ERR_MAX_FLOATERS_EXCEEDED;
            }

            else{
                return 0;
            }
    }

 else {
    return ERR_INVALID_LEVEL_POINTER;
 }

}



/******************************************************************************/
 