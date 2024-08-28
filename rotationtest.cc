#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

vector<vector<string>> grid = {
    {"11","12","13","14"},
    {"21","22","23","24"},
    {"31","32","33","34"},
    {"41","42","43","44"}
};

void rotateCW(vector<vector<string>> &grid) {
    const int n = 4; // n is the dimension of the block

    // Transpose the matrix
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            swap(grid[i][j], grid[j][i]);
        }
    }

    // Reverse each row
    for (int i = 0; i < n; i++) {
        reverse(grid[i].begin(), grid[i].end());
    }
}

void rotateCCW(vector<vector<string>> &grid) {
    const int n = 4; // n is the dimension of the block

    // Transpose the matrix
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            std::swap(grid[i][j], grid[j][i]);
        }
    }

    // Reverse each column
    for (int j = 0; j < n; j++) {
        int start = 0;
        int end = n - 1;
        while (start < end) {
            std::swap(grid[start][j], grid[end][j]);
            start++;
            end--;
        }
    }
}

void printGrid(const vector<vector<string>>& grid) {
    for(const auto& row : grid) {
        for(const auto& element : row) {
            cout << element << ' ';
        }
        cout << '\n';
    }
}

int main(void) {
    cout << "Original Grid:\n";
    printGrid(grid);
    rotateCW(grid);
    cout << "After CW Rotation:\n";
    printGrid(grid);
    rotateCCW(grid);
    cout << "After CCW Rotation:\n";
    printGrid(grid);
    return 0;
}
