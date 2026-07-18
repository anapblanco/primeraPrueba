/*
  @file     +raspiFrontend.h+
  @brief    +Funcionees para el frontend de la raspi+
  @author   +Bianco-Blanco-Gerli-Paysse+
*/

#ifndef FRONTEND_H
#define FRONTEND_H

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>
#include "game.h"
#include "config.h"

/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef int DISP[MAP_WIDTH][MAP_HEIGHT]; //para dibujar mensaje mas rapido, no se si para allegro sirve DELFIIIIII avisame

/***************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Funciones para incializar, actualizar y apagar frontend segun backend
*/
void frontendInit(void);
Input frontendGetInput(void);
void frontendRender(Game * game);
void frontendDestroy(void);

#endif
