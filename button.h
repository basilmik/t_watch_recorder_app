#pragma once
#define LILYGO_WATCH_2020_V3
#define LILYGO_WATCH_HAS_MOTOR
#include <LilyGoWatch.h>

#define BTN_WIDTH 80
#define BORDER_WIDTH 2

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

	void set_text(char* _text)
	{
		text = _text;
	}

	void set_bckg_clr(int _clr)
	{
		bckg_clr = _clr;
	}


	void set_exec_func(functiontype _exec_func)
	{
		exec_func = _exec_func;
	}

	void draw(int16_t x, int16_t y, TFT_eSPI* tft)
	{
		tft->setTextColor(TFT_WHITE);
		if (shape == BS_CIRCLE)
		{
			tft->fillCircle(x, y, BTN_WIDTH/3, bckg_clr);
			tft->setCursor(x - BTN_WIDTH / 4, y - BTN_WIDTH / 4);
		}
		if (shape == BS_RECTANGLE)
		{
			tft->fillRect(x + BORDER_WIDTH, y + BORDER_WIDTH, BTN_WIDTH* 3 -  2* BORDER_WIDTH, BTN_WIDTH - 2 * BORDER_WIDTH, bckg_clr);
			tft->setCursor(x + 2, y + 2);
		}
		if (shape == BS_SQUARE)
		{
			tft->fillRect(x + BORDER_WIDTH, y + BORDER_WIDTH, 
				BTN_WIDTH - 2* BORDER_WIDTH, BTN_WIDTH - 2 * BORDER_WIDTH, bckg_clr);
			tft->setCursor(x + BORDER_WIDTH + 2, y + BORDER_WIDTH + 2);
		}
	
		tft->print(text);
	}

	void draw2(int i, int j, TFT_eSPI* tft, int16_t w, int16_t h)
	{
		Serial.print("draw2 ");
		Serial.print(i);
		Serial.print(" ");
		Serial.println(j);
		//Serial.println("draw2 ");
		int16_t x = BORDER_WIDTH + i * w;
		int16_t y = BORDER_WIDTH + j * h;

		tft->setTextColor(TFT_WHITE);

		if (shape == BS_SQUARE)
		{
			tft->fillRect(x, y,	w - 2 * BORDER_WIDTH, h - 2 * BORDER_WIDTH, bckg_clr);
			tft->setCursor(x + 2, y + 2);
		}

		tft->print(text);
	}



	void click()
	{
		if (exec_func != NULL)
			exec_func(this);

	}

};


