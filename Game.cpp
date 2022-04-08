#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
//#include <vector>
#include "View(ochka).h"
#include "Menushechka.h"
#include "Map(ochka).h"

using namespace sf;
using namespace std;

class Entity//Клас-батько
{
public:
	float dx, dy, x, y, w, h, speed;
	int health;
	bool life, isDeath;
	Image image;
	String name;
	Texture texture;
	Sprite sprite;

	Entity(Image& image, float X, float Y, float W, float H, String Name)
	{
		x = X;
		y = Y;
		w = W;
		h = H;
		name = Name;
		speed = 0;
		health = 100;
		dx = 0;
		dy = 0;
		life = true;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};

class Player :public Entity//Похідний клас головного героя
{
public:
	int dir, playerScore, playerSecretScore;
	Player(Image& image, float X, float Y, float W, float H, String Name) :Entity(image, X, Y, W, H, Name)
	{
		dir = 0;
		playerScore = 0;
		playerSecretScore = 0;
		if (name == "Player1")
		{
			sprite.setTextureRect(IntRect(4, 19, w, h));
		}
	}

	void update(float time)
	{
		switch (dir)
		{
		case 0:
			dx = speed;
			dy = 0;
			break;
		case 1:
			dx = -speed;
			dy = 0;
			break;
		case 2:
			dx = 0;
			dy = speed;
			break;
		case 3:
			dx = 0;
			dy = -speed;
			break;
		}

		x += dx * time;
		y += dy * time;

		speed = 0;
		sprite.setPosition(x, y);
		interactionWithMap();

		if (health <= 0)
		{
			life = false;
		}
	}

	float getWidth()
	{
		return w;
	}

	void setWidth(float width)
	{
		w = width;
	}

	float getHeight()
	{
		return h;
	}

	void setHeight(float height)
	{
		h = height;
	}

	float getPlayerCoordinateX()
	{
		return x;
	}

	float getPlayerCoordinateY()
	{
		return y;
	}

	int getCurrentMission(int x)
	{
		int mission = 0;

		if (x > 0)
		{
			mission = 0;
		}

		if (x > 2200)
		{
			mission = 1;
		}

		if (playerScore == 6)
		{
			mission = 2;
		}

		if (playerSecretScore == 4)
		{
			mission = 3;
		}

		return mission;
	};

	string getTextMission(int currentMission)
	{
		string missionText = "";

		switch (currentMission)
		{
		case 0:
			missionText = "\nFind a room\nwith antidot";
			break;
		case 1:
			missionText = "\nCollect sharp\nrocks for\nself-defence\njust in case";
			currentMission != 0;
			break;
		case 2:
			missionText = "\nFind hidden\nbuttons";
			break;
		case 3:
			missionText = "\nKill the guard\nto steal antidot";
			break;
		}

		return missionText;
	};

	void interactionWithMap()
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == 'c' || TileMap[i][j] == 'd')
				{
					if (dy > 0)
					{
						y = i * 32 - h;
					}

					if (dy < 0)
					{
						y = i * 32 + 32;
					}

					if (dx > 0)
					{
						x = j * 32 - w;
					}

					if (dx < 0)
					{
						x = j * 32 + 32;
					}
				}

				if (TileMap[i][j] == 'd')
					if (playerSecretScore == 4)
					{
						TileMap[i][j] = ' ';
					}

				if (TileMap[i][j] == 's')
				{
					playerScore++;
					TileMap[i][j] = ' ';
				}

				if (TileMap[i][j] == 'c')
				{
					playerSecretScore++;
					TileMap[i][j] = '0';
				}

				if (TileMap[i][j] == 'f')
				{
					health -= 30;
					TileMap[i][j] = '2';
				}

				if (TileMap[i][j] == 'h')
				{
					health += 20;
					TileMap[i][j] = ' ';
				}

				if (TileMap[i][j] == 't')
				{
					life = false;
					isDeath = false;
				}

