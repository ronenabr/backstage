//use version 3001000 of `FastLed` librery. 
#include "FastLED.h"

#include "led_setup.h" 
//This is a crappy program that fades an array of led from a given color to a different color 
// in given number of steps and given delay. 
//I'm using crappy static varibles for the program. Deal with it. 

// Will probably be good only for small led array. 
#define NUM_LEDS 14
CRGB leds[NUM_LEDS];
led_prog program[NUM_LEDS]; 

//Data line connected to pin#6 in Arduino. 
#define PIN 6 

//Set the color of led `i` to `r`,`g`,`b`. 
void setled(char i, char r, char g, char b)
{
      leds[i].r = r;
      leds[i].g = g;
      leds[i].b = b;       
}

 
//Interpolate all leds using start-position
// and end-position set on `program` array.
// In `count` steps with delay `sleep` between steps. 
void run_program(int count, int sleep)
{
  for (int idx=0; idx<count; idx++)
  {
    for (int led=0; led<NUM_LEDS; led++)
    {
      char cur_r = clip((program[led].r_end * idx + program[led].r_start * (count-idx))/count);
      char cur_g = clip((program[led].g_end * idx + program[led].g_start * (count-idx))/count);
      char cur_b = clip((program[led].b_end * idx + program[led].b_start * (count-idx))/count);
      setled(led, cur_r,cur_g,cur_b);       
    }
    FastLED.show();
    delay(sleep);     
  }  
}

//Set all leds in `program` to have start=end
// e.g. in the next run_program will do nothing. 
void set_static()
{
  for (int led=0; led<NUM_LEDS; led++)
  {
    program[led].r_start = program[led].r_end; 
    program[led].g_start = program[led].g_end; 
    program[led].b_start = program[led].b_end; 
  }
}


void setup() {
  FastLED.addLeds<WS2812B, PIN, RGB>(leds, NUM_LEDS);
}


//////////////////////////////////
//     INWORDS model led array  //
//////////////////////////////////
//            Entrence
// /----------@@@@---------\
// | 4+5      6+7+8   9,10 |
// |                       |
// |                       |
// |                       |
// |      12 ^ 11          |
// |        /_\            |
// | 2+3               0+1 |
// \_______________________/

void loop() {
  // put your main code here, to run repeatedly:
  memset(leds, 0, NUM_LEDS * 3);
  memset(program, 0, NUM_LEDS * 6);

  //Initilize the gate-leds in 100 steps. 
  program[6] = led_prog(0,0,0,30,10,100);
  program[7] = led_prog(0,0,0,30,10,100);
  program[8] = led_prog(0,0,0,30,10,100);
  run_program(100, 10);

  //Leave the gate leds as is
  set_static();

  //Turn on the upper corners. 
  program[4] = led_prog(0,0,0,30,10,100);
  program[5] = led_prog(0,0,0,30,10,100);
  program[9] = led_prog(0,0,0,30,10,100);
  program[10] = led_prog(0,0,0,30,10,100);
  run_program(100, 10);

  //Turn on the lower corners. 
  set_static();
  program[0] = led_prog(0,0,0,30,10,100);
  program[1] = led_prog(0,0,0,30,10,100);
  program[2] = led_prog(0,0,0,30,10,100);
  program[3] = led_prog(0,0,0,30,10,100);
  run_program(100, 10);

  //Turn on the tower leds. 
  set_static();  
  program[11] = led_prog(0,0,0,250,100,50);
  program[12] = led_prog(0,0,0,250,100,50);
  program[13] = led_prog(0,0,0,250,100,50);
  run_program(200, 50);

  //Turn off all 4 corners + gate (e.g. first 11 leds)
  set_static();
  for (int led=0; led<11; led++)
    program[led].set_end(0,0,0);
  run_program(200, 50);

  //Turn off the towe leds. 
  set_static();
  for (int led=11; led<14; led++)
    program[led].set_end(0,0,0);
  run_program(100, 50);  
}
