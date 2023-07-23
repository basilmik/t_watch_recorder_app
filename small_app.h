#pragma once
#define LILYGO_WATCH_2020_V3
#define LILYGO_WATCH_HAS_MOTOR
#include <LilyGoWatch.h>
#include "button.h"
#include "gestures.h"

#define X0 20
#define Y0 20


class small_app
{
public:
	int bckg_clr;
	button* buttons;
	int num_of_btns;
	TFT_eSPI* tft;

	small_app()
	{
		bckg_clr = TFT_BLACK;
		buttons = nullptr;
		num_of_btns = 0;		
	}

	void set_tft(TFT_eSPI* _tft)
	{
		tft = _tft;
	}

	void add_btn(button* _new_btn)
	{
		num_of_btns++;

		button* tmp_btns = new button[num_of_btns];
		for (int i = 0; i < num_of_btns - 1; i++)
		{
			tmp_btns[i] = buttons[i];
		}

		buttons = tmp_btns;
		buttons[num_of_btns - 1] = *_new_btn;
	}

	void draw_base()
	{
		tft->fillScreen(TFT_BLACK);
		int16_t x = X0;
		int16_t y = Y0;

		for (int i = 0; i < num_of_btns; i++)
		{
			buttons->draw(x, y, tft);
			x += BTN_WIDTH;
		}
	}

	int find_btn(int16_t _x, int16_t _y)
	{
		for (int i = 0; i < num_of_btns; i++)
		{
			if (_x <= (i + 1) * BTN_WIDTH + X0
				&& _x >= i * BTN_WIDTH + X0
				&& _y <= BTN_WIDTH * 2 + Y0
				&& _y >= BTN_WIDTH + Y0)
				return i;
		}
		return -1;
	}

	int check_btns(int16_t _x, int16_t _y)
	{
		int idx = -1;
		idx = find_btn(_x, _y);
		if (idx != -1)
		{
			buttons[idx].click();
			return 1;
		}
		return 0;
	}

	int check_gesture(gesture_class* gest)
	{
		switch (gest->type)
		{
		case G_TAP:
			return check_btns(gest->x, gest->y);
			

		default:
			return 0;
		}


	}

};


class curtain : public small_app
{
public:

	bool is_folded;
	bool can_fold;

	curtain()
	{
		is_folded = false;
		can_fold = false;
	}

	void draw()
	{
		if (!is_folded)
			draw_base();
	}




};