#include "Shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragShaderPath, const char* geoShaderPath)
{
	if (geoShaderPath == nullptr)
	{
		MakeShader(vertexShaderPath, fragShaderPath);
	}
	else
	{
		MakeShader(vertexShaderPath, fragShaderPath, geoShaderPath);
	}
}

void Shader::MakeShader(const char* vertexShaderPath, const char* fragShaderPath, const char* geoShaderPath)
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

void Shader::Attach() const
{
	glUseProgram(mProgram);
}

void Shader::Create(uint32_t& shader, const char* path, uint32_t type)
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
		std::cout << "[ERROR] " << infoLog << std::endl;
	}
}

void Shader::LinkShader()
{
	mProgram = glCreateProgram();
	glAttachShader(mProgram, mVertex);
	glAttachShader(mProgram, mFragment);
	glLinkProgram(mProgram);
	// check for linking errors
	glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(mProgram, 512, NULL, infoLog);
		std::cout << "[ERROR] " << infoLog << std::endl;
	}
	glDeleteShader(mVertex);
	glDeleteShader(mFragment);
}