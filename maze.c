struct maze{
    int height;
    int width;
    char* mazeArray[height][width];
}
struct pos{
    int x;
    int y;
}
struct validateMaze(){
    // make sure 5 <= height <= 100
    // make sure 5 <= width <= 100
    // loop through each row to check:
        // each row is of equal length
        // each character is either ' ', '#', 'S' or 'E'
        // there is exactly one 'S' and 'E'
        // when 'S' is reached replace with 'X'
    // if any of these fail give error message and end program
    // go back to main and return position of X
}
int moveUp(currentPos){
    // calculate position if moved up and store as newPos
    // call checkTile and return result
    // alert user that they have moved up if checkTile returns 0 or 1
}
int moveLeft(currentPos){
    // calculate position if moved left and store as newPos
    // call checkTile and return result
    // alert user that they have moved left if checkTile returns 0 or 1
}
int moveDown(currentPos){
    // calculate position if moved down and store as newPos
    // call checkTile and return result
    // alert user that they have moved down if checkTile returns 0 or 1
}
int moveRight(currentPos){
    // calculate position if moved right and store as newPos
    // call checkTile and return result
    // alert user that they have moved right if checkTile returns 0 or 1
}
int checkTile(currentPos, newPos){
    // return code 0 if input location is ' ' or 'S' and call movePlayer
    // return code 1 if input location is 'E' and call movePlayer
    // return code 2 & give message if input location is a wall or out of bounds
}
int movePlayer(currentPos, newPos){
    // make current position of 'X' into ' '
    // change new position given to 'X'
}
void showMap(){
    // display maze file line by line
}
int main(){
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