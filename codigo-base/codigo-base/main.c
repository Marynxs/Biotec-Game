#include <stdlib.h>;
#include <time.h>
//#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
//#include "essential.h"

int main() {
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();

	al_set_new_display_flags(ALLEGRO_NOFRAME);
	ALLEGRO_DISPLAY* display = al_create_display(640,480);
	al_set_window_title(display, "bioHospital");

	ALLEGRO_FONT* fontMain = al_load_ttf_font("fonts/retrogaming.ttf", 16, ALLEGRO_TTF_MONOCHROME);
	ALLEGRO_FONT* fontExtra = al_load_ttf_font("fonts/04b.ttf", 24, ALLEGRO_TTF_MONOCHROME);
	ALLEGRO_FONT* fontExtraBig = al_load_ttf_font("fonts/04b.ttf", 40, ALLEGRO_TTF_MONOCHROME);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 20.0);
	ALLEGRO_KEYBOARD_STATE key_state;
	ALLEGRO_MOUSE_STATE mouse_state;

	ALLEGRO_BITMAP* blackpng = NULL;
	ALLEGRO_BITMAP* yellowpng = NULL;
	ALLEGRO_BITMAP* pinkpng = NULL;
	ALLEGRO_BITMAP* bluepng = NULL;
	ALLEGRO_BITMAP* mouseIcon = NULL;
	ALLEGRO_BITMAP* mouseIconClicked = NULL;
	ALLEGRO_BITMAP* titleExe = NULL;
	ALLEGRO_BITMAP* borda = NULL;
	ALLEGRO_BITMAP* exit = NULL;
	ALLEGRO_BITMAP* window = NULL;
	ALLEGRO_BITMAP* minimize = NULL;

	blackpng = al_load_bitmap("assets/black.png");
	yellowpng = al_load_bitmap("assets/yellow.png");
	pinkpng = al_load_bitmap("assets/pink.png");
	bluepng = al_load_bitmap("assets/blue.png");
	mouseIcon = al_load_bitmap("assets/mouse.png");
	mouseIconClicked = al_load_bitmap("assets/mouseclicked.png");
	titleExe = al_load_bitmap("assets/title.png");
	borda = al_load_bitmap("assets/borda.png");
	exit = al_load_bitmap("assets/exit.png");
	window = al_load_bitmap("assets/window.png");
	minimize = al_load_bitmap("assets/minimize.png");
	assert(blackpng != NULL);
	assert(yellowpng != NULL);
	assert(pinkpng != NULL);
	assert(bluepng != NULL);
	assert(mouseIcon != NULL);
	assert(titleExe != NULL);
	assert(borda != NULL);
	assert(exit != NULL);
	assert(window != NULL);
	assert(minimize != NULL);

	//surgery
	struct surgeryFirst {
		ALLEGRO_BITMAP* bitmap;
		int x;
		int y;
	} syringe, syringeJuice;
	struct surgerySecond {
		ALLEGRO_BITMAP* bitmapIdle;
		ALLEGRO_BITMAP* bitmapIngame;
		ALLEGRO_BITMAP* bitmapEnd;
		int x;
		int y;
	}bloodBag;
	ALLEGRO_BITMAP* backgroundSurgery = NULL;
	syringe.bitmap = NULL;
	syringeJuice.bitmap = NULL;
	bloodBag.bitmapIdle = NULL;
	bloodBag.bitmapIngame = NULL;
	bloodBag.bitmapEnd = NULL;

	backgroundSurgery = al_load_bitmap("assets/examroom.png");
	syringe.bitmap = al_load_bitmap("assets/seringa.png");
	syringeJuice.bitmap = al_load_bitmap("assets/seringajuice.png");
	bloodBag.bitmapIdle = al_load_bitmap("assets/bloodbagindle.png");
	bloodBag.bitmapIngame = al_load_bitmap("assets/bloodbagingame.png");
	bloodBag.bitmapEnd = al_load_bitmap("assets/bloodbagfull.png");
	assert(syringe.bitmap != NULL);
	assert(syringeJuice.bitmap != NULL);
	assert(bloodBag.bitmapIdle != NULL);
	assert(bloodBag.bitmapIngame != NULL);
	assert(bloodBag.bitmapEnd != NULL);
	assert(backgroundSurgery != NULL);

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	int x, y, h, w;
	al_get_clipping_rectangle(&x, &y, &w, &h);
	bool levels = true, surgery = false, surgeryFirst = false, surgerySecond = false;
	float timing = 0;
	int height = al_get_display_height(display);
	int width = al_get_display_width(display);
	int centerX = 320, centerY = 240;
	float mouseX = 0, mouseY = 0;

	syringe.x = 250, syringe.y = 150;
	syringeJuice.x = syringe.x, syringeJuice.y = syringe.y - 70;
	
	ALLEGRO_MOUSE_CURSOR* cursor = al_create_mouse_cursor(mouseIcon, mouseX, mouseY);

	bool running = true;
	al_start_timer(timer);
	while (running) {
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		al_get_mouse_state(&mouse_state);
		al_get_keyboard_state(&key_state);
		

		//mouse cursor
		if (al_set_mouse_cursor(display, cursor) && event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			mouseX = event.mouse.x;
			mouseY = event.mouse.y;
		}
		if ((mouse_state.buttons & 1) && (mouseX >= 618 && mouseX <= 637) && (mouseY >= 3 && mouseY <= 17)) {
			running = false;
		}

		//minigame select
		if (levels) {
			al_draw_bitmap(backgroundSurgery, 0, 0, 0);
			al_draw_bitmap(pinkpng, 0, 0, 0);
			al_draw_text(fontMain, al_map_rgb(216, 232, 230), 100, 100, 0, "surgery game");
			if ((mouse_state.buttons & 1) && mouseX >= 100 && mouseX <= 200 && mouseY >= 100 && mouseY <= 200) {
				levels = false;
				surgery = true;
				timing = 0;
			}
		}


		//minigame surgery
		if(surgery) {
			al_draw_bitmap(backgroundSurgery, 0, 0, 0);
		}



		if (event.type == ALLEGRO_EVENT_TIMER) {
			if (surgery) {
				if (timing >= 0 && timing <= 6) {
					al_draw_bitmap(blackpng, 0, 0, 0);
					if (timing >= 0 && timing <= 1)
						al_draw_text(fontExtraBig, al_map_rgb(112, 157, 207), centerX - 80, centerY - 30, 0, "Ready?");
					else if (timing >= 1 && timing <= 2)
						al_draw_text(fontExtraBig, al_map_rgb(235, 198, 134), centerX - 10, centerY - 30, 0, "3");
					else if (timing >= 2 && timing <= 3)
						al_draw_text(fontExtraBig, al_map_rgb(235, 198, 134), centerX - 10, centerY - 30, 0, "2");
					else if (timing >= 3 && timing <= 4)
						al_draw_text(fontExtraBig, al_map_rgb(235, 198, 134), centerX - 10, centerY - 30, 0, "1");
					else if(timing >= 4 && timing <= 5){
						al_draw_text(fontExtraBig, al_map_rgb(235, 198, 134), centerX - 40, centerY - 30, 0, "Go!");
					}
					else{
					}
				}
				if(surgeryFirst) {
					al_draw_bitmap(syringe.bitmap, syringe.x, syringe.y, 0);
					al_set_clipping_rectangle(0, 0, width, 350);
					al_draw_bitmap(syringeJuice.bitmap, syringeJuice.x, syringeJuice.y, 0);
					al_set_clipping_rectangle(0, 0, width, height);
					if (mouse_state.buttons & 1)
						syringeJuice.y = mouseY;
					if (syringeJuice.y <= 10)
						syringeJuice.y = 10;
					if (syringeJuice.y >= 150) {
						syringeJuice.y = 150;
						surgeryFirst = false;
						surgerySecond = true;
					}
				}
				if (surgerySecond) {

				}
			}
			al_draw_bitmap(borda, 0, 0, 0);
			al_draw_bitmap(titleExe, 5, 2, 0);
			al_draw_bitmap(exit, 618, 2, 0);
			al_draw_bitmap(window, 598, 2, 0);
			al_draw_bitmap(minimize, 578, 2, 0);
			timing += 0.05;
			if (mouse_state.buttons & 1)
				al_draw_bitmap(mouseIconClicked, mouseX, mouseY, 0);
			al_flip_display();
		}

	}
	al_destroy_display(display);
	al_destroy_font(fontMain);
	al_destroy_font(fontExtra);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_bitmap(titleExe);
	al_destroy_bitmap(borda);
	al_destroy_bitmap(exit);
	al_destroy_bitmap(window);
	al_destroy_bitmap(minimize);
	return 0;
}