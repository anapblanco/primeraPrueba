/***************************************************************************//**
  @file     frontend_internal.h
  @brief    Header privado del frontend: compartido entre frontend.c,
            allegroPlay.c y allegroMenus.c. NINGUN otro archivo del
            proyecto debe incluir este header (usan allegroFrontend.h).
  @author   Bianco-Blanco-Gerli-Paysse
 ******************************************************************************/
#ifndef _FRONTEND_INTERNAL_H_
#define _FRONTEND_INTERNAL_H_
 
/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "game.h"
#include "entities.h"
#include "config.h"
 
/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/
#define SCALE 90
#define MARGIN 0
#define ROW(r) ((MAP_HEIGHT) - r)
 
/*******************************************************************************
 * SHARED ASSETS (definidos en frontend.c, cargados en loadFiles)
 ******************************************************************************/
extern ALLEGRO_BITMAP* floater_trunk;
extern ALLEGRO_BITMAP* car;
extern ALLEGRO_BITMAP* truck;
extern ALLEGRO_BITMAP* frog;
extern ALLEGRO_BITMAP* pause_img;
extern ALLEGRO_BITMAP* skull;
extern ALLEGRO_BITMAP* trophy;
extern ALLEGRO_BITMAP* heart;
extern ALLEGRO_BITMAP* safe_box;
extern ALLEGRO_BITMAP* floater_leaf;
 
extern ALLEGRO_FONT* very_big_font;
extern ALLEGRO_FONT* big_font;
extern ALLEGRO_FONT* medium_font;
extern ALLEGRO_FONT* small_font;
 
extern ALLEGRO_COLOR white;
extern ALLEGRO_COLOR pink;
 
/*******************************************************************************
 * FUNCTION PROTOTYPES - allegroPlay.c
 ******************************************************************************/
void drawZones(Game * p2game);
void drawObstacles(Game * p2game);
void drawFrog(Game * p2game);
void drawScore(Game * p2game);
void drawLives(Game * p2game);
void drawFinishBoxes(Game * p2game);
void cloneFrog(Game * p2game);
 
/*******************************************************************************
 * FUNCTION PROTOTYPES - allegroMenus.c
 ******************************************************************************/
void drawMainMenu(Game * p2game);
void drawGameOver(Game * p2game);
void drawPaused(Game * p2game);
void drawVictory(Game * p2game);
void drawTop10(Game * p2game);
void top10_notify(Game * p2game, int x, int y);
 
/******************************************************************************/
 
#endif // _FRONTEND_INTERNAL_H_