#pragma once
#ifndef ResourceManager_H
#define ResourceManager_H
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <unordered_map>
#include <memory>

template<typename RESOURCE, typename IDENTIFIER = int>
class ResourceManager
{
public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&) = delete;
	ResourceManager() = default;
	~ResourceManager(){}

	template<typename ... Args>
	void load(const IDENTIFIER& l_id, Args&& ... args) {
		std::unique_ptr<RESOURCE> ptr(new RESOURCE);
		if (!ptr->loadFromFile(std::forward<Args>(args)...))
			throw std::runtime_error("Impossible to load file");
		m_map.emplace(l_id, std::move(ptr));
	}

	RESOURCE& get(const IDENTIFIER& l_id) const {
		return *m_map.at(l_id);
	}

private:
	std::unordered_map<IDENTIFIER, std::unique_ptr<RESOURCE>>	m_map;
};

template<typename IDENTIFIER>
class ResourceManager<sf::Music, IDENTIFIER> {
public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&) = delete;
	ResourceManager() = default;
	~ResourceManager(){}

	template<typename ... Args>
	void load(const IDENTIFIER& l_id, Args&& ... args) {
		std::unique_ptr<sf::Music> ptr(new sf::Music);

		if (!ptr->openFromFile(std::forward<Args>(args)...))
			throw std::runtime_error("Impossible to load file");
		m_map.emplace(id, std::move(ptr));
	}

	sf::Music& get(const IDENTIFIER& l_id) const {
		return *m_map.at(l_id);
	}
private:
	std::unordered_map<IDENTIFIER, std::unique_ptr<sf::Music>>	m_map;
};
#endif // !ResourceManager_H