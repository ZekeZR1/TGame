#pragma once

class SoundEngine {
public:
	SoundEngine();
	~SoundEngine();
	void Update();
	static SoundEngine& GetInstance() {
		static SoundEngine soundEngine;
		return soundEngine;
	}
//private:
	std::unique_ptr<DirectX::AudioEngine> audEngine;
};

static SoundEngine& ISoundEngine() {
	return SoundEngine::GetInstance();
}

