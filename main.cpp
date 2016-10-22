/*
 Author: Qi Mu
 Date: Dec 3 - Dec 5, 2011
 Description: Mega million stimulation program
 */


#include "main.h"

//for testing purpose
//ifstream input("input.txt");

int main()
{
    disclaimer();
    char again;
    
    do{
        srand(time(0));
        int set,
        draw;
        
        vector<vector<int>> top5nums(5, vector<int>(6));
        cout << "Calculating top 5 sets most frequent numbers from " << TEST_DRAW << " sets. Please wait...\n";
        topGenerateManager(top5nums);
        
        vector<vector<int>> user(3, vector<int>(6)); //for storing user's set
        vector<vector<int>> computer(MAX_DRAW, vector<int>(6)); //winning numbers
        
        cout << setprecision(2) << showpoint << fixed;
        cout << "\n\t---- Jackpot is: $" << JACKPOT << " ----" << endl << endl;
        
        //display these top 5 numbers
        int menuChoice;
        cout << "You can choose 5 numbers generated by computer, or make you own choice: \n";
        displayChoiceMenu(top5nums);
        menuChoice = getChoiceMenu();
        if (menuChoice >= 1 && menuChoice <= 5)
        {
            set = 1;
            putTopToUser(user, menuChoice, top5nums);
            
        }
        else
        {
            //enter set number
            set = getSetNum();
            
            //enter number for every set
            getNumberForSets(user, set);
            
        }
        
        //get number of draws from user
        draw = getDrawNum();
        //draw = MAX_DRAW;
        
        //display how many draws and set will be playing
        startInfo(set, draw);
        cout << endl;
        
        cout << "Intializing winning number. Please wait...\n";
        //generate computer draws
        drawGenerator(computer, draw);
        
        //test(computer, draw);
        
        //display and cal info for every draw
        for (int index = 0; index < draw; index++)
        {
            singleDraw(computer[index], index, user, set);
        }
        
        int cost = set * draw;
        displayTotal(cost);
        
        cout << "Would you like to play again? (Y/N): ";
        cin >> again;
        clear();
        cout << endl;
        cout << "Clearing array... Please wait.\n";
        
    } while (again == 'Y' || again == 'y');
    
    cout << "\nThank you so much for playing! Bye!\n";
    
    pause();
    return 0;
    
}

void putTopToUser(vector<vector<int>> &user, int menuChoice, vector<vector<int>> &top5nums)
{
    for (int col = 0; col < 6; col++)
    {
        user[0][col] = top5nums[menuChoice - 1][col];
    }
}

int getChoiceMenu()
{
    int choice;
    do {
        cin >> choice;
        clear();
        if (!(choice >= 1 && choice <= 6))
            cout << "Invalid input.\n";
        else
            break;
    } while (1);
    
    return choice;
}

void topGenerateManager(vector<vector<int>> &top5nums)
{
    // generate test draws
    vector<vector<int>> testDraw(TEST_DRAW, vector<int>(6));
    //generate many draws for counting top 5 most common number in each col
    drawGenerator(testDraw, TEST_DRAW);
    
    //calculate top 5 numbers for every column
    calculateTop5s(top5nums,testDraw);
}

void displayChoiceMenu(vector<vector<int>> &arr)
{
    for (int index = 0; index < 5; index++)
    {
        cout << index + 1 << ". ";
        for (int col = 0; col < 6; col++)
            cout << arr[index][col] << " ";
        if (checkDupWithinSet(arr[index]))
            cout << "[Invalid set]";
        cout << endl;
    }
    cout << "6. Enter your own choice.\n";
}

void calculateTop5s(vector<vector<int>> &top5nums, vector<vector<int>> &draws)
{
    //every iteration complete a col
    for (int col = 0; col < 6; col++)
    {
        int tempCol[5];
        calculateTop5Col(col, tempCol, draws);
        //put tempCol to final array
        for (int row = 0; row < 5; row++)
        {
            top5nums[row][col] = tempCol[row];
        }
    }
}

