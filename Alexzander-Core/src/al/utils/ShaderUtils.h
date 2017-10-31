#pragma once

#include <sstream>
#include <fstream>

#include "al/Common.h"
#include "al/Types.h"


namespace al {

	struct ShaderData
	{
		String VertexSource;
		String FragmentSource;
	};

	class AL_API ShaderUtils
	{
	public:
		inline static ShaderData ParsShader(const String& filePath)
		{
			enum class ShaderType
			{
				NONE = -1, VERTEX_MODE = 0, FRAGMENT_MODE = 1
			};

			std::ifstream stream(filePath);

			ShaderType type = ShaderType::NONE;
			std::stringstream ss[2];
			String line;

			while(getline(stream, line))
				if (line.find("#shader") != String::npos)
				{
					if (line.find("vertex") != String::npos)
					{
						type = ShaderType::VERTEX_MODE;
					}
					else if (line.find("fragment") != String::npos)
					{
						type = ShaderType::FRAGMENT_MODE;
					}
				}
				else
				{
					ss[(int)type] << line << std::endl;
				}
			return{ ss[0].str(), ss[1].str() };
			}
	};
}