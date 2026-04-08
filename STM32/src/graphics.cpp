#include "ssd1306.h"
#include <string.h>

void drawLine(int xa, int ya, int xb, int yb){
  if(xa == xb){
    int yStart = (ya < yb) ? ya : yb;
    int yEnd = (ya < yb) ? yb : ya;
    for(int y = yStart; y <= yEnd; y++){
        set_pixel(xa, y);
    }
    return;
  }
  int dx = abs(xa - xb), dy = abs(ya - yb);
	int p = 2*dy - dx;
	int twoDy = 2*dy, twoDyDx = 2*(dy - dx);
	int x, y, xEnd;
	if(xa>xb){
	   x = xb;
	   y = yb;
	   xEnd = xa;
	}
	else{
	  x = xa; y = ya ; xEnd =  xb;
	}
	set_pixel(x, y);
	while(x < xEnd){
	   x++;
	   if(p<0){
	     p = p+twoDy;
	   }
	   else{
	     y++;
	     p = p+twoDyDx;
	   }
	   set_pixel(x,y);
	}
}
void drawRect(int x, int y, int w, int h){
  drawLine(x,y+h,x,y);
  drawLine(x,y,x+w,y);
  drawLine(x+w,y,x+w,y+h);
  drawLine(x,y+h,x+w,y+h);
}
void plotPoints(int xctr, int yctr, int x, int y){

    set_pixel(xctr + x, yctr + y);
    set_pixel(xctr - x, yctr + y);
    set_pixel(xctr + x, yctr - y);
    set_pixel(xctr - x, yctr - y);
    set_pixel(xctr + y, yctr + x);
    set_pixel(xctr - y, yctr + x);
    set_pixel(xctr + y, yctr - x);
    set_pixel(xctr - y, yctr - x);
}
void drawCircle(int x1, int y1, int r){

    int x = 0, y = r;
    int p = 1-r;
    plotPoints(x1, y1, x, y);
    while (x < y)
    {
      x++;
      if (p < 0)
        p+=2*x+1;
      else
      {
        y--;
        p+= 2*(x-y)+1;
      }
      plotPoints(x1, y1, x, y);
    }
}