/*
 * Declare a min-priority queue of integers.
 * This is a setup fragment with no main function or implemented problem logic.
 */

#include<stdio.h>
#include<queue>

#define MAXSIZE 105
#define DATATYPE int

using namespace std;

priority_queue<DATATYPE, vector<DATATYPE>, greater<DATATYPE> > Q;

