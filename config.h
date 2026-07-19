/***************************************************************************//**
  @file     +config.h+
  @brief    +Constantes de configuracion del juego+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

 #ifndef _CONFIG_H_
 #define _CONFIG_H_
 
 /*******************************************************************************
  * INCLUDE HEADER FILES
  ******************************************************************************/
 
 
 
 /*******************************************************************************
  * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
  ******************************************************************************/
 //MAP SETTINGS////////////////////////////////////////////////////////// 
 #define MAP_WIDTH 15
 
 #define MAP_HEIGHT 15
 
 #define FINISH_LINE MAP_HEIGHT - 1
 
 #define MAX_PLAYING_ZONE_HEIGHT 6
 
 //ENTITIES SETTINGS/////////////////////////////////////////////////////
 #define MAX_OBSTACLES 20
 
 #define MAX_FLOATERS 20
 
 #define ENTITY_UPDATE_PERIOD 0.10
 
 //FROG SETTINGS//////////////////////////////////////////////////////////
 
 #define FROG_X0 (MAP_WIDTH/2)
 
 #define FROG_Y0 0
 
 //GAME SETTINGS/////////////////////////////////////////////////////////
 #define MAX_LIVES 3
 
 #define POINT_WEIGHT 50
 
 #define MAX_SCORE 999
 
 #define MIN_SCORE 0
 
 #define TOP10_SIZE 10
 
 #define TOP10_FILE "top10.txt"
 
 ///////////////////////////////////////////////////////////////////////////////
 #define ISEVEN(x) ((x)%2==0)
 ////////////////////////////////////////////////////////////////
 typedef enum{
   ERR_MAX_OBSTACLES_EXCEEDED=2,
   ERR_MAX_FLOATERS_EXCEEDED, 
   ERR_INVALID_GAME_POINTER, 
   ERR_INVALID_LEVEL_POINTER,
   ERR_INVALID_FROG_POINTER,
   ERR_INVALID_OBSTACLE_POINTER,
   ERR_INVALID_FLOATER_POINTER,
   ERR_INVALID_SCORE_POINTER,
   ERR_INVALID_LIVES_POINTER,
   ERR_INVALID_ID_POINTER,
   ERR_INVALID_FLOATER_COUNT,
   ERR_INVALID_OBSTACLE_COUNT
 }ErrorType;
 
 
 typedef enum{ //con esto aca funco entites.h con rapsi
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SELECT,
    NONE
 } Input;
 
 typedef enum{ //con esto aca funco entites.h con rapsi
    MENU,
    PLAYING,
    PAUSED,
    VICTORY,
    GAME_OVER,
    POINTS,
    EXIT
 } GameStateId;
 
 /*******************************************************************************
  * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
  ******************************************************************************/
 
 // +ej: extern unsigned int anio_actual;+
 
 
 #endif // _CONFIG_H_
 