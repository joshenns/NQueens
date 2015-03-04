/* 
 * ids.cc
 * Joshua Enns
 * CPSC 3750 Assignment 2
 * Iterative deepening implementation
 */


#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
const int N = 8;
using namespace std;

struct state
{
  int board[N][N];
};

/*
 * function initializeBoard
 * set the entire NxN board to 0
 */
void initializeBoard(state *s)
{
  int i, j;
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      s->board[i][j] = 0;
    }
  }
}

/*
 * function printBoard
 * prints the board to the console
 */
void printBoard(state s){
  int i, j;
  for(i=0;i<N;i++){
    cout << "\nrow" << i << " : ";
    for(j=0;j<N;j++){
      cout << s.board[i][j];
    }
  }
}

/*
 * Function newStates
 * find the first row that has no queens and 
 * insert N new states into the frontier, one
 * for every column.
*/
void newStates(state s, stack<state> *frontier, int depth)
{
  int i, j, k, l;
  depth++;
  //loop through board
  for (i=0;i<depth;i++){
    k=1;
    for (j=0;j<N;j++){
      //if the tile has a queen, set k=0
      if (s.board[i][j] == 1) 
      {
        k=0;
      }
      //if the row has no queen, insert a queen
      if(j==N-1 && k==1 && j==N-1)
      {
        for (l=0;l<N;l++)
        {
          //insert queen and push to frontier
          s.board[i][l] = 1;
          frontier->push(s);
          //reset board to prevent duplicate queens
          s.board[i][l] = 0;
        }
        return;
      }
    }
  }
}

/*
 * function isGoal
 * loop through board and check that no two queens
 * attack each other
 */
bool isGoal (state s)
{
  //initialize local variables
  int i,j, x, y, queens;
  int temp = 0;
  bool returnVal = true;
  queens = 0;
  //loop through the board to look for queens
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      //if there is a queen...
      if (s.board[i][j] == 1)
      {
        //increment queen count
        queens++;
        x=i-1;
        y=j;
        //check top
        while (x > 0){
          if (s.board[x][j] == 1){
            returnVal = false;
          }
          x--;
        }
        //check bottom
        x=i+1;
        y=j;
        while (x < N) {
          if (s.board[x][j] == 1){
            returnVal = false;
          }
          x++;
        }
        //check left
        x=i;
        y=j-1;
        while (y > 0){
          if (s.board[i][y] == 1){
            returnVal = false;
          }
          y--;
        }
        //check right
        x=i;
        y=j+1;
        while (y < N){
          if (s.board[i][y] == 1){
            returnVal = false;
          }
          y++;
        }
        //check diagonal
        x=i+1;
        y=j+1;
        while(x<N && y<N){
          if(s.board[x][y]==1){
            returnVal = false;
          }
          x++;
          y++;
        }
        x=i-1;
        y=j+1;
        while(x>=0 && y<N){
          if(s.board[x][y]==1){
            returnVal = false;
          }
          x--;
          y++;
        }
        x=i-1;
        y=j-1;
        while(x>=0 && y>=0){
          if(s.board[x][y]==1){
            returnVal = false;
          }
          x--;
          y--;
        }
        x=i+1;
        y=j-1;
        while(x<N && y>=0){
          if(s.board[x][y]==1){
            returnVal = false;
          }
          x++;
          y--;
        }
      }
    }
  }
  //if there are N queens and none conflict with each other return true
  if ((queens == N) && (returnVal==true)) {
    returnVal = true;
  } else {
    returnVal = false;
  }
  return returnVal;
}

int main()    
{
  //intitialize local variables
  int start_s=clock();
  int i, j, maxSize, depth;
  int count = 0;
  j=0;
  //create empty NxN board
  state s;
  stack<state> frontier;

  //loop through the frontier
  for (depth=0;depth<N;depth++){
    cout << "\nChecking depth " << depth << "...";
    initializeBoard(&s);
    frontier.push(s);
    while (!frontier.empty())
    {
      if (frontier.size()>maxSize){
        maxSize = frontier.size();
      }
      count++;
      s = frontier.top();
      if(isGoal(s))
      {
        cout << "\nSolution:";
        printBoard(s);
        int stop_s=clock();
        cout << "\nTime taken: " << ((stop_s-start_s)/double(CLOCKS_PER_SEC)*1000) << "ms\n";
        cout << "\nNodes Visited: " << count;
        cout << "\nMax Frontier: " << maxSize << "\n";
        return 0;
        /* commented code is used for finding all possible solutions */
        // j++;
        // int stop_s=clock();
        // cout << "\nSolutions so far: " << j;
        // cout << "\ntime so far: " << (abs((start_s-stop_s)/double(CLOCKS_PER_SEC)));
        // if (abs((start_s-stop_s)/double(CLOCKS_PER_SEC))>3600){
        //   cout << "HALT!";
        //   return 0;
        // }
      }
      frontier.pop();
      newStates(s, &frontier, depth);
    }
  }
  // cout << "\nNodes Visited: " << count;
  // cout << "\nMax Frontier: " << maxSize;
  // cout << "\nTotal Solutions: " << j <<"\n";
  return 0;
}


