#include <iostream>
using namespace std;

const int SIZE = 9;  // Size of the Sudoku grid

// Function to print the Sudoku grid
void printGrid(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }
}

// Function to check if a number is already present in the given row
bool isPresentInRow(int grid[SIZE][SIZE], int row, int num) {
    for (int col = 0; col < SIZE; col++) {
        if (grid[row][col] == num)
            return true;
    }
    return false;
}

// Function to check if a number is already present in the given column
bool isPresentInCol(int grid[SIZE][SIZE], int col, int num) {
    for (int row = 0; row < SIZE; row++) {
        if (grid[row][col] == num)
            return true;
    }
    return false;
}

// Function to check if a number is already present in the 3x3 box
bool isPresentInBox(int grid[SIZE][SIZE], int startRow, int startCol, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (grid[row + startRow][col + startCol] == num)
                return true;
        }
    }
    return false;
}

// Function to check if it's safe to place a number at a given position
bool isSafe(int grid[SIZE][SIZE], int row, int col, int num) {
    return !isPresentInRow(grid, row, num) &&
           !isPresentInCol(grid, col, num) &&
           !isPresentInBox(grid, row - row % 3, col - col % 3, num);
}

// Function to find the next empty cell in the Sudoku grid
bool findEmptyCell(int grid[SIZE][SIZE], int& row, int& col) {
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (grid[row][col] == 0)
                return true;
        }
    }
    return false;
}

// Recursive function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[SIZE][SIZE]) {
    int row, col;

    // Check if there are no empty cells left
    if (!findEmptyCell(grid, row, col))
        return true;

    // Try different numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            // Assign the number and recursively solve the puzzle
            grid[row][col] = num;

            // If the puzzle is solved, return true
            if (solveSudoku(grid))
                return true;

            // If the current assignment leads to an incorrect solution, backtrack and try again
            grid[row][col] = 0;
        }
    }

    // If no number can be assigned, the puzzle cannot be solved
    return false;
}

int main() {
    int grid[SIZE][SIZE];

    // Read the Sudoku grid
    cout << "Enter the Sudoku grid (use 0 for empty cells):\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cin >> grid[i][j];
        }
    }

    // Solve the Sudoku puzzle
    if (solveSudoku(grid)) {
        cout << "Sudoku solved:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists for the given Sudoku puzzle.\n";
    }

    return 0;
}