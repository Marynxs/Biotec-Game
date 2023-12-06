#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "essential.h"
#include "surgery.h"
#include "patternity.h"
#include "qwer.h"

int main() {
	al_init();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();

	al_set_new_display_flags(ALLEGRO_NOFRAME);
	ALLEGRO_DISPLAY* display = al_create_display(640, 480);
	al_set_window_title(display, "bioHospital");

	ALLEGRO_FONT* fontMain = al_load_ttf_font("fonts/retrogaming.ttf", 16, ALLEGRO_TTF_MONOCHROME);
	ALLEGRO_FONT* fontExtra = al_load_ttf_font("fonts/04b.ttf", 25, ALLEGRO_TTF_MONOCHROME);
	ALLEGRO_FONT* fontExtraBig = al_load_ttf_font("fonts/04b.ttf", 40, ALLEGRO_TTF_MONOCHROME);

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	ALLEGRO_KEYBOARD_STATE key_state;
	ALLEGRO_MOUSE_STATE mouse_state;

	//frame
	ALLEGRO_BITMAP* title = NULL;
	ALLEGRO_BITMAP* borda = NULL;
	ALLEGRO_BITMAP* exit = NULL;
	ALLEGRO_BITMAP* window = NULL;
	ALLEGRO_BITMAP* minimize = NULL;
	ALLEGRO_BITMAP* youSure = NULL;
	youSure = al_load_bitmap("assets/sure.png");
	title = al_load_bitmap("assets/title.png");
	borda = al_load_bitmap("assets/borda.png");
	exit = al_load_bitmap("assets/exit.png");
	window = al_load_bitmap("assets/window.png");
	minimize = al_load_bitmap("assets/minimize.png");
	assert(title != NULL);
	assert(borda != NULL);
	assert(exit != NULL);
	assert(window != NULL);
	assert(minimize != NULL);

	blackpng.bitmap = al_load_bitmap("assets/black.png");
	yellowpng.bitmap = al_load_bitmap("assets/yellow.png");
	pinkpng.bitmap = al_load_bitmap("assets/pink.png");
	bluepng.bitmap = al_load_bitmap("assets/blue.png");
	mouse.idle = al_load_bitmap("assets/mouse.png");
	mouse.clicked = al_load_bitmap("assets/mouseclicked.png");
	ALLEGRO_BITMAP* option = al_load_bitmap("assets/option.png");

	//titlescreen
	bool menu = true;
	iconGame.buffer = 0.5;
	iconGame.bitmap = al_load_bitmap("assets/iconGame.png");
	iconGame.x = 134;
	iconGame.y = 157;
	menuBg.bitmap = al_load_bitmap("assets/introbg.png");
	startButton.bitmap = al_load_bitmap("assets/start.png");
	startButton.x = 100;
	startButton.y = 425;
	startButton.a = 0;

	//intro & textBox
	bool intro = false, dialougue = false;
	textBox.x = 40;
	textBox.y = 340;
	textBox.bitmap = al_load_bitmap("assets/textbox.png");
	textBox.font = fontMain;
	textBox.buffer = 0;
	ALLEGRO_BITMAP* menuicon = al_load_bitmap("assets/menu.png");

	//surgery
	srand(time(NULL));
	ALLEGRO_BITMAP* backgroundSurgery = al_load_bitmap("assets/examroom.png");
	int xCongrats = 640;
	int xHand = 335;
	int xBuffer = 5;
	int yHand = 175;
	int yPoints = 265;
	int yBuffer = 5;
	int total = 0;
	float totalDNA = 0.0;

	//patternity
	ALLEGRO_BITMAP* paternityBg = al_load_bitmap("assets/paternitybg.png");
	ALLEGRO_BITMAP* pointsBox = al_load_bitmap("assets/pointsbox.png");
	//Usei como RectLeft pois não precisava criar outro mas esse é o padrão que fica em cima
	RectLeft rectPadrao1 = { al_load_bitmap("assets/padrao1.png"), 180, 100 };
	RectLeft rectPadrao2 = { al_load_bitmap("assets/padrao2.png"), 320, 100 };
	RectLeft rectPadrao3 = { al_load_bitmap("assets/padrao3.png"), 470, 100 };
	RectLeft rectPadroes[3] = { rectPadrao1, rectPadrao2, rectPadrao3 };
	//Esses são os retangulos da esquerda que se movem
	RectLeft rectL1 = { al_load_bitmap("assets/Esq1.png"),20,30,20,30,rectL1.x + 120, rectL1.y + 70 };
	RectLeft rectL2 = { al_load_bitmap("assets/Esq4.png"),20,100,20,100,rectL2.x + 120, rectL2.y + 70 };
	RectLeft rectL3 = { al_load_bitmap("assets/Esq2.png"),20,170,20,170,rectL3.x + 120, rectL3.y + 70 };
	RectLeft rectL4 = { al_load_bitmap("assets/Esq3.png"),20,240,20,240,rectL4.x + 120, rectL4.y + 70 };
	RectLeft rectL5 = { al_load_bitmap("assets/Esq6.png"),20,310,20,310,rectL5.x + 120, rectL5.y + 70 };
	RectLeft rectL6 = { al_load_bitmap("assets/Esq5.png"),20,380,20,380,rectL6.x + 120, rectL6.y + 70 };
	RectLeft rects[6] = { rectL1,rectL2,rectL3,rectL4,rectL5,rectL6 };
	//Esses são os retangulos da direita onde são colocados os rentagulos
	RectRight rectR1 = { 170,175,rectR1.x + 120,rectR1.y + 70 };
	RectRight rectR2 = { 170,265,rectR2.x + 120, rectR2.y + 70 };
	RectRight rectR3 = { rectR1.width + 30, rectR1.y + 10, rectR3.x + 120, rectR3.y + 70 };
	RectRight rectR4 = { rectR1.width + 30, rectR2.y + 10, rectR4.x + 120, rectR4.y + 70 };
	RectRight rectR5 = { rectR3.width + 30, rectR1.y, rectR5.x + 120, rectR5.y + 70 };
	RectRight rectR6 = { rectR3.width + 30, rectR2.y, rectR6.x + 120, rectR6.y + 70 };
	RectRight rectsR[6] = { rectR1, rectR2, rectR3, rectR4, rectR5, rectR6 };
	RectLeft* selected_rect = NULL;
	int index = -1;
	int RIndex[6] = { -1,-1,-1,-1,-1,-1 };
	bool confirm = false, correct[3] = { false, false, false }, confirmDraw = false;
	int points = 0;
	float patternPoints = 0.0;

	//rushQWER
	ALLEGRO_BITMAP* rushbg = al_load_bitmap("assets/rushbg.png");
	ALLEGRO_BITMAP* rushGameover = al_load_bitmap("assets/rushend.png");
	int rushPoints = 0;

	//events
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	int x, y, h, w;
	al_get_clipping_rectangle(&x, &y, &w, &h);
	bool levels = false, redraw = false, confirmExit = false, loading = false, sequence = false, congrat = false;
	bool minigames[3] = { false, false, false }, ends[3] = { false, false, false };
	bool surgery = false, dnaInstru = false, dnaPoints = false , dnaVectors = false;
	bool rush = false, countLose = false, rushOver = false;
	bool patternity = false;
	double timing = 0, countFinal = 0;
	int height = al_get_display_height(display);
	int width = al_get_display_width(display);
	int centerX = 320, centerY = 240;

	ALLEGRO_MOUSE_CURSOR* cursor = al_create_mouse_cursor(mouse.idle, mouse.x, mouse.y);

	bool running = true;
	al_start_timer(timer);
	while (running) {
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		al_get_mouse_state(&mouse_state);
		al_get_keyboard_state(&key_state);
		buttons[0].key = al_key_down(&key_state, ALLEGRO_KEY_Q);
		buttons[1].key = al_key_down(&key_state, ALLEGRO_KEY_W);
		buttons[2].key = al_key_down(&key_state, ALLEGRO_KEY_E);
		buttons[3].key = al_key_down(&key_state, ALLEGRO_KEY_R);
		if (event.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
		}
		//mouse cursor
		if (al_set_mouse_cursor(display, cursor) && event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			mouse.x = event.mouse.x;
			mouse.y = event.mouse.y;
		}
		if ((mouse_state.buttons & 1) && (mouse.x >= 618 && mouse.x <= 637) && (mouse.y >= 3 && mouse.y <= 17)) {
			confirmExit = true;
		}
		if (confirmExit) {
			//sim
			if ((mouse_state.buttons & 1) && (mouse.x >= 273 && mouse.x <= 314) && (mouse.y >= 245 && mouse.y <= 265))
				running = false;
			//nao
			if ((mouse_state.buttons & 1) && (mouse.x >= 327 && mouse.x <= 368) && (mouse.y >= 245 && mouse.y <= 265))
				confirmExit = false;
		}
		//menu
		if (menu) {
			al_draw_bitmap(menuBg.bitmap, 0, 0, 0);
			al_draw_bitmap(iconGame.bitmap, iconGame.x, iconGame.y, 0);
			al_draw_tinted_bitmap(startButton.bitmap, al_map_rgba_f(1, 1, 1, startButton.a), startButton.x, startButton.y, 0);
			if (mouse_state.buttons & 1) {
				dialougue = true;
				timing = 0;
			}
		}
		//intro
		if (dialougue) {
			al_draw_bitmap(textBox.bitmap, 40, 340, 0);
			if (countFinal < 1) {
				al_draw_text(textBox.font, al_map_rgb(255, 255, 255), 40 + 30, 340 + 40, 0, "Seja bem-vindo à bioHospital!");
			}
			else if (countFinal >= 1)
				al_draw_text(textBox.font, al_map_rgb(255, 255, 255), 40 + 30, 340 + 40, 0, "Selecione o minigame.");
			if (countFinal >= 2) {
				levels = true;
				dialougue = false;
				intro = false;
				menu = false;

				//free
				al_destroy_bitmap(textBox.bitmap);
				al_destroy_bitmap(iconGame.bitmap);
				al_destroy_bitmap(menuBg.bitmap);
				al_destroy_bitmap(startButton.bitmap);
			}
		}
		//minigame select
		if (levels) {
			al_draw_bitmap(backgroundSurgery, 0, 0, 0);
			al_draw_bitmap(bluepng.bitmap, 0, 0, 0);
			al_draw_bitmap(menuicon, 138, 59, 0);
			al_draw_bitmap(option, 115.5, 434, 0);
			if ((mouse_state.buttons & 1) && mouse.x >= 138 && mouse.x <= 502 && mouse.y >= 59 && mouse.y <= 177) {
				levels = false;
				loading = true;
				minigames[0] = true;
			}
			if ((mouse_state.buttons & 1) && mouse.x >= 138 && mouse.x <= 502 && mouse.y >= 180 && mouse.y <= 298) {
				loading = true;
				minigames[1] = true;
				levels = false;
			}
			if ((mouse_state.buttons & 1) && mouse.x >= 138 && mouse.x <= 502 && mouse.y >= 306 && mouse.y <= 424) {
				loading = true;
				minigames[2] = true;
				levels = false;
			}
			if ((mouse_state.buttons & 1) && mouse.x >= 115 && mouse.x <= 524 && mouse.y >= 434 && mouse.y <= 455) {
				levels = false;
				loading = true;
				minigames[0] = true;
				sequence = true;
			}
		}
		//loading bitmaps
		if (loading) {
			if (minigames[0]) {
				for (int i = 0; i < 8; i++) {
					vectors[i].bitmap = al_load_bitmap("assets/vetoritem.png");
					vectors[i].x = rand() % 350 + 140;
					vectors[i].y = rand() % 230 + 70;
					vectors[i].buffer = 0;
				}
				dna.buffer = -0.1;
				dna.a = 1;
				dna.bitmap = al_load_bitmap("assets/vetores.png");
				surgeryMouse.idle = al_load_bitmap("assets/surgerymouse.png");
				doctor.bitmap = al_load_bitmap("assets/docCam.png");
				doctor.frame1 = al_load_bitmap("assets/doc1.png");
				dnaGameover.bitmap = al_load_bitmap("assets/dnaend.png");
				instru.bitmap = al_load_bitmap("assets/dnainstru.png");
				instru.frame1 = al_load_bitmap("assets/instruhand.png");
				timing = 0;
				surgery = true;
				dnaInstru = true;
				loading = false;
			}
			if (minigames[1]) {
				timing = 0;
				patternity = true;
				loading = false; 
			}
			if (minigames[2]) {
				for (int i = 0; i < 4; i++) {
					buttons[i].points = 0;
					buttons[i].screen = false;
				}
				buttons[0].idle = al_load_bitmap("assets/qicon.png");
				buttons[1].idle = al_load_bitmap("assets/wicon.png");
				buttons[2].idle = al_load_bitmap("assets/eicon.png");
				buttons[3].idle = al_load_bitmap("assets/ricon.png");
				buttons[0].pressed = al_load_bitmap("assets/qiconpressed.png");
				buttons[1].pressed = al_load_bitmap("assets/wiconpressed.png");
				buttons[2].pressed = al_load_bitmap("assets/eiconpressed.png");
				buttons[3].pressed = al_load_bitmap("assets/riconpressed.png");
				timing = 40;
				rush = true;
				loading = false;
			}
		}
		//minigame surgery
		if (surgery) {
			if(!dnaInstru)
				al_hide_mouse_cursor(display);
			al_draw_bitmap(backgroundSurgery, 0, 0, 0);
			if (dnaInstru) {
				al_draw_bitmap(instru.bitmap, 0, 0, 0);
				al_draw_bitmap(instru.frame1, xHand, yHand, 0);
				if (mouse_state.buttons & 1 && mouse.x >= 204 && mouse.x <= 450 && mouse.y >= 373 && mouse.y <= 433) {
					dnaInstru = false;
					timing = 0;
				}
			}
			else if (dnaPoints) {
				al_draw_tinted_bitmap(bluepng.bitmap, al_map_rgba_f(1, 1, 1, dna.a), 0, 0, 0);
				al_draw_bitmap(blackpng.bitmap, 0, 0, 0);
				al_draw_text(fontExtra, al_map_rgb(101, 219, 115), 18, yPoints, 0, "+100");
			}
			else {
				yPoints = 265;
				dna.buffer = 0;
				dna.a = 1;
				al_draw_bitmap(blackpng.bitmap, 0, 0, 0);
			}
			if(ends[0])
				al_show_mouse_cursor(display);
		}
		//minigame paternity
		if (patternity) {
			//Coloca os retangulos nos lugares quando a pessoa soltar o botao esquerdo do mouse
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (selected_rect != NULL) {
					for (int i = 0; i < 6; i++) {
						if ((isInsideRectR(mouse.x, mouse.y, rectsR[i]))) {
							selected_rect->x = rectsR[i].x;
							selected_rect->y = rectsR[i].y;
							selected_rect->width = selected_rect->x + 120;
							selected_rect->height = selected_rect->y + 70;

							for (int j = 0; j < 6; j++) {
								if ((j != index) && selected_rect->x == rects[j].x && selected_rect->y == rects[j].y) {
									selected_rect->x = selected_rect->xInicial;
									selected_rect->y = selected_rect->yInicial;
									selected_rect->width = selected_rect->x + 120;
									selected_rect->height = selected_rect->y + 70;
									break;
								}
								else {
									if (RIndex[i] == -1) {
										RIndex[i] = index;
									}
								}
							}
							break;
						}
						else {
							selected_rect->x = selected_rect->xInicial;
							selected_rect->y = selected_rect->yInicial;
							selected_rect->width = selected_rect->x + 120;
							selected_rect->height = selected_rect->y + 70;
						}
					}

				}
				//logica para ver se estao todos no local correto
				if (((mouse.x >= 250 && mouse.x <= 600) && (mouse.y >= 415 && mouse.y <= 460))) {
					points = 0;
					if ((RIndex[0] == 0 || RIndex[0] == 2) && (RIndex[1] == 0 || RIndex[1] == 2))//0-2 
						correct[0] = true;
					if ((RIndex[2] == 3 || RIndex[2] == 5) && (RIndex[3] == 3 || RIndex[3] == 5))//3-5
						correct[1] = true;
					if ((RIndex[4] == 4 || RIndex[4] == 1) && (RIndex[5] == 4 || RIndex[5] == 1))//4-1
						correct[2] = true;
					confirm = true;
				}
				//verifica se estao todos no local correto
				if (confirm) {
					for (int i = 0; i < 3; i++)
						if (correct[i])
							points += 1;
					ends[1] = true;
					confirm = false;
					countFinal = 0;
				}
			}
		}
		//minigame qwer rush
		if (rush) {
			double keys[4] = { 2, 5, 3, 4 };
			if (!ends[2]) {
				al_draw_bitmap(rushbg, 0, 0, 0);
				al_draw_bitmap(blackpng.bitmap, 0, 0, 0);
				if (!buttons[0].screen) { //640 - qbttnwidth - 25 || 480 - qbttnheight - 25
					buttons[0].x = rand() % (640 - 160 - 50) + 30;
					buttons[0].y = rand() % (480 - 236 - 75) + 25;
				}
				if (!buttons[1].screen) {
					buttons[1].x = rand() % (640 - 178 - 50) + 25;
					buttons[1].y = rand() % (480 - 189 - 75) + 25;
				}
				if (!buttons[2].screen) {
					buttons[2].x = rand() % (640 - 245 - 50) + 35;
					buttons[2].y = rand() % (480 - 175 - 75) + 25;
				}
				if (!buttons[3].screen) {
					buttons[3].x = rand() % (640 - 348 - 50) + 45;
					buttons[3].y = rand() % (480 - 140 - 75) + 25;
				}

				for (int i = 0; i < 4; i++) {
					if (buttons[i].buffer >= keys[i]) {
						buttons[i].screen = true;
						buttons[i].buffer = 0;
					}
					if (buttons[i].key) {
						buttons[i].points += rand() % 25 + 1;
					}
					if (buttons[i].points >= 100) {
						buttons[i].screen = false;
						rushPoints += 50;
					}
				}
			}
			if (buttons[0].screen && buttons[1].screen && buttons[2].screen && buttons[3].screen)
				countLose = true;
			else
				countLose = false;
		}
		//redraw
		if (redraw) {
			if (loading) {
				al_clear_to_color(al_map_rgb(33, 30, 51));
				al_draw_text(fontMain, al_map_rgb(216, 232, 230), 50, 455, 0, "loading...");
			}
			if (menu) {
				//animacao do icon
				if (iconGame.y <= 152)
					iconGame.buffer = 0.5;
				else if (iconGame.y >= 165)
					iconGame.buffer = -0.5;
				iconGame.y += iconGame.buffer;
				//animacao do start
				if (startButton.a >= 1)
					startButton.buffer = -0.1;
				else if (startButton.a <= 0.5)
					startButton.buffer = 0.1;
				startButton.a += startButton.buffer;
			}
			if (surgery) {
				//contagem
				if (dnaInstru) {
					if (xHand >= 360)
						xBuffer = -5/3;
					else if (xHand <= 335)
						xBuffer = 5/3;
					xHand += xBuffer;
				}
				if (timing >= 0 && timing < 6 && !dnaVectors && !dnaInstru) {
					al_draw_bitmap(blackpng.bitmap, 0, 0, 0);
					if (timing >= 0 && timing <= 0.5)
						al_draw_text(fontExtraBig, al_map_rgb(112, 157, 207), centerX - 80, centerY - 30, 0, "Ready?");
					else if (timing >= 0.5 && timing < 1.5)
						al_draw_text(fontExtraBig, al_map_rgb(235, 198, 134), centerX - 10, centerY - 30, 0, "3");
					else if (timing >= 1.5 && timing < 2.5)
						al_draw_text(fontExtraBig, al_map_rgb(235, 198, 134), centerX - 10, centerY - 30, 0, "2");
					else if (timing >= 2.5 && timing < 3.5)
						al_draw_text(fontExtraBig, al_map_rgb(235, 198, 134), centerX - 10, centerY - 30, 0, "1");
					else if (timing >= 3.5 && timing < 4.5) {
						al_draw_text(fontExtraBig, al_map_rgb(235, 198, 134), centerX - 40, centerY - 30, 0, "Go!");
					}
					else if (timing > 5) {
						timing = 30;
						dnaVectors = true;
					}
				}
				//vetor minigame
				else if (dnaVectors) {
					if (dnaPoints) {
						dna.buffer = -0.1;
						if (dna.a <= 0) {
							dnaPoints = false;
						}
						yPoints -= yBuffer;
						dna.a += dna.buffer;
					}
					al_draw_textf(fontExtra, al_map_rgb(216, 232, 230), 25, 25, 0, "%.0f", timing);
					al_draw_textf(fontExtra, al_map_rgb(112, 157, 207), 25, 55, 0, "%d", total);
					al_draw_bitmap(dna.bitmap, 102, 22, 0);
					al_set_clipping_rectangle(110, 51, 420, 281);
					for (int i = 0; i < 8; i++) {
						al_draw_bitmap(vectors[i].bitmap, vectors[i].x, vectors[i].y, 0);
					}
					al_set_clipping_rectangle(0, 0, width, height);
					al_draw_bitmap(doctor.bitmap, 35, 342, 0);
					al_draw_bitmap(doctor.frame1, 35 + 7, 342 + 21, 0);
					if (mouse_state.buttons & 1) {
						for (int i = 0; i < 8; i++) {
							if (mouse.x >= vectors[i].x - 10 && mouse.x <= vectors[i].x + 41 && mouse.y >= vectors[i].y && mouse.y <= vectors[i].y + 43) {
								vectors[i].x = mouse.x - 15;
								vectors[i].y = mouse.y - 20;
								vectors[i].ativo = true;
							}
						}
					}
					for (int i = 0; i < 8; i++) {
						if (vectors[i].ativo && vectors[i].y <= 480) {
							vectors[i].y += vectors[i].buffer;
							vectors[i].buffer += 0.3;
						}
						else if (vectors[i].ativo && vectors[i].y >= 480) {
							total += 100;
							vectors[i].ativo = false;
							dnaPoints = true;
						}
					}
					if (vectors[0].y > 480 && vectors[1].y > 480 && vectors[2].y > 480 && vectors[3].y > 480 && vectors[4].y > 480 && vectors[5].y > 480 && vectors[6].y > 480 && vectors[7].y > 480 || timing <= 0) {
						total += 100;
						ends[0] = true;
						dnaVectors = false;
					}
				}
				if (ends[0]) {
					totalDNA = (total * timing) / 10.0;
					al_draw_bitmap(dnaGameover.bitmap, 0, 0, 0);
					al_draw_textf(fontMain, al_map_rgb(216, 232, 230), 80, 135, 0, "%.0f", timing);
					al_draw_textf(fontExtra, al_map_rgb(112, 157, 207), 80, 255, 0, "%.0f", totalDNA);		
					if (!sequence) {
						al_draw_text(fontMain, al_map_rgb(33, 30, 51), 80, 365, 0, "RMB to leave");
						if (mouse_state.buttons & 1) {
							ends[0] = false;
							minigames[0] = false;
							surgery = false;
							running = false;
						}
					}
					else {
						al_draw_text(fontMain, al_map_rgb(33, 30, 51), 80, 365, 0, "Click to go to the next game");
						if (mouse_state.buttons & 1) {
							ends[0] = false;
							minigames[0] = false;
							surgery = false;
							loading = true;
							minigames[1] = true;
						}
					}
					if (!minigames[0] && !surgery) {
						for (int i = 0; i < 8; i++) {
							al_destroy_bitmap(vectors[i].bitmap);
						}
						al_destroy_bitmap(dna.bitmap);
						al_destroy_bitmap(surgeryMouse.idle);
						al_destroy_bitmap(doctor.bitmap);
						al_destroy_bitmap(doctor.frame1);
						al_destroy_bitmap(dnaGameover.bitmap);
						al_destroy_bitmap(instru.bitmap);
						al_destroy_bitmap(instru.frame1);
					}
				}
			}
			if (patternity) {
				al_draw_bitmap(paternityBg, 0, 0, 0);
				for (int j = 0; j < 6; j++) {
					al_draw_bitmap(rects[j].bitmap, rects[j].x, rects[j].y, 1);
				}
				for (int k = 0; k < 6; k++) {
					al_draw_rectangle(rectsR[k].x, rectsR[k].y, rectsR[k].width, rectsR[k].height, al_map_rgb(255, 255, 255), 1);
				}
				//define qual retangulo esta sendo selecionado
				for (int i = 0; i < 6; i++) {
					if (!(mouse_state.buttons & 1)) {
						if (isInsideRect(mouse.x, mouse.y, rects[i])) {
							selected_rect = &rects[i];
							index = i;
							break;
						}
						else {
							selected_rect = NULL;
						}
					}
				}
				//move o retangulo selecionado a partir do clique esquerdo em cima dele
				if (mouse_state.buttons & 1 && selected_rect != NULL && (mouse.y >= 0 && (mouse.y + selected_rect->height - selected_rect->y) <= height) && (mouse.x >= 0 && (mouse.x + selected_rect->width - selected_rect->x) <= width)) {
					selected_rect->x = mouse.x - 50;
					selected_rect->y = mouse.y - 50;
					selected_rect->width = selected_rect->x + 120;
					selected_rect->height = selected_rect->y + 70;

					//reseta o valor do Index do retangulo direito caso o retangulo selecionado seja movido
					for (int i = 0; i < 6; i++) {
						if (((selected_rect->x != rectsR[i].x) || (selected_rect->y != rectsR[i].y)) && RIndex[i] == index) {
							RIndex[i] = -1;
						}
					}
				}
				
				if (ends[1]) {
					al_draw_bitmap(pointsBox, 30, 50, 0);
					al_draw_textf(fontExtra, al_map_rgb(33, 30, 51), 65, 150, 0, "%.0f", timing);
					al_draw_textf(fontExtra, al_map_rgb(33, 30, 51), 65, 235, 0, "%d/3", points);
					patternPoints = (1000.0 - timing) * points;
					if (patternPoints > 0)
						al_draw_textf(fontExtra, al_map_rgb(33, 30, 51), 55, 265, 0, "%.0f", patternPoints);
					else {
						al_draw_textf(fontExtra, al_map_rgb(33, 30, 51), 55, 265, 0, "%d", points);
						patternPoints = points;
					}

					if (countFinal >= 3) {
						if (!sequence) {
							al_draw_textf(fontMain, al_map_rgb(33, 30, 51), 38, 290, 0, "RMB to leave");
							if (mouse_state.buttons & 1) {
								ends[1] = false;
								minigames[1] = false;
								patternity = false;
								running = false;
							}
						}
						else {
							al_draw_textf(fontMain, al_map_rgb(33, 30, 51), 38, 290, 0, "RMB to next");
							al_draw_textf(fontMain, al_map_rgb(33, 30, 51), 38, 315, 0, "minigame");
							if (mouse_state.buttons & 1) {
								ends[1] = false;
								minigames[1] = false;
								patternity = false;
								loading = true;
								minigames[2] = true;
							}
						}
						if (!minigames[1] && !patternity) {
							for (int i = 0; i < 3; i++) {
								al_destroy_bitmap(rectPadroes[i].bitmap);
							}
							for (int j = 0; j < 6; j++) {
								al_destroy_bitmap(rects[j].bitmap);
							}
						}
					}
				}
			}
			if (rush) {
				if (!ends[2]) {
					al_draw_textf(fontExtra, al_map_rgb(216, 232, 230), 25, 25, 0, "%.0f", timing);
					al_draw_textf(fontExtra, al_map_rgb(216, 232, 230), 25, 55, 0, "%d", rushPoints);
				}
				for (int i = 0; i < 4; i++) {
					if (buttons[i].screen) {
						if (buttons[i].key) {
							al_draw_bitmap(buttons[i].pressed, buttons[i].x, buttons[i].y, 0);
						}
						else {
							al_draw_bitmap(buttons[i].idle, buttons[i].x, buttons[i].y, 0);
						}
					}
					else {
						buttons[i].buffer += 1 / 30.0;
						buttons[i].points = 0;
						if (buttons[i].key) {
							rushPoints -= 10;
						}
					}
				}
				if (countLose) {
					al_draw_bitmap(blackpng.bitmap, 0, 0, 0);
					if (countFinal >= 0 && countFinal <= 1)
						al_draw_text(fontExtraBig, al_map_rgb(235, 198, 134), centerX - 10, centerY - 30, 0, "3");
					else if (countFinal > 1 && countFinal < 2)
						al_draw_text(fontExtraBig, al_map_rgb(235, 198, 134), centerX - 10, centerY - 30, 0, "2");
					else if (countFinal >= 2 && countFinal < 3)
						al_draw_text(fontExtraBig, al_map_rgb(235, 198, 134), centerX - 10, centerY - 30, 0, "1");
					else if (countFinal >= 3) {
						ends[2] = true;
					}
				}
				else 
					countFinal = 0;

				if (timing <= 0) {
					ends[2] = true;
				}
				if (ends[2]) {
					al_draw_bitmap(rushbg, 0, 0, 0);
					al_draw_bitmap(blackpng.bitmap, 0, 0, 0);
					al_draw_bitmap(rushGameover, 0, 0, 0);
					al_draw_textf(fontExtra, al_map_rgb(112, 157, 207), 80, 140, 0, "%d", rushPoints);
					if (sequence)
						al_draw_textf(fontExtra, al_map_rgb(112, 157, 207), 60, 200, 0, "Total:%.0f", patternPoints + rushPoints + totalDNA);
					if (mouse_state.buttons & 1) {
						ends[2] = false;
						minigames[2] = false;
						rush = false;
						running = false;
					}
					if (!minigames[2] && !rush) {
						for (int i = 0; i < 4; i++) {
							al_destroy_bitmap(buttons[i].idle);
							al_destroy_bitmap(buttons[i].pressed);
						}
						al_destroy_bitmap(rushbg);
						al_destroy_bitmap(rushGameover);
					}
				}
			}
			if (confirmExit) {
				al_draw_bitmap(blackpng.bitmap, 0, 0, 0);
				al_draw_bitmap(youSure, 252, 176, 0);
			}
			al_draw_bitmap(borda, 0, 0, 0);
			al_draw_bitmap(title, 5, 2, 0);
			al_draw_bitmap(exit, 618, 2, 0);
			al_draw_bitmap(window, 598, 2, 0);
			al_draw_bitmap(minimize, 578, 2, 0);
			if (!(ends[0] || ends[1] || ends[2])) {
				if (dnaVectors || rush)
					timing -= 1 / 30.0;
				else if (patternity && !confirmDraw)
					timing += 1 / 30.0;
				else if(!patternity)
					timing += 1 / 30.0;
			}				
			if (dialougue || countLose || ends[1])
				countFinal += 1 / 30.0;
			if (dnaVectors)
				al_draw_bitmap(surgeryMouse.idle, mouse.x, mouse.y - 15, 0);
			if (mouse_state.buttons & 1 && !dnaVectors)
				al_draw_bitmap(mouse.clicked, mouse.x, mouse.y, 0);
			al_flip_display();
			redraw = false;
		}
	}

	al_destroy_bitmap(option);
	al_destroy_bitmap(blackpng.bitmap);
	al_destroy_bitmap(yellowpng.bitmap);
	al_destroy_bitmap(bluepng.bitmap);
	al_destroy_bitmap(pinkpng.bitmap);
	al_destroy_bitmap(youSure);
	al_destroy_display(display);
	al_destroy_font(fontMain);
	al_destroy_font(fontExtra);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_bitmap(title);
	al_destroy_bitmap(borda);
	al_destroy_bitmap(exit);
	al_destroy_bitmap(window);
	al_destroy_bitmap(minimize);
	return 0;
}