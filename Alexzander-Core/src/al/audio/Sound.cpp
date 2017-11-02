#include "Sound.h"
#include "AudioEngine.h"

#include <gorilla/ga.h>
#include <gorilla/gau.h>

#include <iostream>

namespace al { namespace audio {

	Sound::Sound(const std::string& name, const std::string& filename)
		: m_Name(name), m_Filename(filename), m_Playing(false)
	{
		std::vector<std::string> split = SplitString(m_Filename, '.');
		if (split.size() < 2)
		{
			std::cout << "[Sound] Invalid file name '" << m_Filename << "'!" << std::endl;
			return;
		}
		m_Sound = gau_load_sound_file(filename.c_str(), split.back().c_str());

		if (m_Sound == nullptr)
			std::cout << "[Sound] Could not load file '" << m_Filename << "'!" << std::endl;
	}

	Sound::~Sound()
	{
		ga_sound_release(m_Sound);
	}

	void Sound::Play()
	{
		gc_int32 quit = 0;
		m_Handle = gau_create_handle_sound(AudioEngine::m_Mixer, m_Sound, &DestroyOnFinish, &quit, NULL);
		m_Handle->sound = this;
		ga_handle_play(m_Handle);
		m_Playing = true;
	}

	void Sound::Loop()
	{
		gc_int32 quit = 0;
		m_Handle = gau_create_handle_sound(AudioEngine::m_Mixer, m_Sound, &LoopOnFinish, &quit, NULL);
		m_Handle->sound = this;
		ga_handle_play(m_Handle);
		m_Playing = true;
	}

	void Sound::Resume()
	{
		gc_int32 quit = 0;
		ga_handle_play(m_Handle);
	}

	void Sound::Pause()
	{
		m_Playing = false;
		ga_handle_stop(m_Handle);
	}

	void Sound::Stop()
	{
		if (!m_Playing)
			return;

		ga_handle_stop(m_Handle);
		m_Playing = false;
	}

	void Sound::SetGain(float gain)
	{
		if (!m_Playing)
		{
			std::cout << "[Sound] Cannot set gain! Sound is not currently playing!" << std::endl;
			return;
		}
		m_Gain = gain;
		ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, gain);
	}

	void DestroyOnFinish(ga_Handle* in_handle, void* in_context)
	{
		Sound* sound = (Sound*)in_handle->sound;
		sound->Stop();
	}

	void LoopOnFinish(ga_Handle* in_handle, void* in_context)
	{
		Sound* sound = (Sound*)in_handle->sound;
		sound->Loop();
		ga_handle_destroy(in_handle);
	}

} }
