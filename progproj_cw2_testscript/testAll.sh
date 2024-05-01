#!/bin/bash

# My masterpiece of a Bash script to test the non-existent Maze game!
# Used this resource to find out about "<<<" (because making a file to send standard-in inputs was killing me): https://askubuntu.com/questions/678915/whats-the-difference-between-and-in-bash
# Also used this resource to find out how to get Bash to accept "\n"s: https://stackoverflow.com/questions/3005963/how-can-i-have-a-newline-in-a-string-in-sh
# I don't have "input files" in the literal sense, because my inputs are fed directly as strings below.

# Function to do the expected output testing, so I don't lose my mind with copy-paste
# Parameter #1: Test Name
# Parameter #2: Expected Output
testOutput()
{
    # Read output file content (adding \n as everything should end with that)
    outputFile=$(cat out.txt)
    outputFile+=$'\n'

    # Compare it to our expected, and print a nice message depending on what we get
    if [ "$outputFile" = "$2" ];
    then
        echo -e $1 " - \e[32mPASS\e[0m"
    else
        echo -e $1 " - \e[31mFAIL\e[0m"
        echo -e "Expected: $2"
        echo "Actual: $outputFile"
    fi
}

# All valid situations are tested below simply by the prescence of valid case handling.

# =========================
# INVALID COMMAND LINE TESTS:
# =========================
# Invalid filename
./maze invalid.txt > out.txt
testOutput "Invalid Filename" $'Error: Unable to read maze file.\n'

# Too few arguments
./maze > out.txt
testOutput "Too Few Arguments" $'Usage: maze <mazefile>.\n'

# Too many arguments
./maze testdata/TODOTODOTODO testdata/TODOTODOTODO > out.txt
testOutput "Too Many Arguments" $'Usage: maze <mazefile>.\n'

# =========================
# MAZE META TESTS:
# =========================
# > 100 Width
./maze testdata/toowide.txt > out.txt
testOutput "Too Wide" $'Error: Maze too wide.\n'

# < 5 Width
./maze testdata/toothin.txt > out.txt
testOutput "Too Thin" $'Error: Maze too thin.\n'

# 0 Width
./maze testdata/zerowidth.txt > out.txt
testOutput "Zero Width" $'Error: Maze too thin.\n'

# > 100 Height
./maze testdata/tootall.txt > out.txt
testOutput "Too Tall" $'Error: Maze too tall.\n'

# < 5 Height
./maze testdata/tooshort.txt > out.txt
testOutput "Too Short" $'Error: Maze too short.\n'

# 0 Height
./maze testdata/empty.txt > out.txt
testOutput "Empty File" $'Error: Maze too thin.\n'

# Must be rectangle -> A row is longer than the rest.
./maze testdata/notrectmorewide.txt > out.txt
testOutput "1 Row Wider Than Rest" $'Error: Maze must be rectangular.\n'

# Must be rectangle -> A row is thinner than the rest.
./maze testdata/notrectmorethin.txt > out.txt
testOutput "1 Row Thinner Than Rest" $'Error: Maze must be rectangular.\n'

# Must be rectangle -> A middle row goes beyond the limit (potential buffer overrun check).
./maze testdata/notrectboundspush.txt > out.txt
testOutput "1 Row Past Limit" $'Error: Maze too wide.\n'

# =========================
# MAZE CONTENT TESTS:
# =========================
# Contains invalid character
./maze testdata/invalidchar.txt > out.txt
testOutput "Invalid Character" $'Error: Unexpected symbol in maze.\n'

# No start
./maze testdata/invalidnomazestart.txt > out.txt
testOutput "No Maze Start" $'Error: No maze starting point.\n'

# No end point
./maze testdata/invalidnomazeend.txt > out.txt
testOutput "No Maze End" $'Error: No maze end point.\n'

# Multiple starts
./maze testdata/invalidmultistartmaze.txt > out.txt
testOutput "Multiple Maze Starts" $'Error: Multiple maze starting points.\n'

# Multiple end points
./maze testdata/invalidmultiendmaze.txt > out.txt
testOutput "Multiple Maze Ends" $'Error: Multiple maze ending points.\n'

