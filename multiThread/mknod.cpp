#include<sys/stat.h>

int main (int argc , char** argv){
	
	mknod(argv[1] , S_IFIFO , 0);
	retutn 0;
}
