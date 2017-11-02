#pragma once

#include "al/Common.h"
#include "al/Types.h"

 #include <string>
 #include <sstream>
 #include <vector>

struct ga_Handle;
struct ga_Sound;

namespace al { namespace audio {

	class AL_API Sound
	{
	private:
		String m_Name;
		String m_Filename;

		ga_Sound* m_Sound;
		ga_Handle* m_Handle;
		signed int m_Position;

		bool m_Playing;
		float m_Gain;
	public:
		Sound(const std::string& name, const std::string& filename);
		~Sound();


		void Play();
		void Loop();
		void Pause();
		void Resume();
		void Stop();

		void SetGain(float gain);

		inline const bool IsPlaying() const { return m_Playing; }
		inline const float GetGain() const { return m_Gain; }
		inline const std::string& GetName() const { return m_Name; }
		inline const std::string& GetFileName() const { return m_Filename; }

		friend void DestroyOnFinish(ga_Handle* in_handle, void* in_context);
		friend void LoopOnFinish(ga_Handle* in_handle, void* in_context);

		static std::vector<std::string> SplitString(const std::string &s, char delimeter) 
		{
			std::vector<std::string> elems;
			std::stringstream ss(s);
			std::string item;
			while (std::getline(ss, item, delimeter)) {
				elems.push_back(item);

			}
			return elems;
		}

	};

} }