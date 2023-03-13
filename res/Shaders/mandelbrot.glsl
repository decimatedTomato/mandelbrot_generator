#version 330 core

precision mediump float;

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define THRESHOLD 4.0
#define MAX_ITERATIONS 50

in vec4 gl_FragCoord;
out vec4 fragColor;

uniform float u_time;
uniform vec2 u_constant;
uniform vec2 u_resolution;

/* Returns the mod squared */
float mod2(vec2 z) {
    return z.x * z.x + z.y * z.y;
}

/* Advances previous iteration */
vec2 next(vec2 previous, vec2 constant) {
    return vec2(previous.x * previous.x - previous.y * previous.y, 2.0 * previous.x * previous.y) + constant;
}

/* Calculates the number of iterations until mod exceeds threshold or max_iterations is reached */
int iterations(vec2 zn, vec2 constant) {
    int iterations = 0;
    while((mod2(zn) < THRESHOLD) && (iterations < MAX_ITERATIONS)) {
        zn = next(zn, constant);
        iterations++;
    }
    return iterations;
}


void main()
{
    vec2 uv = gl_FragCoord.xy / u_resolution;
    int iterations = iterations((uv - 0.5) * u_resolution / length(u_resolution), 0.5 + 0.5 * cos(0.1 * u_time * u_constant));
    vec3 col = vec3(iterations / MAX_ITERATIONS);

    fragColor = vec4(col, 1.0);
};