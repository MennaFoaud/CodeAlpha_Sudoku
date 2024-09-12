#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define N 9

// Function to print the grid
void printGrid(int grid[N][N]){
    for(int row = 0; row < N; row++){
        for(int col = 0; col < N; col++){
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Check if it's safe to place a number
bool isSafe(int grid[N][N], int row, int col, int num){
    // Check row
    for(int x = 0; x < N; x++){
        if (grid[row][x] == num)
            return false;
    }

    // Check column
    for(int x = 0; x < N; x++){
        if(grid[x][col] == num)
            return false;
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (grid[startRow + i][startCol + j] == num)
                return false;
        }
    }
    return true;
}

// Solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[N][N]){
    int row, col;
    bool empty = false;

    // Find the first empty cell
    for(row = 0; row < N; row++){
        for(col = 0; col < N; col++){
            if (grid[row][col] == 0){
                empty = true;
                break;
            }
        }
        if (empty) break;
    }

    // If no empty cell is found, the puzzle is solved
    if (!empty) return true;

    // Try placing numbers 1-9
    for (int num = 1; num <= 9; num++){
        if (isSafe(grid, row, col, num)){
            grid[row][col] = num;

            // Recursively solve the rest of the puzzle
            if (solveSudoku(grid)) return true;

            // Backtrack
            grid[row][col] = 0;
        }
    }

    return false;
}

// Shuffle the grid
void shuffleGrid(int grid[N][N]){
    srand(time(0));
    for (int i = 0; i < N; i += 3){
        for (int j = 0; j < 3; j++){
            int row1 = rand() % 3 + i;
            int row2 = rand() % 3 + i;
            swap(grid[row1], grid[row2]);

            int col1 = rand() % 3;
            int col2 = rand() % 3;
            for(int row = 0; row < N; row++){
                swap(grid[row][col1 + j], grid[row][col2 + j]);
            }
        }
    }
}

// Remove numbers based on difficulty level
void removeNumbers(int grid[N][N], int level){
    int cellsToRemove = level * 10;
    while(cellsToRemove > 0){
        int row = rand() % N;
        int col = rand() % N;
        if(grid[row][col] != 0){
            grid[row][col] = 0;
            cellsToRemove--;
        }
    }
}

// Generate a random Sudoku puzzle
void generateRandomSudoku(int grid[N][N], int level){
    int baseGrid[N][N] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };

    // Copy base grid to grid
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            grid[i][j] = baseGrid[i][j];
        }
    }

    // Shuffle the grid
    shuffleGrid(grid);

    // Remove some numbers to create a puzzle
    removeNumbers(grid, level);
}

int main(){
    int grid[N][N];
    int level;

    cout << "Enter difficulty level (1-3): ";
    cin >> level;

    if (level < 1 || level > 3){
        cout << "Invalid level! Enter a number between 1 and 3." << endl;
        return 1;
    }

    // Generate random Sudoku puzzle
    generateRandomSudoku(grid, level);

    // Print the puzzle
    printGrid(grid);

    // Solve and print the solution
    if (solveSudoku(grid)){
        cout << "Solved Sudoku:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}
