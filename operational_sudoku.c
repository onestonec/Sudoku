#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "includes/ft_func.h"

int h_check(int *row, int guess)
{
    int i = 0;

    while (i < 9)
    {
        if (row[i] == guess)
        {
            return -1;
        } 
        i++;
    }
    return 0;
}

int v_check(int **grid, int j, int guess)
{
    int i = 0;

    while(i < 9)
    {
        if(grid[i][j] == guess)
        {
            return -1;
        }
        i++;
    }
    return 0;
}

int sq_check(int **grid, int i, int j, int guess)
{
    int row_up;
    int row_down;
    int col_up;
    int col_down;

    row_down = (i / 3) * 3;
    row_up = row_down + 2;
    col_down = (j / 3) * 3;
    col_up = col_down + 2;

    while(row_down <= row_up)
    {
        while (col_down <= col_up)
        {
            if(grid[row_down][col_down] == guess)
            {
                return -1;
            }
            col_down++;
        }
        col_down = col_down - 2;
        row_down++;
    }
    return 0;
}

int sudoku(int **grid)
{
    int i = 0;
    int j = 0;
    int guess = 1;

    while(i < 9)
    {
        while(j < 9)
        {
            if (grid[i][j] == 0)
            {
                while (guess < 10)
                {
                    if((h_check(grid[i], guess) == 0) && (v_check(grid, j, guess) == 0) && (sq_check(grid, i, j, guess) == 0))
                    {
                        grid[i][j] = guess;
                        if (sudoku(grid) == -1)
                        {
                            guess++;
                        }else
                            return 0;
                    } else
                    {
                        guess++;
                    } 
                } 
                grid[i][j] = 0;
                return -1;   
            } else
            j++;
        }
        j = 0;
        i++;
    }
}

int main(int argc, char **argv)
{
    int row = 0;
    int pos = 0;
    int i = 1;


    int **grid;
    
    grid = (int **)malloc(sizeof(int *) * 9);
    while(row < 9)
    {
        grid[row] = (int *)malloc(sizeof(int) * 9);
        row++;
    }
    row = 0;
    while (argc - 1 > row)
    {
        while (pos < 9)
        {
            grid[row][pos] = ft_atoi(argv[i][pos]);
            pos++;
        }
        row++;
        i++;
        pos = 0;
    }
    row = 0;
    printf("%d\n", sudoku(grid));
    while (argc - 1 > row) //confirm and print
    {
        while (pos < 9)
        {
            printf("%d",grid[row][pos]);
            pos++;
        }
        printf("\n");
        row++;
        pos = 0;
    } 
    
    return 0;
}