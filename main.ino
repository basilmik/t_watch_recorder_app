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

void tmp_click(button* _btn)
{
	if (_btn->bckg_clr == TFT_RED)
		_btn->bckg_clr = TFT_BLUE;
	else
		_btn->bckg_clr = TFT_RED;
}

void setup() 
{

	ttgo = TTGOClass::getWatch();
	ttgo->begin();
	ttgo->openBL(); // Turn on the backlight (?)
	
	tft = ttgo->tft;
	tft->fillScreen(TFT_BLACK);
	tft->setTextColor(TFT_WHITE);
	tft->setTextSize(4);
	
	btn->set_exec_func(tmp_click);
	crt->add_btn(btn);
	
	crt->set_tft(tft);

	is_scene_updated = false;	

}


void loop() 
{
	if (is_scene_updated == false)
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
}

// eof
