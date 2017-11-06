#pragma once

#include "al/Common.h"
#include "al/Types.h"
#include <vector>

#include "al/audio/sound.h"


#ifndef SOUND_STRUCT
#define SOUND_STRUCT
struct  gau_Manager;
struct  ga_Mixer;
#endif  


namespace al { namespace audio {

		class AL_API AudioEngine
		{
		private:
			friend class Sound;

			static gau_Manager* m_Manager;
			static ga_Mixer*	m_Mixer;

			static std::vector<Sound*> m_Sounds;
		public:
			static void Init();
			static void Add(Sound* sound);
			static Sound* Get(const std::string& name);
			static void Update();
			static void Clean();
		private:
			AudioEngine() { }
		};

} }
