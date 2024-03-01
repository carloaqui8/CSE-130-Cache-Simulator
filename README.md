# CSE-130-Cache-Simulator
Completed Fall 2023

Know the examples
Example 1 (FIFO): Easy
Example 2 (LRU): If you access an element, move it to the "front of the cache"
Example 3 (CLOCK): Clock pointer initially pointing to the first item in the list. If accessed again, reference bit 1. When compulsory miss, make reference bit 0, move pointer to the next 0, replace, move pointer forward by one.
Compulsory vs Capacity Miss:
Compulsory misses counted by if you access an item not in cache
Capacity misses counted by if cache is full and item we want has been seen before
Example: Add A, kicked out, add A again. Need a separate "history" array/list to check if the item has been seen before.
Example output:
a
MISS
b
MISS
c
MISS
//Ctrl + d
3 0
