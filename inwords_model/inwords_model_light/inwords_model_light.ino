//use version 3001000 of `FastLed` librery.
#include "FastLED.h"
#include "math.h"
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
void setled(uint8_t i, uint8_t r, uint8_t g, uint8_t b)
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
  double inverse_count = 1/count; 
  for (int idx = 0; idx < (count+1); idx++)
  {
    for (int led = 0; led < NUM_LEDS; led++)
    {
      if (!program[led].stat)
      {
        uint8_t cur_r = ((program[led].r_end * idx + program[led].r_start * (count - idx)) /count );
        uint8_t cur_g = ((program[led].g_end * idx + program[led].g_start * (count - idx)) /count );
        uint8_t  cur_b = ((program[led].b_end * idx + program[led].b_start * (count - idx)) /count );
        setled(led, cur_r, cur_g, cur_b);
      }
    }
    FastLED.show();
    delay(sleep);
  }
}

//Set all leds in `program` to have start=end
// e.g. in the next run_program will do nothing.
void set_static()
{
  for (int led = 0; led < NUM_LEDS; led++)
  {
    program[led].r_start = program[led].r_end;
    program[led].g_start = program[led].g_end;
    program[led].b_start = program[led].b_end;
    program[led].stat = true; 
  }
}


void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2812B, PIN, RGB>(leds, NUM_LEDS);
}


//////////////////////////////////
//     INWORDS model led array  //
//////////////////////////////////
//            Entrence
// /----------@@@@---------\
// | 4+5      6+7+8   9,10 |
// |                       |
// |         (12)          |
// |                       |
// |      13 ^ 11          |
// |        /_\            |
// | 3+2               0+1 |
// \_______________________/

void parameter(uint8_t  front_r ,uint8_t  front_g, uint8_t   front_b   )
{

  
  int inter_fraction = 3; 
  //Initilize the gate-leds in 100 steps.  
  program[7] = led_prog(0, 0, 0, front_r/inter_fraction, front_g/inter_fraction, front_b/inter_fraction);
  run_program(100, 10);
  //Leave the gate leds as is
  

  //Initilize the gate-leds in 100 steps.  
  program[6] = led_prog(0, 0, 0, front_r, front_g, front_b);
  program[7] = led_prog(front_r/inter_fraction, front_g/inter_fraction, front_b/inter_fraction, front_r, front_g, front_b);
  program[8] = led_prog(0, 0, 0, front_r, front_g, front_b);
  run_program(300, 10);
  //Leave the gate leds as is
  
  set_static();
  program[9] = led_prog(0, 0, 0, front_r/inter_fraction, front_g/inter_fraction, front_b/inter_fraction);
  program[5] = led_prog(0, 0, 0, front_r/inter_fraction, front_g/inter_fraction, front_b/inter_fraction);
  run_program(100, 10);
   
  set_static();  
  program[9] = led_prog(front_r/inter_fraction, front_g/inter_fraction, front_b/inter_fraction, front_r, front_g, front_b);
  program[9] = led_prog(front_r/inter_fraction, front_g/inter_fraction, front_b/inter_fraction, front_r, front_g, front_b);
  program[4] = led_prog(0, 0, 0, 30, 10, 100);  
  program[10] = led_prog(0, 0, 0, 30, 10, 100);
  run_program(300, 10);


  set_static();
  program[0] = led_prog(0, 0, 0, front_r/inter_fraction, front_g/inter_fraction, front_b/inter_fraction);
  program[3] = led_prog(0, 0, 0, front_r/inter_fraction, front_g/inter_fraction, front_b/inter_fraction);
  run_program(100, 10);
   
  set_static();
  program[0] = led_prog(front_r/inter_fraction, front_g/inter_fraction, front_b/inter_fraction, front_r, front_g, front_b);
  program[3] = led_prog(front_r/inter_fraction, front_g/inter_fraction, front_b/inter_fraction, front_r, front_g, front_b);
  program[1] = led_prog(0, 0, 0, 30, 10, 100);  
  program[2] = led_prog(0, 0, 0, 30, 10, 100);
  run_program(300, 10);
}

void tower(unsigned char t_r, unsigned char  t_g, unsigned char  t_b)
{  
  //Turn on the tower leds.
  set_static();
  program[11] = led_prog(0, 0, 0, t_r, t_g, t_b);
  program[12] = led_prog(0, 0, 0, t_r, t_g, t_b);
  program[13] = led_prog(0, 0, 0, t_r, t_g, t_b);
  run_program(300, 10);
}

void final()
{
  delay(10000);    
  set_static();
  //for (int led = 0; led < NUM_LEDS; led++)
  //  program[led].set_end(0, 0, 0);    
  //run_program(200, 15);  
  //delay(2000);
}
void init_state()
{
  for (int led=0; led<NUM_LEDS; led++)
  {
    leds[led].r = 0;
    leds[led].g = 0;
    leds[led].b = 0;
    program[led] = led_prog(); 
  }
  FastLED.show();
}
void loop() {
  // put your main code here, to run repeatedly:

  init_state();
  parameter(60,0,180); 
  tower(30, 100, 0);  
  final();

  init_state();
  delay(3000); 
  
  
  parameter(180,0,60); 
  tower(0, 100, 30);
  final();

  init_state();
  delay(3000); 

  
  parameter(60,180,0); 
  tower(0, 30, 100);
  final();
  
  init_state();
  delay(3000);  
}