void calculateTop5Col(int coln, int tempCol[5], vector<vector<int>> &draws)
{
    
    int occur[RANGE] = {0};
    int occurIndex[RANGE] = {0};
    
    //put occurIndex from 1 to 56
    for (int index  = 0; index < RANGE; index++)
    {
        occurIndex[index] = index;
    }
    
    //occur 0 to 55, store the number of subscripts occur
    for (int row = 0; row < 20; row++)
    {
        occur[draws[row][coln]]++;
    }
    
    //descending sort, move along the occurIndex
    sortOccur(occur, occurIndex);
    
    
    for (int col = 0; col < 5; col++)
    {
        tempCol[col] = occurIndex[col];
    }
}

void sortOccur(int occur[RANGE], int occurIndex[RANGE])
{
    int size = RANGE;
    //selection sort, descending
    int startScan, maxIndex, maxOccur;
    int maxOccurIndex;
    
    for (startScan = 0; startScan < (size - 1); startScan++)
    {
        maxIndex = startScan;
        maxOccur = occur[startScan];
        maxOccurIndex = occurIndex[startScan];
        
        for (int index = startScan + 1; index < size; index++)
        {
            if (occur[index] > maxOccur)
            {
                maxOccur = occur[index];
                maxOccurIndex = occurIndex[index];
                maxIndex = index;
            }
        }
        occur[maxIndex] = occur[startScan];
        occurIndex[maxIndex] = occurIndex[startScan];
        occur[startScan] = maxOccur;
        occurIndex[startScan] = maxOccurIndex;
    }
    
}

void displayWinningNum(int arr[6])
{
    cout << "\t ----Winning number-----\n";
    cout << "\t|  ";
    for (int i = 0; i < 6; i++)
    {
        cout << setw(2) << arr[i] << " ";
    }
    cout << "\t|\n";
    cout << "\t -----------------------\n";
}

void displayTotal(int cost)
{
    cout << setprecision(2) << fixed;
    cout << "        * * * * * * * *\n\n";
    cout << "Cost of Playing: \t\t\t$" << cost << endl << endl
    << "Grand Total Winning: \t\t\t$" << totalWinning << endl
    << "Grand Total Taxes <30%>: \t\t$" << totalWinning * 0.3 << endl
    << "Grand total Takehome: \t\t\t$" << totalTakeHome << endl << endl;
    cout << "        * * * * * * * *\n\n";
    
    //add 50% of the cost of playing to jackpot
    JACKPOT += (static_cast<double>(cost) * 0.5);
}

void singleDraw(vector<int> &winningNum/*int winningNum[6]*/, int draw, vector<vector<int>> &user/*int user[3][6]*/, int set)
{
    //drawTitle(draw);
    //displayWinningNum(winningNum);
    int numWin1, numWin2, winningAmount, total = 0;;
    //for every set
    for (int index = 0; index < set; index++)
    {
        calcWin(winningNum, user[index], numWin1, numWin2, winningAmount);
        /*cout << "Your set #" << index + 1 << " Winning: "
         << numWin1 << " Out of Five, "
         << numWin2 << " Out of One." << endl
         << "Set #" << index+1 << " Winning this draw: \t\t$" << winningAmount << endl;*/
        total += winningAmount;
    }
    //cout << "-----------------------------------------------------\n";
    int tax = total * 0.3;
    int takeHome = total - tax ; /*
                                  cout << "Draw #" << draw + 1 << " Sub Total Win: \t\t\t$" << total << endl
                                  << "Giving Uncle Sam his share of 30%: \t$" << tax << endl
                                  << "Your total TakeHome of this draw: \t$" << takeHome << endl << endl << endl;*/
    
    //add to global variable
    totalWinning += total;
    totalTakeHome += takeHome;
    
    //pause();
}

void drawTitle(int index)
{
    index++;
    cout << "\t******************\n"
    << "\t**    Draw #" << index << "   **\n"
    << "\t******************\n\n";
}

