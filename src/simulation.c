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

float rand_float() { return (float)rand() / ((float)RAND_MAX); }


int main() {
    long long unsigned int t = time(NULL);
    printf("Random seed %llu\n", t);
    srand(t);

    float u_constant[2] ={ rand_float(), rand_float() };
    printf("Constant of %f + %fi\n", u_constant[0], u_constant[1]);
    // Zoom level
    // Left/right/up/down panning

    if(init_GLFW(window_width, window_height, "Simulation") == -1) exit(1);
    init_Debug_Callback();
    init_Quad();

    init_Shader(FRAGMENT_FILEPATH, VERTEX_FILEPATH);
    init_Uniforms(u_constant);

    /* Loop until the user closes the window */
    bool keep_running = true;
    while (keep_running) {
        keep_running = render_frame();
        take_user_input();
    }
    clean_up();
    return 0;
}