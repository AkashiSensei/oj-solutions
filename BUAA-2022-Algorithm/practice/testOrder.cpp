/*
 * Demonstrate randomized quickselect on a generated array:
 * read a one-based rank and print the corresponding smallest element.
 */

#include <bits/stdc++.h>
using namespace std;

int random_partition(int a[],int p,int r)
{
	int ra=rand()%(r+1-p)+p;
	std::swap(a[ra],a[r]);
	int x=a[r];
	int i=p-1;
	for(int j=p;j<r;j++)
		if(a[j]<=x)
			std::swap(a[++i],a[j]);
	std::swap(a[i+1],a[r]);
	return i+1;
}
int random_select(int a[],int p,int r,int i)
{
	if(p==r)
		return a[p];
	int q=random_partition(a,p,r);
	int k=q-p+1;
	if(i==k)
		return a[q];
	else if(i<k)
		return random_select(a,p,q-1,i);
	else 
		return random_select(a,q+1,r,i-k);
}

int vectorInt[100000];

int main() {
	for(int i = 0; i < 10000; i++) {
		vectorInt[i] = i + 10000;
	}

	for(int i = 10000; i < 20000; i++) {
		vectorInt[i] = i - 10000;
	}

	int input;
	cin >> input;
	cout << random_select(vectorInt, 0, 19999, input) << endl;
}
