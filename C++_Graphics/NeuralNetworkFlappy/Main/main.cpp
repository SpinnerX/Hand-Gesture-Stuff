#include <iostream>
#include "game.h"
#include "graphics.h"
#include "EventHandler.h"
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "colors.h"

float normalize(float value, float range){
    return 2.0f * (value / range - 0.5f);
}

template<typename T>
std::string toString(const T& v, const uint8_t decimals = 2)
{
	std::stringstream sx;
	sx << std::setprecision(decimals) << std::fixed;
	sx << v;

	return sx.str();
}

uint32_t aliveCounts(const std::vector<Agent>& players){
	uint32_t alive_counts = 0;
	for (const Agent& p : players) {
		alive_counts += !(p.player.collide);
	}

	return alive_counts;
}



sf::Text currentGenerationText(const uint32_t text_margin, sf::Text& score){
	sf::Text current = score;
	current.setCharacterSize(32);
	current.setPosition(text_margin, 0.5f * text_margin);

	return current;
}
/*
int main(){
	NumberGenerator<>::initialize();

	const uint32_t width = 1600, height = 900;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(width, height), "AutoFlappy", sf::Style::Default, settings);
	window.setFramerateLimit(60);


	bool slow_motion = false;
	const float base_dt = 0.016f;
	float dt = base_dt;

	// INITIALIZING EVENT HANDLERS
	sfev::EventManager event_manager(window);
	event_manager.addEventCallback(sf::Event::Closed, [&](sfev::CstEv ev) { window.close(); });
	event_manager.addKeyPressedCallback(sf::Keyboard::Escape, [&](sfev::CstEv ev) { window.close(); });

	// INTIALIZING SELECTOR<AGENT>
	const uint32_t pop_size = 200;
	Selector<Agent> stadium(pop_size);
	std::vector<sf::Color> colors({ sf::Color(80, 81, 79), 
		                            sf::Color(121, 85, 83),
									sf::Color(161, 88, 86),
									sf::Color(242, 95, 92),
									sf::Color(249, 160, 97),
									sf::Color(255, 224, 102),
									sf::Color(146, 174, 131),
									sf::Color(36, 123, 160),
									sf::Color(74, 158, 170),
									sf::Color(112, 193, 179) });

	// Setting more event handlers for speeding up the frame rates here
	bool full_speed = false;
	event_manager.addKeyPressedCallback(sf::Keyboard::E, [&](sfev::CstEv ev) { full_speed = !full_speed; window.setFramerateLimit((!full_speed)*60); });
	event_manager.addKeyPressedCallback(sf::Keyboard::Space, [&](sfev::CstEv ev) { slow_motion = !slow_motion; dt = slow_motion ? base_dt * 0.1f : base_dt; });

	sf::Font font;
	font.loadFromFile("../res/font.ttf");

	sf::Text score;
	score.setFillColor(sf::Color::White);
	score.setFont(font);
	score.setCharacterSize(20);

	const float text_margin = 10.0f;
	sf::Text current = score;
	current.setCharacterSize(32);
	current.setPosition(text_margin, 0.5f * text_margin);


	score.setPosition(text_margin, text_margin+38);

	sf::Text generationInfo = score;
	generationInfo.setPosition(text_margin, text_margin+62);

	sf::Text graphCaption = score;
	graphCaption.setString("Best Record!");

	sf::Text newBest = score;
	newBest.setString("New Best!");
	newBest.setPosition(width-newBest.getGlobalBounds().width - text_margin, 24.0f + 1.5f * text_margin);

	sf::Text improvement = score;
	improvement.setCharacterSize(16);
	improvement.setPosition(width-512-text_margin, 24.0f + 1.5f * text_margin);
	improvement.setFillColor(sf::Color(96, 211, 148));

	// loading crowns assert here!
	sf::Texture crown;
	crown.loadFromFile("../res/img.png");
	sf::RectangleShape crown_sprite;
	crown_sprite.setTexture(&crown);
	crown_sprite.setSize(sf::Vector2f(80.0, 80.0f));
	crown_sprite.setOrigin(sf::Vector2f(40.0, 70.0f));

	// Loading world and renderer
	World world(width, height);
	Renderer renderer(world, window);

	world.past_threshold = 120.0f;
	world.scroll_speed = 500.0f;
	world.initialize();


	// initializing neural network renderer.
	NeuralRenderer network_printer;
	const sf::Vector2f network_size = network_printer.getSize(4, 6);
	network_printer.position = sf::Vector2f(width - network_size.x - text_margin, height - network_size.y - text_margin);


	// setting up players properties
	const float playerRadius = 30.0f;
	const float graphHeight = 100.0f;

	Graphic bestGraph(200, sf::Vector2f(600.0f, graphHeight), sf::Vector2f(2.0f * text_margin, height - graphHeight - 2.0f * text_margin));
	bestGraph.color = sf::Color(96, 211, 148);
	graphCaption.setPosition(2.0f * text_margin, height - graphHeight - 3.0f * text_margin - 20.0f);
	
	const float back_height = bestGraph.height + 3.0f * text_margin + 20.0f;
	sf::RectangleShape graph_background(sf::Vector2f(bestGraph.width + 2.0f * text_margin, back_height));
	graph_background.setPosition(text_margin, height - back_height - text_margin);
	graph_background.setFillColor(sf::Color(100, 100, 100, 100));


	float bestScore = 1.0f;

	while(window.isOpen()){
		event_manager.processEvents();
		world.initialize();


		for (Agent& a : stadium.getCurrentPopulation()) {
			Player p;
			p.position = sf::Vector2f(150.0f, 250.0f);
			p.radius = playerRadius;
			p.score = 0.0f;
			a.player = p;
		}


		float time = 0.0f;
		float avgFitness = 0.0f;
		uint32_t playersRemainins = 0.0f;
		while (playersRemainins && time < 250.0f && window.isOpen()) {
			event_manager.processEvents();
			const sf::Vector2f next_hole_1 = world.getHole(0);
			const sf::Vector2f next_hole_2 = world.getHole(1);

			uint32_t agent_index = 0;
			for (Agent& agent : stadium.getCurrentPopulation()) {
				if (!agent.player.collide) {
					avgFitness += dt;
					const sf::Vector2f to_hole_1 = next_hole_1 - agent.player.position;
					const std::vector<float> inputs = { normalize(to_hole_1.x, width), normalize(to_hole_1.y, height) };
					agent.execute(inputs);
				}
			}

			time += dt;

			world.update(dt);

			current.setString("Generation: " + toString(stadium.current_iteration));
			score.setString("Current time: " + toString(time));
			generationInfo.setString("Remaining: " + toString(playersRemainins));

			// Draw each frame of each generation.
			window.clear(sf::Color(191, 219, 247));
			window.draw(current);
			window.draw(score);
			window.draw(generationInfo);
			renderer.draw(world);

			// If the speed framerate is not in speeding mode or increased!
			if(!full_speed){
				for (Agent& agent : stadium.getCurrentPopulation()) {
					if (!agent.player.collide) {
						const sf::Vector2f to_hole_1 = next_hole_1 - agent.player.position;
						const std::vector<float> inputs = { normalize(to_hole_1.x, width), normalize(to_hole_1.y, height) };
						network_printer.render(window, agent.network, inputs);
						break;
					}
				}
			}

			bestGraph.setLastValue(time);

			agent_index = 0;
			for (const Agent& p : stadium.getCurrentPopulation()) {
				if (!(p.player.collide)) {
					renderer.draw(p.player, colors[agent_index % 10]);
					if (time > bestScore) {
						crown_sprite.setPosition(p.player.position);
						window.draw(crown_sprite);
					}
				}
				++agent_index;
			}

			// Gauges
			const float gauge_length = 512.0f;
			sf::RectangleShape gauge(sf::Vector2f(gauge_length, 24.0f));

			const float progress_ratio = std::min(1.0f, time / std::max(1.0f, bestScore));
			sf::RectangleShape progress(sf::Vector2f(progress_ratio * gauge_length, 24.0f));
			gauge.setPosition(width - gauge_length - text_margin, text_margin);
			progress.setPosition(width - gauge_length - text_margin, text_margin);
			progress.setFillColor(sf::Color(96, 211, 148));
			
			window.draw(gauge);
			window.draw(progress);

			if (progress_ratio == 1.0f) {
				improvement.setString("+" + toString(time - bestScore));
				window.draw(newBest);
				window.draw(improvement);
			}
			window.draw(graph_background);
			window.draw(graphCaption);
			bestGraph.render(window);

			window.display();
		}
		for (Agent& agent : stadium.getCurrentPopulation()) {
			agent.fitness = std::pow(1.0f * agent.player.score, 1.0f);
			if (agent.fitness > bestScore) {
				bestScore = agent.fitness;
			}
		}

		avgFitness = 0.0f;
		bestGraph.next();
		stadium.nextGeneration();
	}
}*/


