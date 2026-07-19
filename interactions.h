/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.h)+
  @brief    +Descripcion del archivo+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

 #ifndef _INTERACTIONS_H_
 #define _INTERACTIONS_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
  #include "entities.h"
  #include "config.h"
  #include <stdint.h>

/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct Game Game;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

int manageInteractions(Game* game);
/**
 * @brief TODO: Esta funcion detecta y maneja las interacciones de la rana con las otras entidades del juego, con las zonas y los bordes
 * @param game Recibe un puntero a estructura del juego para acceder a todas las entidades, el nivel, el estado y demas.
 * @return devuelve un entero para control de errores
*/

int updateScore(Frog * frog , uint8_t* score, CheckpointId checkpoint);
/**
 * @brief TODO: Esta funcion actualiza el puntaje cada vez que la rana llega a una zona segura. 
 * @param frog Recibe el puntero a la rana para analizar si llego a una zona segura
 * @param score Recibe el puntero al puntaje 
 * @return devuelve un entero para control de errores
*/

/******************************************************************************/

#endif // _INTERACTIONS_H_
