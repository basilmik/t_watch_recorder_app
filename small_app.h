#pragma once
#define LILYGO_WATCH_2020_V3
#define LILYGO_WATCH_HAS_MOTOR
#include <LilyGoWatch.h>
#include "button.h"
#include "gestures.h"

#define X0 0
#define Y0 0


class Grid
{
public:
	int r{ 0 };
	int c{ 0 };
	int w{ 0 };
	int h{ 0 };

	button* buttons{ 0 };

	void set_rc(int _r, int _c)
	{
		r = _r;
		c = _c;
		w = 240 / c;
		h = 240 / r;
		buttons = new button * [_r][_c];
		//for (int i = 0; i < _r; i++)
		//{
		//	buttons[i] = new button*[_c];
		//	for (int j = 0; j < _c; j++)
		//	{
		//		buttons[i][j] = nullptr;
		//	}
		//}
	}

	Grid(int _r = 0, int _c = 0)
	{
		r = _r;
		c = _c;
		w = 240 / c;
		h = 240 / r;
		buttons = new button * [_r][_c];
		//buttons = new button ** [_r];
		//for (int i = 0; i < _r; i++)
		//{
		//	buttons[i] = new button*[_c];
		//	for (int j = 0; j < _c; j++)
		//	{
		//		buttons[i][j] = nullptr;
		//	}
		//}

	}

	void draw(TFT_eSPI* tft)
	{
		Serial.print("drawing");
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				if (buttons[i][j] != nullptr)
					buttons[i][j]->draw2(i, j, tft, w, h);
			}
		}

	}

	void add_btn(button* _new_btn, int i, int j)
	{
		if (i < r && i >= 0)
			if (j < c && j >= 0)
			{
				buttons[i][j] = _new_btn;
				Serial.print(i);
				Serial.print(" ");
				Serial.println(j);
			}
	}


	int check_btns(int16_t _x, int16_t _y)
	{
		find_btn(&_x, &_y);
		if (_x != -1 && _y != -1)
		{
			buttons[_x][_y]->click();
			return 1;
		}
		return 0;
	}


	void find_btn(int16_t* _x, int16_t* _y)
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				if (w * i >= *_x && *_x >= w*(i+1))
					if (h * j >= *_y && *_y >= h * (j + 1))
					{
						*_x = i;
						*_y = j;
						return;
					}
			}
		}
		*_x = -1;
		*_y = -1;
	}

};



class small_app
{
public:
	int bckg_clr;
	button** buttons;
	int num_of_btns;
	TFT_eSPI* tft;
	Grid* grid;


	small_app()
	{
		bckg_clr = TFT_BLACK;
		buttons = nullptr;
		num_of_btns = 0;	
		grid = new Grid(3,3);
	}

	void set_tft(TFT_eSPI* _tft)
	{
		tft = _tft;
	}

	void add_btn(button* _new_btn)
	{
		
		button** tmp_btns = new button*[num_of_btns + 1];
		for (int i = 0; i < num_of_btns; i++)
		{
			tmp_btns[i] = buttons[i];
		}
		num_of_btns++;
		buttons = tmp_btns;
		buttons[num_of_btns - 1] = _new_btn;
	}

	void add_btn2(button* _new_btn, int _i, int _j)
	{
		grid->add_btn(_new_btn, _i, _j);
	}


	void draw_base()
	{
		grid->draw(tft);

		tft->fillScreen(TFT_BLACK);
		//int16_t x = X0;
		//int16_t y = Y0;

		//for (int i = 0; i < num_of_btns; i++)
		//{
		//	buttons[i]->draw(x, y, tft);
		//	x += BTN_WIDTH;
		//}
	}

	int find_btn(int16_t _x, int16_t _y)
	{
		for (int i = 0; i < num_of_btns; i++)
		{
			if (_x <= (i + 1) * BTN_WIDTH + X0)
			{			
				if (_x >= i * BTN_WIDTH + X0)
				{				
					if (_y <= BTN_WIDTH + Y0)
					{					
						if (_y >= Y0)
						{							
							return i;
						}
					}
				}
			}
		}
		return -1;
	}


	/*void find_btn2(int16_t _x, int16_t _y)
	{
		grid->find_btn(&_x, &_y);
	}*/

	int check_btns(int16_t _x, int16_t _y)
	{
		int idx = -1;
		idx = find_btn(_x, _y);
		if (idx != -1)
		{
			Serial.print(idx);
			Serial.println(" click");
			buttons[idx]->click();
			return 1;
		}
		return 0;
	}

	/*int check_btns2(int16_t _x, int16_t _y)
	{
		return grid->check_btns(_x, _y);
	}*/


	int check_gesture(gesture_class* gest)
	{
		switch (gest->type)
		{
		case G_TAP:
			return check_btns(gest->x, gest->y);
			//return check_btns2(gest->x, gest->y);
			

		default:
			return 0;
		}

	}

	//void set_grid_size(int _r, int _c)
	//{
	//	grid->set_rc(_r, _c);
	//}



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