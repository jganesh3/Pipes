#include<iostream>
#include<fstream>
using namespace std;
int main()
{
  string s;
  int counter=1;
  while(!getline(cin, s).eof())
    cout << "Line " << counter++ << ": " << s << endl;
  return 0;
}
