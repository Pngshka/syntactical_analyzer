#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include "analyzer.h"
#include "Hashtable.h"

using namespace std;
HashTable hassh(10);

void main() {
    string s;
    ifstream ifs("C://e//input.txt");

    if (ifs.is_open())
    {
        s.assign((istreambuf_iterator<char>(ifs.rdbuf())), istreambuf_iterator<char>());
        cout << s << endl;
        ifs.close();
    }
    else cerr << "Unable to open file" << endl;
    cout << endl;
    analyzer G(s);
    G.scan(hassh);

    hassh.displayHash();
}

/*
irnt a1bc() {
inst aa, b;
int c;
goto TTT;
asds : goto r;
d = ( h + 1 - ) - 2 ;
gosdsdto F;
return 0;
*/

/*
int abc() {
int a1a, b;
int c;
goto T1TT;
asd : gotio r;
d = ( h + 1 ) + - 2 ;
goto F;
return 0;

*/

/*
int abc() {
int aa, b;
int c;
goto TTT;
asd : goto r;
d = ( h + 1 ) - 2 ;
goto F;
return a;

*/