#include <stdio.h>;
#include <stdlib.h>;
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "display.h"

int main() {
	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* font;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_MOUSE_STATE state;
	ALLEGRO_BITMAP* fundo = NULL;
	ALLEGRO_BITMAP* borda = NULL;
	ALLEGRO_BITMAP* barra = NULL;
	ALLEGRO_BITMAP* verde = NULL;
	ALLEGRO_BITMAP* mouseIcon = NULL;
	ALLEGRO_BITMAP* gameover = NULL;
	ALLEGRO_BITMAP* gamewin = NULL;

	al_init();

	display = al_create_display(640, 480);
	font = al_create_builtin_font();
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 20.0);

	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	//ALLEGRO_DISPLAY_MODE* al_get_display_mode(int index, ALLEGRO_DISPLAY_MODE * mode);

	fundo = al_load_bitmap("fundos/intro.png");
	borda = al_load_bitmap("borda.png");
	barra = al_load_bitmap("barra normal.png");
	verde = al_load_bitmap("barra verde.png");
	mouseIcon = al_load_bitmap("fundos/mouseIcon.png");
	gameover = al_load_bitmap("gameover.png");
	gamewin = al_load_bitmap("gamewin.png");
	assert(barra != NULL);
	assert(verde != NULL);
	assert(mouseIcon != NULL);
	assert(gameover != NULL);
	assert(gamewin != NULL);
	int x, y, h, w, timing = 0;
	al_get_clipping_rectangle(&x, &y, &w, &h);

	float mouseX = 0, mouseY = 0;
	float plus = 0, minus = 1;
	float verdeX = -400;
	bool minigame = true, over = false, win = false;

	int height = al_get_display_height(display);
	int width = al_get_display_width(display);

	ALLEGRO_MOUSE_CURSOR* cursor = al_create_mouse_cursor(mouseIcon, mouseX, mouseY);

	bool running = true;
	al_start_timer(timer);
	while (running) {
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)	running = false;

		//mouse cursor
		if (al_set_mouse_cursor(display, cursor) && event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			mouseX = event.mouse.x;
			mouseY = event.mouse.y;
		}
		//bitmap + mouse
		al_get_mouse_state(&state);
		if (minigame) {
			if (plus > 10) {
				plus = 0.1;
				minus = 1;
			}
			if (state.buttons & 1) {
				/* Primary (e.g. left) mouse button is held. */
				plus += 0.2;
				minus += 0.1;
				verdeX += plus;
			}
			if (state.buttons & 2) {
				/* Secondary (e.g. right) mouse button is held. */
			}
			if (state.buttons & 4) {
				/* Tertiary (e.g. middle) mouse button is held. */
			}
			else {
				verdeX -= minus;
			}
		}


		if (event.type == ALLEGRO_EVENT_TIMER) {
			//colocar um switch para cada minigame
			al_draw_bitmap(fundo, 0, 0, 0);
			al_draw_bitmap(borda, 0, 0, 0);
			al_draw_bitmap(barra, 0, 0, 0);

			//para sair do minigame e ganhar/perder
			if (verdeX < -500) {
				over = true;
				minigame = false;
			}
			if (verdeX > 100) {
				win = true;
				minigame = false;
			}
			//clipping start
			al_set_clipping_rectangle(100, 300, 400, 300);
			al_draw_bitmap(verde, verdeX, 0, 0);
			//clipping end
			al_set_clipping_rectangle(0, 0, width, height);
			if (win) {
				al_draw_bitmap(gamewin, 0, 0, 0);
			}
			if (over) {
				al_draw_bitmap(gameover, 0, 0, 0);
			}
			timing += 0.05;
			al_flip_display();
		}
	}
	al_destroy_display(display);
	al_destroy_font(font);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_bitmap(mouseIcon);
	al_destroy_bitmap(barra);
	al_destroy_bitmap(verde);
	al_destroy_bitmap(gameover);
	al_destroy_bitmap(gamewin);

	return 0;
} 