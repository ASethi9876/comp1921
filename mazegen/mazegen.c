#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/**
* @brief Generates a random integer
* @param lower the lower bound
* @param upper the upper bound
* @return a random integer between the two values
*/
int randInt(int lower, int upper){
    return ((rand() % (upper - lower + 1)) + lower); // Adapted from an example found at https://www.geeksforgeeks.org/generating-random-number-range-c/
}

/**
* @brief Generates a random integer
* @param height the height of the maze
* @param width the width of the maze
* @param maze the array containing the elements of the maze
* @param y the y coordinate that is being searched from
* @param x the x coordinate that is being searched from
*/
void move(int height, int width, char maze[][width], int y, int x){
    bool searchN, searchE, searchS, searchW, searched = false, deadend = false;
    int direction;
    if (y <= 1 || (y > 1 && maze[y-2][x] == ' ')){
        searchN = false;
    } else {
        searchN = true;
    }
    if (x <= 1 || (x > 1 && maze[y][x-2] == ' ')){
        searchW = false;
    } else {
        searchW = true;
    }
    if (y >= (height - 2) || (y < (height - 2) && maze[y+2][x] == ' ')){
        searchS = false;
    } else {
        searchS = true;
    }
    if (x >= (width - 2) ||  (x < (width - 2) && maze[y][x+2] == ' ')){
        searchE = false;
    } else {
        searchE = true;
    }
    
    while (searched == false){
        direction = randInt(0,3);
        if (searchN == false && searchE == false && searchS == false && searchW == false){
            searched = true;
            deadend = true;
        } else if (direction == 0 && searchN == true){ // N
            y -= 1;
            searchN = false;
            searched = true;
        } else if (direction == 1 && searchE == true){ // E
            x += 1;
            searchE = false;
            searched = true;
        } else if (direction == 2 && searchS == true){ // S
            y += 1;
            searchS = false;
            searched = true;
        } else if (direction == 3 && searchW == true){ // W
            x -= 1;
            searchW = false;
            searched = true;
        }
    }

    if (deadend == false){
        maze[y][x] = ' '; // Break wall between the two
        if (direction == 0){
            y -= 1;
        } else if (direction == 1){
            x += 1;
        } else if (direction == 2){
            y += 1;
        } else if (direction == 3){
            x -= 1;
        } else {
            printf("Error\n"); // Just in case
        }
        maze[y][x] = ' ';
        move(height, width, maze, y, x);
        move(height, width, maze, y, x);
    }
}

int main(int argc, char* argv[]){
    if (argc != 4) {
        printf("Usage: mazegen <filename> <height> <width>.\n");
        exit(1);
    }
    
    srand(time(NULL));
    char* filename = argv[1];
    FILE* file = fopen(filename,"w");
    if (file == NULL){
        printf("Error opening file\n");
        exit(1);
    } 

    int height = atoi(argv[2]), width = atoi(argv[3]);

    char maze[height][width];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            maze[i][j] = '#';
        }
    }
    
    int y, x;
    y = randInt(0, height - 1);
    x = randInt(0, width - 1);
    int startY = y, startX = x;
    move(height, width, maze, y, x);
    maze[startY][startX] = 'S';   
    bool endChosen = false;
    while (endChosen == false){
        y = randInt(0,height);
        x = randInt(0,width);
        if (maze[y][x] == ' '){
            maze[y][x] = 'E';
            endChosen = true;
        }
    }

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            fprintf(file, "%c", maze[y][x]);
        }
        fprintf(file,"\n");
    }
    fclose(file);
    return 0;
}