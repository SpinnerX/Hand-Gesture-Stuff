#include <SFML/Graphics.hpp>

// 1pxl = 1mm (arbitrary)
const float scale = 1000.0f;
const float jump_force = 1.0f;

struct Player
{
	Player()
		: collide(false)
		, jumping(false)
		, cooldown(0.0f)
		, score(0.0f)
		, v(0.0f)
	{}

	void update(const float dt)
	{
		if (!collide) {
			score += dt;
		}
		// Gravity
		v += 4.0f * scale * dt;
		// Speed
		position.y += v * dt;

		cooldown -= dt;
	}

	void jump()
	{
		v = -jump_force * scale;
	}

	void hit()
	{
		collide = true;
	}

	sf::Vector2f position;
	float v;
	float radius;
	bool collide;
	bool jumping;
	float cooldown;
	float score;
};