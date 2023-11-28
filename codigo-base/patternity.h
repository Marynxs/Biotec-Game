#include <allegro5/allegro.h>

typedef struct {
    ALLEGRO_BITMAP* bitmap;
    int x;
    int y;
    int xInicial;
    int yInicial;
    int width;
    int height;
} RectLeft;

typedef struct {
    int x;
    int y;
    int width;
    int height;
} RectRight;


bool isInsideRect(int x, int y, RectLeft rect) {
    return ((x >= rect.x && x <= rect.width) &&
        (y >= rect.y && y <= rect.height));
}

bool isInsideRectR(int x, int y, RectRight rect) {
    return ((x >= rect.x && x <= rect.width) &&
        (y >= rect.y && y <= rect.height));
}

bool isInPosition(RectLeft* selected_rect, RectRight target) {
    return (selected_rect->x == target.x && selected_rect->y == target.y);

}

bool iscorrect(RectLeft selected_rect, RectRight target) {
    return (selected_rect.x == target.x && selected_rect.y == target.y);
}

