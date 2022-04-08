#include <SFML/Graphics.hpp>

using namespace sf;

void menu(RenderWindow & window)
{
	Texture instructions, menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images//new game.png");
	menuTexture2.loadFromFile("images//credits.png");
	menuTexture3.loadFromFile("images//quit.png");
	aboutTexture.loadFromFile("images//About.jpg");
	menuBackground.loadFromFile("images//fon.png");
	instructions.loadFromFile("images//Instr.png");

	Sprite instr(instructions), menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;

	menu1.setPosition(480, 170);
	menu2.setPosition(120, 150);
	menu3.setPosition(840, 150);
	about.setPosition(170, 0);

	while (isMenu)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(0, 168, 107));

		if (IntRect(480, 170, 300, 90).contains(Mouse::getPosition(window)))
		{
			menu1.setColor(Color::Green);
			menuNum = 1;
		}

		if (IntRect(120, 150, 300, 90).contains(Mouse::getPosition(window)))
		{
			menu2.setColor(Color::Green);
			menuNum = 2;
		}

		if (IntRect(840, 150, 300, 90).contains(Mouse::getPosition(window)))
		{
			menu3.setColor(Color::Green);
			menuNum = 3;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
			{
				window.draw(instr);
				window.display();
				while (!Keyboard::isKeyPressed(Keyboard::Enter));
				isMenu = false;
			}

			if (menuNum == 2)
			{
				window.draw(about);
				window.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape));
			}

			if (menuNum == 3)
			{
				window.close();
				isMenu = false;
			}
		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
}