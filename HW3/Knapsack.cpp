#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include <time.h>

using namespace std;

struct Item
{
    int id;
    int val;
    int size;
};

void Knapsack_DP(Item items[], int n, int C)//c是最大存储量，n是item的数量
{
     int i, j, dp[n + 1][C + 1];
    bool t[n + 1][C + 1]; // direction of recursion, True means selecting the item
    int solution[n + 1]; // the collection of items in the solution
    if (C <= 0 || n <= 0) {
        return ;
    }
    for(int i = 0; i < n + 1; i++)
        dp[i][0] = i;//初始化，第一竖行为item的值
    for(int i = 1; i < C+1; i++){
        dp[0][i] = i;//初始化，第一行为capacity
        if(dp[0][i] >= items[0].size){
            dp[1][i] = items[0].val;
            t[1][i] = true;
        }
        else{
            dp[1][i] = 0;
            t[1][i] = false;
        }      
    }
       
    for(int i = 2; i < (n + 1); i++){//因为dp[0][j]是C，dp[i][j]与i=0时候比较是错误的，所以i必须大于等于2
        for(int j = 1; j < (C + 1); j++){
            if(dp[0][j] > items[dp[i][0]-1].size)
                    dp[i][j] = max((dp[i-1][dp[0][j]-items[dp[i][0]-1].size]+items[dp[i][0]-1].val),dp[i-1][j]);
            else if(dp[0][j] == items[dp[i][0]-1].size)//如果不排除这种情况，上面会出现j == 0的时候出现错误
                    dp[i][j] = max(items[dp[i][0]-1].val,dp[i-1][j]);
            else 
                    dp[i][j] = dp[i-1][j];
        }
    }
    //判断Y还是N
    for(int i = 2;i < (n + 1);i++){
        for(int j = 1 ; j < (C + 1);j++){
            if(dp[i][j] == dp[i-1][j]){
                t[i][j] = false;
            }
            else 
                t[i][j] = true;
        }
    }
    //此处用于回溯
    int y = C ;
    int x = n ;
    int k = 0;
    while(x > 0){
        if(t[x][y] == true){
            solution[k++] = items[x-1].id;
            y = dp[0][y] - items[x-1].size;
            if(y == 0)
                break;
        }
        x = x - 1;
    }
    cout << "The solution is: ";

    sort(solution, solution + k);
    for(i = 0; i < k; i++){
        cout << solution[i] << " ";
    }
    cout << endl;
    cout << "The objective is: " << dp[n][C] << endl;
}

bool cmp_value(Item a, Item b){
    if(a.val != b.val)
        return a.val > b.val;
    return a.size < b.size;
}

bool cmp_size(Item a, Item b){
    if(a.size != b.size)
        return a.size < b.size;
    return a.val > b.val;;
}

bool cmp_density(Item a, Item b){
    if(a.val/a.size != b.val/b.size)
        return a.val/a.size > b.val/b.size;
    return a.size < b.size;
}

void GreedyMaxValue(Item items[], int n, int C){
    int i, j = 0;
    int c = C, k = 0, total_val = 0;
    int solution[n];

    sort(items, items + n, cmp_value);

    while(j < n){
        if(c >= items[j].size){
            solution[k++] = items[j].id;
            total_val += items[j].val;
            c -= items[j].size;
        }
        j++;
    }
    cout << "The solution is: ";

    sort(solution, solution + k);
    for(i = 0; i < k; i++){
        cout << solution[i] << " ";
    }
    cout << endl;
    cout << "The objective is: " << total_val << endl;
}

void GreedyMinSize(Item items[], int n, int C){
    sort(items, items + n, cmp_size);
    int i, j = 0;
    int c = C, k = 0, total_val = 0;
    int solution[n];

    while(j < n){
        if(c >= items[j].size){
            solution[k++] = items[j].id;
            total_val += items[j].val;
            c -= items[j].size;
        }
        j++;
    }
    cout << "The solution is: ";

    sort(solution, solution + k);
    for(i = 0; i < k; i++){
        cout << solution[i] << " ";
    }
    cout << endl;
    cout << "The objective is: " << total_val << endl;

}

void GreedyMaxDensity(Item items[], int n, int C){
    sort(items, items + n, cmp_density);
    int i, j = 0;
    int c = C, k = 0, total_val = 0;
    int solution[n];

    while(j < n){
        if(c >= items[j].size){
            solution[k++] = items[j].id;
            total_val += items[j].val;
            c -= items[j].size;
        }
        j++;
    }
    cout << "The solution is: ";

    sort(solution, solution + k);
    for(i = 0; i < k; i++){
        cout << solution[i] << " ";
    }
    cout << endl;
    cout << "The objective is: " << total_val << endl;
}


int main() {
    clock_t Start_time, End_time;
    const int n = 100; // n items, capacity = 300
    int length, C = 300;

    int total = 2, i = 1;
    while(i <= total) {
        string filename = "input" + to_string(i) + ".txt";
        cout << endl << "-------------------The result for " + filename + "-------------------" << endl << endl;

        ifstream arr;
        arr.open(filename);
        i++;

        if (!arr) {
            cout << "Unable to open file !" << endl;
            return -1;
        }
        int id, value, size;
        struct Item items[n];
        int k = 0;
        while (arr >> id >> value >> size) {
            items[k].id = id;
            items[k].val = value;
            items[k].size = size;
            k++;
        }

        length = k;
        cout << "Reading of array finished, " << length << " items found." << endl;

        cout << "\n-------Knapsack using Dynamic Programming-------" << endl;
        Start_time = clock();
        Knapsack_DP(items, length, C);
        End_time = clock();
        cout << "The running time is: " << static_cast<double>(End_time - Start_time) / CLOCKS_PER_SEC * 1000 << " ms"
             << endl;

        cout << "\n-------Knapsack using Greedy with maximum value first------" << endl;
        Start_time = clock();
        GreedyMaxValue(items, length, C);
        End_time = clock();
        cout << "The running time is: " << static_cast<double>(End_time - Start_time) / CLOCKS_PER_SEC * 1000 << " ms"
             << endl;

        cout << "\n-------Knapsack using Greedy with minimum size first------" << endl;
        Start_time = clock();
        GreedyMinSize(items, length, C);
        End_time = clock();
        cout << "The running time is: " << static_cast<double>(End_time - Start_time) / CLOCKS_PER_SEC * 1000 << " ms"
             << endl;

        cout << "\n-------Knapsack using Greedy with maximum density first------" << endl;
        Start_time = clock();
        GreedyMaxDensity(items, length, C);
        End_time = clock();
        cout << "The running time is: " << static_cast<double>(End_time - Start_time) / CLOCKS_PER_SEC * 1000 << " ms"
             << endl;
    }
    return 0;
}
