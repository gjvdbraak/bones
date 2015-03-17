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
// Filename...........element/example02.c
// Author.............Cedric Nugteren
// Last modified on...10-October-2014
//

#include <stdio.h>

// This is 'example02', demonstrating unordered element-wise computation
int main(void) {
	int i,j;
	
	// Declare input/output arrays
	int A[4][8];
	int B[4][8];
	
	// Set the input data
	for(i=0;i<4;i++) {
		for(j=0;j<8;j++) {
			A[i][j] = i+j;
		}
	}
	
	// Perform the computation
	#pragma scop
	{
		#pragma species kernel A[0:3,0:7]|element -> B[0:3,0:7]|element
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 8; j++) {
				B[i][j] = A[i][7 - j];
			}
		}
		#pragma species endkernel example02_k1
	}
	#pragma endscop
	
	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}

