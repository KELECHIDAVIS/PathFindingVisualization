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
#include <chrono> // std::chrono::microseconds
#include <thread> // std::this_thread::sleep_for
#include <set>
#include <stack>
#include <queue> 

void draw(GameBoard & board , const int frameTime); // function that handles drawing the board 
void bfs(GameBoard & board); 
void dfs(GameBoard & board); 
void dfsRecur(GameBoard & board); // recursive version 
void dijkstras(GameBoard & board); 
void astar(GameBoard & board); 

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
        cout<<"Blockade : "<< board.blockadeSymbol<<"    "; 
        cout<<endl<<endl<<"Select The Algorithm You Would Like to See: "<<endl; 
        cout<<"Breadth First Search (1) "<<endl; 
        cout<<"Depth First Search (2) "<<endl; 
        cout<<"Dijikstras Algorithm (3)"<<endl; 
        cout<<"A* (4)"<<endl; 
        cout<<"End Program (0)"<<endl; 

        set<int> validResponses = {1,2,3,4,0}; 
        int response; 
        cin>> response ; 

        while(validResponses.find(response) == validResponses.end()) 
        {
            cout<<"Invalid Response Please Try Again"<<endl; 
            cin>> response ; 
        }

//        cout<<"Would you like randomize starting and stopping positions (if first time n is recommended) ? (y/n):  "<<endl; 
//
//
//        set<int> validResponses2 = {'y','n'}; 
//        char response2; 
//        cin>> response2 ; 
//
//        while(validResponses2.find(response2) == validResponses2.end()) 
//        {
//            cout<<"Invalid Response Please Try Again"<<endl; 
//            cin>> response2 ; 
//        }
//
//        if(response == 'y')
//        {
//            board.randomizeTargets(); 
//        }

        switch(response)
        {
            case 1:
                bfs(board); 
                break; 
            case 2 : 
                dfs(board); 
                break; 
            case 3: 
                dijkstras(board); 
                break; 
            case 4: 
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


void bfs(GameBoard & board)
{
    cout<<"Commencing Breadth First Search..." <<endl; 
    this_thread::sleep_for(chrono::milliseconds{750});

    
    queue<Coords> coordQueue; 

    coordQueue.push(board.startCoords)  ; 

    int iterations = 0 ; 
    int frametime = 100; 

    while(!coordQueue.empty()) 
    {
        iterations++; 
        Coords current = coordQueue.front(); 
        
        coordQueue.pop(); 
        // check if this node is the goal node 
        if(current.equals(board.goalCoords))
        {
            cout<<"Goal found in "<< iterations <<" iterations"<<endl; 
            this_thread::sleep_for(chrono::milliseconds{1300});
            break; 
        }

        // add its children / surrounding nodes that are not already visited and mark them visited; the starting node is already assumed to be visited
        for(int i = -1 ; i<=1 ; i++ )
        {
            for(int j = -1 ; j<=1 ; j++ )
            {
                int newRow = current.row + i ; 
                int newCol = current.col +j ; 

                // first check if the coords are even valid 
                if((newRow <0 || newRow >= board.rows) || (newCol <0 || newCol>= board.cols))
                {
                    //invalid 
                    continue; //go next 
                }

                // now check if this current index has been visited alr 

                if((board.grid[newRow][newCol] != board.startSymbol) && (board.grid[newRow][newCol]  != board.visitedSymbol))
                {
                    board.grid[newRow][newCol] = board.visitedSymbol; 

                    coordQueue.push(Coords(newRow, newCol)); 
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

    
    stack<Coords> coordStack; 

    coordStack.push(board.startCoords)  ; 

    int iterations = 0 ; 
    int frametime = 200; 

    while(!coordStack.empty()) 
    {
        iterations++; 
        Coords current = coordStack.top(); 
        
        coordStack.pop(); 
        // check if this node is the goal node 
        if(current.equals(board.goalCoords))
        {
            cout<<"Goal found in "<< iterations <<" iterations"<<endl; 
            this_thread::sleep_for(chrono::milliseconds{1300});
            break; 
        }

        // add its children / surrounding nodes that are not already visited and mark them visited; the starting node is already assumed to be visited
        for(int i = 1 ; i>=-1 ; i-- )
        {
            for(int j =1; j>=-1 ; j-- )
            {
                int newRow = current.row + i ; 
                int newCol = current.col +j ; 

                // first check if the coords are even valid 
                if((newRow <0 || newRow >= board.rows) || (newCol <0 || newCol>= board.cols))
                {
                    //invalid 
                    continue; //go next 
                }

                // now check if this current index has been visited alr 

                if((board.grid[newRow][newCol] != board.startSymbol) && (board.grid[newRow][newCol]  != board.visitedSymbol))
                {
                    board.grid[newRow][newCol] = board.visitedSymbol; 

                    coordStack.push(Coords(newRow, newCol)); 
                }
            }
        }


        draw(board, frametime); 
    }
}
void dijkstras(GameBoard & board){}
void astar(GameBoard & board){}