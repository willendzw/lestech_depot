#include <errno.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <unistd.h>

#define  TDS_UART       "/dev/ttysWK2"
#define  TDS_SPEED      9600
#define  RECV_BUF_MAX   256


/* 
** 
*/

struct termios tty;
static int  sfd;
/*
**Using as a lib, just need 3 APIs below.
*/

int TDS_SerialInit(void);
int TDS_Recv(unsigned char *recv);
int TDS_Send(unsigned char *recv, int len);
int TDS_SerialDeInit(void);



/***********************************************************************************/
static int SetInterfaceAttribs(int fd, int speed, int parity, int waitTime);


int main( int argc, char **argv)
{  
   int ret = 0, i = 0;
   unsigned char  Buf_recv[RECV_BUF_MAX] = {0};
   unsigned char  Buf_send[RECV_BUF_MAX] = {"This is a test string 012345678.\n"};

   ret = TDS_SerialInit();
   if( ret < 0 )
   {
      printf("%s: initialize failed!\n", TDS_UART);
      exit(-1);
   }
  
   printf("Send test start ....\n");
   for( i = 0; i < 10; i++)
   {
       ret = TDS_Send(Buf_send, strlen(Buf_send));
       if( ret < 0 )
       {
           printf("%s: send failed!\n", TDS_UART);
           TDS_SerialDeInit();
           return -1;
       }
   } 

   printf("Receive test start, continue to recv until exit. ....\n");
   while(1)
   {
       ret =  TDS_Recv(Buf_recv);
       if( ret < 0 )
       {
           printf("Recv failed, exit!\n");
           TDS_SerialDeInit();
           return -1;
       }
       printf("Recv:%s\n", Buf_recv);

   }
  
  return 0;
}

int TDS_SerialInit(void)
{
    int ret = 0;
    sfd = open(TDS_UART, O_RDWR | O_NOCTTY | O_SYNC);
    if(sfd <0)  return -1;
 /*
 * if waitTime  < 0, it is blockmode
 *  waitTime in unit of 100 millisec : 20 -> 2 seconds 
 */ 
    ret = SetInterfaceAttribs(sfd, B9600, 0, -1);
    return ret;
}

int TDS_SerialDeInit(void)
{
    close(sfd);
    return 0;
}

int TDS_Recv(unsigned char *recv)
{
   int  len = 0;

   len = read(sfd, recv, RECV_BUF_MAX); 
   if (-1 == len)
   { 
      switch(errno) 
      {
          case EAGAIN:
              printf("__FUNCTION__ = %s, __LINE__ = %d\n", __FUNCTION__, __LINE__);
          break;
          default:
              printf("__FUNCTION__ = %s, __LINE__ = %d\n", __FUNCTION__, __LINE__);
          break;  
      }
   }

   if(0 == len) 
   {
       printf("devic is lost!\n"); /*device maybe be unplugged*/
   }
  
   return len;
}

int TDS_Send(unsigned char *recv, int len)
{
    int ret = 0;
    ret = write(sfd, recv, len );
    if(ret < 0)   return -1;
    else return len; 
}

static int SetInterfaceAttribs(int fd, int speed, int parity, int waitTime)
{
  int isBlockingMode;
        struct termios tty;
        
        isBlockingMode = 0;
        if(waitTime < 0 || waitTime > 255)
   isBlockingMode = 1;
   
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0) /* save current serial port settings */
        {
   printf("__LINE__ = %d, error %s\n", __LINE__, strerror(errno));
            return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = (1 == isBlockingMode) ? 1 : 0;            // read doesn't block
        tty.c_cc[VTIME] =  (1 == isBlockingMode)  ? 0 : waitTime;   // in unit of 100 milli-sec for set timeout value

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                printf("__LINE__ = %d, error %s\n", __LINE__, strerror(errno));
                return -1;
        }
        return 0;
}/*SetInterfaceAttribs*/


