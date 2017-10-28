#pragma once

#include <iostream>
#include <vector>

#include "gl/gl.h"
#include "al/utils/fileutils.h"

#include "glm/glm.hpp"

#include "al/Common.h"

namespace al { namespace graphics {

	class AL_API Shader
	{
	private:
		GLuint m_ShaderID;
		const char* m_VertPath;
		const char* m_FragPath;
	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();


		void SetUniform1f(const GLchar* name, float value);
		void SetUniform1fv(const GLchar* name, float* value, int count);
		void SetUniform1i(const GLchar* name, int value);
		void SetUniform1iv(const GLchar* name, int* value, int count);
		void SetUniform2f(const GLchar* name, const glm::vec2& vector);
		void SetUniform3f(const GLchar* name, const glm::vec3& vector);
		void SetUniform4f(const GLchar* name, const glm::vec4& vector);
		void SetUniformMat4(const GLchar* name, const glm::mat4& matrix);

		void Enable() const;
		void Disable() const;
	private:
		GLuint Load();
		GLint GetUniformLocation(const GLchar* name);
	};

} }