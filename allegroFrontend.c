/*
  @file     +allegroFrontend.c+
  @brief    +Descripcion del archivo+
  @author   +Bianco-Blanco-Gerli-Paysse+
*/

//sino se rompe todo 1

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h> 
#include <allegro5/allegro_image.h>       // Para al_init_image_addon
#include <allegro5/allegro_audio.h>       // Para al_install_audio
#include <allegro5/allegro_primitives.h>

#include "allegroFrontend.h"   
#include "game.h"
#include "entities.h"
#include "config.h"
#include "allegroFrontendInternal.h"


/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/

static ALLEGRO_EVENT_QUEUE *queue = NULL;
static ALLEGRO_DISPLAY* display;

ALLEGRO_BITMAP* floater_trunk = NULL;
ALLEGRO_BITMAP* car = NULL;
ALLEGRO_BITMAP* truck = NULL;
ALLEGRO_BITMAP* frog = NULL;
ALLEGRO_BITMAP* pause_img = NULL;
ALLEGRO_BITMAP* skull = NULL;
ALLEGRO_BITMAP* trophy = NULL;
ALLEGRO_BITMAP* heart = NULL;
ALLEGRO_BITMAP* safe_box = NULL;
ALLEGRO_BITMAP* floater_leaf = NULL;
 
ALLEGRO_FONT* very_big_font = NULL;
ALLEGRO_FONT* big_font = NULL;
ALLEGRO_FONT* medium_font = NULL;
ALLEGRO_FONT* small_font = NULL;
 
ALLEGRO_COLOR white;
ALLEGRO_COLOR pink;
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

 static void loadFiles(void);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void frontendInit(void) {

    //Inicializa el núcleo de Allegro y todos los subsistemas necesarios para el juego. 
    if (al_init() == false) {
        printf("Fallo al_init\n");
        return;
    }
    //Inicializa
    if (al_install_keyboard() == false) {
        printf("Fallo teclado\n");
    }

    if (al_init_image_addon() == false) {
        printf("Fallo image addon\n");
    }

    if (al_init_primitives_addon() == false) {
        printf("Fallo image addon\n");
    }

    if (al_install_audio() == false) {
        printf("Fallo audio\n");
    }

    if (al_init_font_addon() == false) {
        printf("Fallo font addon\n");
    }


    //Creamos ventana del juego
    al_set_new_display_flags(ALLEGRO_WINDOWED);

    display = al_create_display(MAP_WIDTH*SCALE + 2*MARGIN, (MAP_HEIGHT+1)*SCALE);
    if(display == NULL) {
        printf("Fallo al_create_display\n");
        return;
    }

    al_init_ttf_addon();

    //Creamos la cola de eventos para manejar el teclado y la ventana
    queue = al_create_event_queue();
    if(queue == NULL) {
        printf("Fallo al_create_event_queue\n");
        al_destroy_display(display); // Limpiamos la ventana antes de salir
        return;
    }

    // Registramos teclado y eventos de la ventana en la cola
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    //Inicializa los colores globales del frontend
    white = al_map_rgb(255, 255, 255);
    pink = al_map_rgb(255, 105, 180);

    // Cargamos imagenes y fuentes
    loadFiles();
}

/**
 * @brief Inicializa todo el entorno gráfico, periféricos y recursos de Allegro.
 * @return 
 */


Input frontendGetInput(void){
    ALLEGRO_EVENT event;
    
    if (al_get_next_event(queue, &event) == true){
        if (event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_UP:    return UP;   
                case ALLEGRO_KEY_DOWN:  return DOWN;
                case ALLEGRO_KEY_LEFT:  return LEFT;
                case ALLEGRO_KEY_RIGHT: return RIGHT;
                case ALLEGRO_KEY_ENTER: return SELECT;
                //case ALLEGRO_EVENT_DISPLAY_CLOSE: return ;
                default: return NONE;
            }
        }
        /*else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            al_destroy_event_queue(queue);
            al_destroy_display(display);
            return ...; //OJO QUE NO EXISTE EN LA STRUCT ESTE CASO
        } */
       else {
        return NONE;
       }
    }

    else {
        return NONE;
    }
}
  

void frontendRender(Game * game){

    //pintamos todo el fondo de negro para borrar el fotograma anterior
   al_clear_to_color(al_map_rgb(0, 0, 0));

   int game_state = (game -> state.id);
   //int game_state = PAUSED;

   switch (game_state){
    case MENU:
    drawMainMenu(game);
    break;

    case PLAYING:
    drawZones(game);
    drawObstacles(game);
    drawFrog(game);
    drawScore(game);
    drawLevel(game);
    drawLives(game);
    drawFinishBoxes(game);
    cloneFrog(game);
    break;

    case GAME_OVER:
    drawGameOver(game);
    break;

    case VICTORY:
    drawVictory(game);
    break;

    case POINTS:
    drawTop10(game);
    break;

    case PAUSED:
    drawPaused(game);
    break;

    case EXIT:
    break;

    default:
    break;
   }

   al_flip_display();
}


void frontendDestroy(void){

    //Liberamos memoria al finalizar el programa
    if (car) al_destroy_bitmap(car);
    if (truck) al_destroy_bitmap(truck);
    if (trophy) al_destroy_bitmap(trophy);
    if (skull) al_destroy_bitmap(skull);
    if (frog) al_destroy_bitmap(frog);
    if (floater_trunk) al_destroy_bitmap(floater_trunk);
    if (pause_img) al_destroy_bitmap(pause_img);
    if (heart) al_destroy_bitmap(heart);
    if (safe_box) al_destroy_bitmap(safe_box);
    if (floater_leaf) al_destroy_bitmap(floater_leaf);

    
    if (very_big_font) al_destroy_font(very_big_font);
    if (medium_font) al_destroy_font(medium_font);
    if (big_font) al_destroy_font(big_font);
    if (small_font) al_destroy_font(small_font);

    if (queue) al_destroy_event_queue(queue);
    if (display) al_destroy_display(display);
}


 /*******************************************************************************
  *******************************************************************************
                         LOCAL FUNCTION DEFINITIONS
  *******************************************************************************
  ******************************************************************************/

static void loadFiles (void){
    floater_trunk = al_load_bitmap("floater_trunk.png");
    car = al_load_bitmap("car.png");
    printf("car=%p\n", car);
    truck = al_load_bitmap("truck.png");
    printf("truck=%p\n", truck);
    frog = al_load_bitmap("frog.png");
    printf("frog=%p\n", frog);
    skull = al_load_bitmap("skull.png");
    trophy = al_load_bitmap("trophy.png");
    pause_img =al_load_bitmap("pause.png");
    heart = al_load_bitmap("heart.png");
    safe_box = al_load_bitmap("safe_box.png");

    very_big_font = al_load_ttf_font("Tiny5-Regular.ttf", 200, 0);
    if(very_big_font == NULL){
        printf("ERROR: fuente no cargada\n");
    }
    big_font = al_load_ttf_font("Tiny5-Regular.ttf", 110, 0);
    medium_font = al_load_ttf_font("Tiny5-Regular.ttf", 60, 0);
    small_font = al_load_ttf_font("Tiny5-Regular.ttf", 40, 0);
    printf("very_big_font=%p\n", very_big_font);
    printf("big_font=%p\n", big_font);
    printf("medium_font=%p\n", medium_font);
    printf("small_font=%p\n", small_font);

}

