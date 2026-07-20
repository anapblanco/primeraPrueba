/***************************************************************************//**
@file     +allegroFrontend.h+
  @brief    +Funcionees para el frontend de la raspi+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

 #ifndef ALLEGRO_FRONTEND_H
 #define ALLEGRO_FRONTEND_H
 
 /*******************************************************************************
  * INCLUDE HEADER FILES
  ******************************************************************************/
 
 #include <stdint.h>
 #include "game.h"
 #include "config.h"

 /*******************************************************************************
  * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
  ******************************************************************************/
 
 /***************************************************************************
  * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
  ******************************************************************************/
 
 /**
  * @brief Funciones para incializar, actualizar y apagar frontend 
 */
void frontendInit(void);
Input frontendGetInput(void);
void frontendRender(Game * game);
void frontendDestroy(void);

#endif
 
 