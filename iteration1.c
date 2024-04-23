#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int randInt(int lower, int upper){
    return ((rand() % (upper - lower + 1)) + lower); // Adapted from an example found at https://www.geeksforgeeks.org/generating-random-number-range-c/
}

int main(int argc, char* argv[]){
    if (argc != 4) {
        printf("Usage: mazegen <filename> <height> <width>.\n");
        exit(1);
    }

    char* filename = argv[1];
    FILE* file = fopen(filename,"w");
    if (file == NULL){
        printf("Error opening file\n");
        exit(1);
    } 

    int height = atoi(argv[2]), width = atoi(argv[3]);

    char maze[height][width];
    int visitedMap[height][width];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            maze[i][j] = '#';
            visitedMap[i][j] = 0;
        }
    }
    int visited[height*width][2];
    srand(time(0));
    int y = 0, x = 0;
    y = randInt(0, height - 1);
    x = randInt(0, width - 1);
    maze[y][x] = 'S';
    int count = 0, direction = 0;
    bool moved,searchN,searchE,searchS,searchW,alternatives,noMove;
    while (count >= 0) {
        moved = false;
        if (y == 0 || (y > 1 && maze[y-2][x] == ' ')){
            searchN = false;
        } else {
            searchN = true;
        }
        if (x == 0 || (x > 1 && maze[y][x-2] == ' ')){
            searchW = false;
        } else {
            searchW = true;
        }
        if (y == (height - 1) || (y < (height - 2) && maze[y+2][x] == ' ')){
            searchS = false;
        } else {
            searchS = true;
        }
        if (x == (width - 1) ||  (x < (width - 2) && maze[y][x+2] == ' ')){
            searchE = false;
        } else {
            searchE = true;
        }
        while (moved == false){ // Repeat until new valid coordinate found
            direction = randInt(0,3);
            if (direction == 0 && searchN == true){ // N
                y -= 1;
                searchN = false;
            } else if (direction == 1 && searchE == true){ // E
                x += 1;
                searchE = false;
            } else if (direction == 2 && searchS == true){ // S
                y += 1;
                searchS = false;
            } else if (direction == 3 && searchW == true){ // W
                x -= 1;
                searchW = false;
            }
            if (searchN == false && searchE == false && searchS == false && searchW == false){
                alternatives = false;
            } else {
                alternatives = true;
            }
    
            if (maze[y][x] == '#'){
                maze[y][x] = ' ';
                if (alternatives = true){ // Will only go back if other options
                    visited[count][0] = y, visited[count][1] = x, visitedMap[y][x] = 1;
                    count += 1;
                }
                moved = true;

            } else if (alternatives == false || visitedMap[y][x] == 1){ // Returns to most recent node with alternative routes if no alternatives here or its been here before
                count -= 1;
                printf("%d\n",count);
                if (count >= 0){
                    y = visited[count][0], x = visited[count][1]; // Go back to most recent
                }
                moved = true;
            }
            for (int a = 0; a < height; a++){
                for (int b = 0; b < width; b++){
                    if (a == y && b == x){
                        printf("m");
                    } else {
                        printf("%d", visitedMap[a][b]);
                    }
                }
                printf("\n");
            }
            printf("\n");
        }
    }
    bool endChosen = false;
    while (endChosen == false){
        y = randInt(0,height);
        x = randInt(0,width);
        if (maze[y][x] == ' '){
            maze[y][x] = 'E';
            endChosen = true;
            printf("%d %d %c \n",y,x,maze[y][x]);
        }
    }
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            char e = maze[y][x];
            printf("%c", e);
        }
        printf("\n");
    }
    fclose(file);
    return 0;
}