//
// Creator:    http://www.dicelocksecurity.com
// Version:    vers.3.0.0.1
//
// Copyright © 2008-2010 DiceLock Security, LLC. All rights reserved.
//
//                               DISCLAIMER
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED WARRANTIES,
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// 
// DICELOCK IS A REGISTERED TRADEMARK OR TRADEMARK OF THE OWNERS
// 

#include <stdexcept>
#include <stdlib.h>
#include <math.h>
#include "rankTest.h"


using namespace std;


namespace DiceLockSecurity {
	
  namespace RandomTest {

	// Random Test Class enumerator name
	const RandomTests RankTest::test = Rank;
	// Random Test Class minimum stream length
	const unsigned int	RankTest::minimumLength = 38912;

	// Constructor, default 
	RankTest::RankTest() {

		chiSquared = 0.0;
		matrixNumber = 0;
		bitsDiscarded = 0;
		p30 = 0.0; 
		p31 = 0.0;	
		p32 = 0.0;
		f30 = 0.0; 
		f31 = 0.0; 
		f32 = 0.0;
	}


	// Constructor with a MathematicalFunctions object instantiated 
	RankTest::RankTest(MathematicalFunctions* mathFuncObj) {

		chiSquared = 0.0;
		matrixNumber = 0;
		bitsDiscarded = 0;
		p30 = 0.0; 
		p31 = 0.0;	
		p32 = 0.0;
		f30 = 0.0; 
		f31 = 0.0; 
		f32 = 0.0;
	}

	// Destructor
	RankTest::~RankTest() {

		chiSquared = 0.0;
		matrixNumber = 0;
		bitsDiscarded = 0;
		p30 = 0.0; 
		p31 = 0.0;	
		p32 = 0.0;
		f30 = 0.0; 
		f31 = 0.0; 
		f32 = 0.0;
	}
	
	// Tests randomness of the BaseCryptoRandomStream and returns the random value
	bool RankTest::IsRandom(BaseCryptoRandomStream* bitStream) {
		int        r;
		double     product;
		int        i, k;
		double     arg1;
		double     R;					
		bitItem** matrix = CreateMatrix(32, 32);
	

		if (matrix != NULL) {
			if (bitStream->GetBitLength() < this->GetMinimumLength()) {
				this->error = InsufficientNumberOfBits;
				this->random = false;
				return this->random;
			}
			this->error = NoError;
			this->matrixNumber = (int) floor((long double)bitStream->GetBitLength()/(32*32));	
			if (isZero(this->matrixNumber)) {
				this->error = InsufficientNumberOfBits;
				this->pValue = 0.00;
				this->random = false;
			}
			else {
				this->bitsDiscarded = bitStream->GetBitLength()%(32*32);
				r = 32;					
				product = 1;
				for(i = 0; i <= r-1; i++)
					product *= ((1.e0-pow((double)2,i-32))*(1.e0-pow((double)2,i-32)))/(1.e0-pow((double)2,i-r));
				this->p32 = pow((double)2,r*(32+32-r)-32*32) * product;
				r = 31;
				product = 1;
				for(i = 0; i <= r-1; i++)
					product *= ((1.e0-pow((double)2,i-32))*(1.e0-pow((double)2,i-32)))/(1.e0-pow((double)2,i-r));
				this->p31 = pow((double)2,r*(32+32-r)-32*32) * product;
				this->p30 = 1 - (this->p32+this->p31);
				this->f32 = 0;
				this->f31 = 0;
				for(k = 0; k < this->matrixNumber; k++) {			
					DefineMatrix(bitStream, 32, 32, matrix, k);
					R = ComputeRank(32,32,matrix);
					if (R == 32) this->f32++;			
					if (R == 31) this->f31++;
				}
				this->f30 = (double)this->matrixNumber - (this->f32+this->f31);
				this->chiSquared =(double)((pow(this->f32 - this->matrixNumber*this->p32,2)/(double)(this->matrixNumber*this->p32) +
	                            pow(this->f31 - this->matrixNumber*this->p31,2)/(double)(this->matrixNumber*this->p31) +
	                            pow(this->f30 - this->matrixNumber*this->p30,2)/(double)(this->matrixNumber*this->p30)));
				arg1 = -this->chiSquared/2.e0;
				this->pValue = exp(arg1);
				if (this->pValue < this->alpha) {	
    				this->random = false;
				}
				else {
					this->random = 1;
				}
				for(i = 0; i < 32; i++)			
					free(matrix[i]);
				free(matrix);
			}
			if (isNegative(this->pValue) || isGreaterThanOne(this->pValue)) {
				this->error = PValueOutOfRange;
				this->random = false;
			}
		}  
		else {
    		this->error = InsufficientMemory;
			this->random = false; 
		}
		return this->random;
	}

	// Initializes the object
	void RankTest::Initialize(void) {

		BaseRandomTest::Initialize();
		chiSquared = 0.0;
		matrixNumber = 0;
		bitsDiscarded = 0;
		p30 = 0.0; 
		p31 = 0.0;	
		p32 = 0.0;
		f30 = 0.0; 
		f31 = 0.0; 
		f32 = 0.0;
	}

	// Gets the type of the object
	RandomTests RankTest::GetType(void) {

		return this->test;
	}

