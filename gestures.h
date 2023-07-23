#pragma once
#define LILYGO_WATCH_2020_V3
#define LILYGO_WATCH_HAS_MOTOR
#include <LilyGoWatch.h>

typedef enum gesture_type_t
{
	G_NONE = -1,
	G_UNRECOGNIZED,
	G_UP,
	G_DOWN,
	G_LEFT,
	G_RIGHT,
	G_TAP
} g_type;


class gesture_class
{
public:
	g_type type;
	int16_t x;
	int16_t y;

	gesture_class()
	{
		x = 0; y = 0;
		type = G_UNRECOGNIZED;
	}

	gesture_class(int16_t _x, int16_t _y, g_type _t)
	{
		x = _x;
		y = _y;
		type = _t;
	}

	void set(int16_t _x, int16_t _y, g_type _t)
	{
		x = _x;
		y = _y;
		type = _t;
	}


	g_type detect_type(int16_t _delx, int16_t _dely)
	{
		if (_delx > 45 && (_dely < 20 && _dely > -20))
			return G_RIGHT;
		else
		if (_delx < -45 && (_dely < 20 && _dely > -20))
			return G_LEFT;
		else
		if (_dely > 45 && (_delx < 20 && _delx > -20))
			return G_DOWN;
		else
		if (_dely < -45 && (_delx < 20 && _delx > -20))
			return G_UP;
		else
		if (_delx < 3 && _delx > -3 && _dely < 3 && _dely > -3)
			return G_TAP;
		else
			return G_UNRECOGNIZED;
	}

	bool is_recognized()
	{
		if (type == G_UNRECOGNIZED)
			return false;
		else
			return true;
	}

	void print(TFT_eSPI* tft)
	{
		tft->setCursor(0, 0);
		switch (type)
		{
		case G_RIGHT:
			tft->print("right");
			break;
		case G_LEFT:
			tft->print("left");
			break;
		case G_UP:
			tft->print("up");
			break;
		case G_DOWN:
			tft->print("down");
			break;
		case G_TAP:
			tft->print("TAP ");
			tft->print(x);
			tft->print(" ");
			tft->print(y);
			break;

		default:
			break;
		}
	}



	int get_gesture(TTGOClass* ttgo)
	{
		int16_t sx, sy;
		int16_t ex, ey;
		int16_t delx, dely;

		if (ttgo->getTouch(sx, sy))
		{
			while (ttgo->getTouch(ex, ey))
			{
				delx = ex - sx;
				dely = ey - sy;

				if (dely > 50 || delx > 50)
					break;
			}

			set(ex, ey, detect_type(delx, dely));
			return 1;
		}

		return 0;
	}



};


