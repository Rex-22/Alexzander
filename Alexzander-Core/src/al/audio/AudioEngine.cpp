#include "AudioEngine.h"

#define GAU_THREAD_POLICY_MULTI 2
#include <gorilla/ga.h>
#include <gorilla/gau.h>
#include "al/utils/Log.h"

namespace al { namespace audio {

	gau_Manager* AudioEngine::m_Manager = nullptr;
	ga_Mixer* AudioEngine::m_Mixer = nullptr;

	std::vector<Sound*> AudioEngine::m_Sounds;

	void AudioEngine::Init()
	{
		AL_INFO("[Sound] Initializing audio engine...");
		gc_initialize(0);
		m_Manager = gau_manager_create();
		m_Mixer = gau_manager_mixer(m_Manager);
		AL_INFO("[Sound] Audio engine initialized!");
	}

	void AudioEngine::Add(Sound* sound)
	{
		AL_DEBUG("[Sound] Adding sound to manager...");
		m_Sounds.push_back(sound);
	}

	Sound* AudioEngine::Get(const std::string& name)
	{
		for (Sound* sound : m_Sounds)
		{
			if (sound->GetName() == name)
				return sound;
		}

		AL_ERROR("[Sound] No sound found! ", name);
		return nullptr;
	}

	void AudioEngine::Clean()
	{
		for (int i = 0; i < m_Sounds.size(); i++)
			delete m_Sounds[i];
		
		AL_INFO("[Sound] Shutting down audio engine...");
		gau_manager_destroy(m_Manager);
		gc_shutdown();
	}

	void AudioEngine::Update()
	{
		gau_manager_update(m_Manager);
	}

} }
