#include "firefly-rk3399-gpio.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/* GPIO0_A1 : Open/Close the door
** GPIO2_A2 : Door state detection, Low, door closed; High, door opened
** GPIO1_C7 : Lock state detection, Low, locked, High, opened
*/

int DoorPin = 53;
int DoorStatePin = 66;
int LockStatePin = 55;

int LockInit(void);
int LockDoor( int lock );
int DoorState(void);
int LockState(void);


int main( int argc, char **argv)
{  
   int ret = 0, i = 0;

   ret = LockInit();
   if( ret != 0 ) 
   {
      printf("Lock initialization failed!\n");
      return -1;
   }

   i = atoi( argv[1] );

  if( i ) LockDoor(1);
  else LockDoor(0);

   printf("Lock test start.\n");
   //while(1)
   {
      i++;
      i = i%2;
      sleep(5);
      if( DoorState() ) printf("Door is closed.\n");
      else printf("Door is Open.\n"); 
      if( LockState() ) printf("Lock is closed.\n");
      else printf("Lock is Open.\n");
     // LockDoor( i );
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

int LockInit(void)
{
    int ret = 0;

    ret = firefly_rk3399_initRegMap();
    if( -1 == ret ) 
    {
        printf("\nFirefly GPIO initialization failed!\n");
        return -1;
    }
    /* Set the lock pin to oupput  */
    firefly_rk3399_pinMode( DoorPin, OUTPUT );

    /* Set the dtate detection to input */
    firefly_rk3399_pullUpDnControl( DoorStatePin, PUD_UP );
    firefly_rk3399_pinMode( DoorStatePin, INPUT );
    firefly_rk3399_pullUpDnControl( LockStatePin, PUD_UP );
    firefly_rk3399_pinMode( LockStatePin, INPUT );
    return 0;
}

int LockDoor( int lock )
{
    if( lock ) firefly_rk3399_digitalWrite( DoorPin, HIGH );
    else firefly_rk3399_digitalWrite( DoorPin, LOW );
    
    if( LOW == DoorState() ) return 0;
    else return 1;
}

/*  0 open, 1 close */
int DoorState(void)
{
    if( LOW == firefly_rk3399_digitalRead( DoorStatePin ) ) return 1;
    else return 0;    
}

/*  0, open, 1 close */
int LockState(void)
{
    if( LOW == firefly_rk3399_digitalRead( LockStatePin ) ) return 1;
    else return 0;
}

