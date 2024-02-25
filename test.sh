#!/bin/bash

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
timeout 0.2s ./maze mazes/maze_not_text > tmp
if grep -q "Error: Invalid filename." tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Unvailable file - "
timeout 0.2s ./maze mazes/null.txt > tmp
if grep -q "Error: Invalid filename." tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "Testing Maze Files"

echo -n "No maze given - "
timeout 0.2s ./maze mazes/no_maze.txt > tmp
if grep -q "Error: maze file does not have expected format.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maze is too small - "
timeout 0.2s ./maze mazes/small_maze.txt > tmp
if grep -q "Error: maze file does not have expected format.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maze is too large - "
timeout 0.2s ./maze mazes/large_maze.txt > tmp
if grep -q "Error: maze file does not have expected format.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maze is not rectangular - "
timeout 0.2s ./maze mazes/non_rect_maze.txt > tmp
if grep -q "Error: maze file does not have expected format.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maze has invalid characters - "
timeout 0.2s ./maze mazes/inv_char_maze.txt > tmp
if grep -q "Error: maze file does not have expected format.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maze has multiple starts - "
timeout 0.2s ./maze mazes/two_starts_maze.txt > tmp
if grep -q "Error: maze file does not have expected format.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maze has no end - "
timeout 0.2s ./maze mazes/endless_maze.txt > tmp
if grep -q "Error: maze file does not have expected format.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Minimum size for maze - "
timeout 0.2s ./maze mazes/min_maze.txt > tmp
if grep -q "File standard_maze.txt successfully loaded.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maximum size for maze - "
timeout 0.2s ./maze mazes/max_maze.txt > tmp
if grep -q "File standard_maze.txt successfully loaded.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Standard size maze - "
timeout 0.2s ./maze mazes/standard_maze.txt > tmp
if grep -q "File standard_maze.txt successfully loaded.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "Testing Inputs"

echo -n "No input given - "
echo "" | timeout 0.2s ./maze mazes/standard_maze.txt > tmp
if grep -q "Invalid input.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Invalid input given - "
echo "x" | timeout 0.2s ./maze mazes/standard_maze.txt > tmp
if grep -q "Invalid input.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "W inputted for valid move - "
echo "W" | timeout 0.2s ./maze mazes/standard_maze.txt > tmp
if grep -q "You have moved up.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "w inputted for valid move - "
echo "W" | timeout 0.2s ./maze mazes/standard_maze.txt > tmp
if grep -q "You have moved up.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "w inputted for invalid move - "
echo "W" | timeout 0.2s ./maze mazes/unmovable_maze.txt > tmp
if grep -q "Cannot make this move.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "a inputted for valid move - "
echo "a" | timeout 0.2s ./maze mazes/standard_maze.txt > tmp
if grep -q "You have moved left.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "a inputted for invalid move - "
echo "a" | timeout 0.2s ./maze mazes/unmovable_maze.txt > tmp
if grep -q "Cannot make this move.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "s inputted for valid move - "
echo "s" | timeout 0.2s ./maze mazes/standard_maze.txt > tmp
if grep -q "You have moved down.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "s inputted for invalid move - "
echo "s" | timeout 0.2s ./maze mazes/unmovable_maze.txt > tmp
if grep -q "Cannot make this move.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "d inputted for valid move - "
echo "d" | timeout 0.2s ./maze mazes/standard_maze.txt > tmp
if grep -q "You have moved right.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "d inputted for invalid move - "
echo "d" | timeout 0.2s ./maze mazes/unmovable_maze.txt > tmp
if grep -q "Cannot make this move.";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "m inputted"
echo "d" | timeout 0.2s ./maze mazes/standard_maze.txt > tmp
if grep -q "Map:";
then
    echo "PASS"
else
    echo "FAIL"
fi

# Includes both valid and invalid moves
echo -n "Full maze playthrough - "
timeout 0.2s ./maze mazes/standard_maze.txt <inputs/input.txt> tmp
if grep -q "You have completed the maze!";
then
    echo "PASS"
else
    echo "FAIL"
fi
