/*
* @Author : Ganesh Joshi
* CSCI 611 Assignment 2
* Date: 02/17/2015
*
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <string>
#include <stdlib.h>
#include<iostream>

using namespace std;

int main(int argc, char*argv[])
{
  string inprog, outprog;
  cout << "What program should spit into the pipe ?";
  getline(cin, inprog);
  cout << "What program should suck from the pipe ?";
  getline(cin, outprog);

  // debug
  //cout<<inprog<<endl;
  //cout<<outprog<<endl;

  int child1_pid, child2_pid;
  int fifofd[2];
  pipe(fifofd); //I now have a parent with a pipe
  //Todo:
  //fork two times.
  //The first child should execlp outprog and spit into pipe.
  //The second child should execlp inprog and suck from the pipe
  //After the forks, the parent should waitpid() two times

  child1_pid=fork();
  if(child1_pid == -1)
  {
    cout<<"Unable to fork 1!!!";
    exit(0);
  }
  if(child1_pid==0){
    //Child process;
    //To write, we need to set the stdout to pipe

    close(fifofd[0]);
    dup2(fifofd[1],1);
    close(fifofd[1]);
    if(execlp(inprog.c_str(),inprog.c_str(),NULL)==-1){
      cout<<"Enable to execute";
      exit(0);
    }

  }else{
    //parent process

      child2_pid=fork();

      if(child2_pid == -1)
      {
        cout<<"Unable to fork 2!!!";
        exit(0);
      }


      if(child2_pid==0){
        //Now read from the pipe
        close(fifofd[1]);
        dup2(fifofd[0],0);
        close(fifofd[0]);

        if(execlp(outprog.c_str(),outprog.c_str(),NULL)==-1){
          cout<<"Enable to execute!!";
          exit(0);
        }

      }


      close(fifofd[0]);
      close(fifofd[1]);
      int status;
      waitpid(child2_pid,&status,0);



  }




  return 0;
}
