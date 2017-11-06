#include "al/al.h"
#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>

#include "al/utils/ShaderUtils.h"
#include "al/utils/Log.h"

namespace al { namespace graphics {

	Shader::Shader(const String& shaderPath)
		:m_ShaderPath(shaderPath.c_str())
	{
		m_ShaderID = CreateProgram();

		int texIDs[32];
		for (int i = 0; i < 31; ++i)
		{
			texIDs[i] = i;
		}

		Enable();
		SetUniform1iv("textures", texIDs, 31);
		Disable();
	}


	Shader::Shader(const char* source)
	{
		m_ShaderID = CreateProgram(source);

		int texIDs[32];
		for (int i = 0; i < 31; ++i)
		{
			texIDs[i] = i;
		}

		Enable();
		SetUniform1iv("textures", texIDs, 31);
		Disable();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderID);
	}

	GLuint Shader::CreateProgram(const char* src) const
	{
		GLuint program = glCreateProgram();

		ShaderData source = ShaderUtils::ParsSource(src);

		const char* vertSource = source.VertexSource.c_str();
		const char* fragSource = source.FragmentSource.c_str();

		int vertex = CreateShader(GL_VERTEX_SHADER, vertSource);
		int fragment = CreateShader(GL_FRAGMENT_SHADER, fragSource);

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);

		GLint error;
		glGetProgramiv(program, GL_LINK_STATUS, &error);
		if (error == GL_FALSE)
		{
			GLint length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetProgramInfoLog(program, length, &length, &error[0]);
			std::cout << "Failed to link program!" << std::endl << &error[0] << std::endl;
		}

		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	GLuint Shader::CreateProgram() const
	{
		GLuint program = glCreateProgram();

		ShaderData source = ShaderUtils::ParsShader(m_ShaderPath);

		const char* vertSource = source.VertexSource.c_str();
		const char* fragSource = source.FragmentSource.c_str();

		int vertex = CreateShader(GL_VERTEX_SHADER, vertSource);
		int fragment = CreateShader(GL_FRAGMENT_SHADER, fragSource);

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);

		GLint error;
		glGetProgramiv(program, GL_LINK_STATUS, &error);
		if (error == GL_FALSE)
		{
			GLint length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetProgramInfoLog(program, length, &length, &error[0]);
			std::cout << "Failed to link program!" << std::endl << &error[0] << std::endl;
		}

		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	GLuint Shader::CreateShader(uint type, const char* source) const
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

		return "unknowm";
	}

	Shader* Shader::CreateFromSource(const char* source)
	{
		Shader* result = new Shader(source);
		return result;
	}


	GLint Shader::GetUniformLocation(const GLchar* name) const
	{
		return glGetUniformLocation(m_ShaderID, name);
	}

	void Shader::SetUniform1f(const GLchar* name, float value) const
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1fv(const GLchar* name, float* value, int count) const
	{
		glUniform1fv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform1i(const GLchar* name, int value) const
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1iv(const GLchar* name, int *value, int count) const
	{
		glUniform1iv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform2f(const GLchar* name, const glm::vec2& vector) const
	{
		glUniform2f(GetUniformLocation(name), vector.x, vector.y);
	}

	void Shader::SetUniform3f(const GLchar* name, const glm::vec3& vector) const
	{
		glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::SetUniform4f(const GLchar* name, const glm::vec4& vector) const
	{
		glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::SetUniformMat4(const GLchar* name, const glm::mat4& matrix) const
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
