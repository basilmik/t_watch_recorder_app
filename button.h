#pragma once
#define LILYGO_WATCH_2020_V3
#define LILYGO_WATCH_HAS_MOTOR
#include <LilyGoWatch.h>

#define BTN_WIDTH 80

typedef enum button_shape_t
{
	BS_CIRCLE,
	BS_RECTANGLE,
	BS_SQUARE
} b_shape;

class button;

typedef void (*functiontype)(button*);


class button
{
public:

	int bckg_clr;
	int txt_clr;
	char* text;
	b_shape shape;
	functiontype exec_func{0};


	button(functiontype _exec_func = 0)
	{
		bckg_clr = TFT_RED;
		txt_clr = TFT_WHITE;
		text = new char[4];
		text = "NO\0";
		shape = BS_SQUARE;
		exec_func = _exec_func;
	}

	void set_exec_func(functiontype _exec_func)
	{
		exec_func = _exec_func;
	}

	void draw(int16_t x, int16_t y, TFT_eSPI* tft)
	{
		if (shape == BS_CIRCLE)
		{
			tft->fillCircle(x, y, BTN_WIDTH, bckg_clr);
		}
		if (shape == BS_RECTANGLE)
		{
			tft->fillRect(x, y, BTN_WIDTH* 3, BTN_WIDTH, bckg_clr);
		}
		if (shape == BS_SQUARE)
		{
			tft->fillRect(x, y, BTN_WIDTH, BTN_WIDTH, bckg_clr);
		}

		tft->setTextColor(TFT_WHITE);

		tft->setCursor(x + 2, y + 2);
		tft->print(text);
	}

	void click()
	{
		if (exec_func != NULL)
			exec_func(this);
	}

};


