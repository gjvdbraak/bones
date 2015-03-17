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
// Filename...........element/example07.c
// Author.............Cedric Nugteren
// Last modified on...10-October-2014

#include <stdio.h>
#include <stdlib.h>

// This is 'example07', demonstrating variable length arrays (C99 VLAs)
int main(void) {
	int a,b,c;
	int dim_1A = 50;
	int dim_1B = 40;
	
	// Declare input/output arrays
	int in1[dim_1A][dim_1B][30];
	int in2[dim_1A][dim_1B][30];
	int out[dim_1A][dim_1B][30];
	
	// Set the input data
	for(a=0;a<dim_1A;a++) {
		for(b=0;b<dim_1B;b++) {
			for(c=0;c<30;c++) {
				in1[a][b][c] = a*b+c;
				in2[a][b][c] = -(c/4)+6;
			}
		}
	}
	
	// Perform the computation
	#pragma scop
	{
		#pragma species kernel in1[0:dim_1A-1,0:dim_1B-1,0:29]|element ^ in2[0:dim_1A-1,0:dim_1B-1,0:29]|element -> out[0:dim_1A-1,0:dim_1B-1,0:29]|element
		for (a = 0; a < dim_1A; a++) {
			for (b = 0; b < dim_1B; b++) {
				for (c = 0; c < 30; c++) {
					out[a][b][c] = in1[a][b][c] + in2[a][b][c];
				}
			}
		}
		#pragma species endkernel example07_k1
	}
	#pragma endscop
	
	// Clean-up and exit the function
	fflush(stdout);
	return 0;
}

