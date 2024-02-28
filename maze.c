// a struct to hold the maze and the position of X
struct maze{
    int height;
    int width;
    int* position[2]
    char* mazeArray[height][width];
}

// a procedure to tidy up the dynamically allocated memory before exiting the program
void freeMaze(){
    // check maze isn't null
    // set each pointer to null
    // set array of null pointers to 0
    // free image pointer
}

// a function to create the  maze struct
int createMaze(mazefile){
    // check first row is of length between 5 and 100, and store as width
    // loop through each row of the first column to check between 5 and 100, and store as height
    // if it is:
        // initialise a pointer for the maze struct
        // allocate array height as height
        // loop through each row:
            // allocate the array width for that row as width
            // convert each character to an element of the maze array 
            // if \n reached early or there are still chars left on the row call freeMaze(), give an error message and return 1
        // call validateMaze() and return the result
    // else:
        // give error message and return 1
}

int validateMaze(mazefile){
    // loop through each element of each row of mazeArray:
        // each character is either ' ', '#', 'S' or 'E'
        // there is exactly one 'S' and 'E'
        // if either of these fail, call freeMaze(), give an error message and return 1
        // when 'S' is reached replace with 'X' and store position in struct
    // if successful, go back to main and 0
}

int getInput(){
    // loop until E reached:
        // ask for input
        // w - call moveUp()
        // a - call moveLeft()
        // s - call moveDown()
        // d - call moveRight()
        // m - call showMap()
        // if the end is found / 1 is returned, return 1
}


int moveUp(){
    // calculate position if moved up and store as a 1d array called newPos
    // call checkTile() and return result
    // alert user that they have moved up if checkTile() returns 0 or 1
}

int moveLeft(){
    // calculate position if moved left and store as a 1d array called newPos
    // call checkTile() and return result
    // alert user that they have moved left if checkTile() returns 0 or 1
}

int moveDown(){
    // calculate position if moved down and store as a 1d array called newPos
    // call checkTile() and return result
    // alert user that they have moved down if checkTile() returns 0 or 1
}

int moveRight(){
    // calculate position if moved right and store as a 1d array called newPos
    // call checkTile() and return result
    // alert user that they have moved right if checkTile() returns 0 or 1
}

int checkTile(newPos){
    // search for the value stored in mazeArray at the position given
    // return code 0 if input location is ' ' or 'S' and call movePlayer()
    // return code 1 if input location is 'E' and call movePlayer()
    // return code 2 & give message if input location is '#' or outside of the array

void movePlayer(newPos){
    // make current position of 'X' into ' '
    // change new position given to 'X'
    // update position in struct to match this
}

void showMap(){
    // loop through each row of the maze and print it
}

int main(){
    // if the file exists and is in .txt format:
        // call ValidateMaze(), end program if 1 returned
        // call getInput()
        // once 0 is returned from getInput():
            // give win message+
            // call freeMaze()
            // end program
    // else give error message and end program
}