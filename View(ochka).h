#include <SFML/Graphics.hpp>

using namespace sf;

View view;

View getPlayerCoordinateForView(float x, float y)
{
	float tempX = x;
	float tempY = y;

	if (x < 320)
	{
		tempX = 320;
	}

	if (y < 240)
	{
		tempY = 240;
	}

	if (y > 430)
	{
		tempY = 430;
	}

	view.setCenter(tempX, tempY);
	return view;
}