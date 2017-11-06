#include "al/al.h"
#include "Sound.h"
#include "AudioEngine.h"

#include "al/utils/Log.h"

#include <gorilla/ga.h>
#include <gorilla/gau.h>

#include <iostream>

namespace al { namespace audio {

	Sound::Sound(const std::string& name, const std::string& filename)
		: m_Name(name), m_Filename(filename), m_Playing(false), m_Count(0)
	{
		AL_INFO("[Sound] Creating sound...");

		std::vector<std::string> split = SplitString(m_Filename, '.');
		if (split.size() < 2)
		{
			AL_ERROR("[Sound] Invalid file name '", m_Filename, "'!");
			return;
		}
		m_Sound = gau_load_sound_file(filename.c_str(), split.back().c_str());

		if (m_Sound == nullptr)
			AL_ERROR("[Sound] Could not load file '", m_Filename, "'!");
	}

	Sound::~Sound()
	{
		AL_INFO("[Sound] Releasing sound...");
		ga_sound_release(m_Sound);
	}

	void Sound::Play()
	{
		if (m_Playing)
		{
			AL_WARN("[Sound] The sound is already playing!");
			return;
		}
		gc_int32 quit = 0;
		m_Handle = gau_create_handle_sound(AudioEngine::m_Mixer, m_Sound, &DestroyOnFinish, &quit, NULL);
		m_Handle->sound = this;
		AL_DEBUG("[Sound] Starting audio playback...");
		ga_handle_play(m_Handle);
		m_Playing = true;
		m_Count++;
	}

	void Sound::Loop()
	{
		gc_int32 quit = 0;
		AL_DEBUG("[Sound] Starting audio loop...");
		m_Handle = gau_create_handle_sound(AudioEngine::m_Mixer, m_Sound, &LoopOnFinish, &quit, NULL);
		m_Handle->sound = this;
		ga_handle_play(m_Handle);
		m_Playing = true;
	}

	void Sound::Resume()
	{
		if (m_Playing)
		{
			AL_WARN("[Sound] Sound already playing!");
			return;
		}

		m_Playing = true;
		AL_DEBUG("[Sound] Resuming audio...");
		ga_handle_play(m_Handle);
	}

	void Sound::Pause()
	{
		if (!m_Playing) 
		{
			AL_WARN("[Sound] Sound already paused!");
			return;
		}

		m_Playing = false;
		AL_DEBUG("[Sound] Pausing audio...");
		ga_handle_stop(m_Handle);
	}	

	void Sound::Stop()
	{
		if (!m_Playing)
		{
			AL_WARN("[Sound] Sound already stoped!");
			return;
		}
		AL_DEBUG("[Sound] Stoping audio playback...");
		ga_handle_stop(m_Handle);
		m_Playing = false;
	}

	void Sound::SetGain(float gain)
	{
		if (!m_Playing)
		{
			AL_WARN("[Sound] Cannot set gain! Sound is not currently playing!");
			return;
		}
		m_Gain = gain;
		AL_DEBUG("[Sound] Increasing gain...", m_Gain);
		ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, gain);
	}

	void DestroyOnFinish(ga_Handle* in_handle, void* in_context)
	{
		Sound* sound = (Sound*)in_handle->sound;
		sound->m_Count--;
		AL_DEBUG("[Sound] Stoping audio...", sound->m_Count, " remaing");
		if (sound->m_Count == 0)
			sound->Stop();
	}

	void LoopOnFinish(ga_Handle* in_handle, void* in_context)
	{
		Sound* sound = (Sound*)in_handle->sound;
		sound->Loop();
		AL_DEBUG("[Sound] Stoping audio loop...");
		ga_handle_destroy(in_handle);
	}

} }
