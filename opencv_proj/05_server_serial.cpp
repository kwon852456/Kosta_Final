// #include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <fcntl.h>


#define BUF_MAX 512
#define BUF_LEN 128

using namespace std;
int main(int argc, char **argv)
{
    struct sockaddr_in servaddr, cliaddr;
    int sockfd; // socket descripter
    static int acc_sock;   // accept_socket
    char temp[20];
    char buffer[128];
    socklen_t addrlen = sizeof(cliaddr);
    // FILE* F;

    int fd=0;
    // int i = 0;
 
    // char buf[BUF_MAX];
    // char tmp, read_byte=0;
 
    struct termios newtio;
 
    if(argc < 2)
    {
        printf("Usage: %s port \n", argv[0]);
        return -1;
    }

    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket failed !");
        return -1;
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[1])); servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed !");
        return -1;
    }

	listen(sockfd, 3);
	int msg_size;
	puts("Listening.....");
	acc_sock = accept(sockfd, (struct sockaddr*)&cliaddr, &addrlen);

	if(acc_sock < 0)
	{
	    perror("accept failed !");
	    return -1;
	}
	puts("Connected client");

	inet_ntop(AF_INET , &cliaddr.sin_addr,temp,sizeof(temp));
	printf("Server : %s client connected , \n ", temp);

	// FILE* fp;
	fd = open( "/dev/ttyUSB0", O_RDWR | O_NOCTTY );
	// F = fopen( "/dev/ttyUSB0", "rw" );
	if(fd<0) { cout << "error" << endl; return(-1); }
	 
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
	while(1){
	
		while((msg_size = read(acc_sock , buffer , 1024) > 0)){
			// cout << "Msg exists.." << endl;

			// write(fd,buffer,10);
			write(fd,'1',1);
			// fprintf(F,"1");
			
			// fsync(fd);
			// buffer[0] = '\0';
			// write(acc_sock , buffer , 1024);
			// fp = fdopen(sockfd , "rw");
			// fflush(fp);
			// fp = fdopen(fd , "rw");
			// fprintf(fp,"1");
			// fflush(fp);
			// fflush(fp);
			// fsync(sockfd);

		}
	}


	// printf("Server : %s client closed \n ", temp);
	close(acc_sock);
		
	// if((strcmp(buffer," x")) != 0){
		// break;
	// }

    	close(sockfd);
    return 0;
}
