#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include "ArgumentManager.h"
#include "theavl.h"

using namespace std;

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
  const string input = am.get("input");
  const string output = am.get("output");

  /*ifstream inputfile("input9.txt");
  ofstream outputfile("output.txt");*/
  ifstream inputfile(input);
  ofstream outputfile(output);

  if (!inputfile.is_open()) {
    cout << "File not found!" << endl;
    return 0;
  }
  bool isEmpty = inputfile.peek() == EOF;

  string line, theNum;
  int num;
  AVL start;

  if(isEmpty){

  }
  else{
    while(getline(inputfile, line)){
      if(line.empty()){
        continue;
      }
      else{
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());

        if(line.find("Insert") != string::npos){
          theNum = line.substr(7,line.length());
          theNum = theNum.substr(0, theNum.length()-1);
          //cout << theNum << endl;
          num = stoi(theNum);
          start.insert(num);
        }
        else if(line.find("Remove") != string::npos){
          theNum = line.substr(7,line.length());
          theNum = theNum.substr(0, theNum.length()-1);
          //cout << theNum << endl;
          num = stoi(theNum);
          start.remove(num);
        }
      }
    }
  }

  start.print(outputfile);

  
  inputfile.close();
  outputfile.close();

  return 0;
}