#!/bin/bash
#gcc maze.c -m maze

echo -e "Argument Tests"

echo -n "No argument -"
./maze > tmp
if grep -q "Usage: mazeGame <filename>" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Two arguments -"
./maze a b> tmp
if grep -q "Usage: mazeGame <filename>" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


echo -n "Invalid file type -"
./maze maze > tmp
if grep -q "Error: Invalid filename" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Unvailable file -"
./maze null.txt > tmp
if grep -q "Error: Invalid filename" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Loading successful file - "
./maze successful_data.txt > tmp
if grep -q "File successful_data.txt successfully loaded";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "No maze given - "
./maze no_maze.txt > tmp
if grep -q "Error: maze file does not have expected format";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maze is too small - "
./maze small_maze.txt > tmp
if grep -q "Error: maze file does not have expected format";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maze is too large - "
./maze large_maze.txt > tmp
if grep -q "Error: maze file does not have expected format";
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Maze - "
./maze small_maze.txt > tmp
if grep -q "Error: maze file does not have expected format";
then
    echo "PASS"
else
    echo "FAIL"
fi