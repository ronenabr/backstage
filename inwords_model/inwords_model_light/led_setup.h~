//This library defines a program - A start and end configuration of a led array. 


struct led_prog
{
  led_prog() :
  r_start(0), b_start(0), g_start(0),
  r_end(0), b_end(0), g_end(0)
  {}
  
  //Ctor - interpolate from (r,g,b) = (rs,gs,bs) ==> (re,ge,be)
  led_prog(char rs, char gs, char bs, char re, char ge, char be)
    : 
    r_start(rs), b_start(bs),g_start(gs),
    r_end(be), b_end(be), g_end(ge)
    {}

  //set the end configuration for led. 
  void set_end(char r,char g, char b)
  {
    r_end = r;
    g_end = g;
    b_end = b;
  }

  //Set start configuration for led. 
  void set_start(char r,char g, char b)
  {
    r_start = r;
    g_start = g;
    b_start = b;
  }

  char r_start;
  char g_start;
  char b_start;

  char r_end;
  char g_end;
  char b_end; 
};



char clip(int i)
{
  if (i<0)
    return 0;
  if (i>250)
    return 250; 
}




