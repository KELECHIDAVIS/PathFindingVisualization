/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: kboss
 *
 * Created on December 8, 2023, 4:39 PM
 */

#include "GameBoard.h" 
#include "SimpleVector.h"
#include <chrono> // std::chrono::microseconds
#include <thread> // std::this_thread::sleep_for
#include <set>
#include <stack>
#include <queue> 
#include <map>

void draw(GameBoard & board , const int frameTime); // function that handles drawing the board 
void bfs(GameBoard & board); 
void dfs(GameBoard & board); 
void generatePath(GameBoard& board , Node* currentNode);  // a recursive function that handles path generation 
void astar(GameBoard & board); 
void mergeSort(SimpleVector<Node*> &arr, int l, int r) ; 
void merge(SimpleVector<Node*>& arr, int p, int q, int r); 
int getDistance(Node* node1 , Node* node2 ); 
void generatePathAstar(GameBoard& board , Node* endNode ); 
int main()
{
    srand(time(0)); 

    bool gameRunning = true; 
    const int frameTime = 2000; // how many milliseconds before we draw the next frame ; 
    
 
   
   
    
    while(gameRunning)
    {
        GameBoard board; 

        system("clear"); 
        cout<<"Symbol meaning: "<<endl; 
        cout<<"Starting Node: "<< board.startSymbol<<"    "; 
        cout<<"Goal Node: "<< board.goalSymbol<<"    "; 
        cout<<"Empty space: "<< board.emptySymbol<<"    "; 
        cout<<"Visited Node: "<< board.visitedSymbol<<"    ";     
        cout<<"Optimal Path : "<< board.pathSymbol<<"    "; 
        cout<<endl<<endl<<"Select The Algorithm You Would Like to See: "<<endl; 
        cout<<"Breadth First Search (1) "<<endl; 
        cout<<"Depth First Search (2) "<<endl; 
        cout<<"A* (3)"<<endl; 
        cout<<"End Program (0)"<<endl; 

        set<int> validResponses = {1,2,3,4,0}; 
        int response; 
        cin>> response ; 

        while(validResponses.find(response) == validResponses.end()) 
        {
            cout<<"Invalid Response Please Try Again"<<endl; 
            cin>> response ; 
        }

        if(response== 0 )
            break; 
        cout<<"Would you like randomized starting and goal position ? (y/n):  "<<endl; 
        cout<<"It is recommended to see all algorithms default before randomizing"<<endl; 


        set<char> validResponses2 = {'y','n'}; 
        char response2; 
        cin>> response2 ; 

        while(validResponses2.find(response2) == validResponses2.end()) 
        {
            cout<<"Invalid Response Please Try Again"<<endl; 
            cin>> response2 ; 
        }

        if(response2 == 'y')
        {
            cout<<"Randomized"<<endl; 
            board.randomizeTargets(); 
            this_thread::sleep_for(chrono::milliseconds{750});
        }

        switch(response)
        {
            case 1:
                bfs(board); 
                break; 
            case 2 : 
                dfs(board); 
                break; 
            case 3: 
                astar(board); 
                break; 
            case 0 :
                gameRunning = false; 
                break; 
        }

    }



    return 0; 
}


void draw(GameBoard &board, const int frameTime)// redraw board everytime there was an update made to it 
{
    system("clear"); 

    board.printBoard(); 

    this_thread::sleep_for(chrono::milliseconds{frameTime});
}

// starts from the goal node then branches back to the start node 
void generatePath(GameBoard& board ,  Node* currentNode)
{
    if(currentNode == board.startNode )
        return; 
    
    currentNode->symbol = board.pathSymbol; 
    draw(board , 200); 
    
    Node* parentNode = currentNode->parent; 
    
    
    generatePath(board, parentNode); 
    
    
}
                                                                                          
