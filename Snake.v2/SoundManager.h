#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

class SoundManager
{
public:
	SoundManager() = default;

	// ------------------------
	// Sound Effects
	// ------------------------
	bool loadSound(const std::string& id, const std::string& filepath);
	void playSound(const std::string& id, bool loob = false);
	void stopSound(const std::string& id);
	void setVolume(const std::string& id, float volume);
	void stopAllSounds();

	// ------------------------
	// Music
	// ------------------------
	bool loadMusic(const std::string& filepath);
	void playMusic(bool loop = true);
	void stopMusic();
	void setMusicVolume(float volume);

private:
	std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
	std::unordered_map<std::string, sf::Sound> sounds;

	sf::Music music;
};

