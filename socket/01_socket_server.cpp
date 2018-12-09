#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>

using namespace std;

int main (int argc , char** argv){

	cout << " argc : " << argc << endl;
	
	struct sockaddr_in servaddr , cliaddr; //실제 네트워크에서 받아올 인터넷 주소
	int sockfd; // 프로그램 내에서 사용할 소켓번호
	int acc_sock;
	socklen_t addrlen = sizeof(cliaddr);


	
	sockfd = socket(PF_INET , SOCK_STREAM , 0); //IPv4 사용 , tcp방식의 소켓생성

	if(sockfd < 0){
		cout << "sockfd filed" << endl;
		return -1;
	}

	servaddr.sin_family = AF_INET;
	cout << " before port " << endl;
	servaddr.sin_port = htons(atoi(argv[1]));
	cout << " after port " << endl;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sockfd , (struct sockaddr*)&servaddr , sizeof(servaddr)) < 0){
		cout << "bind failed" << endl;
		return -1;
	}

	listen(sockfd , 3);
	
	while(1){
		puts("Listening......");

		acc_sock = accept(sockfd , (struct sockaddr*)&cliaddr,(socklen_t*)sizeof(cliaddr));
		if(acc_sock < 0){
			perror("accept failed...!");
			return -1;
		}
		puts("Connected Client...!");
	}

	close(sockfd);
	return 0;
 

	
	
}
