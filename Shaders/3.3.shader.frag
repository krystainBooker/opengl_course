/**
 * The fragment shader requires a vec4 color output variable
 */
 
#version 330
out vec4 FragColor;
in vec3 vertexColor;  //The input variable from the vertex shader
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    //   FragColor = vertexColor;
    // FragColor = texture(ourTexture, TexCoord);
    // FragColor = texture(ourTexture, TexCoord) * vec4(vertexColor, 1.0);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}