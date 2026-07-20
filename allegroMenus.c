/***************************************************************************//**
  @file     allegroMenus.c
  @brief    Dibujo de las pantallas de menu/estado: MENU, GAME_OVER, PAUSED,
            VICTORY y POINTS (top10).
  @author   Bianco-Blanco-Gerli-Paysse
 ******************************************************************************/


/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "config.h"
#include "allegroFrontendInternal.h"
#include "game.h"
#include "entities.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
 

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


 void drawMainMenu (Game* p2game){

    int spacing1 = 140;
    int spacing2 = 100;
    int y_menu = 430;
    int y_option1 = y_menu + spacing1;
    int x_menu;
    int x_center =(SCALE*MAP_WIDTH)/2; //el medio de la pantalla

    ALLEGRO_COLOR color;

    int option_selected = (p2game -> state.menu.selected);

    int title_width = al_get_text_width(very_big_font, "FROGGER");

    x_menu = x_center - title_width/2;

    al_draw_text(very_big_font, white, x_center, 150, ALLEGRO_ALIGN_CENTER, "FROGGER");

    al_draw_text(big_font, white, x_menu, y_menu, ALLEGRO_ALIGN_LEFT, "MENU");

    color = (option_selected == MENU_PLAY)? pink : white;
    al_draw_text(medium_font, color, x_menu, y_option1, ALLEGRO_ALIGN_LEFT, "Play");

    color = (option_selected == MENU_POINTS)? pink : white;
    al_draw_text(medium_font, color, x_menu, y_option1 + spacing2, ALLEGRO_ALIGN_LEFT, "Best scores");

    color = (option_selected == MENU_EXIT)? pink : white;
    al_draw_text(medium_font, color, x_menu, y_option1 + 2*spacing2, ALLEGRO_ALIGN_LEFT, "Exit");
}

 void drawGameOver (Game* p2game){
    ALLEGRO_COLOR color;

    int option_selected = (p2game -> state.gameOver.selected);
    int spacing1 = 250;
    int spacing2 = 100;
    int y_title = 400;
    int y_options = y_title + spacing1;
    int x_options;
    int x_center =(SCALE*MAP_WIDTH)/2; //el medio de la pantalla
    int y_skull = y_title/2;

    int score = ( p2game->score);
    char score_as_string[20];

    int title_width = al_get_text_width(very_big_font, "GAME OVER");
    int skull_width = al_get_bitmap_width(skull);
    x_options = x_center - title_width/2;

    al_draw_bitmap(skull, x_center- skull_width/2, y_skull, 0);

    al_draw_text(very_big_font, white, x_center, y_title, ALLEGRO_ALIGN_CENTER, "GAME OVER");

    color = (option_selected == GAME_OVER_MENU)? pink : white;
    al_draw_text(medium_font, color, x_options, y_options, ALLEGRO_ALIGN_LEFT, "Back to menu");

    color = (option_selected == GAME_OVER_EXIT)? pink : white;
    al_draw_text(medium_font, color, x_options, y_options + spacing2, ALLEGRO_ALIGN_LEFT, "Exit");

    snprintf(score_as_string, sizeof(score_as_string), "TOTAL SCORE: %d", score);
    al_draw_text(big_font, white, x_options, y_options + 2*spacing2, ALLEGRO_ALIGN_LEFT,score_as_string);

    //si el usuario es top10, notificamos
    top10_notify(p2game, x_options, y_options + 4*spacing2);
}

 void drawVictory(Game* p2game){

    ALLEGRO_COLOR color;

    int option_selected = (p2game -> state.victory.selected);
    int spacing1 = 250;
    int spacing2 = 100;
    int y_title = 400;
    int y_options = y_title + spacing1;
    int x_options;
    int x_center =(SCALE*MAP_WIDTH)/2; //el medio de la pantalla
    int y_trophy = y_title/2;

    int title_width = al_get_text_width(very_big_font, "YOU WIN");
    int trophy_width = al_get_bitmap_width(trophy);
    x_options = x_center - title_width/2;

    int score = ( p2game->score);
    char score_as_string[20];

    al_draw_bitmap(trophy, x_center- trophy_width/2, y_trophy, 0);

    al_draw_text(very_big_font, white, x_center, y_title, ALLEGRO_ALIGN_CENTER, "YOU WIN");

    color = (option_selected == VICTORY_MENU)? pink : white;
    al_draw_text(medium_font, color, x_options, y_options, ALLEGRO_ALIGN_LEFT, "Back to menu");

    color = (option_selected == VICTORY_EXIT)? pink : white;
    al_draw_text(medium_font, color, x_options, y_options + 2*spacing2, ALLEGRO_ALIGN_LEFT, "Exit");

    snprintf(score_as_string, sizeof(score_as_string), "TOTAL SCORE: %d", score);
    al_draw_text(big_font, white, x_options, y_options + 2*spacing2, ALLEGRO_ALIGN_LEFT,score_as_string);

    //si el usuario es top10, notificamos
    top10_notify(p2game, x_options, y_options + 4*spacing2);
    
}

 void drawPaused (Game* p2game){

    ALLEGRO_COLOR color;

    int option_selected = (p2game -> state.paused.selected);
    int spacing1 = 180;
    int spacing2 = 100;
    int y_title = 600;
    int y_options = y_title + spacing1;
    int x_options;
    int x_center =(SCALE*MAP_WIDTH)/2; //el medio de la pantalla
    int y_image = y_title/3;

    int title_width = al_get_text_width(big_font, "GAME PAUSED");
    int image_width = al_get_bitmap_width(pause_img);
    x_options = x_center - title_width/2;

    al_draw_bitmap(pause_img, x_center- image_width/2, y_image, 0);

    al_draw_text(big_font, white, x_center, y_title, ALLEGRO_ALIGN_CENTER, "GAME PAUSED");

    color = (option_selected == PAUSED_MENU)? pink : white;
    al_draw_text(medium_font, color, x_options, y_options, ALLEGRO_ALIGN_LEFT, "Back to menu");

    color = (option_selected == PAUSED_PLAY)? pink : white;
    al_draw_text(medium_font, color, x_options, y_options + spacing2, ALLEGRO_ALIGN_LEFT, "Continue");

    color = (option_selected == PAUSED_EXIT)? pink : white;
    al_draw_text(medium_font, color, x_options, y_options + 2*spacing2, ALLEGRO_ALIGN_LEFT, "Exit");
}

 void drawTop10(Game* p2game){

    ALLEGRO_COLOR color;

    int i;
    char position[5]; //string #1, #2, ...
    char score_as_string[30]; //string para poner puntaje en pantalla
    int *pScores = p2game->scoresTop10;
    int selected = p2game->state.points.selected;

    // Constantes de diseño
    int x_center = (SCALE*MAP_WIDTH)/2;
    int y_title = 100;
    int spacing_trophy = 100;
    int spacing1 = 60;
    int spacing2 = 70;

    int orig_width = al_get_bitmap_width(trophy);
    int orig_height = al_get_bitmap_height(trophy);

    // Dimensiones para centrado
    int title_width = al_get_text_width(big_font, "TOP 10");
    int title_height = al_get_font_line_height(big_font);

    // Dimensiones para centrado
    int x_trophy1 = x_center - title_width/2 - spacing_trophy - al_get_bitmap_width(trophy);
    int x_trophy2 = x_center + title_width/2 + spacing_trophy;
    int y_top1 = y_title + title_height + spacing1;

    // 1. Dibujar Título y Trofeos
    al_draw_text(big_font, white, x_center, y_title, ALLEGRO_ALIGN_CENTER, "TOP 10");
    al_draw_scaled_bitmap(trophy, 0, 0, orig_width, orig_height, x_trophy1, y_title, title_height, title_height, 0);
    al_draw_scaled_bitmap(trophy, 0, 0, orig_width, orig_height, x_trophy2, y_title, title_height, title_height, 0);

    // 2. Dibujar Lista del Top 10
    for (i = 0; i < TOP10_SIZE; i++){
        snprintf(score_as_string, sizeof(score_as_string), "%d", pScores[i]);
        snprintf(position, sizeof(position), "#%d", i + 1);

        color = (selected == i) ? pink : white;

        al_draw_text(small_font, color, x_trophy1, y_top1 + i*spacing2, ALLEGRO_ALIGN_LEFT, position);
        al_draw_text(small_font, color, x_trophy2 + title_height, y_top1 + i*spacing2, ALLEGRO_ALIGN_RIGHT, score_as_string);
    }
    // 3. Dibujar Opciones de Menú
    color = (selected == POINTS_MENU)? pink : white;
    al_draw_text(medium_font, color, x_trophy1, y_top1 + (TOP10_SIZE +2)*spacing2, ALLEGRO_ALIGN_LEFT, "Back to menu");

    color = (selected == POINTS_EXIT)? pink : white;
    al_draw_text(medium_font, color, x_trophy1,y_top1 + (TOP10_SIZE+3)*spacing2, ALLEGRO_ALIGN_LEFT, "Exit");
}

 void top10_notify(Game* p2game, int x, int y){
    if (p2game->score > p2game->scoresTop10[TOP10_SIZE - 1]){
        al_draw_text(medium_font, pink, x, y, ALLEGRO_ALIGN_LEFT,
                "YOU MADE IT TO THE TOP 10!");
    
            return;
        }
    return;
}