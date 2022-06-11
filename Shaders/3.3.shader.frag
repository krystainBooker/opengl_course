/**
 * The fragment shader requires a vec4 color output variable
 */
 
#version 330
out vec4 FragColor;
in vec3 vertexColor;  //The input variable from the vertex shader
//uniform vec4 ourColour; 

void main()
{
    //   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    //   FragColor = vertexColor;
    FragColor = vec4(vertexColor, 1.0);
}