# Shaders/GLSL

## Types
 GLSL supports basic types' **int, float, double, uint, and bool**.
 Additionally it features two containers **vectors, and matrices**.

 Vectors in GLSL is a 2,3, or 4 component container for any basic type.
  - **vecn**: the default vector of n floats
  - **bvecn**: a vector of n booleans
  - **ivecn**: a vector of n integers.
  - **uvecn**: a vector of n unsigned integers.
  - **dvecn**: a vector of n double components.

 ## Uniforms
 Global variables that are shared between shaders and OpenGL.
 Uniforms are global, though uniforms will keep their value until they're either reset or updated.
 
**If a uniform is declared but not used in GLSL, it will be removed via the compiler.**

## Vertex Shader
Vertex shaders input variables are known as a vertex attribute
Inputs limited to **16 4-component vertex attributes** (Some hardware may allow for more, query by GL_MAX_VERTEX_ATTRIBS)

On the vertex shader we need to specify the location of the input data with location metadata,
which allows us to pass in multiple inputs.

The location metadata refers to the size of input variable
``` 
    layout(location = 0) out vec3 vals[4];    // Consumes 4 locations
    layout(location = 4) out OutData myOut;   // Consumes 6 locations. dvec4 uses 2, and `val[3]` uses 3 total
    layout(location = 10) out vec2 texCoord;  // Consumes 1 location
```
[Additional details](https://www.khronos.org/opengl/wiki/Layout_Qualifier_(GLSL))

When types and names are equal on both sides OpenGL will link those variables together automatically to send
data between shaders.

## Fragment Shader

The fragment shader requires a vec4 color output variable