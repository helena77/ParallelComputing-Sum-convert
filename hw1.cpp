/**
* @file hw1.cpp - performs the same task as hw1_setup.cpp, but using a
*                 parallel algorithm using two threads to do so
* @author Helena Wang
* @see "Seattle University, CPSC5600, Fall 2018"
*/
#include <iostream>
#include "ThreadGroup.h"
using namespace std;

const int N_THREADS = 2;

int encode(int v) {
	// do something time-consuming (and arbitrary)
	for (int i = 0; i < 500; i++)
		v = ((v * v) + v) % 10;
	return v;
}

int decode(int v) {
	// do something time-consuming (and arbitrary)
	return encode(v);
}

class EncodeThread {
public:
	void operator()(int id, int *sharedData, int length) {
		int *data = (int*)sharedData;
		int length_per_thread = length / N_THREADS;
		int start = id * length_per_thread;
		for (int i = start; i < start + length_per_thread; i++)
			data[i] = encode(data[i]);
	}
};

class DecodeThread {
public:
	void operator()(int id, int *sharedData, int length) {
		int *data = (int*)sharedData;
		int length_per_thread = length / N_THREADS;
		int start = id * length_per_thread;
		for (int i = start; i < start + length_per_thread; i++)
			data[i] = decode(data[i]);
	}
};


void prefixSums(int *data, int length) {
	int encodedSum = 0;

	ThreadGroup<EncodeThread> encoders;
	for (int i = 0; i < N_THREADS; i++)
		encoders.createThread(i, &data);
	encoders.waitForAll();

	// Report the results once all the threads join (i.e., are finished)
	std::cout << "All threads are now done!" << std::endl;
	for (int i = 0; i < N_THREADS; i++)
		std::cout << "thread " << i << " Done" << std::endl;

	for (int i = 0; i < length; i++) {
		encodedSum += data[i];
		data[i] = encodedSum;
	}

	ThreadGroup<DecodeThread> decoders;
	for (int i = 0; i < N_THREADS; i++)
		decoders.createThread(i, &data);
	decoders.waitForAll();

	// Report the results once all the threads join (i.e., are finished)
	std::cout << "All threads are now done!" << std::endl;
	for (int i = 0; i < N_THREADS; i++)
		std::cout << "thread " << i << " Done" << std::endl;
}

int main() {
	int length = 1000 * 1000;

	// make array
	int *data = new int[length];
	for (int i = 1; i < length; i++)
		data[i] = 1;
	data[0] = 6;

	// transform array into converted/deconverted prefix sum of original
	prefixSums(data, length);

	// printed out result is 6, 6, and 2 when data[0] is 6 to start and the rest 1
	cout << "[0]: " << data[0] << endl
		<< "[" << length / 2 << "]: " << data[length / 2] << endl
		<< "[end]: " << data[length - 1] << endl;

	delete[] data;
	return 0;
}


