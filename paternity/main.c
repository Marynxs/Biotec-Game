#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int xInicial;
    int yInicial;
    int r;
    int g;
    int b;
} Rect;

bool isInsideRect(int x, int y, Rect rect) {
    return (x >= rect.x && x <= rect.width &&
        y >= rect.y && y <= rect.height);
}

bool isInPosition(Rect rect, Rect target) {
    return (rect.x >= target.x && rect.y >= target.y);
}

int main()
{
    al_init();
    al_install_mouse();
    al_init_primitives_addon();

    ALLEGRO_DISPLAY* display = al_create_display(640, 480);
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 20.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_BITMAP* gamewin = NULL;



    if (!display)
        printf("Erro em mostrar na tela");
    if (!al_init())
        printf("Erro ao iniciar");
    if (!al_install_mouse())
        printf("Erro ao installar o mouse");

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    gamewin = al_load_bitmap("gamewin.png");

    bool done = false;
    int win = 0;
    int height = al_get_display_height(display);
    int width = al_get_display_width(display);
    Rect rect1 = { 0, 0, rect1.x + 200, rect1.y + 100,  0,0,  255,0,0 };
    Rect rect2 = { 0, 100, rect2.x + 200, rect2.y + 100,  0,100,  0,255,0 };
    Rect rect3 = { 0, 200, rect3.x + 200, rect3.y + 100,  0,200,  0,0,255 };
    Rect rect4 = { 0, 300, rect4.x + 200, rect4.y + 100,  0,300,  255,255,255 };
    Rect rect5 = { 210,100,rect5.x + 200,rect5.y + 100,210,100,255,255,0 };
    Rect rect6 = { 210,210,rect6.x + 200,rect6.y + 100,210,210,255,255,0 };
    Rect retan[4] = { rect1,rect2,rect3,rect4 };
    Rect* selected_rect = NULL;
    bool jafoi1 = false, jafoi2 = false;

    al_start_timer(timer);
    ALLEGRO_EVENT event;
    ALLEGRO_MOUSE_STATE state;

    while (!done) {
        al_wait_for_event(queue, &event);

        switch (event.type) {

        case ALLEGRO_EVENT_TIMER:
            al_clear_to_color(al_map_rgb(0, 0, 0));
            for (int i = 0; i < 4; i++) {
                al_draw_filled_rectangle(retan[i].x, retan[i].y, retan[i].width, retan[i].height, al_map_rgb(retan[i].r, retan[i].g, retan[i].b));
            }
            al_draw_rectangle(rect5.x, rect5.y, rect5.width, rect5.height, al_map_rgb(255, 255, 255), 1);
            al_draw_rectangle(rect6.x, rect6.y, rect6.width, rect6.height, al_map_rgb(255, 255, 255), 1);

            al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", rect1.x, rect1.y);
            if (win >= 2) {
                al_draw_text(font, al_map_rgb(255, 255, 255), 200, 200, 0, "Venceu");
                al_draw_bitmap(gamewin, 0, 0, 0);
            }

            al_flip_display();
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;

        case ALLEGRO_EVENT_MOUSE_AXES:
            al_get_mouse_state(&state);
            for (int i = 0; i < 4; i++) {

                if (!(state.buttons & 1)) {
                    if (isInsideRect(event.mouse.x, event.mouse.y, retan[i])) {
                        selected_rect = &retan[i];
                        break;
                    }
                    else {
                        selected_rect = NULL;
                    }
                }


            }

            if (state.buttons & 1 && selected_rect != NULL && (event.mouse.y >= 0 && (event.mouse.y + selected_rect->height - selected_rect->y) <= height) && (event.mouse.x >= 0 && (event.mouse.x + selected_rect->width - selected_rect->x) <= width)) {
                selected_rect->x = event.mouse.x;
                selected_rect->y = event.mouse.y;
                selected_rect->width = selected_rect->x + 200;
                selected_rect->height = selected_rect->y + 100;
            }



            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            if (selected_rect != NULL) {
                if (isInsideRect(event.mouse.x, event.mouse.y, rect5)) {
                    selected_rect->x = rect5.x;
                    selected_rect->y = rect5.y;
                    selected_rect->width = selected_rect->x + 200;
                    selected_rect->height = selected_rect->y + 100;

                }
                else if (isInsideRect(event.mouse.x, event.mouse.y, rect6)) {
                    selected_rect->x = rect6.x;
                    selected_rect->y = rect6.y;
                    selected_rect->width = selected_rect->x + 200;
                    selected_rect->height = selected_rect->y + 100;
                }
                else {
                    selected_rect->x = selected_rect->xInicial;
                    selected_rect->y = selected_rect->yInicial;
                    selected_rect->width = selected_rect->x + 200;
                    selected_rect->height = selected_rect->y + 100;
                }
                if (jafoi1 == false && (selected_rect == &retan[0]) && ((selected_rect->x == rect5.x && selected_rect->y == rect5.y) || (selected_rect->x == rect6.x && selected_rect->y == rect6.y))) {
                    win++;
                    jafoi1 = true;
                }
                if (jafoi2 == false && (selected_rect == &retan[2]) && ((selected_rect->x == rect5.x && selected_rect->y == rect5.y) || (selected_rect->x == rect6.x && selected_rect->y == rect6.y))) {
                    win++;
                    jafoi2 = true;
                }

            }

            break;
        }



    }

    al_destroy_display(display);
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_bitmap(gamewin);
    al_destroy_event_queue(queue);
    al_uninstall_mouse();

    return 0;
}