void bfs(GameBoard & board)
{
    cout<<"Commencing Breadth First Search..." <<endl; 
    this_thread::sleep_for(chrono::milliseconds{750});

    
    queue<Node*> nodeQueue; 
    nodeQueue.push(board.startNode)  ; 

    int iterations = 0 ; 
    int frametime = 100; 

    while(!nodeQueue.empty()) 
    {
        iterations++; 
        Node* currentNode = nodeQueue.front(); 
        
        nodeQueue.pop(); 
        // check if this node is the goal node 
        if(currentNode == board.goalNode)
        {
            cout<<"Goal found in "<< iterations <<" iterations"<<endl; 
            currentNode->symbol = board.goalSymbol; 
            this_thread::sleep_for(chrono::milliseconds{1300});
            
            cout<<"Now generating optimal path... "<<endl; 
            this_thread::sleep_for(chrono::milliseconds{1300});
            generatePath(board, currentNode->parent);
            
            break; 
        }

        // add its children / surrounding nodes that are not already visited and mark them visited; the starting node is already assumed to be visited
        for(int i = -1 ; i<=1 ; i++ )
        {
            for(int j = -1 ; j<=1 ; j++ )
            {
                if(i== j)
                {
                    continue ;                     
                }
                
                if(i ==0 && j==0)
                {
                    continue; 
                }
                
                int newRow = currentNode->row + i ; 
                int newCol = currentNode->col +j ; 

                // first check if the coords are even valid 
                if((newRow <0 || newRow >= board.rows) || (newCol <0 || newCol>= board.cols))
                {
                    //invalid 
                    continue; //go next 
                }

                // now check if this current index has been visited alr 

                if((board.grid[newRow][newCol]->symbol != board.startSymbol) && (board.grid[newRow][newCol]->symbol != board.visitedSymbol))
                {
                    board.grid[newRow][newCol]->symbol = board.visitedSymbol; 
                    board.grid[newRow ][newCol] ->parent = currentNode; // set the parent for later ; 
                    nodeQueue.push(board.grid[newRow][newCol]); 
                }
            }
        }


        draw(board, frametime); 
    }
    
}

void dfs(GameBoard & board)
{
    cout<<"Commencing Depth First Search..." <<endl; 
    this_thread::sleep_for(chrono::milliseconds{750});

    
    stack<Node*> nodeStack; 
    nodeStack.push(board.startNode)  ; 

    int iterations = 0 ; 
    int frametime = 100; 

    while(!nodeStack.empty()) 
    {
        iterations++; 
        Node* currentNode = nodeStack.top(); 
        
        nodeStack.pop(); 
        // check if this node is the goal node 
        if(currentNode == board.goalNode)
        {
           cout<<"Goal found in "<< iterations <<" iterations"<<endl; 
            currentNode->symbol = board.goalSymbol; 
            this_thread::sleep_for(chrono::milliseconds{1300});
            
            cout<<"Now generating path (unoptimal because of DFS) ... "<<endl; 
            this_thread::sleep_for(chrono::milliseconds{1300});
            generatePath(board, currentNode->parent);
            break; 
        }

        // add its children / surrounding nodes that are not already visited and mark them visited; the starting node is already assumed to be visited
        for(int i = 1 ; i>=-1 ; i-- )
        {
            for(int j = 1 ; j>=-1 ; j-- )
            {
                
                if(i== j)
                {
                    continue ;                     
                }
                
                if(i ==0 && j==0)
                {
                    continue; 
                }
                
                int newRow = currentNode->row + i ; 
                int newCol = currentNode->col +j ; 

                // first check if the coords are even valid 
                if((newRow <0 || newRow >= board.rows) || (newCol <0 || newCol>= board.cols))
                {
                    //invalid 
                    continue; //go next 
                }

                // now check if this current index has been visited alr 

                if((board.grid[newRow][newCol]->symbol != board.startSymbol) && (board.grid[newRow][newCol]->symbol != board.visitedSymbol))
                {
                    board.grid[newRow][newCol]->symbol = board.visitedSymbol; 
                    board.grid[newRow ][newCol] ->parent = currentNode; // set the parent for later ; 
                    nodeStack.push(board.grid[newRow][newCol]); 
                }
            }
        }


        draw(board, frametime); 
    }
}

