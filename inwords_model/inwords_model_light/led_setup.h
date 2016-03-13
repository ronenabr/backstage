//This library defines a program - A start and end configuration of a led array. 


struct led_prog
{
  led_prog() :
  r_start(0), b_start(0), g_start(0),
  r_end(0), b_end(0), g_end(0),
  stat(true) 
  {}
  
  //Ctor - interpolate from (r,g,b) = (rs,gs,bs) ==> (re,ge,be)
  led_prog(uint8_t  rs, uint8_t  gs, uint8_t  bs, uint8_t  re, uint8_t  ge, uint8_t  be)
    : 
    r_start(rs), b_start(bs),g_start(gs),
    r_end(re), b_end(be), g_end(ge),
    stat(false)
    {}

  //set the end configuration for led. 
  void set_end(unsigned  char r,uint8_t  g, uint8_t  b)
  {
    r_end = r;
    g_end = g;
    b_end = b;
    stat = false; 
  }

  //Set start configuration for led. 
  void set_start(uint8_t  r,uint8_t  g, uint8_t  b)
  {
    r_start = r;
    g_start = g;
    b_start = b;
    stat = false; 
  }

  uint8_t  r_start;
  uint8_t  g_start;
  uint8_t  b_start;

  uint8_t  r_end;
  uint8_t  g_end;
  uint8_t  b_end; 

  bool stat; 
};



char clip(float i)
{
  if (i<0)
    return 0;
  if (i>250)
    return 250; 
}




