#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include "Window.h"

namespace al { namespace graphics {

	Shader::Shader(const char* shaderPath)
		: m_ShaderPath(shaderPath)
	{
		m_ShaderID = CreateProgram();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderID);
	}

	GLuint Shader::CreateProgram()
	{
		GLuint program = glCreateProgram();

		//std::string vertSourceString = FileUtils::ReadFile(m_VertPath);
		//std::string fragSourceString = FileUtils::ReadFile(m_FragPath);
		//std::String vertSourceString = ShaderUtils::

		ShaderData source = ShaderUtils::ParsShader(m_ShaderPath);

		const char* vertSource = source.VertexSource.c_str();
		const char* fragSource = source.FragmentSource.c_str();

		glAttachShader(program, CreateShader(GL_VERTEX_SHADER, vertSource));
		glAttachShader(program, CreateShader(GL_FRAGMENT_SHADER, fragSource));

		glLinkProgram(program);
		glValidateProgram(program);

		//glDeleteShader(vertex);
		//glDeleteShader(fragment);

		return program;
	}

	GLuint Shader::CreateShader(uint type, const char* source)
	{
		GLuint id = glCreateShader(type);

		glShaderSource(id, 1, &source, NULL);
		glCompileShader(id);

		GLint error;
		glGetShaderiv(id, GL_COMPILE_STATUS, &error);
		if (error == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(id, length, &length, &error[0]);
			std::cout << "Failed to compile " << GetType(type) << " shader!" << std::endl << &error[0] << std::endl;
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	const char* Shader::GetType(uint type) const
	{
		switch (type)
		{
		case  GL_VERTEX_SHADER :
			return "vertex";
		case  GL_FRAGMENT_SHADER:
			return "fragment";
		case  GL_GEOMETRY_SHADER:
			return "geometry";
		}
	}

	GLint Shader::GetUniformLocation(const GLchar* name)
	{
		return glGetUniformLocation(m_ShaderID, name);
	}

	void Shader::SetUniform1f(const GLchar* name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1fv(const GLchar* name, float* value, int count)
	{
		glUniform1fv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform1i(const GLchar* name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1iv(const GLchar* name, int *value, int count)
	{
		glUniform1iv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform2f(const GLchar* name, const glm::vec2& vector)
	{
		glUniform2f(GetUniformLocation(name), vector.x, vector.y);
	}

	void Shader::SetUniform3f(const GLchar* name, const glm::vec3& vector)
	{
		glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::SetUniform4f(const GLchar* name, const glm::vec4& vector)
	{
		glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::SetUniformMat4(const GLchar* name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::Enable() const
	{
		glUseProgram(m_ShaderID);
	}

	void Shader::Disable() const
	{
		glUseProgram(0);
	}

} }
