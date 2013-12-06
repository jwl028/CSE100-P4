#include <iostream>
#include "boggleplayer.cpp"
#include <string>
#include <locale>
#include <set>
#include <vector>

using namespace std;

int main()
{
BogglePlayer player;
string custom1[]={"T","o","T"};
string custom2[]={"a","b","c"};
string custom3[]={"s","c","e"};
string** custom4;

custom4 = new string*[3];
for(unsigned int r=0; r<3;r++) {
  custom4[r] = new string[3];
}
for(int j = 0; j < 3; j++) {
  custom4[0][j] = custom1[j];
  custom4[1][j] = custom2[j];
  custom4[2][j] = custom3[j];
}
player.setBoard(3,3,custom4);
vector<int> test;
test = player.isOnBoard("BCE");

while(!test.empty()){
cout << test.back() << endl;
test.pop_back();
}



string tester = "TEST";
cout << tester.substr(1);
//for(int i = 0; i < 3; i++) {
//for(int j = 0; j < 3; j++) {
//cout << custom4[i][j] << " ";
//}
//cout << "/n";
//}
//}

const set<string>& listwords = "hello";
player.buildLexicon(listwords);

}
