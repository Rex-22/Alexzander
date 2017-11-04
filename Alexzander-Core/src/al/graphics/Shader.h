#pragma once

#include <iostream>
#include <vector>

#include "gl/gl.h"
#include "al/utils/ShaderUtils.h"

#include "glm/glm.hpp"

#include "al/Common.h"
#include "al/Types.h"

namespace al { namespace graphics {

	class AL_API Shader
	{
	private:
		GLuint m_ShaderID;
		const char* m_ShaderPath;
	public:
		Shader(const char* shaderPath);
		~Shader();

		void SetUniform1f(const GLchar* name, float value) const;
		void SetUniform1fv(const GLchar* name, float* value, int count) const;
		void SetUniform1i(const GLchar* name, int value) const;
		void SetUniform1iv(const GLchar* name, int* value, int count) const;
		void SetUniform2f(const GLchar* name, const glm::vec2& vector) const;
		void SetUniform3f(const GLchar* name, const glm::vec3& vector) const;
		void SetUniform4f(const GLchar* name, const glm::vec4& vector) const;
		void SetUniformMat4(const GLchar* name, const glm::mat4& matrix) const;

		void Enable() const;
		void Disable() const;
	private:
		GLuint CreateProgram() const;
		GLuint CreateShader(uint type, const char* source) const;
		const char* GetType(uint type) const;
		GLint GetUniformLocation(const GLchar* name) const;
	};

} }