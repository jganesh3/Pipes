#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<iostream>

using namespace std;
// 0 stdin
// 1 stdout
// 2 stderr
int main()
{
  int mydescriptors[2];
  int result=pipe(mydescriptors);
  //  mydescriptors[0]; //input. Suck from this.
  //  mydescriptors[1];  //output. Spit in this.
  if(result != 0)
    cerr << "ouch";
  int pid=fork();

  if(pid==0)//I am the child
  {
    close(1);
    //close(mydescriptors[0]);
    write(mydescriptors[1], "Hello", 5);
  }
  else  // I am the parent
  {
    close(1);
    char what_was_spit[6];
    read(mydescriptors[0], what_was_spit, 5);
    what_was_spit[5]='\0'; //cap my C-style string with a null character.
    cout << "The child said: " << what_was_spit << endl;
  }

  return 0;
}
