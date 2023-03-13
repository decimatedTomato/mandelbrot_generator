#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "handle_opengl.c"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480

// USER DEFINITIONS
#define FRAGMENT_FILEPATH "res/shaders/mandelbrot.glsl"
#define VERTEX_FILEPATH "res/shaders/vertex.glsl"
#define THRESHOLD 4.0
#define MAX_ITERATIONS 50

// DISPLAY
typedef enum DisplayMode { // As of yet unused
    PAUSED, RENDERING
} DisplayMode;

DisplayMode mode = RENDERING;
int window_width = DEFAULT_WINDOW_WIDTH;
int window_height = DEFAULT_WINDOW_HEIGHT;
bool is_fullscreen = false;

float u_constant[2];

float rand_float() { return (float)rand() / ((float)RAND_MAX); }

/* Sets new random values for u_constant */
void restart() {
    u_constant[0] = rand_float();
    u_constant[1] = rand_float();
    printf("Constant of %f + %fi\n", u_constant[0], u_constant[1]);
    update_u_constant(u_constant);
}

int main() {
    long long unsigned int t = time(NULL);
    printf("Random seed %llu\n", t);
    srand(t);


    if(init_GLFW(window_width, window_height, "Simulation") == -1) exit(1);
    init_Debug_Callback();
    init_Quad();

    init_Shader(FRAGMENT_FILEPATH, VERTEX_FILEPATH);
    init_Uniforms();
    restart();
    // Zoom level
    // Left/right/up/down panning

    /* Loop until the user closes the window */
    bool keep_running = true;
    while (keep_running) {
        keep_running = render_frame();
        take_user_input();
    }
    clean_up();
    return 0;
}