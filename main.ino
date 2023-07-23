#define LILYGO_WATCH_2020_V3
#define LILYGO_WATCH_HAS_MOTOR
#include <LilyGoWatch.h>
#include "gestures.h"


 TTGOClass* ttgo = nullptr;
 TFT_eSPI* tft = nullptr;


void setup() 
{
  // put your setup code here, to run once:

  ttgo = TTGOClass::getWatch();
  ttgo->begin();
  ttgo->openBL(); // Turn on the backlight (?)

  tft = ttgo->tft;
  tft->fillScreen(TFT_BLACK);
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(4);

}

gesture_class* gst = new gesture_class;

void loop() 
{

	gst->get_gesture(ttgo);
 
	gst->print(tft);
	if (!gst->is_recognized())
		tft->fillScreen(TFT_BLACK);

}

// eof
