#include <allegro5/allegro.h>

typedef struct {
    ALLEGRO_BITMAP* bitmap;
    int x;
    int y;
    int width;
    int height;
    int xInicial;
    int yInicial;
} RectLeft;

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int xInicial;
    int yInicial;
    int r, g, b;
} RectTemp;

typedef struct {
    int x;
    int y;
    int width;
    int height;
} RectRight;


bool isInsideRect(int x, int y, RectTemp rect) {
    return ((x >= rect.x && x <= rect.width) &&
        (y >= rect.y && y <= rect.height));
}

bool isInsideRectR(int x, int y, RectRight rect) {
    return ((x >= rect.x && x <= rect.width) &&
        (y >= rect.y && y <= rect.height));
}

bool isInPosition(RectTemp* selected_rect, RectRight target) {
    return (selected_rect->x == target.x && selected_rect->y == target.y);

}

bool iscorrect(RectTemp selected_rect, RectRight target) {
    return (selected_rect.x == target.x && selected_rect.y == target.y);
}

