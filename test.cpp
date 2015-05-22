#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include<iostream>

int main(int argc, char* argv[])
{
     int f1[2];
     char buff;

     if(pipe(f1) != -1)
          //cout<<"Pipe1 allright! \n";

     int pid = fork();
     if(pid==0)
     {
          close(1);
          dup(f1[1]);

          close(f1[0]);
          close(f1[1]);

          close(0);
          execlp("ls", "ls", "-l", NULL);
     }
     //cout<<"ls-pid = %d\n";

     int f2[2];
     if(pipe(f2) != -1)
          //cout<<"Pipe2 allright \n";

     pid = fork();
     if(pid==0)
     {
          close(0);
          dup(f1[0]);

          close(f1[0]);
          close(f1[1]);

          close(1);
          dup(f2[1]);

          close(f2[0]);
          close(f2[1]);

          execlp("grep", "grep", "^d", NULL);
          // system("strace grep '^d'"); exit(0);
     }
     //printf("grep-pid = %d\n", pid);

     close(f1[0]);
     close(f1[1]);

     pid = fork();
     if(pid==0)
     {
          close(0);
          dup(f2[0]);
          close(f2[0]);
          close(f2[1]);

          execlp("wc", "wc", "-l", NULL);
     }
     //printf("wc-pid = %d\n", pid);

     close(f2[0]);
     close(f2[1]);
}
