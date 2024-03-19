#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_ARG 1
#define EXIT_FILE 2
#define EXIT_INV 3

// a struct to hold the maze and the position of the player
struct maze{
    int height;
    int width;
    int* currentPos[2]
    char* mazeArray[height][width];
}

// a procedure to tidy up the dynamically allocated memory before exiting the program
void freeMaze(){
    // check maze isn't null
    // set each pointer to null
    // set array of null pointers to 0
    // free image pointer
}

// a function to create the maze struct
int createMaze(filename){
    // call openFile()
    // if it is unopenable, give an error message and return 2
    FILE* file = fopen(filename,"r");
    if (file == NULL){
        return 2;
    }

    // otherwise, check first row is of length between 5 and 100, and store as width
    // loop through each row of the first column:
        // increase a counter by 1 for each iteration
    // check counter is between 5 and 100, and store as height
    // if height and width are valid:
        // initialise a pointer for the maze struct
        // allocate array height as height
        // loop through each row:
            // allocate the array width for that row as width
            // convert each character to an element of the maze array 
            // if \n reached early or there are still chars left on the row call freeMaze(), give an error message and return 1
        // call validateMaze() and return the result
    // else:
        // give error message and return 3
    }

int validateMaze(){
    // loop through each element of each row of mazeArray:
        // each character is either ' ', '#', 'S' or 'E'
        // there is exactly one 'S' and 'E'
        // if either of these fail, call freeMaze(), give an error message and return 3
        // when 'S' is reached replace with 'X' and store position in struct
    // if successful, go back to main and 0
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
                showMap();
                break;

            default:
                printf("Invalid input.");
                break;
        }
    return 0;
    }
}


int moveUp(maze* this){
    // get both values from currentPos
    // subtract 1 from currentPos[1]
    // store as newPos
    // call checkTile() and return result
    // alert user that they have moved up if checkTile() returns 0 or 1
    int newPos[2] = this->currentPos;
    newPos[1] -= 1;
    int value = checkTile(this, newPos);
    if (value <= 1){
        printf("You have moved up.");
    }
    return value;
    
}

int moveLeft(maze* this){
    // get both values from currentPos
    // subtract 1 from currentPos[0]
    // store as newPos
    // call checkTile() and return result
    // alert user that they have moved left if checkTile() returns 0 or 1
}

int moveDown(maze* this){
    // get both values from currentPos
    // add 1 to currentPos[1]
    // store as newPos
    // call checkTile() and return result
    // alert user that they have moved down if checkTile() returns 0 or 1
}

int moveRight(maze* this){
    // get both values from currentPos
    // add 1 to currentPos[0]
    // store as newPos
    // call checkTile() and return result
    // alert user that they have moved right if checkTile() returns 0 or 1
}

int checkTile(maze* this, int* newPos){
    // search for the value stored in mazeArray at the position given
    // return code 0 if input location is ' ' or 'S' and call movePlayer()
    // return code 1 if input location is 'E' and call movePlayer()
    // return code 2 & give message if input location is '#' or outside of the array
    if (newPos[0] < 0 || newPos[0] > this->height || newPos[1] < 0 || newPos[1] > this->width){
        return 2;
    } else {
        char value = this->mazeArray[newPos[0]][newPos[1]];
        if (value = 'E') {
            return 0;
        } else if (value = ' ' || value = 'S'){
            movePlayer(this, newPos);
            return 1;
        } else {
            return 2;
        }
    }
}

void movePlayer(maze* this, int* newPos){
    // make current position of 'X' in mazeArray into ' '
    // change new position given to 'X'
    // update currentPos in struct to match this
    this->mazeArray[currentPos[0]][currentPos[1]] = ' ';
    this->currentPos = newPos;
    this->mazeArray[newPos[0]][newPos[1]] = 'X';
}

void showMap(){
    // loop through each row of the maze and print it
}

int main(args){
    // DON'T NEED TO check the file is in .txt format
    // check args are valid
    // if it is:
        // call validateMaze(), end program if 2/3 returned
        // call getInput()
        // once 0 is returned from getInput():
            // give win message
            // call freeMaze()
            // end program
    // else give error message and end program exit code 1
    if (args.length() != 1){
        printf("Usage: maze <filename>.");
        exit(EXIT_ARG);
    }

    int mazeCheck = validateMaze(args[0]);
    if (mazeCheck == 2){
        printf("Error: Invalid filename.");
        exit(EXIT_FILE);
    } else if (mazeCheck == 3){
        printf("Error: maze file does not have expected format.");
        exit(EXIT_MAZE);
    
    getInput(this);
    printf("You have completed the maze!");
    freeMaze();
    exit(EXIT_SUCCESS);
    
}