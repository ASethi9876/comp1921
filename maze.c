/**
* @file maze.c
* @author Asher Sethi
* @brief Code for COMP1921 Coursework 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_ARG 1
#define EXIT_FILE 2
#define EXIT_INV 3

// a struct to hold the maze and the position of the player
typedef struct __Maze{
    int height;
    int width;
    int currentPos[2];
    char** mazeArray;
} maze;

// a procedure to tidy up the dynamically allocated memory before exiting the program
void freeMaze(maze* this){
    // check maze isn't null
    if (this == NULL){
        return;
    }

    // set each pointer to null
    if (this->mazeArray != NULL) {
        for (int i = 0; i < this->height; i++){
            free(this->mazeArray[i]);
            this->mazeArray[i] = NULL;
        }
        free(this->mazeArray);
        this->mazeArray = NULL;

    }
    // set array of null pointers to 0
    // free image pointer
}

void showMap(maze* this){
    // loop through each row of the maze and print it
    printf("Map: \n");
    for (int y = 0; y < this->height; y++){
        for (int x = 0; x < this->width; x++){
            printf("%c", this->mazeArray[y][x]);
        }
        printf("\n");
    }
}

int validateMaze(maze* this){
    int sCount = 0;
    int eCount = 0;
    for (int y = 0; y < this->height; y++){
        for (int x = 0; x < this->width; x++){
            char c = this->mazeArray[y][x];
            if (c == 'S') {
                if (sCount != 0){
                    return 3;
                } else {
                    sCount = 1;
                    this->mazeArray[y][x] = 'X';
                    this->currentPos[0] = y, this->currentPos[1] = x;
                }
            } else if (c == 'E'){
                if (eCount != 0){
                    return 3;
                } else {
                    eCount = 1;
                }
            //} else if (c != ' ' && c != '#'){
               // return 3;
            }
        }
    }
    return 0;
}

// a function to create the maze struct
int createMaze(maze* this, char* filename){
    // call openFile()
    // if it is unopenable, give an error message and return 2
    FILE* file = fopen(filename,"r");
    if (file == NULL){
        return 2;
    }  
    // otherwise, check first row is of length between 5 and 100, and store as width
    
    char line[1000];
    char tempArray[1000][1000];
    
    // loop through each row of the first column:
        // increase a counter by 1 for each iteration
    // check counter is between 5 and 100, and store as height
    int count = 0;
    int width = 0;
    while (fgets(line, sizeof(line), file)){
        int i = 0;
        while (line[i+1] != 'n'){ // stops at the newline
            tempArray[count][i] = line[i];
            i++;
        }
        count++;
        if (i < 5 || i > 100){  // check if wrong size or line width is different to previous width
            return 3;
        } else {
            width = i;
        }

    }
    int height = count;
    if (height < 5 || height > 100){
        return 3;
    }
    // if height and width are valid:
        // initialise a pointer for the maze struct
    this->height = height;
    this->width = width;
    this->mazeArray = malloc(this->height);

    for (int y = 0; y < height; y++){
        this->mazeArray[y] = malloc(this->width);
        for (int x = 0; x < width; x++){
            this->mazeArray[y][x] = tempArray[y][x];
        }
    }

    this->mazeArray[0] = malloc(this->width);
    for (int x = 0; x < width; x++){ // necessary fix as previously the first line was storing a random set of characters
        this->mazeArray[0][x] = tempArray[0][x];
    }

    //showMap(this);
    int mazeTest = validateMaze(this);
    return mazeTest;
        // loop through each row:
            // allocate the array width for that row as width
            // convert each character to an element of the maze array 
            // if \n reached early or there are still chars left on the row call freeMaze(), give an error message and return 1
        // call validateMaze() and return the result
    // else:
        // give error message and return 3

}

void movePlayer(maze* this, int* newPos){
    this->mazeArray[this->currentPos[0]][this->currentPos[1]] = ' ';
    this->currentPos[0] = newPos[0], this->currentPos[1] = newPos[1];
    this->mazeArray[newPos[0]][newPos[1]] = 'X';
}

int checkTile(maze* this, int* newPos){
    if (newPos[0] < 0 || newPos[0] >= this->height || newPos[1] < 0 || newPos[1] >= this->width){
        printf("Cannot make this move.");
        return 2;
    } else {
        char value = this->mazeArray[newPos[0]][newPos[1]];
        if (value == 'E') {
            printf("%c",value);
            return 0;
        } else if (value == ' ' || value == 'S'){
            movePlayer(this, newPos);
            return 1;
        } else {
            printf("Cannot make this move.");
            return 2;
        }
    }
}

int moveUp(maze* this){
    // get both values from currentPos
    // subtract 1 from currentPos[1] NOPE
    // store as newPos
    // call checkTile() and return result
    // alert user that they have moved up if checkTile() returns 0 or 1
    int newPos[2] = {};
    newPos[0] = this->currentPos[0] - 1; 
    newPos[1] = this->currentPos[1];
    int value = checkTile(this, newPos);
    if (value <= 1){
        printf("You have moved up.");
    }
    return value;
    
}

int moveLeft(maze* this){
    int newPos[2] = {};
    newPos[0] = this->currentPos[0]; 
    newPos[1] = this->currentPos[1] - 1;
    int value = checkTile(this, newPos);
    if (value <= 1){
        printf("You have moved left.");
    }
    return value;
}

int moveDown(maze* this){
    int newPos[2] = {};
    newPos[0] = this->currentPos[0] + 1; 
    newPos[1] = this->currentPos[1];
    int value = checkTile(this, newPos);
    if (value <= 1){
        printf("You have moved down.");
    }
    return value;
}

int moveRight(maze* this){
    int newPos[2] = {};
    newPos[0] = this->currentPos[0]; 
    newPos[1] = this->currentPos[1] + 1;
    int value = checkTile(this, newPos);
    if (value <= 1){
        printf("You have moved right.");
    }
    return value;
}

int getInput(maze* this){

    printf("W - Move up. \n");
    printf("A - Move left. \n");
    printf("S - Move down. \n");
    printf("D - Move right. \n");
    printf("M - Display map. \n");
    
    int value = 1;
    while (value != 0){
        char input = 'M';  
        printf("Enter input: ");    
        scanf(" %c",&input);

        switch(input){
            case 'W':
            case 'w':
                value = moveUp(this);
                break;

            case 'A':
            case 'a':
                value = moveLeft(this);
                break;

            case 'S':
            case 's':
                value = moveDown(this);
                break;

            case 'D':
            case 'd':
                value = moveRight(this);
                break;
            
            case 'M':
            case 'm':
                showMap(this);
                break;

            default:
                printf("Invalid input.");
                break;
        }
    }
    return 0;
}

int main(int argc, char* argv[]){
    if (argc != 2){ // needs exactly ./maze and filename for arguments
        printf("Usage: maze <filename>. \n");
        exit(EXIT_ARG);
    }

    maze* this = malloc(sizeof(maze)); // allocate enough memory for the structure in main

    int mazeCheck = createMaze(this, argv[1]);
    if (mazeCheck == 2){
        printf("Error: Invalid filename.\n");
        freeMaze(this);
        exit(EXIT_FILE);
    } else if (mazeCheck == 3){
        printf("Error: maze file does not have expected format.\n");
        freeMaze(this);
        exit(EXIT_INV);
    } else {
        printf("File %s successfully loaded.\n",argv[1]);
        getInput(this);
        printf("You have completed the maze!\n");
        freeMaze(this);
        exit(EXIT_SUCCESS);
    }
    return 0;
}