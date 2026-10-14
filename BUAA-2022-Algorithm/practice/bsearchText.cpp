/*
 * Experiment with lower_bound and upper_bound on sorted arrays,
 * including custom-structure comparisons, and print the resulting indices.
 */

#include<bits/stdc++.h>

using namespace std;
struct pikaqiu{
    int num;
    int cnt;

    bool operator<(const pikaqiu &p){
        return num < p.num;
    }
};

struct Person {
    std::string name;
    int age;
    bool operator<(const Person& other) const {
        return age < other.age;
    }
    bool operator<(const int& other) const {
        return age < other;
    }

    Person() {}
    Person(std::string name, int age) : name(name), age(age){}
};

int a[100000];
pikaqiu b[100000];
int main() {
    Person people[] = {{"Alice", 20}, {"Bob", 22}, {"Charlie", 25}};
    int n = 3;
    Person x = {"Alice", 20};
    auto it = std::lower_bound(people, people + n, 22);
    cout << it - people << endl;


    for(int i = 0; i < 100000; i++) {
        a[i] = i / 3;
        b[i] = {i, 0};
    }
    int input;
    
    sort(b, b + 100000);

    while(1) {
        cin >> input;
        cout << lower_bound(a, a + 100000, input) - a << endl;
        cout << upper_bound(a, a + 100000, input) - a << endl;
        //cout << upper_bound(b, b + 100000, input) - b << endl;
    }
}