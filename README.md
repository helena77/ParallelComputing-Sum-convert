# Sum-convert
The sequential program is a kind of prefix sum, except that each value in the array is first (expensively) encoded before it is added into the sum and the prefix sums are then (expensively) decoded before putting them back in the original array as the result. The idea is that we are simulating a more complex encoding and decoding function.

The project shold be able to substantially speed up the program by using two threads running at the same time

ThreadGroup.h -- a class that uses pthreads to create threads and allows you to wait for all of them to finish
hw1_setup.cpp -- the sequential version of the program
hw1.cpp -- performs the same task as hw1_setup.cpp, but using a parallel algorithm using two threads to do so.
example.cpp -- example of how to use the ThreadGroup class
Makefile -- in order to build it all
