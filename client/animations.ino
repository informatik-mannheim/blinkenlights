/**
 * Collection of different animations.
 *
 * (c) 2021 Thomas Smits
 */

#include "config.h"
#include "animations.h"
#include "hardware.h"

#define NUM_ANIMATION_FUNCTIONS 6

static void hsv_to_rgb(int H, int S, int V, int *r_out, int *g_out, int *b_out) {
    
    if (H > 360 || H < 0 || S > 100 || S < 0 || V > 100 || V < 0) {
        *r_out = *g_out = *b_out = 0;
        return;
    }
    
    float s = S / 100.0;
    float v = V / 100.0;
    float C = s * v;
    float X = C * ( 1.0 - abs(fmod(H / 60.0, 2.0) - 1.0));
    float m = v - C;

    float r, g, b;
    
    if (H >= 0 && H < 60){
        r = C;
        g = X;
        b = 0;
    }
    else if (H >= 60 && H < 120) {
        r = X;
        g = C;
        b = 0;
    }
    else if (H >= 120 && H < 180) {
        r = 0;
        g = C;
        b = X;
    }
    else if (H >= 180 && H < 240) {
        r = 0;
        g = X;
        b = C;
    }
    else if (H >= 240 && H < 300) {
        r = X;
        g = 0;
        b = C;
    }
    else{
        r = C;
        g = 0;
        b = X;
    }
    
    *r_out = (r + m) * 255;
    *g_out = (g + m) * 255;
    *b_out = (b + m) * 255;
}


/**
 * Initialize the animations available.
 */
void setup_animations() {
    animation_functions *functions = (animation_functions*) malloc(sizeof(animation_functions));

    functions->num_callbacks = NUM_ANIMATION_FUNCTIONS;

    functions->callbacks = (animation_function*) calloc(functions->num_callbacks, sizeof(animation_function));

    int i = 0;

    functions->callbacks[i++] = black;
    functions->callbacks[i++] = led_on;
    functions->callbacks[i++] = led_off;
    functions->callbacks[i++] = knight_rider;
    functions->callbacks[i++] = pride;
    functions->callbacks[i++] = color_wheel;

    // add your functions here

    animations = functions;
}

/* ####################################### */
/* Animation functions go here */
/* ####################################### */

void led_on(uint id, uint param) {
    tracenl("Playing led_on");
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void led_off(uint id, uint param) {
    tracenl("Playing led_off");
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
}

#define STEP_PAUSE 10

void knight_rider(uint it, uint param) {

    tracenl("Playing knight_rider");

    if (param != 0) {
       for (int i = NUM_LEDS - 1; i >= 0; i--) {
            leds[i] = CRGB::Red;
            FastLED.show();
            //FastLED.delay(STEP_PAUSE);
            //leds[i] = CRGB::Black;
      }
    }
    else {
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i] = CRGB::Red;
            FastLED.show();
            //FastLED.delay(STEP_PAUSE);
            //leds[i] = CRGB::Black;
        }
    }
}

#define PRIDE_SHOW_DELAY 1000

void pride(uint id, uint param) {

    tracenl("Playing pride");

    static uint16_t sPseudotime = 0;
    static uint16_t sLastMillis = 0;
    static uint16_t sHue16 = 0;

    uint8_t sat8 = beatsin88( 87, 220, 250);
    uint8_t brightdepth = beatsin88( 341, 96, 224);
    uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
    uint8_t msmultiplier = beatsin88(147, 23, 60);

    uint16_t hue16 = sHue16;//gHue * 256;
    uint16_t hueinc16 = beatsin88(113, 1, 3000);

    uint16_t ms = millis();
    uint16_t deltams = ms - sLastMillis ;
    sLastMillis  = ms;
    sPseudotime += deltams * msmultiplier;
    sHue16 += deltams * beatsin88( 400, 5,9);
    uint16_t brightnesstheta16 = sPseudotime;

    for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
        hue16 += hueinc16;
        uint8_t hue8 = hue16 / 256;

        brightnesstheta16  += brightnessthetainc16;
        uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

        uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
        uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
        bri8 += (255 - brightdepth);

        CRGB newcolor = CHSV( hue8, sat8, bri8);

        uint16_t pixelnumber = i;
        pixelnumber = (NUM_LEDS-1) - pixelnumber;

        nblend( leds[pixelnumber], newcolor, 64);
  }

    FastLED.show();
    FastLED.delay(PRIDE_SHOW_DELAY);

    if (param > 0) {
        pride(id, param - 1);
    }
}

void black(uint id, uint param) {

    tracenl("Playing black");

    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }

    FastLED.show();
}

#define COLOR_WHEEL_DELAY 10

void color_wheel(uint id, uint param) {
    static int current_color = 0;

    tracenl("Playing color_wheel");

    int s = 90;
    int v = 90;
    
    for (int h = 0; h < 360; h++) {
      CRGB newcolor = CHSV(h, s, v);
       for ( uint16_t i = 0 ; i < NUM_LEDS; i++) {
          
          leds[i] = newcolor;          
       }       
       FastLED.show();
       FastLED.delay(COLOR_WHEEL_DELAY);
    }
    for (int h = 360; h < 0; h--) {
      CRGB newcolor = CHSV(h, s, v);
       for ( uint16_t i = 0 ; i < NUM_LEDS; i++) {
          
          leds[i] = newcolor;          
       }       
       FastLED.show();
       FastLED.delay(COLOR_WHEEL_DELAY);
    }
}