				if (TileMap[i][j] == 'g')
				{
					isDeath = true;
					life = false;
				}
			}
	}
};

class Enemy :public Entity//Похідний клас ворога
{
public:
	Enemy(Image& image, float X, float Y, float W, float H, String Name) :Entity(image, X, Y, W, H, Name)
	{
		if (name == "EasyEnemy")
		{
			sprite.setTextureRect(IntRect(3, 116, w, h));
			dx = 0.1;
		}
	}

	void collisionWithMap(float Dx, float Dy)
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == 'c' || TileMap[i][j] == 'd')
				{
					if (Dy > 0)
					{
						y = i * 32 - h;
					}

					if (Dy < 0)
					{
						y = i * 32 + 32;
					}

					if (Dx > 0)
					{
						x = j * 32 - w;
						dx = -0.1;
						sprite.scale(-1, 1);
					}

					if (Dx < 0)
					{
						x = j * 32 + 32;
						dx = 0.1;
						sprite.scale(-1, 1);
					}
				}
			}
	}

	void update(float time)
	{
		if (name == "EasyEnemy")
		{
			collisionWithMap(dx, 0);
			x += dx * time;
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0)
			{
				life = false;
			}
		}
	}
};

int main()
{
	RenderWindow window(VideoMode(1376, 768), "Attempt to live");
	menu(window);
	view.reset(FloatRect(0, 0, 640, 480));

	Font font;
	font.loadFromFile("Spotlight_Typewriter_NC.ttf");

	Font fontD;
	fontD.loadFromFile("CyrilicOld.TTF");

	Text textD("", fontD, 40);
	textD.setFillColor(Color::Red);
	textD.setStyle(Text::Bold);

	Text text("", fontD, 40);
	text.setFillColor(Color::Red);
	text.setStyle(Text::Bold);

	Text textM("", font, 20);
	textM.setFillColor(Color::Black);

	Image map_image;
	map_image.loadFromFile("images\\5z1KX.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Image questImage;
	questImage.loadFromFile("images\\missionbg.jpg");

	Texture questTexture;
	questTexture.loadFromImage(questImage);

	Sprite sQuest;
	sQuest.setTexture(questTexture);
	sQuest.setTextureRect(IntRect(0, 0, 340, 510));
	sQuest.setScale(0.6f, 0.6f);

	Image heroImage;
	heroImage.loadFromFile("images\\hero.png");
	heroImage.createMaskFromColor(Color(41, 33, 59));

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images\\PC_HMM_wolf.png");

	Player p(heroImage, 250, 250, 96, 96, "Player1");
	Enemy easyEnemy(easyEnemyImage, 2650, 50, 127, 83, "EasyEnemy");

	bool showMissionText = true;
	float CurrentFrame = 0;
	Clock clock;
	int gameTime = 0;

	while (window.isOpen())//Події під час відкриття вікна
	{
		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}

			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Tab)
				{
					switch (showMissionText)
					{
					case true:
					{
						ostringstream playerHealthString, task, playerScoreString;
						playerHealthString << p.health;
						playerScoreString << p.playerScore;
						task << p.getTextMission(p.getCurrentMission(p.getPlayerCoordinateX()));
						textM.setString(L"Health:" + playerHealthString.str() + "\n" + task.str() + "\n" + "\n" + L"Rocks:" + playerScoreString.str() + L"/6");
						textM.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);
						sQuest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);
						showMissionText = false;
						break;
					}
					case false:
					{
						textM.setString("");
						showMissionText = true;
						break;
					}
					}
				}
		}

		if (p.life == true)
		{
			if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
			{
				p.dir = 1;
				p.speed = 0.1;

				CurrentFrame += 0.005 * time;

				if (CurrentFrame > 3)
				{
					CurrentFrame -= 3;
				}

				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 134, 96, 56));
				getPlayerCoordinateForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
			}

			else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
			{
				p.dir = 0;
				p.speed = 0.1;

				CurrentFrame += 0.005 * time;

				if (CurrentFrame > 3)
				{
					CurrentFrame -= 3;
				}

				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 230, 96, 56));
				getPlayerCoordinateForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
			}

			else if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
			{
				p.dir = 3;
				p.speed = 0.1;

				CurrentFrame += 0.005 * time;

				if (CurrentFrame > 3)
				{
					CurrentFrame -= 3;
				}

				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 307, 96, 96));
				getPlayerCoordinateForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
			}

			else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
			{
				p.dir = 2;
				p.speed = 0.1;

				CurrentFrame += 0.005 * time;

				if (CurrentFrame > 3)
				{
					CurrentFrame -= 3;
				}

				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 4, 96, 96));
				getPlayerCoordinateForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
			}
		}

		if (p.isDeath == true)
		{
			ostringstream isDeath;
			textD.setString("\n\nThere is way to antidot\nand to my new life..");
			textD.setPosition(view.getCenter().x - 125, view.getCenter().y);
		}

		if (p.isDeath == false)
		{
			ostringstream isDeath;
			textD.setString("\n\nMy rocks are just\njoke for him.\nHe is so strong...");
			textD.setPosition(view.getCenter().x, view.getCenter().y);
		}

		if (p.life == false)
		{
			ostringstream death;
			text.setString("The end!\nEsc to exit");
			text.setPosition(view.getCenter().x, view.getCenter().y);
		}

		//Vector2i localPosition = Mouse::getPosition(window);
		//Vector2f pos = window.mapPixelToCoords(localPosition);
		//cout << "locPos" << localPosition.x << localPosition.y << "\n";

		/*if (localPosition.x < 3)
		{
			view.move(-0.2 * time, 0);
		}

		if (localPosition.x > window.getSize().x - 3)
		{
			view.move(0.2 * time, 0);
		}

		if (localPosition.y > window.getSize().y - 3)
		{
			view.move(0, 0.2 * time);
		}

		if (localPosition.y < 3)
		{
			view.move(0, -0.2 * time);
		}

		if (Keyboard::isKeyPressed(Keyboard::R))
		{
			return true;
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			return false;
		}*/

		p.update(time);
		easyEnemy.update(time);

		window.setView(view);
		window.clear();

		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')
				{
					s_map.setTextureRect(IntRect(96, 32, 32, 32));
				}

				if (TileMap[i][j] == 't')
				{
					s_map.setTextureRect(IntRect(96, 32, 32, 32));
				}

				if (TileMap[i][j] == 'g')
				{
					s_map.setTextureRect(IntRect(96, 32, 32, 32));
				}

				if (TileMap[i][j] == 'b')
				{
					s_map.setTextureRect(IntRect(96, 32, 32, 32));
				}

				if (TileMap[i][j] == 's')
				{
					s_map.setTextureRect(IntRect(480, 160, 32, 32));
				}

				if (TileMap[i][j] == '0')
				{
					s_map.setTextureRect(IntRect(256, 128, 32, 32));
				}

				if (TileMap[i][j] == 'f')
				{
					s_map.setTextureRect(IntRect(704, 288, 32, 32));
				}

				if (TileMap[i][j] == 'h')
				{
					s_map.setTextureRect(IntRect(256, 640, 32, 32));
				}

				if (TileMap[i][j] == 'd')
				{
					s_map.setTextureRect(IntRect(352, 96, 32, 32));
				}

				if (TileMap[i][j] == '2')
				{
					s_map.setTextureRect(IntRect(608, 256, 32, 32));
				}

				if (TileMap[i][j] == 'c')
				{
					s_map.setTextureRect(IntRect(575, 288, 32, 32));
				}

				s_map.setPosition(j * 32, i * 32);

				window.draw(s_map);
			}

		window.draw(easyEnemy.sprite);

		if (!showMissionText)
		{
			textM.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);
			sQuest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);
			window.draw(sQuest);
			window.draw(textM);
		}

		window.draw(p.sprite);
		window.draw(text);
		window.draw(textD);
		window.display();
	}

	return 0;
}