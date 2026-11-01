#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string Shader::readFile(const char* path)
{
    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "Shader file not found: " << path << std::endl;
        return "";
    }
    std::stringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

GLuint Shader::compileShader(GLenum type, const std::string& source)
{
    GLuint sh = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(sh, 1, &src, NULL);
    glCompileShader(sh);
    return sh;
}

void Shader::checkCompileErrors(GLuint shader, const std::string& type)
{
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
        std::cerr << "Shader compile error (" << type << "):\n" << infoLog << std::endl;
    }
}

void Shader::checkLinkErrors(GLuint program)
{
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
        std::cerr << "Program link error:\n" << infoLog << std::endl;
    }
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    GLuint vs = compileShader(GL_VERTEX_SHADER, readFile(vertexPath));
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, readFile(fragmentPath));
    checkCompileErrors(vs, "VERTEX");
    checkCompileErrors(fs, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vs);
    glAttachShader(ID, fs);
    glLinkProgram(ID);
    checkLinkErrors(ID);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Shader::use() const { glUseProgram(ID); }

void Shader::setBool(const char* name, bool v) const
{
    glUniform1i(glGetUniformLocation(ID, name), (int)v);
}

void Shader::setInt(const char* name, int v) const
{
    glUniform1i(glGetUniformLocation(ID, name), v);
}

void Shader::setFloat(const char* name, float v) const
{
    glUniform1f(glGetUniformLocation(ID, name), v);
}

void Shader::setVec2(const char* name, float v0, float v1) const
{
    glUniform2f(glGetUniformLocation(ID, name), v0, v1);
}

void Shader::setVec3(const char* name, float v0, float v1, float v2) const
{
    glUniform3f(glGetUniformLocation(ID, name), v0, v1, v2);
}

void Shader::setVec4(const char* name, float v0, float v1, float v2, float v3) const
{
    glUniform4f(glGetUniformLocation(ID, name), v0, v1, v2, v3);
}

void Shader::setVec2(const char* name, const float* v) const
{
    glUniform2fv(glGetUniformLocation(ID, name), 1, v);
}

void Shader::setVec3(const char* name, const float* v) const
{
    glUniform3fv(glGetUniformLocation(ID, name), 1, v);
}

void Shader::setVec4(const char* name, const float* v) const
{
    glUniform4fv(glGetUniformLocation(ID, name), 1, v);
}

void Shader::setFloatArray(const char* name, int count, const float* v) const
{
    glUniform1fv(glGetUniformLocation(ID, name), count, v);
}

void Shader::setIntArray(const char* name, int count, const int* v) const
{
    glUniform1iv(glGetUniformLocation(ID, name), count, v);
}

void Shader::setMat2(const char* name, const float* m) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, m);
}

void Shader::setMat3(const char* name, const float* m) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, m);
}

void Shader::setMat4(const char* name, const float* m) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, m);
}