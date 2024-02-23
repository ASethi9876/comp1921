#!/bin/bash
#gcc maze.c -m maze

echo -e "Argument Tests"

echo -n "No argument - "
./maze > tmp
if grep -q "Usage: maze <filename>." tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Two arguments - "
./maze a b > tmp
if grep -q "Usage: maze <filename>." tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


echo -n "Invalid file type - "
./maze maze > tmp
if grep -q "Error: Invalid filename." tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Unvailable file - "
./maze null.txt > tmp
if grep -q "Error: Invalid filename." tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Loading successful file - "
./maze standard_maze.txt > tmp
if grep -q "File standard_maze.txt successfully loaded.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "Testing Maze Files"

echo -n "No maze given - "
./maze no_maze.txt > tmp
if grep -q "Error: maze file does not have expected format.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maze is too small - "
./maze small_maze.txt > tmp
if grep -q "Error: maze file does not have expected format.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maze is too large - "
./maze large_maze.txt > tmp
if grep -q "Error: maze file does not have expected format.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maze is not rectangular - "
./maze non_rect_maze.txt > tmp
if grep -q "Error: maze file does not have expected format.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maze has invalid characters - "
./maze inv_char_maze.txt > tmp
if grep -q "Error: maze file does not have expected format.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maze has multiple starts - "
./maze two_starts_maze.txt > tmp
if grep -q "Error: maze file does not have expected format.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maze has no end - "
./maze endless_maze.txt > tmp
if grep -q "Error: maze file does not have expected format.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Minimum size for maze - "
./maze min_maze.txt > tmp
if grep -q "Enter input: ";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maximum size for maze - "
./maze max_maze.txt > tmp
if grep -q "Enter input: ";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Standard size maze - "
./maze standard_maze.txt > tmp
if grep -q "Enter input: ";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "Testing Inputs"

echo -n "No input given - "
echo "" | ./maze standard_maze.txt <> tmp
if grep -q "Invalid input.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Invalid input given - "
echo "x" | ./maze standard_maze.txt <> tmp
if grep -q "Invalid input.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "W inputted for valid move - "
echo "W" | ./maze standard_maze.txt <> tmp
if grep -q "You have moved up.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "w inputted for valid move - "
echo "W" | ./maze standard_maze.txt <> tmp
if grep -q "You have moved up.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "w inputted for invalid move - "
echo "W" | ./maze unmovable_maze.txt <> tmp
if grep -q "Cannot make this move.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "a inputted for valid move - "
echo "a" | ./maze standard_maze.txt <> tmp
if grep -q "You have moved left.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "a inputted for invalid move - "
echo "a" | ./maze unmovable_maze.txt <> tmp
if grep -q "Cannot make this move.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "s inputted for valid move - "
echo "s" | ./maze standard_maze.txt <> tmp
if grep -q "You have moved down.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "s inputted for invalid move - "
echo "s" | ./maze unmovable_maze.txt <> tmp
if grep -q "Cannot make this move.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "d inputted for valid move - "
echo "d" | ./maze standard_maze.txt <> tmp
if grep -q "You have moved right.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "d inputted for invalid move - "
echo "d" | ./maze unmovable_maze.txt <> tmp
if grep -q "Cannot make this move.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "m inputted"
echo "d" | ./maze standard_maze.txt <> tmp
if grep -q "Map:";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Win condition reached - "
echo "w" | ./maze instant_win_maze.txt <> tmp
if grep -q "You have completed the maze!";
then
    echo "PASS"
else
    echo "FAIL"
fi