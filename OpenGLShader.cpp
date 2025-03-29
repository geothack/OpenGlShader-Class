#include "PreEngine.h"
#include "OpenGLShader.h"

namespace BASE {



	OpenGLShader::OpenGLShader(const char* vertexShaderPath, const char* fragShaderPath, const char* geoShaderPath)
	{
		if (geoShaderPath == nullptr)
		{
			MakeShader(vertexShaderPath, fragShaderPath);
		}
		else
		{
			MakeShader(vertexShaderPath, fragShaderPath,geoShaderPath);
		}
	}

	void OpenGLShader::MakeShader(const char* vertexShaderPath, const char* fragShaderPath, const char* geoShaderPath)
	{
		if (geoShaderPath == nullptr)
		{
			Create(mVertex, vertexShaderPath, GL_VERTEX_SHADER);
			Create(mFragment, fragShaderPath, GL_FRAGMENT_SHADER);
			LinkShader();
		}
		else
		{
			Create(mVertex, vertexShaderPath, GL_VERTEX_SHADER);
			Create(mFragment, fragShaderPath, GL_FRAGMENT_SHADER);
			Create(mGeometry, fragShaderPath, GL_GEOMETRY_SHADER);
			LinkShader();
		}
	}

	void OpenGLShader::Use() const
	{
		glUseProgram(mProgram);
	}

	void OpenGLShader::Create(UINT32& shader, const char* path, UINT32 type)
	{
		std::ifstream file;
		
		std::stringstream ssfile;

		std::string code;

		file.open(path);
		std::stringstream vShaderStream;
		ssfile << file.rdbuf();
		
		file.close();
		code = ssfile.str();
		const char* glShader = code.c_str();

		shader = glCreateShader(type);
		glShaderSource(shader, 1, &glShader, NULL);
		glCompileShader(shader);
		// check for shader compile errors
		
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "[ERROR COMPILATION] " << infoLog << std::endl;
		}
	}

	void OpenGLShader::LinkShader()
	{
		mProgram = glCreateProgram();
		glAttachShader(mProgram, mVertex);
		glAttachShader(mProgram, mFragment);
		glLinkProgram(mProgram);
		// check for linking errors
		glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(mProgram, 512, NULL, infoLog);
			std::cout << "[ERROR LINKING_FAILED] " << infoLog << std::endl;
		}
		glDeleteShader(mVertex);
		glDeleteShader(mFragment);
	}

}