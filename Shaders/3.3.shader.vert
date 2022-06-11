/**
 * Vertex shaders input variables are known as a vertex attribute
 * Inputs limited to 16 4-component vertex attributes (Some hardware may allow for more, query by GL_MAX_VERTEX_ATTRIBS)
 *
 * On the vertex shader we need to specify the location of the input data with location metadata,
 * which allows us to pass in multiple inputs.
 *
 * The location metadata refers to the size of input variable
 *      layout(location = 0) out vec3 vals[4];    // Consumes 4 locations
 *      layout(location = 4) out OutData myOut;   // Consumes 6 locations. dvec4 uses 2, and `val[3]` uses 3 total
 *      layout(location = 10) out vec2 texCoord;  // Consumes 1 location
 * Additional details: https://www.khronos.org/opengl/wiki/Layout_Qualifier_(GLSL)
 *
 * When types and names are equal on both sides OpenGL will link those variables together automatically to send
 * data between shaders.
 */
 
#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;
out vec3 vertexColor;  //Specify a color output to the fragment shader

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = aColour;
    // vertexColor = vec4(0.5, 0.0, 0.0, 1.0); //Set the output variable to dark-red
}