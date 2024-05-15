#include "../inc/raycast.h"

int main(void) {
    t_player player;

    int pixel_count = -1;
    while (++pixel_count < WINDOW_W)
    {
        raycast(NULL, &player);
    }
    
}