/* 
 * bfs.cc
 * Joshua Enns
 * CPSC 3750 Assignment 2
 * Breadth first implementation
 */


#include <iostream>
#include <queue>
#include <stack>
#include <ctime>
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

void newStates(state s, queue<state> *frontier)
{
  int i, j, k, l;
  //loop through board
  for (i=0;i<N;i++){
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
        
        //check top
        x=i-1;
        y=j;
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
  //initialize local variables
  int start_s=clock();
  int j = 0;
  int count = 0;
  int maxSize = 0;
  //create empty NxN board
  state s;
  initializeBoard(&s);    
  //put empty board in frontier 
  queue<state> frontier;
  frontier.push(s);
  //loop through the frontier
  while (!frontier.empty())
  {
    count++;
    //keep track of max frontier size
    if (frontier.size() > maxSize){
      maxSize = frontier.size();
    }
    //copy first node in frontier to current state
    s = frontier.front();
    //
    if(isGoal(s))
    {
      //output solution board state to console
      cout << "Solution: ";
      printBoard(s);
      cout << "\nNodes Visited: " << count;
      cout << "\nMax Frontier Size: " << maxSize;
      int stop_s=clock();
      cout << "\nTime taken: " << ((stop_s-start_s)/double(CLOCKS_PER_SEC)*1000) << "ms\n";
      return 0;
      /* commented code is used for finding all possible solutions */
      j++;
      // int stop_s=clock();
      // cout << "\nSolutions so far: " << j;
      // cout << "\ntime so far: " << (abs((start_s-stop_s)/double(CLOCKS_PER_SEC)));
      // if ((abs((start_s-stop_s)/double(CLOCKS_PER_SEC)))>3600){
      //   cout << "HALT!";
      //   return 0;
      // }
    }
    frontier.pop();
    newStates(s, &frontier);
  }
  cout << "There are no solutions.";
  // cout << "\nTotal Solutions: " << j <<"\n";
  return 0;
}


