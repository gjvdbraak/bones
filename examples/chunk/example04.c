//
// This file is part of the Bones source-to-source compiler examples. This C-code
// example is meant to illustrate the use of Bones. For more information on Bones
// use the contact information below.
//
// == More information on Bones
// Contact............Cedric Nugteren <c.nugteren@tue.nl>
// Web address........http://parse.ele.tue.nl/bones/
//
// == File information
// Filename...........chunk/example04.c
// Author.............Cedric Nugteren
// Last modified on...10-October-2014
//

#include <stdio.h>
#define SIZE 1024

// This is 'example04', a basic element to chunk example with an if-statement in the body
int main(void) {
	int i;
	int threshold = 19;
	
	// Declare input/output arrays
	char A[SIZE];
	char B[SIZE*2];
	
	// Set the input data
	for(i=0;i<SIZE;i++) {
		A[i] = i%100;
	}
	
	// Set the output data to zero
	for(i=0;i<SIZE*2;i++) {
		B[i] = 0;
	}
	
	// Perform the computation
	#pragma scop
	#pragma species kernel A[0:SIZE-1]|element -> B[0:SIZE*2-1]|chunk(0:1)
	for(i=0;i<SIZE;i++) {
		float a = A[i];
		B[i*2] = A[i];
		if (a > threshold) {
			B[i*2+1] = A[i];
		}
		else {
			B[i*2+1] = 0;
		}
	}
	#pragma species endkernel example4
	#pragma endscop
	
	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}

