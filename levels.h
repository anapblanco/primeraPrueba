/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.h)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

 #ifndef _LEVELS_H_
 #define _LEVELS_H_
 
 /*******************************************************************************
  * INCLUDE HEADER FILES
  ******************************************************************************/
 #include "entities.h"
 #include "config.h"
 #include <stdint.h>
   
 /*******************************************************************************
  * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
  ******************************************************************************/
 
 typedef struct Game Game; //va aca
 
 typedef enum{
     SMALL=2,
     MEDIUM,
     LARGE
 }FloaterLength;
 
 typedef enum{
     CAR_LENGTH=1,
     TRUCK_LENGTH
 }ObstacleLength;
 
 typedef enum{
     MIN_GAP=1,
     MEDIUM_GAP,
     MAX_GAP
 }RowGap;
 
 typedef enum{
     ROAD,
     SAFE,
     WATER,
     START,
     DEFAULT
 } Zone;
 
 typedef enum{
     LEVEL_1,
     LEVEL_2,
     LEVEL_3,
     LEVEL_COUNT
 } LevelId;

 
 typedef struct{
 
     CheckpointId checkpoint;
 
     Entity* firstEntity;
 
     Zone zone;
 
     uint8_t  entityCount;
 
     int  entityLength;
 
     RowGap gap;
 
     Speed speed;
 
     Direction direction;
 
 }Row;
 
 typedef struct {
     LevelId id;
     GameEntities* entities;
     Row rows[MAP_HEIGHT +1];
 } Level;
 
 
 /*******************************************************************************
  * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
  ******************************************************************************/
 
 // +ej: extern unsigned int anio_actual;+
 
 /*******************************************************************************
  * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
  ******************************************************************************/
 int initLevel(Game * game);
 int checkLevel(Game * game);
 int goToNextLevel(Game * game);
 int arrivedAtFinishLine(uint8_t  y);
 
 /**
  * @brief TODO: completar descripcion
  * @param param1 Descripcion parametro 1
  * @param param2 Descripcion parametro 2
  * @return Descripcion valor que devuelve
 */
 
 
 
 #endif // _LEVELS_H_
