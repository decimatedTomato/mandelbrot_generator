#version 330 core

precision mediump float;

#define THRESHOLD 4.0
#define MAX_ITERATIONS 50

in vec4 gl_FragCoord;
out vec4 fragColor;

uniform vec2 u_constant;
uniform vec2 u_resolution;

/* Returns the mod squared */
float mod2(vec2 z) {
    return z.x * z.x + z.y * z.y;
}

/* Advances previous iteration */
vec2 next(vec2 previous) {
    return vec2(previous.x * previous.x - previous.y * previous.y, 2.0 * previous.x * previous.y) + u_constant;
}

/* Calculates the number of iterations until mod exceeds threshold or max_iterations is reached */
int iterations(vec2 zn) {
    int iterations = 0;
    while((mod2(zn) < THRESHOLD) && (iterations < MAX_ITERATIONS)) {
        zn = next(zn);
        iterations++;
    }
    return iterations;
}


void main()
{
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;
    vec3 col = vec3(iterations(uv) / MAX_ITERATIONS);
    // if(iterations(uv) > 0.0) col = vec3(1.0);

    fragColor = vec4(col, 1.0);
};