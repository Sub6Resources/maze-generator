#include <iostream>
#include <map>

const int N = 1;
const int S = 2;
const int E = 4;
const int W = 8;

std::map<int, int> DX;
std::map<int, int> DY;
std::map<int, int> OPPOSITE;

void printGrid(int* grid[], int width, int height) {
    for (int x = 0; x < width; ++x) {
        std::cout << " " << "_";
    }
    std::cout << std::endl;
    for (int y = 0; y < height; ++y) {
        std::cout << "|";
        for (int x = 0; x < width; ++x) {
            std::cout << (((grid[y][x] & S) != 0)? " ": "_");
            if((grid[y][x] & E) != 0) {
                std::cout << ((((grid[y][x] | grid[y][x+1]) & S) != 0)? " ": "_");
            } else {
                std::cout << "|";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void saveGridToFile(int* grid[], int width, int height) {

}

void carve_passages_from(int currentX, int currentY, int* grid[], int width, int height) {
    int directions[4] = {N, S, E, W};
    std::random_shuffle(std::begin(directions), std::end(directions));

    for (int direction : directions) {
        int newX = currentX + DX[direction];
        int newY = currentY + DY[direction];

        if((newY >= 0 && newY < height) && (newX >= 0 && newX < width) && grid[newY][newX] == 0) {
            grid[currentY][currentX] |= direction;
            grid[newY][newX] |= OPPOSITE[direction];
            carve_passages_from(newX, newY, grid, width, height);
        }
    }
}

int main() {
    //Initialize maps
    DX[E] = 1;
    DX[W] = -1;
    DX[N] = 0;
    DX[S] = 0;

    DY[E] = 0;
    DY[W] = 0;
    DY[N] = -1;
    DY[S] = 1;

    OPPOSITE[E] = W;
    OPPOSITE[W] = E;
    OPPOSITE[N] = S;
    OPPOSITE[S] = N;

    std::cout << "Hello, World!" << std::endl;

    int width, height;

    std::cout << "Please enter the maze width: ";
    std::cin >> width;
    std::cout << "Please enter the maze height: ";
    std::cin >> height;

    int *grid[height];
    for (int y = 0; y < height; ++y) {
        grid[y] = new int[width];
        for (int x = 0; x < width; ++x) {
            grid[y][x] = 0;
        }
    }

    carve_passages_from(0, 0, grid, width, height);

    printGrid(grid, width, height);

    std::cout << "Finished!" << std::endl;

    return 0;
}