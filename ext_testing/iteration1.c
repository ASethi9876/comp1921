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

    srand(time(0));
    int height = atoi(argv[2]), width = atoi(argv[3]);

    char maze[height][width];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            maze[i][j] = '#';
        }
    }

    int visited[height*width][2];
    int y = 0, x = 0;
    y = randInt(0, height - 1);
    x = randInt(0, width - 1);
    maze[y][x] = 'S';

    int count = 0, direction = 0;
    bool moved,searchN,searchE,searchS,searchW,alternatives,noMove;
    
    while (count >= 0) {
        moved = false;
        if (y == 0 || (y > 1 && maze[y-2][x] == ' ') || (y > 0 && maze[y-1][x] == ' ')){
            searchN = false;
        } else {
            searchN = true;
        }
        if (x == 0 || (x > 1 && maze[y][x-2] == ' ') || (x > 0 && maze[y][x-1] == ' ' )){
            searchW = false;
        } else {
            searchW = true;
        }
        if (y == (height - 1) || (y < (height - 2) && maze[y+2][x] == ' ') || (y < (height - 1) && maze[y+1][x] == ' ')){
            searchS = false;
        } else {
            searchS = true;
        }
        if (x == (width - 1) ||  (x < (width - 2) && maze[y][x+2] == ' ') || (y < (height - 1) && maze[y][x+1] == ' ')){
            searchE = false;
        } else {
            searchE = true;
        }
        
        while (moved == false){
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
                    visited[count][0] = y, visited[count][1] = x;
                    count += 1;
                }
                moved = true;

            } else if (alternatives == false){ // Returns to most recent node with alternative routes if no alternatives
                count -= 1;
                if (count >= 0){
                    y = visited[count][0], x = visited[count][1]; // Go back to most recent
                }
                moved = true;
            }
        }
    }

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
        fprintf(file,"\\n\n"); // Prints the \n to the text file followed by a newline, adapted from a response found at: https://www.quora.com/Is-it-possible-to-print-n-in-C
    }
    fclose(file);
    return 0;
}