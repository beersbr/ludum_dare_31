#include "ShaderProgram.h"


std::map<std::string, ShaderProgram*> ShaderProgram::shaders;

ShaderProgram::ShaderProgram(void)
{
	shaderID = -1;
}


ShaderProgram::~ShaderProgram(void)
{

}

GLuint ShaderProgram::Uniform(std::string uname) const
{
	// TODO: Do error checking here
	return glGetUniformLocation(shaderID, uname.c_str());
}

void ShaderProgram::Enable()
{
	glUseProgram(shaderID);
}

void ShaderProgram::Disable()
{
	glUseProgram(0);
}

ShaderProgram* ShaderProgram::CreateShader(std::string name, std::string vertexPath, std::string fragmentPath)
{

	if(ShaderProgram::ShaderExists(name))
	{
		fprintf(stdout, "WARNING: Cannot create shader with duplicate name %s\n", name);
		return ShaderProgram::shaders[name];
	}

	ShaderProgram::shaders[name] = new ShaderProgram();
	ShaderProgram::shaders[name]->vertexShaderPath = vertexPath;
	ShaderProgram::shaders[name]->fragmentShaderPath = fragmentPath;

	ShaderProgram::CompileShader(ShaderProgram::shaders[name]);

	return ShaderProgram::shaders[name];
}

bool ShaderProgram::CompileShader(ShaderProgram *shader, const bool forceRecompile)
{
	if(shader->shaderID <= 0 && !forceRecompile)
	{
		fprintf(stdout, "(%s): WARNING: attempt to compile previously compiled shader. ( current program ID: %d)\n", __FILE__, shader->shaderID);
		return false;
	}

	if(forceRecompile)
	{
		fprintf(stdout, "(%s): WARNING: Recompiling previously compiled shader. (current  program ID: %d)\n", __FILE__, shader->shaderID);
	}

	shader->vertexShaderCode = ShaderProgram::ReadFile(shader->vertexShaderPath);
	shader->fragmentShaderCode = ShaderProgram::ReadFile(shader->fragmentShaderPath);

	GLuint vertexProgramID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentProgramID = glCreateShader(GL_FRAGMENT_SHADER);;

	int compileVertexLogLength = 0;
	int compileFragmentLogLength = 0;

	std::vector<char> vertexCompileLogMessage = std::vector<char>(0);
	std::vector<char> fragmentCompileLogMessage = std::vector<char>(0);

	GLint vertexCompileResult = GL_FALSE;
	GLint fragmentCompileResult = GL_FALSE;

	const char* vertexSource = shader->vertexShaderCode.c_str();
	const char* fragmentSource = shader->fragmentShaderCode.c_str();

	// check if the vertex shader compile ok
	glShaderSource(vertexProgramID, 1, &vertexSource, NULL);
	glCompileShader(vertexProgramID);

	glGetShaderiv(vertexProgramID, GL_COMPILE_STATUS, &vertexCompileResult);
	glGetShaderiv(vertexProgramID, GL_INFO_LOG_LENGTH, &compileVertexLogLength);
	vertexCompileLogMessage.resize(compileVertexLogLength);
	glGetShaderInfoLog(vertexProgramID, compileVertexLogLength, NULL, &vertexCompileLogMessage[0]);

	fprintf(stdout, " -- VERTEX SHADER COMPILED (%d)\n%s\n", vertexCompileResult, &vertexCompileLogMessage[0]);

	if(vertexCompileResult == GL_FALSE)
		return false;

	// check if the fragment shader compile ok
	glShaderSource(fragmentProgramID, 1, &fragmentSource, NULL);
	glCompileShader(fragmentProgramID);

	
	glGetShaderiv(fragmentProgramID, GL_COMPILE_STATUS, &fragmentCompileResult);
	glGetShaderiv(fragmentProgramID, GL_INFO_LOG_LENGTH, &compileFragmentLogLength);
	fragmentCompileLogMessage.resize(compileFragmentLogLength);
	glGetShaderInfoLog(fragmentProgramID, compileFragmentLogLength, NULL, &fragmentCompileLogMessage[0]);

	fprintf(stdout, " -- FRAGMENT SHADER COMPILED (%d)\n%s\n", fragmentCompileResult, &fragmentCompileLogMessage[0]);

	if(fragmentCompileResult == GL_FALSE)
		return false;


	// link the programs and get shader ID
	shader->shaderID = glCreateProgram();
	glAttachShader(shader->shaderID, vertexProgramID);
	glAttachShader(shader->shaderID, fragmentProgramID);
	glLinkProgram(shader->shaderID);

	// check that everything linked ok
	std::vector<char> linkProgramLog = std::vector<char>(0);
	int linkLogLength = 0;
	GLint linkResult = GL_FALSE;
	
	glGetProgramiv(shader->shaderID, GL_LINK_STATUS, &linkResult);
	glGetProgramiv(shader->shaderID, GL_INFO_LOG_LENGTH, &linkLogLength);
	linkProgramLog.resize(linkLogLength);
	glGetProgramInfoLog(shader->shaderID, linkLogLength, NULL, &linkProgramLog[0]);

	fprintf(stdout, " -- PROGRAM LINKED (%d)\n%s\n", linkResult, &linkProgramLog[0]);

	if(linkResult == GL_FALSE)
		return false;

	fprintf(stdout, " -- Shader compiled OK (id: %d)\n", shader->shaderID);

	glDeleteProgram(vertexProgramID);
	glDeleteProgram(fragmentProgramID);

	return true;
}

std::string ShaderProgram::ReadFile(std::string const filePath)
{
	std::fstream fileStream(filePath.c_str(), std::ios::in);

	if(!fileStream.is_open())
	{
		fprintf(stdout, "Could not open file at path %s\n", filePath);
		return std::string("ERROR");
	}

	std::string data = "";
	std::string line = "";
	while(std::getline(fileStream, line))
	{
		data += (line + "\n");
	}

	fileStream.close();

	return data;
	
}

bool ShaderProgram::ShaderExists(std::string name)
{
	std::map<std::string, ShaderProgram*>::iterator it = shaders.find(name);
	return (it != ShaderProgram::shaders.end());
	
}