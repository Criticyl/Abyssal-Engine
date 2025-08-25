#include "abyssalpch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Abyssal {

    Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
    {

		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			ABYSSAL_CORE_ERROR("Vertex Shader compilation failure:");
			ABYSSAL_CORE_ERROR("{0}", infoLog.data());
			ABYSSAL_CORE_ASSERT(false, "Vertex Shader compilation failure!");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			ABYSSAL_CORE_ERROR("Fragment Shader compilation failure:");
			ABYSSAL_CORE_ERROR("{0}", infoLog.data());
			ABYSSAL_CORE_ASSERT(false, "Fragment Shader compilation failure!");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_ShaderID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_ShaderID, vertexShader);
		glAttachShader(m_ShaderID, fragmentShader);

		// Link our program
		glLinkProgram(m_ShaderID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_ShaderID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_ShaderID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_ShaderID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_ShaderID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			ABYSSAL_CORE_ERROR("Shader program linking failure:");
			ABYSSAL_CORE_ERROR("{0}", infoLog.data());
			ABYSSAL_CORE_ASSERT(false, "Shader program linking failure!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_ShaderID, vertexShader);
		glDetachShader(m_ShaderID, fragmentShader);
    }

    Shader::~Shader()
    {
		glDeleteProgram(m_ShaderID);
    }

    void Shader::Bind() const
    {
		glUseProgram(m_ShaderID);
    }

    void Shader::Unbind() const
    {
		glUseProgram(0);
    }
}