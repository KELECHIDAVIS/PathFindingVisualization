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

// the game is gonna be a graph/tree where generally each space within the graph has 4 possible neighbors 
struct GameBoard 
{
    int rows=10; 
    int cols = 15; 
    char **grid; 
    Coords startCoords ; 
    Coords goalCoords; 
    char startSymbol = '@'; 
    char visitedSymbol ='x'; 
    char emptySymbol = '-'; 
    char goalSymbol = '$'; 
    char blockadeSymbol = '0'; 

    // regular 10x15 game board with the start at the top left and goal at bottom right 
    GameBoard()
    {
        // init grid 
        grid = new char*[rows]; 

        for(int i = 0 ; i< rows ; i++ )
        {
            grid[i] = new char[cols]; 

            for(int j=0 ; j<cols;  j++)
            {
                grid[i][j] = emptySymbol; 
            }
        }

        grid[0][0] = startSymbol; 
        startCoords.row = 0 ; 
        startCoords.col = 0 ; 
        grid[rows-1][cols-1] = goalSymbol;  
        goalCoords.row = rows-1 ; 
        goalCoords.col = cols-1; 
    }

    GameBoard(int rowSize, int colSize, bool randomCoords)
    {
        // init grid 
        rows = rowSize ; 
        cols = colSize ; 
        grid = new char*[rows]; 

        for(int i = 0 ; i< rows ; i++ )
        {
            grid[i] = new char[cols]; 

            for(int j=0 ; j<cols;  j++)
            {
                grid[i][j] = emptySymbol; 
            }
        }

        if(!randomCoords)
        {
            grid[0][0] = startSymbol; 
            startCoords.row = 0 ; 
            startCoords.col = 0 ; 
            grid[rows-1][cols-1] = goalSymbol;  
            goalCoords.row = rows-1 ; 
            goalCoords.col = cols-1; 
        }else
        {
            int startRow = rand()%rows; 
            int startCol = rand()%cols; 

            int goalRow = rand()%rows; 
            int goalCol = rand()%cols; 

            // they can't equal each other 
            while(goalCol==startCol && goalRow==startRow)
            {
                int goalRow = rand()%rows; 
                int goalCol= rand()%cols; 
            }

            startCoords.row = startRow; 
            startCoords.col = startCol; 
            goalCoords.row = goalRow; 
            goalCoords.col = goalCol; 

            grid[startCoords.row][startCoords.col] = startSymbol; 
            grid[goalCoords.row][goalCoords.col] = goalSymbol;  
        }
        
    }

    ~GameBoard(){
        for(int i = 0 ; i< rows ; i++ )
        {
            delete [] grid[i]; 
        }

        delete [] grid; 
    }

    // randomizes that start and goals coordinates ; 
    void randomizeTargets()
    {
            int startRow = rand()%rows; 
            int startCol = rand()%cols; 

            int goalRow = rand()%rows; 
            int goalCol = rand()%cols; 

            // they can't equal each other 
            while(goalCol==startCol && goalRow==startRow)
            {
                int goalRow = rand()%rows; 
                int goalCol= rand()%cols; 
            }

            startCoords.row = startRow; 
            startCoords.col = startCol; 
            goalCoords.row = goalRow; 
            goalCoords.col = goalCol; 

            grid[startCoords.row][startCoords.col] = startSymbol; 
            grid[goalCoords.row][goalCoords.col] = goalSymbol;  
    }

    void printBoard ()
    {

        for(int i = 0 ; i< rows; i++ )
        {

            for(int j = 0 ; j< cols; j++)
            {
                cout<<grid[i][j]<<" "; 
            }
            cout<<endl; 
        }
    }

   
}; 

#endif