	// Gets the minimum random stream length
	unsigned int RankTest::GetMinimumLength(void) {

		return this->minimumLength;
	}

	// Gets the "chiSquared" result
	double RankTest::GetChiSquared(void) {

		return this->chiSquared;
	}

	// Gets the "matrixNumber" result
	int RankTest::GetMatrixNumber(void) {

		return this->matrixNumber;
	}

	// Gets the "bitsDiscarded" result
	int RankTest::GetBitsDiscarded(void) {

		return this->bitsDiscarded;
	}

	// Gets the "p30" result
	double RankTest::GetP30(void) {

		return this->p30;
	}

	// Gets the "p31" result
	double RankTest::GetP31(void) {

		return this->p31;
	}
	// Gets the "p32" result
	double RankTest::GetP32(void) {

		return this->p32;
	}

	// Gets the "f30" result
	double RankTest::GetF30(void) {

		return this->f30;
	}

	// Gets the "f31" result
	double RankTest::GetF31(void) {

		return this->f31;
	}
	// Gets the "f32" result
	double RankTest::GetF32(void) {

		return this->f32;
	}

	// Create Matrix 
	bitItem** RankTest::CreateMatrix(int M, int Q) {
		int i;
		bitItem **matrix;	

		if ((matrix = (bitItem**) calloc(M, sizeof(bitItem *))) == NULL) {
			this->error = InsufficientMemory;
			return matrix;	
		}
		else {
			for (i = 0; i < M; i++) {
				if ((matrix[i] = (bitItem*)calloc(Q, sizeof(bitItem))) == NULL) {
					this->error = InsufficientMemory;
        			return NULL;
				}
			}
			return matrix;
		}
	}

	// Define Matrix 
	void RankTest::DefineMatrix(BaseCryptoRandomStream* stream, int M, int Q, bitItem** m,int k) {
		int   i,j;
  
		for (i = 0; i < M; i++) 
			for (j = 0; j < Q; j++) { 
				m[i][j].bit = stream->GetBitPosition(k*(M*Q)+j+i*M);
			}
		return;
	}

	// Deletes matrix 
	void RankTest::DeleteMatrix(int M, bitItem** matrix) {
		int i;
  
		for (i = 0; i < M; i++)
			free(matrix[i]);
		free(matrix);
	}

	// Computes rank 
	int RankTest::ComputeRank(int M, int Q, bitItem** matrix) {
		int i;
		int rank;
		int m = MIN(M,Q);

		for(i = 0; i < m-1; i++) {
			if (matrix[i][i].bit == 1) 
				PerformElementaryRowOperations(0, i, M, Q, matrix);
			else { 	
				if (FindUnitElementAndSwap(0, i, M, Q, matrix) == 1) 
					PerformElementaryRowOperations(0, i, M, Q, matrix);
			}	
	   }	
		for(i = m-1; i > 0; i--) {
			if (matrix[i][i].bit == 1)
				PerformElementaryRowOperations(1, i, M, Q, matrix);
			else { 	
				if (FindUnitElementAndSwap(1, i, M, Q, matrix) == 1) 
					PerformElementaryRowOperations(1, i, M, Q, matrix);
			}
		} 
		rank = DetermineRank(m,M,Q,matrix);
		return rank;
	}	

	// Perform Elementary Row Operations
	void RankTest::PerformElementaryRowOperations(int flag, int i, int M, int Q, bitItem** A) {
		int j,k;

		switch(flag) { 
			case 0: for(j = i+1; j < M;  j++)
						if (A[j][i].bit == 1) 
							for(k = i; k < Q; k++) 
								A[j][k].bit = (A[j][k].bit + A[i][k].bit) % 2;
					break;
			case 1: for(j = i-1; j >= 0;  j--)
						if (A[j][i].bit == 1)
							for(k = 0; k < Q; k++)
								A[j][k].bit = (A[j][k].bit + A[i][k].bit) % 2;
					break;
		}
		return;
	}

	// Find Unit Element And Swap
	int	RankTest::FindUnitElementAndSwap(int flag, int i, int M, int Q, bitItem** A) { 
		int index;
		int row_op = 0;

		switch(flag) {
			case 0: index = i+1;
					while ((index < M) && (A[index][i].bit == 0)) 
						index++;
					if (index < M) 
					row_op = SwapRows(i,index,Q,A);
					break;
			case 1:
					index = i-1;
					while ((index >= 0) && (A[index][i].bit == 0)) 
						index--;
					if (index >= 0) 
						row_op = SwapRows(i,index,Q,A);
					break;
		}
		return row_op;
	}

	// Swap Rows 
	int	RankTest::SwapRows(int i, int index, int Q, bitItem** A) {
		int p;
		short temp;

		for(p = 0; p < Q; p++) {
			temp = A[i][p].bit;
			A[i][p].bit = A[index][p].bit;
			A[index][p].bit = temp;
		}
		return 1;
	}

	// Determine Rank 
	int	RankTest::DetermineRank(int m, int M, int Q, bitItem** A) {
		int i, j, rank, allZeroes;

		rank = m;
		for(i = 0; i < M; i++) {
			allZeroes = 1; 
			for(j=0; j < Q; j++) {
				if (A[i][j].bit == 1) {
					allZeroes = 0;
					break;
				}
			}
			if (allZeroes == 1) rank--;	
		} 
		return rank;
	}
  }
}