int main(){
	NumberGenerator<>::initialize();

	const uint32_t win_width = 1600;
	const uint32_t win_height = 900;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(win_width, win_height), "AutoFlappy", sf::Style::Default, settings);
	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	bool slow_motion = false;
	const float base_dt = 0.016f;
	float dt = base_dt;

	EventManager event_manager(window);
	event_manager.addEventCallback(sf::Event::Closed, [&](CstEv ev) { window.close(); });
	event_manager.addKeyPressedCallback(sf::Keyboard::Escape, [&](CstEv ev) { window.close(); });

	// const uint32_t pop_size = 200;
	const uint32_t pop_size = 200;
	Selector<Agent> stadium(pop_size);

	/*std::vector<sf::Color> colors({ sf::Color(80, 81, 79), 
		                            sf::Color(121, 85, 83),
									sf::Color(161, 88, 86),
									sf::Color(242, 95, 92),
									sf::Color(249, 160, 97),
									sf::Color(255, 224, 102),
									sf::Color(146, 174, 131),
									sf::Color(36, 123, 160),
									sf::Color(74, 158, 170),
									sf::Color(112, 193, 179) });*/
	
	std::vector<sf::Color> colors;
	colors.push_back(COLORS::fuscous_gray);
	colors.push_back(COLORS::beige_red_and_brown);
	colors.push_back(COLORS::apple_blossom);
	colors.push_back(COLORS::bittersweet_color);
	colors.push_back(COLORS::heliotrope_purple_violet);
	colors.push_back(COLORS::somePurple);
	colors.push_back(COLORS::duskBlue);
	colors.push_back(COLORS::malachiteColor);
	colors.push_back(COLORS::blueGreen);

	bool full_speed = false;
	event_manager.addKeyPressedCallback(sf::Keyboard::E, [&](CstEv ev) { full_speed = !full_speed; window.setFramerateLimit((!full_speed) * 60); });
	event_manager.addKeyPressedCallback(sf::Keyboard::Space, [&](CstEv ev) { slow_motion = !slow_motion; dt = slow_motion ? base_dt * 0.1f : base_dt; });

	sf::Font font;
	font.loadFromFile("../res/font.ttf");

	const float text_margin = 10.0f;

	// initializing the assets.
	sf::Text score;
	score.setFillColor(sf::Color::White);
	score.setFont(font);
	score.setCharacterSize(20);

	sf::Text current_generation = score;
	current_generation.setCharacterSize(32);
	current_generation.setPosition(text_margin, 0.5f * text_margin);
	score.setPosition(text_margin, text_margin + 38);

	sf::Text generation_info = score;
	generation_info.setPosition(text_margin, text_margin + 62);
	sf::Text graph_caption = score;
	graph_caption.setString("Best fitness");

	sf::Text new_best = score;
	new_best.setString("New BEST!");
	new_best.setPosition(win_width - new_best.getGlobalBounds().width - text_margin, 24.0f + 1.5f * text_margin);
	
	sf::Text improvement = score;
	improvement.setCharacterSize(16);
	improvement.setPosition(win_width - 512 - text_margin, 24.0f + 1.5f * text_margin);
	improvement.setFillColor(sf::Color(96, 211, 148));



	// initializing the world after setting up the text.
	World world(win_width, win_height);
	world.past_threshold = 120.0f;
	world.scroll_speed = 500.0f;
	world.initialize();
	Renderer renderer(world, window);

	sf::Texture crown;
	crown.loadFromFile("../res/crown.png");
	sf::RectangleShape crown_sprite;
	crown_sprite.setTexture(&crown);
	crown_sprite.setSize(sf::Vector2f(80.0, 80.0f));
	crown_sprite.setOrigin(sf::Vector2f(40.0, 70.0f));

	// Setting up the neural network renderer for the game!
	NeuralRenderer network_printer;
	const sf::Vector2f network_size = network_printer.getSize(4, 6);
	network_printer.position = sf::Vector2f(win_width - network_size.x - text_margin, win_height - network_size.y - text_margin);

	const float player_radius = 30.0f;
	const float graph_height = 100.0f;


	// Setting up properties for the fitness graph!
	// This is how we set that graph up!
	// Such as the fitness graph.
	Graphic bestGraph(200, sf::Vector2f(600.0f, graph_height), sf::Vector2f(2.0f * text_margin, win_height - graph_height - 2.0f * text_margin));
	bestGraph.color = sf::Color(96, 211, 148);
	graph_caption.setPosition(2.0f * text_margin, win_height - graph_height - 3.0f * text_margin - 20.0f);
	const float back_height = bestGraph.height + 3.0f * text_margin + 20.0f;
	sf::RectangleShape graph_background(sf::Vector2f(bestGraph.width + 2.0f * text_margin, back_height));
	graph_background.setPosition(text_margin, win_height - back_height - text_margin);
	
	graph_background.setFillColor(sf::Color(100, 100, 100, 100)); // sets the background to a specific color (100, 100, 100, 100) is light blue
	// graph_background.setFillColor(sf::Color(0, 0, 0, 0));

	float best_score = 1.0f; // setting the best score to be.
	while (window.isOpen()) {
		event_manager.processEvents();

		world.initialize();
		
		// This is how we initialize all of the players with specific properties before using them in the game!
		for (Agent& a : stadium.getCurrentPopulation()) {
			Player p;
			p.position = sf::Vector2f(150.0f, 250.0f);
			p.radius = player_radius;
			p.score = 0.0f;
			a.player = p;
		}

		float time = 0.0f;

		float avgFitness = 0.0f;
		uint32_t agents_remaining = 1;
		while (agents_remaining && time < 250.0f && window.isOpen()) {
			event_manager.processEvents();

			// These variables hole1 and hole2 allow us to give the effect as if we are going through the level
			// Such as letting the pipes flow through each frame with ease.
			const sf::Vector2f next_hole_1 = world.getHole(0);
			const sf::Vector2f next_hole_2 = world.getHole(1);

			
			// This iteration is how we simulate the physics for the game.
			// Giving us the effect of how the player is able to give the jumping effects.
			uint32_t agent_index = 0;
			for (Agent& agent : stadium.getCurrentPopulation()) {

				// This is also how we are checking if each player through out the game has not made collided with the pipes in the game!
				if (!agent.player.collide) {
					avgFitness += dt;
					const sf::Vector2f to_hole_1 = next_hole_1 - agent.player.position;
					const std::vector<float> inputs = { normalize(to_hole_1.x, win_width), normalize(to_hole_1.y, win_height) };
					agent.execute(inputs);
				}
			}

			time += dt; // update the time!

			// This is how we update each player frame by frame, though we are also checking if we had collided with any of the pipes!
			world.update(dt);
			for (Agent& agent : stadium.getCurrentPopulation()) world.checkPlayer(agent.player, dt);

			agents_remaining = aliveCounts(stadium.getCurrentPopulation());

			// Status of each generation of circles that we generate!
			current_generation.setString("Generation " + toString(stadium.current_iteration));
			score.setString("Current time " + toString(time));
			generation_info.setString("Remaining: " + toString(agents_remaining));

			// Graphics
			// This is what renders the background color and the entire world through the "world" object!
			window.clear(sf::Color(191, 219, 247));
			window.draw(current_generation);
			window.draw(score);
			window.draw(generation_info);
			renderer.draw(world);




			// Checking if user decides to increase framerates!
			if (!full_speed) {
				for (Agent& agent : stadium.getCurrentPopulation()) {
					if (!agent.player.collide) {
						const sf::Vector2f to_hole_1 = next_hole_1 - agent.player.position;
						const std::vector<float> inputs = { normalize(to_hole_1.x, win_width), normalize(to_hole_1.y, win_height) };
						network_printer.render(window, agent.network, inputs);
						break;
					}
				}
			}

			// Grab the previous best time to compare to current time, for checking better improvement.
			bestGraph.setLastValue(time);


			// This is how we iterate through all of the circle sprites!
			agent_index = 0;
			for (const Agent& p : stadium.getCurrentPopulation()) {
				if (!(p.player.collide)) {
					renderer.draw(p.player, colors[agent_index % 10]);
					if (time > best_score) {
						crown_sprite.setPosition(p.player.position);
						window.draw(crown_sprite);
					}
				}
				++agent_index;
			}

			
			// Gauge
			const float gauge_length = 512.0f;
			sf::RectangleShape gauge(sf::Vector2f(gauge_length, 24.0f));
			const float progress_ratio = std::min(1.0f, time / std::max(1.0f, best_score));
			sf::RectangleShape progress(sf::Vector2f(progress_ratio * gauge_length, 24.0f));
			gauge.setPosition(win_width - gauge_length - text_margin, text_margin);
			progress.setPosition(win_width - gauge_length - text_margin, text_margin);
			progress.setFillColor(sf::Color(96, 211, 148));

			window.draw(gauge);
			window.draw(progress);

			// This checks if the players have made an improvement/show the times!
			if (progress_ratio == 1.0f) {
				improvement.setString("+" + toString(time - best_score));
				window.draw(new_best);
				window.draw(improvement);
			}

			// This is where we draw the gauges, and progression bard for the game
			window.draw(gauge);
			window.draw(progress);

			// This is where we draw the graphs on the interface!
			// window.draw(graph_background);
			window.draw(graph_caption);
			bestGraph.render(window);

			window.display();
		}
		
		// This is what adjusts the graph shown in the interface.
		for (Agent& agent : stadium.getCurrentPopulation()) {
			agent.fitness = std::pow(1.0f * agent.player.score, 1.0f);
			if (agent.fitness > best_score) best_score = agent.fitness;
		}

		avgFitness = 0.0f;
		bestGraph.next();
		stadium.nextGeneration();
	}

	return 0;
}
