#include "Shader.h"

Shader:: ~Shader()
{
	if (programID != 0)
	{
		glDeleteProgram(programID);
	}
}

void Shader::LoadAttributes()
{
	attrVertices = glGetAttribLocation(programID, "vertices");
    attrColors = glGetAttribLocation(programID, "colors");
    attrNormals = glGetAttribLocation(programID, "normals");
    attrTangents = glGetAttribLocation(programID, "tangents");
    attrBitangents = glGetAttribLocation(programID, "bitangents");    
    attrWVP = glGetUniformLocation(programID, "WVP");
    attrTexCoords = glGetAttribLocation(programID, "texCoords");
    attrTexTranslation = glGetAttribLocation(programID, "texTranslation");
    attrInstanceMatrix = glGetAttribLocation(programID, "instanceMatrix");
}

void Shader::SetVec3(const char* _name, glm::vec3 _value)
{
    GLint loc = glGetUniformLocation(programID, _name);
    if (loc != -1)
    {
        glUniform3fv(loc, 1, &_value[0]);
    }
}

void Shader::SetMat4(const char* _name, glm::mat4 _value)
{
    GLint loc = glGetUniformLocation(programID, _name);
    if (loc != -1)
    {
        glUniformMatrix4fv(loc, 1, GL_FALSE, &_value[0][0]);
    }
}

void Shader::SetFloat(const char* _name, float _value)
{
    GLint loc = glGetUniformLocation(programID, _name);
    if (loc != -1)
    {
        glUniform1f(loc, _value);
    }
}

void Shader::SetTextureSampler(const char* _name, GLuint _texUint, int _texUintId, int _value)
{
    GLint loc = glGetUniformLocation(programID, _name);
    if (loc != -1)
    {
        glActiveTexture(_texUint);
        glBindTexture(GL_TEXTURE_2D, _value);
        glUniform1i(loc, _texUintId);
    }
}

void Shader::EvaluateShader(int _infoLength, GLuint _id)
{
	if (_infoLength > 0)
	{
		std::vector<char> errorMessage(_infoLength + 1);
		glGetShaderInfoLog(_id, _infoLength, NULL, &errorMessage[0]);
		M_ASSERT(NULL, ("%s\n", &errorMessage[0]));
	}
}

GLuint Shader::LoadShaderFile(const char* _filePath, GLenum _type)
{
    GLuint shaderID = glCreateShader(_type);

    std::string shaderCode;
    std::ifstream shaderStream(_filePath, std::ios::in);
    bool isOpen = shaderStream.is_open();
    M_ASSERT(shaderStream.is_open(), ("Impossible %s Read FAQ!\n", _filePath));
    std::string Line = "";
    while (getline(shaderStream, Line))
    {
        shaderCode += "\n" + Line;
    }
    shaderStream.close();

    char const* sourcePointer = shaderCode.c_str();
    glShaderSource(shaderID, 1, &sourcePointer, NULL);
    glCompileShader(shaderID);

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    EvaluateShader(infoLogLength, shaderID);

    glAttachShader(programID, shaderID);

    return shaderID;

}

void Shader::CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath)
{
    programID = glCreateProgram();

    GLuint vertexShaderID = LoadShaderFile(_vertexFilePath, GL_VERTEX_SHADER);
    GLuint fragmentShaderID = LoadShaderFile(_fragmentFilePath, GL_FRAGMENT_SHADER);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    EvaluateShader(infoLogLength, programID);

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

void Shader::LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath)
{
    CreateShaderProgram(_vertexFilePath, _fragmentFilePath);
    LoadAttributes();
}

void Shader::SetInt(const char* _name, int _value)
{
    GLint loc = glGetUniformLocation(programID, _name);
    if (loc != -1)
    {
        glUniform1i(loc, _value);
    }
}