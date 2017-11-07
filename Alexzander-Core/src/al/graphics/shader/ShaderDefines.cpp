#include "al/al.h"
#include "ShaderDefines.h"

namespace al { namespace graphics { namespace Shaders {

	static const char* s_BasicLightShader =
#include "default/BasicLight.glsl"
		;

	Shader* BasicLightingShader()
	{
		return Shader::CreateFromSource(s_BasicLightShader);
	}

} } }