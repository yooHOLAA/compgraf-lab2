#pragma once
#include <GL/glew.h>
#include <string>

class Shader {
public:
    GLuint ID = 0;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use() const;

    // uniform в одну строку: разные типы и количество элементов
    void setBool(const char* name, bool v) const;
    void setInt(const char* name, int v) const;
    void setFloat(const char* name, float v) const;

    void setVec2(const char* name, float v0, float v1) const;
    void setVec3(const char* name, float v0, float v1, float v2) const;
    void setVec4(const char* name, float v0, float v1, float v2, float v3) const;

    void setVec2(const char* name, const float* v) const;
    void setVec3(const char* name, const float* v) const;
    void setVec4(const char* name, const float* v) const;

    void setFloatArray(const char* name, int count, const float* v) const;
    void setIntArray(const char* name, int count, const int* v) const;

    void setMat2(const char* name, const float* m) const;
    void setMat3(const char* name, const float* m) const;
    void setMat4(const char* name, const float* m) const;

private:
    static std::string readFile(const char* path);
    static GLuint compileShader(GLenum type, const std::string& source);
    static void checkCompileErrors(GLuint shader, const std::string& type);
    static void checkLinkErrors(GLuint program);
};
