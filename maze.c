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

/**
* @brief Free the memory allocated to the maze struct
*
* @param this the pointer to the maze struct being freed
*/
void freeMaze(maze* this){
    if (this == NULL){
        return;
    }

    if (this->mazeArray != NULL) {
        for (int i = 0; i < this->height; i++){
            free(this->mazeArray[i]);
            this->mazeArray[i] = NULL;
        }
        free(this->mazeArray);
        this->mazeArray = NULL;

    }
}

/**
* @brief Display the map of the maze
*
* @param this the pointer to the maze struct
*/
void showMap(maze* this){
    printf("Map: \n");
    for (int y = 0; y < this->height; y++){
        for (int x = 0; x < this->width; x++){
            printf("%c", this->mazeArray[y][x]);
        }
        printf("\n");
    }
}

/**
* @brief Check each character in the maze array is valid
* @param this the pointer to the maze struct
* @return int 0 if valid, 3 if invalid
*/
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
                    this->mazeArray[y][x] = 'X'; // Replaces the start with 'X', doesn't need to put back 'S' later as it isn't necessary info for the user
                    this->currentPos[0] = y, this->currentPos[1] = x;
                }
            } else if (c == 'E'){
                if (eCount != 0){
                    return 3;
                } else {
                    eCount = 1;
                }
            } else if (c != ' ' && c != '#'){
                return 3;
            }
        }
    }
    if (sCount == 0 || eCount == 0){
        return 3;
    } else {
        return 0;
    }
}

/**
* @brief Allocate memory to the maze struct and check the height and width of the maze
* @param this the pointer to the maze struct
* @param filename the file pointer to open
* @return int 0 if valid, 2 if file is invalid and 3 if maze is invalid
*/
int createMaze(maze* this, char* filename){
    // call openFile()
    // if it is unopenable, give an error message and return 2
    FILE* file = fopen(filename,"r");
    if (file == NULL){
        return 2;
    }  
    // otherwise, check first row is of length between 5 and 100, and store as width
    
    char line[1000];
    char tempArray[1000][1000]; // a larger than necessary array means it will not break if the maze is too large

    int count = 0;
    int width = 0;
    while (fgets(line, sizeof(line), file)){ // sizeof(line) acts like the buffer
        int i = 0;
        while (line[i+1] != 'n'){ // stops at the newline
            tempArray[count][i] = line[i];
            i++;
        }
        if (i < 5 || i > 100 || (width != i && count > 0)){  // check if wrong size or line width is different to previous width
            return 3;
            
        } else {
            width = i;
        }
        count++;

    }
    int height = count;
    if (height < 5 || height > 100){
        return 3;
    }

    this->height = height;
    this->width = width;
    this->mazeArray = malloc(this->height * sizeof(char*));

    for (int y = 0; y < this->height; y++){
        this->mazeArray[y] = malloc(this->width);
        for (int x = 0; x < this->width; x++){
            this->mazeArray[y][x] = tempArray[y][x];
        }
    }

    fclose(file);
    int mazeTest = validateMaze(this);
    return mazeTest;

}

/**
* @brief Updates the position of the player from their current location to new location
* @param this the pointer to the maze struct
* @param newPos the pointer to the new position that the player is moving to
*/
void movePlayer(maze* this, int* newPos){
    this->mazeArray[this->currentPos[0]][this->currentPos[1]] = ' ';
    this->currentPos[0] = newPos[0], this->currentPos[1] = newPos[1];
    this->mazeArray[newPos[0]][newPos[1]] = 'X';
}

/**
* @brief Check the location the player is moving to is valid
* @param this the pointer to the maze struct
* @param newPos the pointer to the new position that the player is moving to
* @return int 0 if the end is reached, 1 if the move is valid otherwise and 2 if the move is invalid
*/
int checkTile(maze* this, int* newPos){
    if (newPos[0] < 0 || newPos[0] >= this->height || newPos[1] < 0 || newPos[1] >= this->width){
        printf("Cannot make this move.\n");
        return 2;
    } else {
        char value = this->mazeArray[newPos[0]][newPos[1]];
        if (value == 'E'){
            return 0;
        } else if (value == ' ' || value == 'S'){
            movePlayer(this, newPos);
            return 1;
        } else {
            printf("Cannot make this move.\n");
            return 2;
        }
    }
}

/**
* @brief Calculate the player's coordinates after moving up
* @param this the pointer to the maze struct
* @return int 0 if the end is reached, 1 if the move is valid otherwise and 2 if the move is invalid
*/
int moveUp(maze* this){
    int newPos[2] = {};
    newPos[0] = this->currentPos[0] - 1; 
    newPos[1] = this->currentPos[1];
    int value = checkTile(this, newPos);
    if (value <= 1){
        printf("You have moved up.\n");
    }
    return value;
    
}

/**
* @brief Calculate the player's coordinates after moving left
* @param this the pointer to the maze struct
* @return int 0 if the end is reached, 1 if the move is valid otherwise and 2 if the move is invalid
*/
int moveLeft(maze* this){
    int newPos[2] = {};
    newPos[0] = this->currentPos[0]; 
    newPos[1] = this->currentPos[1] - 1;
    int value = checkTile(this, newPos);
    if (value <= 1){
        printf("You have moved left.\n");
    }
    return value;
}

/**
* @brief Calculate the player's coordinates after moving down
* @param this the pointer to the maze struct
* @return int 0 if the end is reached, 1 if the move is valid otherwise and 2 if the move is invalid
*/
int moveDown(maze* this){
    int newPos[2] = {};
    newPos[0] = this->currentPos[0] + 1; 
    newPos[1] = this->currentPos[1];
    int value = checkTile(this, newPos);
    if (value <= 1){
        printf("You have moved down.\n");
    }
    return value;
}

/**
* @brief Calculate the player's coordinates after moving right
* @param this the pointer to the maze struct
* @return int 0 if the end is reached, 1 if the move is valid otherwise and 2 if the move is invalid
*/
int moveRight(maze* this){
    int newPos[2] = {};
    newPos[0] = this->currentPos[0]; 
    newPos[1] = this->currentPos[1] + 1;
    int value = checkTile(this, newPos);
    if (value <= 1){
        printf("You have moved right.\n");
    }
    return value;
}

/**
* @brief Get the player's input repeatedly
* @param this the pointer to the maze struct
* @return int 0 when the end is reached
*/
int getInput(maze* this){
    printf("W - Move up.\n");
    printf("A - Move left.\n");
    printf("S - Move down.\n");
    printf("D - Move right.\n");
    printf("M - Display map.\n");
    
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
                printf("Invalid input.\n");
                break;
        }
    }
    return 0;
}

int main(int argc, char* argv[]){
    if (argc != 2){ // needs exactly ./maze and filename for arguments
        printf("Usage: maze <filename>.\n");
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