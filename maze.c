struct maze{
    int height;
    int length;
    char* mazeArray[height][width];
}
struct pos{
    int x;
    int y;
}
int validateMaze{
    // make sure 5 <= height <= 100
    // make sure 5 <= width <= 100
    // loop through each row to check:
        // each row is of equal length
        // each character is either ' ', '#', 'S' or 'E'
        // there is exactly one 'S' and 'E'
        // when 'S' is reached replace with 'X'
    // if any of these fail give error message and end program
    // go back to main
}
int moveUp(currentPos){
    // calculate position if moved up and store as newPos
    // call checkTile and return result
}
int moveLeft(currentPos){
    // calculate position if moved left and store as newPos
    // call checkTile and return result
}
int moveDown(currentPos){
    // calculate position if moved down and store as newPos
    // call checkTile and return result
}
int moveRight(currentPos){
    // calculate position if moved right and store as newPos
    // call checkTile and return result
}
int checkTile(currentPos, newPos){
    // return code 0 if input location is ' ' or 'S' and call movePlayer
    // return code 1 if input location is 'E' and call movePlayer
    // return code 2 & send error message if input location is a wall or out of bounds
}
int movePlayer(currentPos, newPos){
    // if 0 or 1 returned, make current position of 'X' into ' '
    // change new position given to 'X'
}
void showMap{
    // display maze file line by line
}
int main{
    // if the file exists and is in .txt format:
        // load maze from file
        // call validateMaze
    // else give error message and end program
    // loop until E reached:
        // ask for input
        // w - call moveUp
        // a - call moveLeft
        // s - call moveDown
        // d - call moveRight
        // m - call showMap
    // if end found (return code = 1) give win message
}