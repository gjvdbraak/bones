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
// Filename...........shared/example02.c
// Author.............Cedric Nugteren
// Last modified on...10-October-2014
//

#include <stdio.h>

// This is 'example02', demonstrating a 3D input reduction to scalar
int main(void) {
	int a,b,c;
	
	// Declare input/output arrays
	float in[8][16][32];
	float out[1];
	
	// Set the input data
	for(a=0;a<8;a++) {
		for(b=0;b<16;b++) {
			for(c=0;c<32;c++) {
				in[a][b][c] = 1;
			}
		}
	}
	
	// Perform the computation
	out[0] = 0;
	#pragma scop
	{
		#pragma species kernel out[0:0]|full ^ in[0:7,0:15,0:31]|element -> out[0:0]|shared
		for (a = 0; a < 8; a++) {
			for (b = 0; b < 16; b++) {
				for (c = 0; c < 32; c++) {
					out[0] = out[0] + in[a][b][c];
				}
			}
		}
		#pragma species endkernel example02_k1
	}
	#pragma endscop
	
	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}

