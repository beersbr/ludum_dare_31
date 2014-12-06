#include "ShaderProgram.h"


std::map<std::string, ShaderProgram> ShaderProgram::shaders;

ShaderProgram::ShaderProgram(void)
{
	shaderID = -1;
}


ShaderProgram::~ShaderProgram(void)
{

}

bool ShaderProgram::CompileShader(ShaderProgram shader, const bool debug)
{
	shader.vertexShaderCode = ShaderProgram::ReadFile(shader.vertexShaderPath);
	shader.fragmentShaderCode = ShaderProgram::ReadFile(shader.fragmentShaderPath);

	GLuint vertexProgramID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentProgramID = glCreateShader(GL_FRAGMENT_SHADER);;

	int compileVertexLogLength = 0;
	int compileFragmentLogLength = 0;

	std::vector<char> vertexCompileLogMessage = std::vector<char>(0);
	std::vector<char> fragmentCompileLogMessage = std::vector<char>(0);

	GLint vertexCompileResult = GL_FALSE;
	GLint fragmentCompileResult = GL_FALSE;

	const char* vertexSource = shader.vertexShaderCode.c_str();
	const char* fragmentSource = shader.fragmentShaderCode.c_str();


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
	glShaderSource(fragmentProgramID, 1, &vertexSource, NULL);
	glCompileShader(fragmentProgramID);

	
	glGetShaderiv(fragmentProgramID, GL_COMPILE_STATUS, &fragmentCompileResult);
	glGetShaderiv(fragmentProgramID, GL_INFO_LOG_LENGTH, &compileFragmentLogLength);
	fragmentCompileLogMessage.resize(compileFragmentLogLength);
	glGetShaderInfoLog(fragmentProgramID, compileFragmentLogLength, NULL, &fragmentCompileLogMessage[0]);

	fprintf(stdout, " -- FRAGMENT SHADER COMPILED (%d)\n%s\n", fragmentCompileResult, &fragmentCompileLogMessage[0]);

	if(fragmentCompileResult == GL_FALSE)
		return false;


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