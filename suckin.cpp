#include<iostream>
#include<fstream>
using namespace std;
int main()
{
  ifstream inf("mypipe");
  string s;
  int counter=1;
  while(!getline(inf, s).eof())
    cout << "Line " << counter++ << ": " << s << endl;
  return 0;
}
