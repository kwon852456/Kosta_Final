#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main()
{
    int pid;
    int i , x;

    i = 1000;
    pid = fork();
    if (pid == -1)
    {
        perror("fork error ");
        exit(0);
    }
    else if (pid == 0)
    {
        printf("child: my PID: %d\n", getpid());
        while(1)
        {
            printf("-->%d\n", i);
            i++;
            sleep(1);
        }
    }else if (pid == 1){
	printf ("second : my PID : %d \n",getpid());
	while(1){
		printf("__>%d\n" , x );	
		x++;
		sleep(1);
	}
    
    }
    else
    {
        printf(" parent : my child's PID is %d\n", pid);
        while(1)
        {
           printf("==>%d\n", i);
           i += 4;
           sleep(1);
        }
    }
}
