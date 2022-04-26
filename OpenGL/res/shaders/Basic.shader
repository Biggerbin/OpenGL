#shader vertex
#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
    v_TexCoord = textCoord;
}

#shader fragment
#version 330 core
out vec4 ucolor;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

in vec2 v_TexCoord;

void main()
{
    ucolor = texture(u_Texture, v_TexCoord);
    
}
