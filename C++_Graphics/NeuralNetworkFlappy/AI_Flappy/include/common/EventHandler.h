#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>



// Helper using for shorter types
using EventCallback = std::function<void(const sf::Event& event)>;

template<typename T>
using EventCallbackMap = std::unordered_map<T, EventCallback>;

using CstEv = const sf::Event&;


/*
	This class handles subtyped events like keyboard or mouse events
	The unpack function allows to get relevant information from the processed event
*/
template<typename T>
class SubTypeManager{
public:
	SubTypeManager(std::function<T(const sf::Event&)> _unpack) : unpack(_unpack) {}

	~SubTypeManager() = default;

	void processEvent(const sf::Event& event) const {
		T sub_value = unpack(event);

		auto iter = callmap.find(sub_value);
		
		if (iter != callmap.end()) (iter->second)(event); // Call its associated callback
	}

	void addCallback(const T& sub_value, EventCallback callback) {
		callmap[sub_value] = callback;
	}

private:
	EventCallbackMap<T> callmap;
	std::function<T(const sf::Event&)> unpack;
};

/*
	This class handles any type of event and call its associated callbacks if any.
	To process key event in a more convenient way its using a KeyManager
*/
class EventManager{
public:
	EventManager(sf::Window& _window) :
		window(_window),
		keyPressed([&](const sf::Event& event) {return event.key.code; }),
		keyReleased([&](const sf::Event& event) {return event.key.code; }),
		mousePressed([&](const sf::Event& event) {return event.mouseButton.button; }),
		mouseReleased([&](const sf::Event& event) {return event.mouseButton.button; }){
		// Register key events built in callbacks
		this->addEventCallback(sf::Event::EventType::KeyPressed, [&](const sf::Event& event) {keyPressed.processEvent(event); });
		this->addEventCallback(sf::Event::EventType::KeyReleased, [&](const sf::Event& event) {keyReleased.processEvent(event); });
		this->addEventCallback(sf::Event::EventType::MouseButtonPressed, [&](const sf::Event& event) {mousePressed.processEvent(event); });
		this->addEventCallback(sf::Event::EventType::MouseButtonReleased, [&](const sf::Event& event) {mouseReleased.processEvent(event); });
	}

	// Attach new callback to an event
	void addEventCallback(sf::Event::EventType type, EventCallback callback){
		events_callmap[type] = callback;
	}

	// Calls events' attached callbacks
	void processEvents() const{
		// Iterate over events
		sf::Event event;
		while (window.pollEvent(event)){

			// If event type is registred
			sf::Event::EventType type = event.type;
			auto it = events_callmap.find(type);

			if (it != events_callmap.end()) (it->second)(event);
		}
	}

	// Removes a callback
	void removeCallback(sf::Event::EventType type){
		// If event type is registred
		// auto it(m_events_callmap.find(type));
		auto it = events_callmap.find(type);
		
		if (it != events_callmap.end())events_callmap.erase(it);// Remove its associated callback
	}

	// Adds a key pressed callback
	void addKeyPressedCallback(sf::Keyboard::Key key_code, EventCallback callback){
		keyPressed.addCallback(key_code, callback);
	}

	// Adds a key released callback
	void addKeyReleasedCallback(sf::Keyboard::Key key_code, EventCallback callback){
		keyReleased.addCallback(key_code, callback);
	}

	// Adds a mouse pressed callback
	void addMousePressedCallback(sf::Mouse::Button button, EventCallback callback){
		mousePressed.addCallback(button, callback);
	}

	// Adds a mouse released callback
	void addMouseReleasedCallback(sf::Mouse::Button button, EventCallback callback){
		mouseReleased.addCallback(button, callback);
	}

private:
	sf::Window& window;

	SubTypeManager<sf::Keyboard::Key> keyPressed;
	SubTypeManager<sf::Keyboard::Key> keyReleased;

	SubTypeManager<sf::Mouse::Button> mousePressed;
	SubTypeManager<sf::Mouse::Button> mouseReleased;

	EventCallbackMap<sf::Event::EventType> events_callmap;
};