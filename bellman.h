#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
using namespace std;

char getCharVertex(int);
int getIntVertex(char);

void copyBFValueToBFValuePrev(int[20], int[20]);
void BF(int[20][20], int, char, int[20], int[20]);
string BF_Path(int[20][20], int, char, char);
