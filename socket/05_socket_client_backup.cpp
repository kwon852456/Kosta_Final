#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>


#define BUF_LEN 128


using namespace std;
int main(int argc, char **argv)
{
    int sock;
    struct sockaddr_in servaddr;

    char buf[BUF_LEN+1];


    if(argc < 3)
    {
        printf("Usage: %s ip_address port\n", argv[0]);
        return -1;
    }

    if((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0 )
    {
        perror("socket failed !");
        return -1;
    }

    bzero((char*)&servaddr,sizeof(servaddr));
    
    servaddr.sin_family = AF_INET;

    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    servaddr.sin_port = htons(atoi(argv[2]));

    //연결 요청,, 
	    if(connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Connection failed !");
        return -1;
    }
    FILE *fp;

    while(1){
	    cout << "input msg " << endl;
	    cin >> buf;
   	    write(sock , buf , 1024);

	    fp = fdopen(sock,"rw");
	    fflush(fp);
   	 
	// while((nbyte = read(sock , buf , 1024)) > 0 ){
                    // printf("%s" , buf);
            // }
	       		
    }


    puts("Connection Success !");
    close(sock);

    return 0;
}
