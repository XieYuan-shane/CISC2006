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
    int i = 0; // 主串的位置
    int j = 0; // 模式串的位置

    while(i < T.size() && j < P.size()){
        if(T[i] == P[j]){
            i ++;
            j ++;
        }
        else {
            j = 0;
            i = i - j + 1;
        }
    }
    if( j == P.size()){
        return i - j;
    }
    else return -1;
}

void computeFailureFunction(string P, int* f)  // compute the failure function on P
{
	int pLen = P.size();
	f[0] = 0;//起始值，f[0] = 0;
	int j = 0;
	int i = 1;
	while (i < pLen )
	{
		//p[k]表示前缀，p[j]表示后缀  
		if (P[j] == P[i])
		{   
			f[i] = j + 1; 
            ++j;
			++i;
		}
        else if (j == 0){
            f[i] = 0;
            ++i;
        }
		else
		{
			j = f[j - 1];
		}
	}
}

int KMP(string T, string P)
{
    int lenT = T.size(), lenP = P.size();
    int f[lenP];
    int i = 0, j = 0;
    computeFailureFunction(P, f);
	while (i < lenT && j < lenP)
	{
		//当前字符匹配成功（即T[i] == P[j]），都令i++，j++    
		if (T[i] == P[j])
		{
			i++;
			j++;
		}
        else if(j == 0){
            i++;
        }
        else
		{
			 
			j = f[j - 1];
		}
	}
	if (j == lenP)
		return i - j;
	else
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

