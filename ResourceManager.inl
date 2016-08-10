#include <stdexcept> //runtime_error
#include <utility> //forward

namespace utils
{
    template<typename RESOURCE,typename IDENTIFIER>
    template<typename ... Args>
    RESOURCE& ResourceManager<RESOURCE,IDENTIFIER>::load(const IDENTIFIER& id,Args&& ... args)
    {
        std::unique_ptr<RESOURCE> ptr(new RESOURCE);
        if(!ptr->loadFromFile(std::forward<Args>(args)...))
            throw std::runtime_error("Impossible to load file");
        if(_map.emplace(id,std::move(ptr)).second == false)
            throw std::runtime_error("Impossible to emplace in map. Object already load?");
		std::cout << "Load " << id << std::endl;
        return *_map[id];
    }

    template<typename RESOURCE,typename IDENTIFIER>
    bool ResourceManager<RESOURCE,IDENTIFIER>::count(const IDENTIFIER& id)const
    {
        return _map.count(id);
    }

    template<typename RESOURCE,typename IDENTIFIER>
    RESOURCE& ResourceManager<RESOURCE,IDENTIFIER>::get(const IDENTIFIER& id)const
    {
        return *_map.at(id);
    }

    template<typename RESOURCE,typename IDENTIFIER>
    template<typename ... Args>
    RESOURCE& ResourceManager<RESOURCE,IDENTIFIER>::getOrLoad(const IDENTIFIER& id,Args&& ... args)
    {
		if (_map.count(id) == 0) {
			return load(id, args...);
		}
        return get(id);
    }

    template<typename RESOURCE,typename IDENTIFIER>
    void ResourceManager<RESOURCE,IDENTIFIER>::clear()
    {
        _map.clear();
    }

	template<typename RESOURCE, typename IDENTIFIER>
	wv::ItemManager* ResourceManager<RESOURCE, IDENTIFIER>::makeItemManager() {
		return new wv::ItemManager(this);
	}

    //sf::Music special case

    template<typename IDENTIFIER>
    template<typename ... Args>
    sf::Music& ResourceManager<sf::Music,IDENTIFIER>::load(const IDENTIFIER& id,Args&& ... args)
    {
        std::unique_ptr<sf::Music> ptr(new sf::Music);

        if(!ptr->openFromFile(std::forward<Args>(args)...))
            throw std::runtime_error("Impossible to load file");
        if(_map.emplace(id,std::move(ptr)).second == false)
            throw std::runtime_error("Impossible to emplace in map. Object aleardy load?");
        return *_map[id];
    };

    template<typename IDENTIFIER>
    bool ResourceManager<sf::Music,IDENTIFIER>::count(const IDENTIFIER& id)const
    {
        return _map.count(id);
    }

    template<typename IDENTIFIER>
    sf::Music& ResourceManager<sf::Music,IDENTIFIER>::get(const IDENTIFIER& id) const
    {
        return *_map.at(id);
    }

    template<typename IDENTIFIER>
    template<typename ... Args>
    sf::Music& ResourceManager<sf::Music,IDENTIFIER>::getOrLoad(const IDENTIFIER& id,Args&& ... args)
    {
        if(_map.count(id) == 0)
            return load(id,args...);
        return get(id);
    }

    template<typename IDENTIFIER>
    void ResourceManager<sf::Music,IDENTIFIER>::clear()
    {
        _map.clear();
    }

    //animation
    //
   /* template<typename IDENTIFIER>
    template<typename ... Args>
    Animation& ResourceManager<Animation,IDENTIFIER>::load(const IDENTIFIER& id,Args&& ... args)
    {
        std::unique_ptr<Animation> ptr(new Animation(std::forward<Args>(args)...));
        if(_map.emplace(id,std::move(ptr)).second == false)
            throw std::runtime_error("Impossible to emplace in map. Object aleardy load?");
        return *_map[id];
    };

    template<typename IDENTIFIER>
    bool ResourceManager<Animation,IDENTIFIER>::count(const IDENTIFIER& id)const
    {
        return _map.count(id);
    }

    template<typename IDENTIFIER>
    Animation& ResourceManager<Animation,IDENTIFIER>::get(const IDENTIFIER& id) const
    {
        return *_map.at(id);
    }

    template<typename IDENTIFIER>
    template<typename ... Args>
    Animation& ResourceManager<Animation,IDENTIFIER>::getOrLoad(const IDENTIFIER& id,Args&& ... args)
    {
        if(_map.count(id) == 0)
            return load(id,args...);
        return get(id);
    }

    template<typename IDENTIFIER>
    void ResourceManager<Animation,IDENTIFIER>::clear()
    {
        _map.clear();
    }*/
}
