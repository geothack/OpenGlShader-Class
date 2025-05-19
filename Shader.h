#pragma once
#include "opengl.h"
#include <glm/glm.hpp>

#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class Shader
{
public:

    Shader() = default;

    Shader(const char* vertexShaderPath, const char* fragShaderPath, const char* geoShaderPath = nullptr);

    void MakeShader(const char* vertexShaderPath, const char* fragShaderPath, const char* geoShaderPath = nullptr);

    void Attach() const;

public:

    void SetBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(mProgram, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void SetInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(mProgram, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void SetFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(mProgram, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void SetVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(mProgram, name.c_str()), 1, &value[0]);
    }
    void SetVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(mProgram, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void SetVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(mProgram, name.c_str()), 1, &value[0]);
    }
    void SetVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(mProgram, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void SetVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(mProgram, name.c_str()), 1, &value[0]);
    }
    void SetVec4(const std::string& name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(mProgram, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void SetMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void SetMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void SetMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

public:
    inline uint32_t GetProgram() const { return mProgram; }

private:
    void Create(uint32_t& shader, const char* path, uint32_t type);

    void LinkShader();

private:
    uint32_t mProgram;
    uint32_t mVertex;
    uint32_t mFragment;
    uint32_t mGeometry;
    

    int success;
    char infoLog[512];

};