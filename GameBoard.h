/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   GameBoard.h
 * Author: kboss
 *
 * Created on December 8, 2023, 4:40 PM
 */

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream> 
#include <string>
using namespace std; 


struct Coords
{
    int row , col; 
    Coords(){} 
    Coords(int r, int c )
    {
        row = r ; 
        col = c ; 
    }

    bool equals(Coords &other)
    {
        if(row == other.row && col == other.col)
        {
            return true; 
        }
        return false; 
    }
}; 

struct Node 
{
    int row ; 
    int col ; 
    Node* parent= nullptr;  
    int gCost ; 
    int hCost ;  
    
    char symbol ; 
    
    Node(int row , int col )
    {
        this->row = row; 
        this->col = col ; 
    }
    bool samePos(Node * other)
    {
        if(row == other->row && col == other->col)
        {
            return true; 
        }
        return false; 
    }
    
    int getFCost()
    {
        return hCost+ gCost;   
    }
    
    
};
// the game is gonna be a graph/tree where generally each space within the graph has 4 possible neighbors 
struct GameBoard 
{
    int rows=10; 
    int cols = 15; 
    Node ***grid; 
    Node * startNode ;
    Node* goalNode; 
    char startSymbol = '@'; 
    char visitedSymbol ='-'; 
    char emptySymbol = '.'; 
    char goalSymbol = '$'; 
    char blockadeSymbol = '0'; 
    char pathSymbol = 'X'; 

    // regular 10x15 game board with the start at the top left and goal at bottom right 
    GameBoard()
    {
        
        // init grid 
        grid = new Node**[rows]; 

        for(int i = 0 ; i< rows ; i++ )
        {
            grid[i] = new Node*[cols]; 

            for(int j=0 ; j<cols;  j++)
            {
                grid[i][j] = new Node(i, j );  
                grid[i][j]->symbol = emptySymbol; 
            }
        }
        startNode = grid[0][0]; 
        goalNode = grid[rows-1][cols-1]; 
        
        startNode->symbol = startSymbol ; 
        goalNode->symbol = goalSymbol; 
        
    }

//    GameBoard(int rowSize, int colSize, bool randomCoords)
//    {
//        
//        // init grid 
//        rows = rowSize ; 
//        cols = colSize ; 
//        grid = new char*[rows]; 
//
//        for(int i = 0 ; i< rows ; i++ )
//        {
//            grid[i] = new char[cols]; 
//
//            for(int j=0 ; j<cols;  j++)
//            {
//                grid[i][j] = emptySymbol; 
//            }
//        }
//
//        if(!randomCoords)
//        {
//            grid[0][0] = startSymbol; 
//            startCoords.row = 0 ; 
//            startCoords.col = 0 ; 
//            grid[rows-1][cols-1] = goalSymbol;  
//            goalCoords.row = rows-1 ; 
//            goalCoords.col = cols-1; 
//        }else
//        {
//            int startRow = rand()%rows; 
//            int startCol = rand()%cols; 
//
//            int goalRow = rand()%rows; 
//            int goalCol = rand()%cols; 
//
//            // they can't equal each other 
//            while(goalCol==startCol && goalRow==startRow)
//            {
//                int goalRow = rand()%rows; 
//                int goalCol= rand()%cols; 
//            }
//
//            startCoords.row = startRow; 
//            startCoords.col = startCol; 
//            goalCoords.row = goalRow; 
//            goalCoords.col = goalCol; 
//
//            grid[startCoords.row][startCoords.col] = startSymbol; 
//            grid[goalCoords.row][goalCoords.col] = goalSymbol;  
//        }
//        
//    }

    ~GameBoard(){
        for(int i = 0 ; i< rows ; i++ )
        {
            for(int j = 0 ; j< cols; j++)
            {
                delete grid[i ][j] ; 
            }
            delete [] grid[i]; 
        }

        delete [] grid; 
    }
    
    unsigned int JSHash(const std::string& str)
    {
       unsigned int hash = 1315423911;

       for(std::size_t i = 0; i < str.length(); i++)
       {
          hash ^= ((hash << 5) + str[i] + (hash >> 2));
       }

       return hash;
    }
    
    //gonna be determined by a random string and hashing 
    
    string randString(int stringLength)
    {
        string letters= "abcdefghijklmnoqrstuvwxyz"; 
        
        string randoString = ""; 
        
        for(int i =0 ; i< stringLength; i++)
        {
            randoString += letters[rand()%letters.size()]; 
        }
        return randoString; 
    }
    // randomizes that start and goals coordinates ; 
    int randRow()
    {
        string hashString = randString(rand()%5 + 5) ; //string of length 5 - 10 
        
        return JSHash(hashString) %rows; 
    }
    
    int randCol()
    {
        string hashString = randString(rand()%5 + 5) ; //string of length 5 - 10 
        
        return JSHash(hashString) %cols; 
    }
    void randomizeTargets()
    {
            int startRow = randRow(); 
            int startCol = randCol(); 

            int goalRow = randRow(); 
            int goalCol = randCol(); 

            // they can't equal each other 
            while(goalCol==startCol && goalRow==startRow)
            {
                int goalRow = rand()%rows; 
                int goalCol= rand()%cols; 
            }

            this->startNode->symbol= emptySymbol; 
            this->goalNode->symbol= emptySymbol; 
            
            this->startNode = grid[startRow][startCol]; 
            this->goalNode = grid[goalRow][goalCol];
            
            this->startNode->symbol = startSymbol ; 
            this->goalNode ->symbol = goalSymbol ; 
    }

    void printBoard ()
    {

        for(int i = 0 ; i< rows; i++ )
        {

            for(int j = 0 ; j< cols; j++)
            {
                cout<<grid[i][j]->symbol<<" "; 
            }
            cout<<endl; 
        }
    }

   
}; 

#endif