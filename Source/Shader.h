#ifndef OPENGL_COURSE_SHADER_H
#define OPENGL_COURSE_SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    // Program Id
    unsigned int ID;

    /**
     * Constructor reads and builds the shader
     * @param vertexPath
     * @param fragmentPath
     */
    Shader(const char *vertexPath, const char *fragmentPath);

    /**
     * Use/Activate the shader
     */
    void use();

    /**
    * Set the variable on the passed in name and value
    * @param name
    * @param value
    */
    void setBool(const std::string &name, bool value) const;

    /**
    * Set the variable on the passed in name and value
    * @param name
    * @param value
    */
    void setInt(const std::string &name, int value) const;

    /**
    * Set the variable on the passed in name and value
    * @param name
    * @param value
    */
    void setFloat(const std::string &name, float value) const;

private:
    void CheckCompileErrors(unsigned int shader, std::string type);
};

#endif //OPENGL_COURSE_SHADER_H
