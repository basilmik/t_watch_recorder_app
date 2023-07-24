#define LILYGO_WATCH_2020_V3
#define LILYGO_WATCH_HAS_MOTOR
#include <LilyGoWatch.h>
#include "gestures.h"
#include "small_app.h"

TTGOClass* ttgo = nullptr;
TFT_eSPI* tft = nullptr;
gesture_class* gst = new gesture_class;
curtain* crt = new curtain;

bool is_scene_updated;

button* btn = new button;
button* btn2 = new button;
button* btn3 = new button;

void tmp_click(button* _btn)
{
	Serial.println("exec");


	if (_btn->bckg_clr == TFT_RED)
	{
		_btn->set_text("yel");
		_btn->bckg_clr = TFT_YELLOW;
	}
	else
	{	
		_btn->set_text("red");
		_btn->bckg_clr = TFT_RED;
	}
}

void tmp_click2(button* _btn)
{
	Serial.println("exec2");
	
	if (_btn->bckg_clr == TFT_RED)
	{
		_btn->set_text("blu");
		_btn->bckg_clr = TFT_BLUE;
	}
	else
	{	
		_btn->set_text("red");
		_btn->bckg_clr = TFT_RED;
	}
}

void tmp_click3(button* _btn)
{
	Serial.println("exec3");
	
}

void setup() 
{
	Serial.begin(115200);
	ttgo = TTGOClass::getWatch();
	ttgo->begin();
	ttgo->openBL(); // Turn on the backlight (?)
	
	tft = ttgo->tft;
	tft->fillScreen(TFT_BLACK);
	tft->setTextColor(TFT_WHITE);
	tft->setTextSize(4);
	
	btn->set_exec_func(tmp_click);
	btn->set_bckg_clr(TFT_YELLOW);

	//btn2->set_exec_func(tmp_click2);
	//btn2->set_text("yes");
	//btn3->set_exec_func(tmp_click3);
	

	//crt->add_btn(btn);
	//crt->add_btn(btn2);
	//crt->add_btn(btn3);

	crt->set_tft(tft);
	
	crt->add_btn2(btn, 0, 0);
	

	is_scene_updated = false;	
	crt->draw();
}


void loop() 
{
	
	/*if (is_scene_updated == false)
	{
		crt->draw();
		is_scene_updated = true;
	}

	if (gst->get_gesture(ttgo))
	{

	if (gst->is_recognized())
		if (crt->check_gesture(gst))
			is_scene_updated = false;
	}
	*/
}

// eof
