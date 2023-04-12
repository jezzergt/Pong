#include <SFML/Graphics.hpp>
#include <string>

int main(int argc, char const* argv[])
{
	int score = 0;
	float dx, dy, speed = 5;
	dx = 0;
	dy = 0;

	sf::RenderWindow window(sf::VideoMode(300, 400), "Pong Game");
	window.setFramerateLimit(30);

	sf::Font font;
	font.loadFromFile("dependencies/fonts/Arial.ttf");

	sf::Text text("", font);
	text.setString(std::to_string(score));
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);

	sf::RectangleShape ball(sf::Vector2f(10, 10));
	ball.setFillColor(sf::Color::White);
	ball.setPosition(100, 100);

	sf::RectangleShape player(sf::Vector2f(40, 10));
	player.setFillColor(sf::Color::White);
	player.setPosition(130, 385);

	while (window.isOpen())
	{
		sf::Vector2f ballPosition = ball.getPosition();
		sf::Vector2f playerPosition = player.getPosition();

		if (ballPosition.x < 0) dx = speed;
		else if (ballPosition.x > 300 - 10) dx = -speed;
		if (ballPosition.y < 0) dy = speed;
		else if (ballPosition.y > 400 - 10)
		{
			dy = 0;
			dx = 0;
			score = 0;
		}

		if (ballPosition.x >= playerPosition.x && ballPosition.x <= playerPosition.x + 40)
			if (ballPosition.y >= playerPosition.y - 10)
			{
				score++;
				text.setString(std::to_string(score));
				dy = -speed;
			}

			ball.move(dx, dy);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				dx = speed;
				dy = speed;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (playerPosition.x > 0)
					player.move(-speed, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (playerPosition.x < 300 - 40)
					player.move(speed, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				ball.setPosition(100, 100);
				score = 0;
				text.setString(std::to_string(score));
			}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) 
				window.close();
		}

		window.clear();
		window.draw(ball);
		window.draw(player);
		window.draw(text);
		window.display();
	}

	return 0;
}