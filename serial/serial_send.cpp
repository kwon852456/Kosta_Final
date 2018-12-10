#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <termios.h>
#include <fcntl.h>
#include <iostream>

 
#define BUF_MAX 512
 
using namespace std;
int main( void)
{
    int fd,i=0;
 
    char buf[BUF_MAX];
    char tmp, read_byte=0;
 
    struct termios newtio;
 
 
 
//    fd = open( "/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NONBLOCK );
    fd = open( "/dev/ttyUSB0", O_RDWR | O_NOCTTY );
        if(fd<0) { fprintf(stderr,"ERR\n"); exit(-1); }
 
    memset( &newtio, 0, sizeof(newtio) );
 
 
    newtio.c_cflag = B57600;
    newtio.c_cflag |= CS8;
    newtio.c_cflag |= CLOCAL;
    newtio.c_cflag |= CREAD;
    newtio.c_iflag = IGNPAR;
 //   newtio.c_iflag = ICRNL;
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;
    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN] = 0;
 
    tcflush (fd, TCIFLUSH );
    tcsetattr(fd, TCSANOW, &newtio );
 
sleep(3);
int x = 0 ;
FILE *fp;
while(1) {
 
        write(fd, "2", 10); // 1 : turn cam to left 2: turn cam to right based on servo

	fp = fdopen(fd,"wr");
	fflush(fp);
        // i = read(fd,buf,BUF_MAX);
        // buf[i] = '\0';
        // printf("%s",buf);
	cout << " while()...." << endl;
        sleep(1);
        }
        // close( fd);
	x++;
		if(x > 100){
        		return 0;
		}
}