# =========================
# MAZE INTERACTION TESTS:
# =========================
# Invalid Input
./maze testdata/pathright.txt <<< $'I\nD\nD\n' > out.txt
testOutput "Invalid Input" $'Error: Invalid input.\nYou won the game!\n'

# MAP PRINTING TESTS:
# Shows initial position (Using "M")
./maze testdata/pathright.txt <<< $'M\nD\nD\n' > out.txt
testOutput "Shows Initial Position" \
    $'\n#####\n#X  #\n#####\n#   #\n#####\nYou won the game!\n'

# Map print shows changes mid-game (using M *and* m)
./maze testdata/pathright.txt <<< $'D\nM\nm\nD\n' > out.txt
testOutput "Map Print Updates Mid-Game" \
    $'\n#####\n# X #\n#####\n#   #\n#####\n\n#####\n# X #\n#####\n#   #\n#####\nYou won the game!\n'

# =========================
# MAP MOVEMENT TESTS:
# (I always win at the end of all of these so I can cleanly end each program *and* be sure we did stay in the right place and didn't move even when printing the message)
# =========================
# Valid Move Up & Win Moving Up
./maze testdata/pathup.txt <<< $'W\nw\n' > out.txt
testOutput "Valid Move Up" $'You won the game!\n'

# Valid Move Right & Win Moving Right
./maze testdata/pathright.txt <<< $'D\nd\n' > out.txt
testOutput "Valid Move Right" $'You won the game!\n'

# Valid Move Down & Win Moving Down
./maze testdata/pathdown.txt <<< $'S\ns\n' > out.txt
testOutput "Valid Move Down" $'You won the game!\n'

# Valid Move Left & Win Moving Left
./maze testdata/pathleft.txt <<< $'A\na\n' > out.txt
testOutput "Valid Move Left" $'You won the game!\n'

# Invalid Move Up & Win
./maze testdata/pathright.txt <<< $'W\nw\nD\nD\n' > out.txt
testOutput "Invalid Move Up" $'You bumped into a wall!\nYou bumped into a wall!\nYou won the game!\n'

# Invalid Move Right & Win
./maze testdata/pathup.txt <<< $'D\nd\nW\nw\n' > out.txt
testOutput "Invalid Move Right" $'You bumped into a wall!\nYou bumped into a wall!\nYou won the game!\n'

# Invalid Move Down & Win
./maze testdata/pathright.txt <<< $'S\ns\nD\nD\n' > out.txt
testOutput "Invalid Move Down" $'You bumped into a wall!\nYou bumped into a wall!\nYou won the game!\n'

# Invalid Move Left & Win
./maze testdata/pathright.txt <<< $'A\na\nD\nD\n' > out.txt
testOutput "Invalid Move Left" $'You bumped into a wall!\nYou bumped into a wall!\nYou won the game!\n'

# Invalid Move Left (into edge) & Win
./maze testdata/openwalls.txt <<< $'A\nA\nA\na\nS\nS\n' > out.txt
testOutput "Invalid Move Left (Into Edge)" $'You bumped into a wall!\nYou bumped into a wall!\nYou won the game!\n'

# Invalid Move Right (into edge) & Win
./maze testdata/openwalls.txt <<< $'D\nD\nD\nd\nA\nA\nA\nA\nS\nS\n' > out.txt
testOutput "Invalid Move Right (Into Edge)" $'You bumped into a wall!\nYou bumped into a wall!\nYou won the game!\n'

# Invalid Move Up (into edge) & Win
./maze testdata/openwalls.txt <<< $'W\nW\nW\nw\nS\nS\nA\nA\nS\nS\n' > out.txt
testOutput "Invalid Move Up (Into Edge)" $'You bumped into a wall!\nYou bumped into a wall!\nYou won the game!\n'

# Invalid Move Down (into edge) & Win
./maze testdata/openwalls.txt <<< $'S\nS\nS\ns\nW\nW\nA\nA\nS\nS\n' > out.txt
testOutput "Invalid Move Down (Into Edge)" $'You bumped into a wall!\nYou bumped into a wall!\nYou won the game!\n'