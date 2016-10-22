#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

const int TEST_DRAW = 100000; //numbers of set to generate to calculate top 5 most common set
const int MAX_DRAW = 10000; //user max number of set user can choose to play/draw
const int RANGE = 57;

double JACKPOT = 300000;
double totalWinning = 0,
	totalTakeHome  = 0;

void drawProgress(int index);
void putTopToUser(vector<vector<int>> &user, int menuChoice, vector<vector<int>> &top5nums);
int getChoiceMenu();
void topGenerateManager(vector<vector<int>> &top5nums);
void displayChoiceMenu(vector<vector<int>> &arr);
void calculateTop5s(vector<vector<int>> &top5nums, vector<vector<int>> &draws);
void calculateTop5Col(int coln, int tempCol[5], vector<vector<int>> &draws);
void sortOccur(int occur[RANGE], int occurIndex[RANGE]);
bool checkDupAmongSet(vector<int> arr, vector<vector<int>> &all);
bool checkDupWithinSet(vector<int> &arr);
int findSize(vector<vector<int>> &all);
void startInfo(int set, int draw);
void disclaimer();
void test(int arr[7][6], int limit);
void displayTotal(int cost);
//void singleDraw(vector<int> winningNum, int draw, int user[3][6], int set);
void singleDraw(vector<int> &winningNum/*int winningNum[6]*/, int draw, vector<vector<int>> &user/*int user[3][6]*/, int set);
void drawTitle(int index);
//void calcWin(int winningNum[6], int user[6], int &numWin1, int &numWin2, int &winningAmount);
void calcWin(vector<int> &winningNum, vector<int> &user/*int user[6]*/, int &numWin1, int &numWin2, int &winningAmount);
int calcPrize(int numWin1, int numWin2);
//void getNumberForSets(int user[3][6], int set);
void getNumberForSets(vector<vector<int>> &user/*int user[3][6]*/, int set);
void clear();
void test(int arr[7][6]);
int getSetNum();
//int getNormalNum(int num, int arr[6]);
int getNormalNum(int num, vector<int> &arr/*int arr[6]*/);
bool checkDuplicate(vector<int> &arr, int val, int subscriptUpTo);
int getMegaballNum();
int getDrawNum();
//void drawGenerator(int arr[7][6], int draws);
void drawGenerator(vector<vector<int>> &arr/*int arr[MAX_DRAW][6]*/, int draws);
void generateFive(vector<int> &arr/*int arr[6]*/);
int generateNormalNum();
bool checkCompDuplication(int arr[5], int subscript, int val);
int generateMegaballNum();
int calcNetPrize(int arr[6], int user[3][6], int draws, int set);
void pause();
//bool checkDup(int arr[6]);
bool checkDup(vector<int> &arr,vector<vector<int>> &all);
bool linearSearch(int value, vector<int> &list/*int list[]*/, int skip, int numElems);
void clearScreen();
void makeSpace();
void displayWinningNum(int arr[6]);