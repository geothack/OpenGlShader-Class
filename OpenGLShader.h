#pragma once

#include "Base/Base.h"

namespace BASE {

    class GAME_BASE_API OpenGLShader
    {
    public:

        OpenGLShader() = default;

        OpenGLShader(const char* vertexShaderPath, const char* fragShaderPath, const char* geoShaderPath = nullptr);

        void MakeShader(const char* vertexShaderPath, const char* fragShaderPath, const char* geoShaderPath = nullptr);

        void Use() const;

    public:
        inline UINT32 GetProgram() const { return mProgram; }

    private:
        void Create(UINT32& shader, const char* path, UINT32 type);
        
        void LinkShader();

    private:
        UINT32 mProgram;
        UINT32 mVertex;
        UINT32 mFragment;
        UINT32 mGeometry;

        int success;
        char infoLog[512];

    };


}