#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include <time.h>

using namespace std;

int BruteForce(string T, string P)   // T is text string, P is pattern string
{


    return -1;
}

void computeFailureFunction(string P, int* f)  // compute the failure function on P
{

}

int KMP(string T, string P)
{
    int lenT = T.size(), lenP = P.size();
    int f[lenP];
    int i = 0, j = 0;
    computeFailureFunction(P, f);

    return -1;
}

int main() {
    clock_t Start_time, End_time;
    const int n = 200000, t = 8;
    string str;
    string p[t] = {"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBCCCCCCCCCCCCCCC",
                   "FJZRVSAMACSRXNTGGVVKTFXBWYDTQJMJTF",
                   "CCCCCCCCCCCCCCCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBB",
                   "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBCCCCCCCCCZYOENZLXS",
                   "AAAAAAAAAAAAAAAAAAAAAAAAABC",
                   "NWYWCRGBGECHHROVBRHLJXHLHPPLAYOLJO",
                   "AAABBBBBBCCCCCCCCCCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBCCCCCCCCCCAAA",
                   "AAABBBBBBCCCCCCCCCCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBCCCCCCCCCCAAB"
    };

    ifstream arr;
    arr.open("string.txt");
    if (!arr) {
        cout << "Unable to open file !"<<endl;
        return -1;
    }

    char c;
    int k = 0, result;
    while (arr >> c) {  // load string from input file
        str += c;
        k++;
    }
    cout << "Reading of string T finished. Length = " << k << endl;

    for(int i = 0; i < t; i++){
        cout << "\n-------String Matching (Round-" << i+1 << ")-------" << endl;
        cout << "P = " << p[i] << endl << endl;

        cout << "using BruteForce algorithm" << endl;
        Start_time = clock();
        result = BruteForce(str, p[i]);
        if(result == -1)
            cout << " P is not a sub-string of T" << endl;
        else
            cout << " P = T[" << result << ", " << result+p[i].size()-1 << "]" << endl;
        End_time = clock();
        cout<<" running time: "<<static_cast<double>(End_time-Start_time)/CLOCKS_PER_SEC*1000<<" ms"<<endl;

        cout << "using KMP algorithm" << endl;
        Start_time = clock();
        result = KMP(str, p[i]);
        if(result == -1)
            cout << " P is not a sub-string of T" << endl;
        else
            cout << " P = T[" << result << ", " << result+p[i].size()-1 << "]" << endl;
        End_time = clock();
        cout<<" running time: "<<static_cast<double>(End_time-Start_time)/CLOCKS_PER_SEC*1000<<" ms"<<endl;
    }

    return 0;
}

