#include "firefly-rk3399-gpio.h"
#include <stdio.h>
int main()
{
  int buf[] = {123,126,124};

  int a=0, n=3;
  if( firefly_rk3399_initRegMap() == -1) {
  	printf("rk3399_initRegMap faile\n");
  }else printf("rk3399_initRegMap OK\n");
  
  for(int i=0; i<n; i++){
	  printf("O--i=%d ----\n", i);
	  sleep(1);
	  firefly_rk3399_pinMode(buf[i], OUTPUT);
	  firefly_rk3399_digitalWrite(buf[i], HIGH);
	  a=firefly_rk3399_digitalRead(buf[i]);
	  printf("a is %d  \n",a);
	  sleep(1);
	  firefly_rk3399_digitalWrite(buf[i], LOW);
	  a=firefly_rk3399_digitalRead(buf[i]);
	  printf("a is %d  \n",a);
	  sleep(1);
  }
/*
  for(int i=0; i<n; i++){
	  printf("I---i=%d ---- \n", i);
	  firefly_rk3399_pinMode(buf[i], INPUT);
	  firefly_rk3399_pullUpDnControl(buf[i], PUD_UP);
	  sleep(1); 
	  a=firefly_rk3399_digitalRead(buf[i]);
	  printf("a is %d  \n",a);
	  firefly_rk3399_pullUpDnControl(buf[i], PUD_DOWN);
	  sleep(1);
	  a=firefly_rk3399_digitalRead(buf[i]);
	  printf("a is %d  \n",a);
	  sleep(1);
  }
 */
  return 0;
}
