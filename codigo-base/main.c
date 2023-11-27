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

/*void vectorclicked(int mouseX, int vectorX, int mouseY, int vectorY, bool ativo) {
	if (mouseX >= vectorX && mouseX <= vectorX + 41 && mouseY >= vectorY && mouseY <= vectorY + 43) {
		vectorX = mouseX;
		vectorY = mouseY;
		ativo = true;
	}
}*/



int main() {
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();

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

	//surgery
	srand(time(NULL));
	ALLEGRO_BITMAP* backgroundSurgery = NULL;
	for (int i = 0; i < 8; i++) {
		vectors[i].bitmap = al_load_bitmap("assets/vetoritem.png"); 
		vectors[i].x = rand() % 350 + 140;
		vectors[i].y = rand() % 230 + 70;
		vectors[i].buffer = 0;
	}
	dna.bitmap = al_load_bitmap("assets/vetores.png");
	surgeryMouse.idle = al_load_bitmap("assets/surgerymouse.png");
	doctor.bitmap = al_load_bitmap("assets/docCam.png");
	doctor.frame1 = al_load_bitmap("assets/doc1.png");
	doctor.frame2 = al_load_bitmap("assets/doc2.png");
	doctor.frame3 = al_load_bitmap("assets/doc3.png");
	doctor.buffer = 0;
	backgroundSurgery = al_load_bitmap("assets/examroom.png");
	assert(backgroundSurgery != NULL);

	//patternity
	RectTemp rectL1 = { 20,30, rectL1.x + 120, rectL1.y + 70,20,30, 255,0,255};
	RectTemp rectL2 = { 20,100, rectL2.x + 120, rectL2.y + 70,20,100, 0,255,0 };
	RectTemp rectL3 = { 20,170, rectL3.x + 120, rectL3.y + 70,20,170,255,255,0 };
	RectTemp rectL4 = { 20,240, rectL4.x + 120, rectL4.y + 70,20,240,0,0,0 };
	RectTemp rectL5 = { 20,310, rectL5.x + 120, rectL5.y + 70,20,310,255,255,255 };
	RectTemp rectL6 = { 20,380, rectL6.x + 120, rectL6.y + 70,20,380,100,155,200 };
	RectTemp rects[6] = { rectL1,rectL2,rectL3,rectL4,rectL5,rectL6};
	RectRight rectR1 = { 180,150,rectR1.x + 120,rectR1.y + 70};
	RectRight rectR2 = { 180,250,rectR2.x + 120, rectR2.y + 70 };
	RectRight rectR3 = { rectR1.width + 20, rectR1.y, rectR3.x + 120, rectR3.y + 70 };
	RectRight rectR4 = { rectR1.width + 20, rectR2.y, rectR4.x + 120, rectR4.y + 70 };
	RectRight rectR5 = { rectR3.width + 20, rectR1.y, rectR5.x + 120, rectR5.y + 70 };
	RectRight rectR6 = { rectR3.width + 20, rectR2.y, rectR6.x + 120, rectR6.y + 70 };
	RectRight rectsR[6] = { rectR1, rectR2, rectR3, rectR4, rectR5, rectR6 };
	RectTemp* selected_rect = NULL;
	int index = -1;
	int RIndex[6] = {-1,-1,-1,-1,-1,-1};
	bool correct = false;
	

	//events
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	int x, y, h, w;
	al_get_clipping_rectangle(&x, &y, &w, &h);
	bool levels = false, surgery = false, dnaVectors = false, surgerySecond = false, patternity = false;
	float timing = 0;
	int total = 0;
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
		//mouse cursor
		if (al_set_mouse_cursor(display, cursor) && event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			mouse.x = event.mouse.x;
			mouse.y = event.mouse.y;
		}
		if ((mouse_state.buttons & 1) && (mouse.x >= 618 && mouse.x <= 637) && (mouse.y >= 3 && mouse.y <= 17)) {
			running = false;
		}
		//menu
		if (menu) {
			al_draw_bitmap(menuBg.bitmap, 0, 0, 0);
			al_draw_bitmap(iconGame.bitmap, iconGame.x, iconGame.y, 0);
			al_draw_tinted_bitmap(startButton.bitmap, al_map_rgba_f(1, 1, 1, startButton.a), startButton.x, startButton.y, 0);
			if (mouse_state.buttons & 1) {
				menu = false;
				intro = true;
				timing = 0;

				//free
				al_destroy_bitmap(iconGame.bitmap);
				al_destroy_bitmap(menuBg.bitmap);
				al_destroy_bitmap(startButton.bitmap);
			}
		}
		//intro
		if (intro) {
			dialougue = true;
		}
		if (dialougue) {
			al_draw_bitmap(textBox.bitmap, 40, 340, 0);
			if (textBox.buffer >= 1 && textBox.buffer < 3) {
				al_draw_text(textBox.font, al_map_rgb(255, 255, 255), 40 + 30, 340 + 40, 0, "Seja bem-vindo à bioHospital!");
			}
			else if (textBox.buffer == 3 && textBox.buffer < 4)
				al_draw_text(textBox.font, al_map_rgb(255, 255, 255), 40 + 30, 340 + 40, 0, "Selecione o minigame.");
			if (textBox.buffer >= 4) {
				levels = true;
				dialougue = false;
				intro = false;
				menu = false;
			}
		}
		//minigame select
		if (levels) {
			al_draw_bitmap(backgroundSurgery, 0, 0, 0);
			al_draw_bitmap(pinkpng.bitmap, 0, 0, 0);
			al_draw_text(fontMain, al_map_rgb(216, 232, 230), 100, 100, 0, "surgery game");
			al_draw_text(fontMain, al_map_rgb(216, 232, 230), 100, 200, 0, "patternity test game");
			if ((mouse_state.buttons & 1) && mouse.x >= 100 && mouse.x <= 200 && mouse.y >= 100 && mouse.y <= 200) {
				levels = false;
				surgery = true;
				timing = 0;
			}
			else if ((mouse_state.buttons & 1) && mouse.x >= 100 & mouse.x <= 300 && mouse.y > 200 && mouse.y <= 300) {
				levels = false;
				patternity = true;
			}
		}
		//minigame surgery
		if (surgery) {
			al_hide_mouse_cursor(display);
			al_draw_bitmap(backgroundSurgery, 0, 0, 0);
			if (dnaVectors) {
				al_draw_bitmap(blackpng.bitmap, 0, 0, 0);
			}
		}



		if (event.type == ALLEGRO_EVENT_TIMER) {
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
			if (intro) {
				if (dialougue) {
					if (mouse_state.buttons & 1)
						textBox.buffer += 1;
				}
			}
			if (surgery) {
				//contagem
				if (timing >= 0 && timing < 6 && !dnaVectors) {
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
					doctor.buffer += 1 / 10.0;
					al_draw_textf(fontExtra, al_map_rgb(216, 232, 230), 25, 25, 0, "%.0f", timing);
					al_draw_textf(fontExtra, al_map_rgb(216, 232, 230), 25, 55, 0, "%d", total);
					al_draw_bitmap(dna.bitmap, 102, 22, 0);
					al_set_clipping_rectangle(110, 51, 420, 281);
					for (int i = 0; i < 8; i++) {
						al_draw_bitmap(vectors[i].bitmap, vectors[i].x, vectors[i].y, 0);
					}
					al_set_clipping_rectangle(0, 0, width, height);
					al_draw_bitmap(doctor.bitmap, 35, 342, 0);
					if (fmod(timing, 2))
						al_draw_bitmap(doctor.frame1, 35 + 7, 342 + 21, 0);
					else if (fmod(timing, 3) < 2)
						al_draw_bitmap(doctor.frame2, 35 + 7, 342 + 21, 0);
					else
						al_draw_bitmap(doctor.frame3, 35 + 7, 342 + 21, 0);
					if (mouse_state.buttons & 1) {
						if (mouse.x >= vectors[0].x - 10 && mouse.x <= vectors[0].x + 41 && mouse.y >= vectors[0].y && mouse.y <= vectors[0].y + 43) {
							vectors[0].x = mouse.x - 15;
							vectors[0].y = mouse.y - 20;
							vectors[0].ativo = true;
						}
						else if (mouse.x >= vectors[1].x - 10 && mouse.x <= vectors[1].x + 41 && mouse.y >= vectors[1].y && mouse.y <= vectors[1].y + 43) {
							vectors[1].x = mouse.x - 15;
							vectors[1].y = mouse.y - 20;
							vectors[1].ativo = true;
						}
						else if (mouse.x >= vectors[2].x - 10 && mouse.x <= vectors[2].x + 41 && mouse.y >= vectors[2].y && mouse.y <= vectors[2].y + 43) {
							vectors[2].x = mouse.x - 15;
							vectors[2].y = mouse.y - 20;
							vectors[2].ativo = true;
						}
						else if (mouse.x >= vectors[3].x - 10 && mouse.x <= vectors[3].x + 41 && mouse.y >= vectors[3].y && mouse.y <= vectors[3].y + 43) {
							vectors[3].x = mouse.x - 15;
							vectors[3].y = mouse.y - 20;
							vectors[3].ativo = true;
						}
						else if (mouse.x >= vectors[4].x - 10 && mouse.x <= vectors[4].x + 41 && mouse.y >= vectors[4].y && mouse.y <= vectors[4].y + 43) {
							vectors[4].x = mouse.x - 15;
							vectors[4].y = mouse.y - 20;
							vectors[4].ativo = true;
						}
						else if (mouse.x >= vectors[5].x - 10 && mouse.x <= vectors[5].x + 41 && mouse.y >= vectors[5].y && mouse.y <= vectors[5].y + 43) {
							vectors[5].x = mouse.x - 15;
							vectors[5].y = mouse.y - 20;
							vectors[5].ativo = true;
						}
						else if (mouse.x >= vectors[6].x - 10 && mouse.x <= vectors[6].x + 41 && mouse.y >= vectors[6].y && mouse.y <= vectors[6].y + 43) {
							vectors[6].x = mouse.x - 15;
							vectors[6].y = mouse.y - 20;
							vectors[6].ativo = true;
						}
						else if (mouse.x >= vectors[7].x - 10 && mouse.x <= vectors[7].x + 41 && mouse.y >= vectors[7].y && mouse.y <= vectors[7].y + 43) {
							vectors[7].x = mouse.x - 15;
							vectors[7].y = mouse.y - 20;
							vectors[7].ativo = true;
						}
					}
					if (!(mouse_state.buttons & 1)) {
						int i = 0;
						if (vectors[i].ativo && vectors[i].y <= 480) {
							vectors[i].y += vectors[i].buffer;
							vectors[i].buffer += 0.5;
						}
						else if (vectors[i].ativo && vectors[i].y >= 480) {
							total += 100;
							vectors[i].ativo = false;
						}
						i = 1;
						if (vectors[i].ativo && vectors[i].y <= 480) {
							vectors[i].y += vectors[i].buffer;
							vectors[i].buffer += 0.5;
						}
						else if (vectors[i].ativo && vectors[i].y >= 480) {
							total += 100;
							vectors[i].ativo = false;
						}
						i = 2;
						if (vectors[i].ativo && vectors[i].y <= 480) {
							vectors[i].y += vectors[i].buffer;
							vectors[i].buffer += 0.5;
						}
						else if (vectors[i].ativo && vectors[i].y >= 480) {
							total += 100;
							vectors[i].ativo = false;
						}
						i = 3;
						if (vectors[i].ativo && vectors[i].y <= 480) {
							vectors[i].y += vectors[i].buffer;
							vectors[i].buffer += 0.5;
						}
						else if (vectors[i].ativo && vectors[i].y >= 480) {
							total += 100;
							vectors[i].ativo = false;
						}
						i = 4;
						if (vectors[i].ativo && vectors[i].y <= 480) {
							vectors[i].y += vectors[i].buffer;
							vectors[i].buffer += 0.5;
						}
						else if (vectors[i].ativo && vectors[i].y >= 480) {
							total += 100;
							vectors[i].ativo = false;
						}
						i = 5;
						if (vectors[i].ativo && vectors[i].y <= 480) {
							vectors[i].y += vectors[i].buffer;
							vectors[i].buffer += 0.5;
						}
						else if (vectors[i].ativo && vectors[i].y >= 480) {
							total += 100;
							vectors[i].ativo = false;
						}
						i = 6;
						if (vectors[i].ativo && vectors[i].y <= 480) {
							vectors[i].y += vectors[i].buffer;
							vectors[i].buffer += 0.5;
						}
						else if (vectors[i].ativo && vectors[i].y >= 480) {
							total += 100;
							vectors[i].ativo = false;
						}
						i = 7;
						if (vectors[i].ativo && vectors[i].y <= 480) {
							vectors[i].y += vectors[i].buffer;
							vectors[i].buffer += 0.5;
						}
						else if (vectors[i].ativo && vectors[i].y >= 480) {
							total += 100;
							vectors[i].ativo = false;
						}
					}
				}
			}
			if (patternity) {
				al_draw_bitmap(backgroundSurgery, 0, 0, 0);
				al_draw_bitmap(blackpng.bitmap, 0, 0, 0);

				//desenha os retangulos (sera mudado para as imagens a esquerda)
				for (int i = 0; i < 6; i++) {
					al_draw_filled_rectangle(rects[i].x, rects[i].y, rects[i].width, rects[i].height, al_map_rgb(rects[i].r, rects[i].g, rects[i].b));
					al_draw_rectangle(rectsR[i].x, rectsR[i].y, rectsR[i].width, rectsR[i].height, al_map_rgb(255, 255, 255), 1);
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
					selected_rect->x = mouse.x;
					selected_rect->y = mouse.y;
					selected_rect->width = selected_rect->x + 120;
					selected_rect->height = selected_rect->y + 70;

					//reseta o valor do Index do retangulo direito caso o retangulo selecionado seja movido
					for (int i = 0; i < 6; i++) {
						if (((selected_rect->x != rectsR[i].x) || (selected_rect->y != rectsR[i].y)) && RIndex[i] == index) {
							RIndex[i] = -1;
						}
					}
					
				}
				//botao de confirmar
				al_draw_text(fontExtra, al_map_rgb(235, 198, 134), 400, 400, 0, "Confirmar");


				//logica para ver se estao todos no local correto
				if ((mouse_state.buttons & 1) && ((mouse.x >= 400 && mouse.x <= 600) && (mouse.y >= 400 && mouse.y <= 450))) {
					if (((RIndex[0] == 0 || RIndex[0] == 2) && (RIndex[1] == 0 || RIndex[1] == 2)) && 
						((RIndex[2] == 3 || RIndex[2] == 5) && (RIndex[3] == 3 || RIndex[3] == 5)) &&
						((RIndex[4] == 4 || RIndex[4] == 1) && (RIndex[5] == 4 || RIndex[5] == 1))) {
						correct = true;
					}
					else {
						correct = false;
					}
					
				}

				//verifica se estao todos no local correto
				if (correct) {
					al_draw_text(fontExtra, al_map_rgb(235, 198, 134), 250, 400, 0, "Ganhou");
				}


				//debug
				/*for (int i = 0; i < 3; i++) {
					al_draw_textf(fontExtra, al_map_rgb(216, 232, 230), i * 40 + 40, 55, 0, "%d", correct[i]);
				}
				al_draw_textf(fontExtra, al_map_rgb(216, 232, 230), 300, 55, 0, "%d", index);
				al_draw_textf(fontExtra, al_map_rgb(216, 232, 230), 400, 55, 0, "%d", RIndex[0]);
				al_draw_textf(fontExtra, al_map_rgb(216, 232, 230), 500, 55, 0, "%d", RIndex[1]);
				//al_draw_textf(fontExtra, al_map_rgb(216, 232, 230), 200, 155, 0, "%d", LIndex[0]);
				//al_draw_textf(fontExtra, al_map_rgb(216, 232, 230), 500, 155, 0, "%d", LIndex[1]);
				*/
				
			} 

			al_draw_bitmap(borda, 0, 0, 0);
			al_draw_bitmap(title, 5, 2, 0);
			al_draw_bitmap(exit, 618, 2, 0);
			al_draw_bitmap(window, 598, 2, 0);
			al_draw_bitmap(minimize, 578, 2, 0);
			if (dnaVectors)
				timing -= 1/30.0;
			else
				timing += 1/30.0;
			if (dnaVectors){
				al_draw_bitmap(surgeryMouse.idle, mouse.x, mouse.y - 15, 0);
			}

			if (mouse_state.buttons & 1 && !dnaVectors)
				al_draw_bitmap(mouse.clicked, mouse.x, mouse.y, 0);
			al_flip_display();
		}

		//Coloca os retangulos nos lugares quando a pessoa soltar o botao esquerdo do mouse
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			if (patternity && selected_rect != NULL) {
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
		}

	}
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