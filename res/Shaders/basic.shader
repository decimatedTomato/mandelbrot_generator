#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
   gl_Position = position;
};

#shader fragment
#version 330 core

in vec4 gl_FragCoord;
out vec4 fragColor;
// layout(location = 0) out vec4 color;

uniform vec2 u_resolution;

void main()
{
   vec2 uv = gl_FragCoord.xy / u_resolution.xy;

   vec3 col = vec3(0.0, uv);

   // Output to screen
   fragColor = vec4(col,1.0);
};