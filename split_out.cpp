#include<iostream>
#include<fstream>
using namespace std;
int main()
{
  ofstream outf("mypipe");
  outf << "This is my clever output" << endl;
  outf << "Here's a bit more for good measure" << endl;
  outf.close();
  return 0;
}
