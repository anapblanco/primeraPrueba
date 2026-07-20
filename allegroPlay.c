/***************************************************************************//**
  @file     allegroPlay.c
  @brief    Dibujo de todo lo que se ve durante el estado PLAYING.
  @author   Bianco-Blanco-Gerli-Paysse
 ******************************************************************************/
 
/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
 
#include "allegroFrontendInternal.h"
#include "game.h"
#include "entities.h"
#include "config.h"
 
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


 void drawZones(Game * p2game){
    
    int i, y1, y2;
    int x1 = 0;
    int x2 = MAP_WIDTH*SCALE;
    ALLEGRO_COLOR road_colour = al_map_rgb(45, 45, 48);
    ALLEGRO_COLOR water_colour = al_map_rgb(0, 119, 190);
    ALLEGRO_COLOR safe_colour = al_map_rgb(46, 139, 87);


    for (i=0 ; i <= MAP_HEIGHT ; i++){
        y1 = ROW(i)*SCALE;
        y2 = y1 + SCALE;

        switch (((p2game->level).rows[i]).zone){
            case ROAD:
            al_draw_filled_rectangle(x1, y1, x2, y2, road_colour);
            break;

            case WATER:
            al_draw_filled_rectangle(x1, y1, x2, y2, water_colour);
            break;

            case START:
            al_draw_filled_rectangle(x1, y1, x2, y2, safe_colour);
            break;

            case SAFE:
            al_draw_filled_rectangle(x1, y1, x2, y2, safe_colour);
            break;

            default: break;

        }
    }

}

 void drawObstacles( Game* p2game){

    int i, x, y, new_lenght, new_height, space = 10;
    int flag_direction = 0; //flag para rotar el dibujo

    //Bucle generador de vehículos
    for (i=0 ; i<MAX_OBSTACLES ; i++){
        //Si la entidad está activa, la dibujamos en la pantalla
        if (p2game -> entities.obstacles[i].active){
            x = (p2game -> entities.obstacles[i].x)*SCALE;
            y = ROW((p2game -> entities.obstacles[i].y))*SCALE;

            //en los png los vehículos apuntan para la izquierda
            if ((p2game -> entities.obstacles[i].direction) == DIR_LEFT){
                flag_direction = 0;
            }
            else {
                flag_direction = ALLEGRO_FLIP_HORIZONTAL;
            }

            if (p2game -> entities.obstacles[i].length == CAR_LENGTH){
                al_draw_scaled_bitmap(car, 0, 0, al_get_bitmap_width(car), al_get_bitmap_height(car), x, y, al_get_bitmap_width(car)-space, al_get_bitmap_height(car)-space, flag_direction);
            }
            else { //es camión
                al_draw_scaled_bitmap(truck, 0, 0, al_get_bitmap_width(truck), al_get_bitmap_height(truck), x, y, al_get_bitmap_width(truck)-4*space, al_get_bitmap_height(truck)-4*space, flag_direction);
            }
        }

    }

    //Bucle generador de flotadores
    for (i=0 ; i<MAX_FLOATERS ; i++){
        //Si la entidad está activa, la dibujamos en la pantalla
        if (p2game -> entities.floaters[i].active){
            x = (p2game -> entities.floaters[i].x)*SCALE;
            y = ROW((p2game -> entities.floaters[i].y))*SCALE;
            new_lenght = (p2game -> entities.floaters[i].length)*SCALE;
            new_height = SCALE;
            
            if ((p2game -> entities.floaters[i].direction) == DIR_LEFT){
                flag_direction = 0;
            }
            else {
                flag_direction = ALLEGRO_FLIP_HORIZONTAL;
            }
            //Dibujamos el tronco con el largo correspondiente
            al_draw_scaled_bitmap(floater_trunk, 0, 0, al_get_bitmap_width(floater_trunk),
                al_get_bitmap_height(floater_trunk), x, y, new_lenght, new_height,flag_direction );
        }

    }
}

 void drawFrog(Game * p2game){
    int x = (p2game -> frog.x)*SCALE + MARGIN;
    int y = ROW((p2game -> frog.y))*SCALE;
    int space = 35;
    al_draw_scaled_bitmap (frog, 0, 0,al_get_bitmap_width(frog), al_get_bitmap_height(frog), x, y, al_get_bitmap_width(frog)-space, al_get_bitmap_height(frog)-space, 0);
}

 void drawScore(Game* p2game){
    int score = ( p2game->score);
    int spacing = 30;
    char score_as_string[11];
    snprintf(score_as_string, sizeof(score_as_string), "SCORE: %d", score);
    al_draw_text(small_font, white, spacing, spacing, ALLEGRO_ALIGN_LEFT, score_as_string);
}

 void drawLevel(Game* p2game){
    int level = (p2game->level.id)+1;
    int spacing = 30;
    char level_as_string[11];
    snprintf(level_as_string, sizeof(level_as_string), "LEVEL: %d", level);
    al_draw_text(small_font, white, spacing, MAP_HEIGHT*SCALE - spacing, ALLEGRO_ALIGN_LEFT, level_as_string);
}

 void drawLives(Game* p2game){
    int text_height = al_get_font_line_height(small_font);
    int i, spacing = 30;
    int lives = (p2game->lives);
    for (i=0 ; i<lives ; i++){
        al_draw_scaled_bitmap(heart, 0, 0, al_get_bitmap_width(heart), al_get_bitmap_height(heart), MAP_WIDTH*SCALE - (i+1)*(text_height+spacing), spacing, text_height, text_height, 0);
    }
}

 void drawFinishBoxes(Game* p2game){
    
    int i, x, y;

    for (i=0 ; i<5 ; i++){
        x = (p2game -> level.finishBoxes[i].x)*SCALE;
        y = ROW(MAP_HEIGHT+1)*SCALE;
        al_draw_scaled_bitmap(safe_box, 0, 0, al_get_bitmap_width(safe_box), al_get_bitmap_height(safe_box), x, y, SCALE, SCALE, 0);
    }
}

 void cloneFrog(Game * p2game){
    int i, x, y,zones_occupied;

    for (i=0,zones_occupied = 1; i<FINISH_BOX_COUNT ; i++){
        if(p2game -> level.finishBoxes[i].occupied){
            x = (p2game -> level.finishBoxes[i].x)*SCALE;
            y = ROW(MAP_HEIGHT+1)*SCALE;
                al_draw_scaled_bitmap(frog, 0, 0, al_get_bitmap_width(frog), al_get_bitmap_height(frog), x, y, SCALE, SCALE, 0);
        }
    }
}

