struct maze{
    int height;
    int length;
    char* mazeArray[height][width];
}
struct pos{
    int x;
    int y;
    int returnCode;
}
int validateMaze{
    // check maze is within min / max height / width
    // check each row / column is equal
    // check all characters in maze are valid
}
int moveUp(pos){
    // calculate position if moved up
    // call checkTile
}
int moveLeft(pos){
    // calculate position if moved left
    // call checkTile
}
int moveDown(pos){
    // calculate position if moved down
    // call checkTile
}
int moveRight(pos){
    // calculate position if moved right
    // call checkTile
}
int checkTile(pos){
    // return code 0 if input location is free and call movePlayer
    // return code 1 if input location is the end and call movePlayer
    // return code 2 & send error message if input location is a wall
    // return code 3 & send error message if input location is out of bounds
}
int movePlayer(pos){
    // if 0 or 1 returned, make previous position of 'X' into ' '
    // change pos given in maze to 'X'
    // return code 1 if end reached, 0 otherwise
}
void showMap{
    // display maze file line by line
}
int main{
    // load from file
    // validate maze file
    // loop until E reached:
        // ask for input
        // w - call moveUp
        // a - call moveLeft
        // s - call moveDown
        // d - call moveRight
        // m - call showMap
    // if end found (return code = 1) give win message
}