void calcWin(vector<int> &winningNum, vector<int> &user/*int user[6]*/, int &numWin1, int &numWin2, int &winningAmount) {
    numWin1 = 0, numWin2 = 0;
    for (int index = 0; index < 5; index++)
    {
        if (winningNum[index] == user[index])
            numWin1++;
    }
    if (winningNum[5] == user[5])
        numWin2++;
    winningAmount = calcPrize(numWin1, numWin2);
}

int calcPrize(int numWin1, int numWin2)
{
    int winningAmount = 0;
    if (numWin1 == 5 && numWin2 == 1)
        winningAmount = JACKPOT;
    else if (numWin1 == 5 && numWin2 == 0)
        winningAmount = 250000;
    else if (numWin1 == 4 && numWin2 == 1)
        winningAmount = 10000;
    else if (numWin1 == 4 && numWin2 == 0)
        winningAmount = 150;
    else if (numWin1 == 3 && numWin2 == 1)
        winningAmount = 150;
    else if (numWin1 == 3 && numWin2 == 0)
        winningAmount = 7;
    else if (numWin1 == 2 && numWin2 == 1)
        winningAmount = 10;
    else if (numWin1 == 1 && numWin2 == 1)
        winningAmount = 3;
    else if (numWin1 == 0 && numWin2 == 1)
        winningAmount = 2;
    
    return winningAmount;
}

void getNumberForSets(vector<vector<int>> &user/*int user[3][6]*/, int set)
{
    for (int index = 0; index < set; index++)
    {
        cout << "Numbers for set #" << index + 1 << ": (1 - 56)\n";
        //enter 5 number
        for (int num = 0; num < 5; num++)
            user[index][num] = getNormalNum(num,user[index]);
        //enter megaball number
        user[index][5] = getMegaballNum();
    }
}

void disclaimer()
{
    cout << "\n\n\n";
    cout << "\t   Simulation of Mega Millions lottery game (MA)\n\n"
    << "\tQi Mu\n"
    << "\t2011\n"
    << "\t\t\t     Disclaimer\n"
    << "\t----------------------------------------------------\n"
    << "\t* This is not an actual lottery game\n"
    << "\t* This simulation has no affiliation with the actual\n"
    << "\t  Massachusetts Mega Millions lottery game\n"
    << "\t* This simulating is for educational purpose only\n\n";
    
}

void startInfo(int set, int draws)
{
    cout << "\n\tYou will be playing with " << set << " set of number for " << draws << " draws.\n\n";/*
                                                                                                       << "                       --  Instructions -- \n\n"
                                                                                                       << "\tFor every set:\n"
                                                                                                       << "\tChoose 5 different numbers from the range 1 to 56.\n";
                                                                                                       cout << "\tthen choose 1 number from 1 to 46 (Megaball number).\n\n";*/
}

void clear()
{
    cin.clear();
    cin.ignore();
}
//test user array, delete later on
void test(int arr[MAX_DRAW][6], int limit)
{
    cout << "\n\t\t -------Draws generated---------\n";
    for (int i = 0; i < limit; i++)
    {
        cout << "\t\t|  ";
        for (int j = 0; j < 6; j++)
        {
            cout << setw(2) << arr[i][j] << " ";
        }
        cout << "\t\t|" << endl;
    }
    cout << "\t\t -------------------------------\n";
}
//get a value from 1 to 3
int getSetNum()
{
    int num;
    bool error = true;
    do{
        cout << "The number of set you would like to play? (1 - 3): ";
        cin >> num;
        clear();
        if (num < 1 || num > 4)
        {
            cout << "Error, invalid number.\n";
        }
        else
            error = false;
        
    } while (error);
    
    return num;
}
//get a value 1 to 56
int getNormalNum(int num, vector<int> &arr/*int arr[6]*/)
{
    int val;
    bool error = true;
    
    do {
        cout << "No. " << num+1 << " of 6: ";
        //input >> val;
        cin >> val;
        clear();
        if (val < 1 || val > 56)
            cout << "Error, nvalid number.\n";
        else if (checkDuplicate(arr, val, num))
            cout << "The number cannot be same as the previous number.\n";
        else
            error = false;
    } while (error);
    
    return val;
}

