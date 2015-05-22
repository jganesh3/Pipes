#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<iostream>
#include <sys/wait.h>
using namespace std;
int main()
{
  int pid=fork();
  if(pid==0) //I am the child
  {
    int fd=open("data.txt", O_RDONLY); //fd==3
    cout << "child process" << endl;
    close(0);//close stdin
    dup2(fd,0);
    close(fd);
    execlp("./stdin_sucker", "./stdin_sucker", NULL);
  }
  else //I am the parent
  {
    cout << "parent process" << endl;
    int status;
    wait(&status); //wait for the child process to finish
    string test_str;
    //Note, the parent's stdin is still the keyboard
    cout << "Enter a string for the parent ";
    getline(cin, test_str);
    cout << "You entered" << test_str << endl;
  }
  return 0;
}
