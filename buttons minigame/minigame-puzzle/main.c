#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

int main() {
	srand(time(NULL));
	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* font;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_KEYBOARD_STATE key_state;
	ALLEGRO_BITMAP* fundo = NULL;
	ALLEGRO_BITMAP* QIcon = NULL;
	ALLEGRO_BITMAP* WIcon = NULL;
	ALLEGRO_BITMAP* EIcon = NULL;
	ALLEGRO_BITMAP* RIcon = NULL;
	ALLEGRO_BITMAP* borda = NULL;
	ALLEGRO_BITMAP* gameover = NULL;
	ALLEGRO_BITMAP* gamewin = NULL;
	ALLEGRO_BITMAP* mouseIcon = NULL;

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

	fundo = al_load_bitmap("fundos/exam room.png");
	borda = al_load_bitmap("borda.png");
	gameover = al_load_bitmap("gameover.png");
	gamewin = al_load_bitmap("gamewin.png");
	mouseIcon = al_load_bitmap("fundos/mouseIcon.png");
	QIcon = al_load_bitmap("qicon.png");
	WIcon = al_load_bitmap("wicon.png");
	EIcon = al_load_bitmap("eicon.png");
	RIcon = al_load_bitmap("ricon.png");
	assert(fundo != NULL);
	assert(borda != NULL);
	assert(gameover != NULL);
	assert(gamewin != NULL);
	assert(mouseIcon != NULL);
	assert(QIcon != NULL);
	assert(WIcon != NULL);
	assert(EIcon != NULL);
	assert(RIcon != NULL);
	
	int x, y, h, w;
	al_get_clipping_rectangle(&x, &y, &w, &h);

	int qRandomX, qRandomY;
	int wRandomX, wRandomY;
	int eRandomX, eRandomY;
	int rRandomX, rRandomY;
	float mouseX = 0, mouseY = 0;
	float qPoints = 0, wPoints = 0, ePoints = 0, rPoints = 0, timing = 0;
	bool qTela = false, wTela = false, eTela = false, rTela = false, over = false, win = false;

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

		al_get_keyboard_state(&key_state);
		if (al_key_down(&key_state, ALLEGRO_KEY_Q)) {
			qPoints += rand() % 10 + 1;
		}
		if (al_key_down(&key_state, ALLEGRO_KEY_W)) {
			wPoints += rand() % 10 + 1;
		}
		if (al_key_down(&key_state, ALLEGRO_KEY_E)) {
			ePoints += rand() % 10 + 1;
			//al_flip_display();
		}
		if (al_key_down(&key_state, ALLEGRO_KEY_R)) {
			rPoints += rand() % 10 + 1;
			//al_flip_display();
		}
		//gameover/gamewin
		if (qTela && wTela && eTela && rTela)
			over = true;
		else if (timing >= 40)
			win = true;

		//qwer
		if (!qTela) {
			qRandomX = rand() % 600 + 20;
			qRandomY = rand() % 440 + 20;
		}
		if (timing >= 3 && timing < 15 || timing >= 15) {
			qTela = true;
		}
		if (qPoints > 100 && timing < 15 || qPoints > 200)
			qTela = false;

		if (!wTela) {
			wRandomX = rand() % 600 + 20;
			wRandomY = rand() % 440 + 20;
		}
		if (timing >= 6 && timing < 18 || timing >= 18) {
			wTela = true;
		}
		if (wPoints > 100 && timing < 18 || wPoints > 200)
			wTela = false;

		if(!eTela){
			eRandomX = rand() % 600 + 20;
			eRandomY = rand() % 440 + 20;
		}
		if (timing >= 9 && timing < 21 || timing >= 21) {
			eTela = true;
		}
		if (ePoints > 100 && timing < 21 || ePoints > 200)
			eTela = false;

		if(!rTela){
			rRandomX = rand() % 600 + 20;
			rRandomY = rand() % 440 + 20;
		}
		if (timing >= 12 && timing < 24 || timing >= 24) {
			rTela = true;
		}
		if (rPoints > 100 && timing < 24 || rPoints > 200 )
			rTela = false;

		if (event.type == ALLEGRO_EVENT_TIMER) {
			//colocar um switch para cada minigame
			al_draw_bitmap(fundo, 0, 0, 0);
			al_draw_bitmap(borda, 0, 0, 0);
			//al_draw_text(font, al_map_rgb(255, 255, 255), 50, 50, 0, "hello world");
			if (qTela)
				al_draw_bitmap(QIcon, qRandomX, qRandomY, 0);
			if (wTela)
				al_draw_bitmap(WIcon, wRandomX, wRandomY, 0);
			if (eTela)
				al_draw_bitmap(EIcon, eRandomX, eRandomY, 0);
			if (rTela)
				al_draw_bitmap(RIcon, rRandomX, rRandomY, 0);

			if (over)
				al_draw_bitmap(gameover, 0, 0, 0);
			if (win)
				al_draw_bitmap(gamewin, 0, 0, 0);

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
	al_destroy_bitmap(fundo);
	al_destroy_bitmap(borda);
	al_destroy_bitmap(gameover);
	al_destroy_bitmap(gamewin);
	al_destroy_bitmap(QIcon);
	al_destroy_bitmap(WIcon);
	al_destroy_bitmap(EIcon);
	al_destroy_bitmap(RIcon);

	return 0;
}