bool checkDuplicate(vector<int> &arr/*int arr[6]*/, int val, int subscriptUpTo)
{
    bool haveSame = false;
    for (int index = 0; index < subscriptUpTo; index++)
    {
        if (arr[index] == val)
            return true;
    }
    return haveSame;
}
//get a value from 1 to 46
int getMegaballNum()
{
    int val;
    bool error = true;
    
    do {
        cout << "No. 6 of 6 (Megaball): ";
        //input >> val;
        cin >> val;
        clear();
        if (val < 1 || val > 46)
            cout << "Error, nvalid number.\n";
        else
            error = false;
    } while (error);
    
    return val;
}
//get a value from 1 to 7
int getDrawNum()
{
    int val;
    bool error = true;
    
    do {
        cout << "The number of your draws (1 - " << MAX_DRAW << "): ";
        cin >> val;
        clear();
        if (val < 1 || val > 100000)
            cout << "Error, nvalid number.\n";
        else
            error = false;
    } while (error);
    
    return val;
}
//generate random number of n sets

void drawGenerator(vector<vector<int>> &arr, int draws)
{
    int index;
    //for every set user specified
    for (index = 0; index < draws; index++) {
        
        //display progression information
        drawProgress(index);
        
        bool haveDup = true;
        //if generated 5 number have duplication, generate again, until no duplicated number in a set
        do {
            generateFive(arr[index]);
            if (checkDupWithinSet(arr[index]) && checkDupAmongSet(arr[index], arr))
                haveDup = true;
            else
                haveDup = false;
        } while (haveDup);
        
        arr[index][5] = generateMegaballNum();
    }
    drawProgress(index);
    
    cout << endl << endl;
}

void drawProgress(int index)
{
    if (index % 100 == 0) 
    {
        cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
        cout << "\t Set generated: " << setw(4) << index;
    }
}

bool checkDupAmongSet(vector<int> arr, vector<vector<int>> &all)
{
    int size = findSize(all);
    for (int i = 0; i < size - 1; i++)
    {
        if (arr == all[i])
            return true;
    }
    return false;
    
}

int findSize(vector<vector<int>> &all)
{
    for (int i = 0; ; i++)
    {
        if (all[i][0] == 0)
            return i;
    }
}

bool checkDupWithinSet(vector<int> &arr)
{
    bool dup = false;
    for (int index = 0; index < 5; index++)
    {
        if (linearSearch(arr[index], arr, index, 6))
            dup = true;
    }
    return dup;
}

bool linearSearch(int value, vector<int> &list/*int list[]*/, int skip, int numElems)
{
    int index = 0;
    bool found = false;
    
    while (index < numElems && !found)
    {
        if (index != skip)
        {
            if (list[index] == value)
            {
                found = true;
            }
        }
        index++;
    }
    return found;
    
}
void generateFive(vector<int> &arr/*int arr[6]*/){
    for (int index = 0; index < 5; index++)
        arr[index]= generateNormalNum();
    
}
//return a value from 1 to 56
int generateNormalNum()
{
    int val = rand() % 56 + 1;
    
    return val;
}

//return a value from 1 to 46
int generateMegaballNum()
{
    return rand() % 46 + 1;
}
//compare winning number from computer with user's input, and return prize amount
int calcNetPrize(int arr[6], int user[3][6], int draws, int set)
{
    return 0;
}
void pause()
{
    cout << endl;
    cout << "Press Enter key to continue...";
    //cin.ignore();
    cin.get();
    cout << endl;
}
void makeSpace()
{
    for (int index = 0; index < 8; index++)
        cout << endl;
}