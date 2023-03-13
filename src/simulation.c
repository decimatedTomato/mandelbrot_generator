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
#define SHADER_FILE_PATH "res/shaders/basic.shader"
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

typedef struct Complex {
    float r, i;
} Complex;

Complex added_constant; 

void complex_random(Complex* z) {
    z -> r = rand_float();
    z -> i = rand_float();
}
Complex* complex_new(float r, float i) {
    Complex* z = malloc(sizeof(Complex));
    z -> r = r;
    z -> i = i;
    return z;
}
Complex* complex_copy(Complex* z) {
    return complex_new(z -> r, z -> i);
}

/* Returns the mod squared */
float mod2(Complex* z) {
    return z -> r * z -> r + z -> i * z -> i;
}

/* Modifies argument */
void next(Complex* previous) {
    const float zr = previous -> r * previous -> r - previous -> i * previous -> i + added_constant.r;
    const float zi = 2.0 * previous -> r * previous -> i + added_constant.i;
    previous -> r = zr;
    previous -> i = zi;
}

/* Calculates the number of iterations until mod exceeds threshold or max_iterations is reached */
int iterations(Complex* z0) {
    int iterations = 0;
    Complex* zn = complex_copy(z0);
    while(mod2(&zn) < THRESHOLD && iterations < MAX_ITERATIONS) {
        next(zn);
        iterations++;
    }
    return iterations;
}

void render() {

}

int main() {
    long long unsigned int t = time(NULL);
    printf("Random seed %llu\n", t);
    srand(t);

    if(init_GLFW(window_width, window_height, "Simulation") == -1) exit(1);
    init_Debug_Callback();
    init_Quad();

    init_Shader(SHADER_FILE_PATH);
    init_Uniforms();

    /* Loop until the user closes the window */
    bool keep_running = true;
    while (keep_running) {
        keep_running = render_frame();
        take_user_input();
    }
    clean_up();
    return 0;
}