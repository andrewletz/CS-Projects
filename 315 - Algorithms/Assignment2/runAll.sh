#!/bin/bash
echo "20 3"
python3 longestPath.py < inSample1.txt
echo
echo "6 8"
python3 longestPath.py < inSample2.txt
echo
echo "149 1"
python3 longestPath.py < inPath100.txt
echo
echo "29 268435456"
python3 longestPath.py < inLarge1.txt
echo
echo "1338 32"
python3 longestPath.py < inRan.txt
echo
echo "19 262144"
python3 longestPath.py < inLarge2.txt