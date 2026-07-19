/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.h)+
  @brief    +Descripcion del archivo+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

 #ifndef _ENTITIES_H_
 #define _ENTITIES_H_
 
 /*******************************************************************************
  * INCLUDE HEADER FILES
  ******************************************************************************/
 #include "config.h"
 #include <stdbool.h>
 #include <stdint.h>
 
 /*******************************************************************************
  * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
  ******************************************************************************/
 typedef struct Game Game; //necesario aca 
 
 typedef enum{
     DIR_LEFT,
     DIR_RIGHT
 } Direction;
 
 typedef enum{
     SLOW=1,
     MEDIUM_SPEED,
     FAST
 }Speed;
 
 typedef enum{
    NO_CHECKPOINT,
    CHECKPOINT_1,
    CHECKPOINT_2,
    CHECKPOINT_COUNT
} CheckpointId;

 typedef struct{
     int  x; //int para x negativos
     int  y;
     Speed speed;
     Direction direction;
     CheckpointId lastCheckpoint;
 } Frog;
 
 typedef struct{
     int  x; //int para x negativos
     int  y;
     uint8_t  length;
     //int height; 
     Speed speed;
     Direction direction;
     int type;
     bool active;
 }Entity;
 
 typedef struct{
     Entity obstacles[MAX_OBSTACLES];
     Entity floaters[MAX_FLOATERS];
 }GameEntities;
 
 
 /*******************************************************************************
  * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
  ******************************************************************************/
 
 
 
 /*******************************************************************************
  * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
  ******************************************************************************/
 
 int initFrog(Frog * frog);
 /**
  * @brief TODO: Inicializamos la rana, la ubicamos en su posicion inical 
  * @param frog Recibimos un puntero a la rana del juego para settear sus condiciones iniciales
  * @return Devuelve un entero para manejo de errores
 */
 
 int resetFrog(Frog * frog);
 /**
  * @brief TODO: completar descripcion
  * @param param1 Descripcion parametro 1
  * @param param2 Descripcion parametro 2
  * @return Devuelve un entero para manejo de errores
 */
 
 int moveFrog(Frog * frog , Input input);
 /**
  * @brief TODO: completar descripcion
  * @param param1 Descripcion parametro 1
  * @param param2 Descripcion parametro 2
  * @return Devuelve un entero para manejo de errores
 */
 
 int moveFrogWithFloater(Frog * frog , Entity* floater);
 /**
  * @brief TODO: completar descripcion
  * @param param1 Descripcion parametro 1
  * @param param2 Descripcion parametro 2
  * @return Descripcion valor que devuelve
 */
 
 int updateEntities();
 /**
  * @brief TODO: completar descripcion
  * @param param1 Descripcion parametro 1
  * @param param2 Descripcion parametro 2
  * @return Descripcion valor que devuelve
 */
 int frogDies(Frog * frog, uint8_t* lives, GameStateId* id);
 /**
  * @brief TODO: completar descripcion
  * @param param1 Descripcion parametro 1
  * @param param2 Descripcion parametro 2
  * @return Descripcion valor que devuelve
 */
 
 /******************************************************************************/
 
 #endif // _ENTITIES_H_