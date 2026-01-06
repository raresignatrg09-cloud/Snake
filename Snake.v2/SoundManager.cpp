#include "SoundManager.h"
#include <iostream>

// ------------------------
// Sound Effects
// ------------------------

bool SoundManager::loadSound(const std::string& id, const std::string& filepath)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(filepath))
	{
		std::cerr << "Error: Could not load sound from " << filepath << std::endl;
		return false;
	}

	soundBuffers[id] = buffer;

	sf::Sound sound;
	sound.setBuffer(soundBuffers[id]);
	sounds[id] = sound;

	return true;
}

void SoundManager::playSound(const std::string& id, bool loob)
{
	auto it = sounds.find(id);
	if (it != sounds.end())
	{
		it->second.setLoop(loob);
		it->second.play();
	}
	else
	{
		std::cerr << "Error: Sound with ID " << id << " not found!" << std::endl;
	}
}

void SoundManager::stopSound(const std::string& id)
{
	auto it = sounds.find(id);
	if (it != sounds.end())
	{
		it->second.stop();
	}
	else
	{
		std::cerr << "Error: Sound with ID " << id << " not found!" << std::endl;
	}
}

void SoundManager::setVolume(const std::string& id, float volume)
{
	auto it = sounds.find(id);
	if (it != sounds.end())
	{
		it->second.setVolume(volume);
	}
	else
	{
		std::cerr << "Error: Sound with ID " << id << " not found!" << std::endl;
	}
}

void SoundManager::stopAllSounds()
{
	for (auto& [id, sound] : sounds)
	{
		sound.stop();
	}
}

// ------------------------
// Music
// ------------------------

bool SoundManager::loadMusic(const std::string& filepath)
{
	if (!music.openFromFile(filepath))
	{
		std::cerr << "Error: Could not load music from " << filepath << std::endl;
		return false;
	}
	return true;
}

void SoundManager::playMusic(bool loop)
{
	music.setLoop(loop);
	music.play();
}

void SoundManager::stopMusic()
{
	music.stop();
}

void SoundManager::setMusicVolume(float volume)
{
	music.setVolume(volume);
}