void mergeSort(SimpleVector<Node*> &arr, int l, int r) {
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    // Merge the sorted subarrays
    merge(arr, l, m, r);
  }
}

void merge(SimpleVector<Node*>& arr, int p, int q, int r) {
  
  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  SimpleVector<Node*> L(n1), M(n2);

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i]->getFCost() <= M[j]->getFCost()) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

void astar(GameBoard & board)
{
    SimpleVector<Node*> openList; // nodes to be evaluated ; will be sort to choose from the lowest fcost
    set<Node*> closedSet;  // nodes alr evaluated 
    set<Node*> openSet; // to keep track of which are in the open list 
    
    // add starting node to open set 
    openList.pshBack(board.startNode); 
    openSet.insert(board.startNode); 
    int iterations = 0 ; 
    int frametime = 180; 
    
    
    
    while(openList.size() >0 )
    {
        iterations++; 
        // get the node with the smallest fcost 
        mergeSort(openList, 0 , openList.size()-1); // might have to do another way because hcost is  also valuable 
        
        Node * currentNode = openList.popFrnt(); //give the best and removes it 
        openSet.erase(currentNode); 
        closedSet.insert(currentNode); 
        
        if( currentNode == board.goalNode)
        {
            cout<<"Goal found in "<< iterations <<" iterations"<<endl; 
            currentNode->symbol = board.goalSymbol; 
            this_thread::sleep_for(chrono::milliseconds{1300}); 
            
            cout<<"Now generating optimal path ... "<<endl; 
            this_thread::sleep_for(chrono::milliseconds{1300});
            generatePathAstar(board, currentNode);
            break; 
        }
        
        // now iterate through neighbors of currentNode 
        
        for(int i = 1 ; i>=-1 ; i-- )
        {
            for(int j = 1 ; j>=-1 ; j-- )
            {
                
                if(i== j)
                {
                    continue ;                     
                }
                
                if(i ==0 && j==0)
                {
                    continue; 
                }
                
                int newRow = currentNode->row + i ; 
                int newCol = currentNode->col +j ; 

                // first check if the coords are even valid 
                if((newRow <0 || newRow >= board.rows) || (newCol <0 || newCol>= board.cols))
                {
                    //invalid 
                    continue; //go next 
                }
                
                // it has been visited alr
                if(closedSet.find(board.grid[newRow][newCol]) != closedSet.end())
                {
                    continue; 
                }
                
                int newMovementCost = currentNode->gCost + getDistance(currentNode, board.grid[newRow][newCol]); 
                
                if(newMovementCost < currentNode->gCost || openSet.find(board.grid[newRow][newCol]) == openSet.end())
                {
                    board.grid[newRow][newCol]->gCost = newMovementCost ; 
                    board.grid[newRow][newCol]->hCost = getDistance(board.grid[newRow][newCol], board.goalNode); 
                    board.grid[newRow][newCol]->parent = currentNode ;
                    
                    if(openSet.find(board.grid[newRow][newCol]) == openSet.end())
                    {
                        board.grid[newRow][newCol]->symbol = board.visitedSymbol; 
                        openList.pshBack(board.grid[newRow][newCol]); 
                        openSet.insert(board.grid[newRow][newCol]); 
                    }
                }
                
            }
        }
        
        draw(board, frametime); 
    }
  
    
}

int getDistance(Node* node1 , Node* node2 ){
    int distX = abs(node1->col - node2->col); 
    int distY = abs(node1->row - node2->row);  
    
    if( distX > distY )
    {
        return 14*distY + 10*(distX -distY); 
    }
    
    return 14*distX + 10*(distY-distX); 
}
void generatePathAstar( GameBoard& board , Node* goalNode )
{
    Node* currentNode = goalNode; 
    
    while(currentNode != board.startNode )
    {
        currentNode->symbol = board.pathSymbol; 
        currentNode = currentNode->parent; 
        
        draw(board ,200); 
    }
    
}
