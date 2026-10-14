/*
 * Repeatedly merge the two smallest lengths with a min heap
 * and accumulate a cost of twice their sum for each merge.
 */

#include<iostream>
#include<queue>
#define ull unsigned long long

using namespace std;
priority_queue<ull, vector<ull>, greater<ull> > length;

int main() {
    ull n, temp;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> temp;
        //cout << temp << endl;
        length.push(temp);
    }

    unsigned long long cost = 0, l1, l2;
    for(int i = 0; i < n - 1; i++) {
        l1 = length.top();
        length.pop();
        l2 = length.top();
        length.pop();

        cost += 2 * (l1 + l2);
        length.push(l1 + l2);
    }

    cout << cost;
    return 0;
}