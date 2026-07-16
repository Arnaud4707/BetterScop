#include "../include/shader.hpp"

bool firstMouseObj = true;
float lastXObj = 800.0f / 2.0;
float lastYObj = 600.0 / 2.0;

Shader::Shader(const char *vertexPath, const char *fragmentPath, float rotx, float roty, bool rotObj)
{
	this->rotX = rotx;
	this->rotY = roty;
	this->rot = rotObj;
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure &e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();

	// 2. compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	};

	// similiar for Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	};

	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	// print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
				  << infoLog << std::endl;
	}

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void	Shader::use()
{ 
    glUseProgram(ID);
}

void	Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}
void	Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}
void	Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void	Shader::setVec2(const std::string &name, const vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}
void	Shader::setVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
}
// ------------------------------------------------------------------------
void	Shader::setVec3(const std::string &name, const vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value.x); 
}
void	Shader::setVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
}
// ------------------------------------------------------------------------
void	Shader::setVec4(const std::string &name, const vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}
void	Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{ 
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
}
// ------------------------------------------------------------------------
void	Shader::setMat2(const std::string &name, const mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void	Shader::setMat3(const std::string &name, const mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void	Shader::setMat4(const std::string &name, const mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, &mat[0][0]);
}

void	Shader::mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
	(void)window;
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouseObj)
	{
		lastXObj = xpos;
		lastYObj = ypos;
		firstMouseObj = false;
	}

	float xoffset = xpos - lastXObj;
	float yoffset = lastYObj - ypos;
	lastXObj = xpos;
	lastYObj = ypos;

	float sensitivity = 0.005f;

	if (this->rot)
	{
		this->use();
		// world transformation
	    mat4 model = mat4(1.0f);
	    model = translate(model, vec3(0.0f));
	    model = scale(model, vec3(0.05f)); 
		this->rotX += xoffset * sensitivity;
		this->rotY += yoffset * sensitivity;
		// testy = yoffset;
		model = rotate(model, this->rotY, vec3(0.0f, 1.0f, 0.0f));
		model = rotate(model, this->rotX, vec3(1.0f, 0.0f, 0.0f));
		// model = rotate(model, this->rotY, vec3(1.0f, 0.0f, 0.0f));
		// model = rotate(model, this->rotX, vec3(0.0f, 1.0f, 0.0f));
		this->setMat4("model", model);
	}
	else
		cam.ProcessMouseMovement(xoffset, yoffset);
}

void Shader::resetMouse()
{
    firstMouseObj = true;
}