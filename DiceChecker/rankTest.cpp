//
// Creator:    http://www.dicelocksecurity.com
// Version:    vers.6.0.0.1
//
// Copyright © 2008-2012 DiceLock Security, LLC. All rights reserved.
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
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// DICELOCK IS A REGISTERED TRADEMARK OR TRADEMARK OF THE OWNERS.
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
	const unsigned long int RankTest::minimumLength = 38912;

	// Constructor, default 
	RankTest::RankTest() {

		this->chiSquared = 0.0;
		this->matrixNumber = 0;
		this->bitsDiscarded = 0;
		this->p30 = 0.0; 
		this->p31 = 0.0;	
		this->p32 = 0.0;
		this->f30 = 0.0; 
		this->f31 = 0.0; 
		this->f32 = 0.0;
	}


	// Constructor with a MathematicalFunctions object instantiated 
	RankTest::RankTest(MathematicalFunctions* mathFuncObj) {

		this->chiSquared = 0.0;
		this->matrixNumber = 0;
		this->bitsDiscarded = 0;
		this->p30 = 0.0; 
		this->p31 = 0.0;	
		this->p32 = 0.0;
		this->f30 = 0.0; 
		this->f31 = 0.0; 
		this->f32 = 0.0;
	}

	// Destructor
	RankTest::~RankTest() {

		this->chiSquared = 0.0;
		this->matrixNumber = 0;
		this->bitsDiscarded = 0;
		this->p30 = 0.0; 
		this->p31 = 0.0;	
		this->p32 = 0.0;
		this->f30 = 0.0; 
		this->f31 = 0.0; 
		this->f32 = 0.0;
	}
	
	// Gets the BaseRandomTest random state of the last executed BaseCryptoRandomStream
	bool RankTest::IsRandom(void) {

		return BaseRandomTest::IsRandom();
	}

	// Tests randomness of the BaseCryptoRandomStream and returns the random value
	bool RankTest::IsRandom(BaseCryptoRandomStream* bitStream) {
		signed long int r, i;
		unsigned long int k;
		double     product;
		double     arg1;
		double     R;					
		unsigned char** matrix = CreateMatrix(32, 32);
	

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
					this->random = true;
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
		this->chiSquared = 0.0;
		this->matrixNumber = 0;
		this->bitsDiscarded = 0;
		this->p30 = 0.0; 
		this->p31 = 0.0;	
		this->p32 = 0.0;
		this->f30 = 0.0; 
		this->f31 = 0.0; 
		this->f32 = 0.0;
	}

	// Gets the type of the object
	RandomTests RankTest::GetType(void) {

		return this->test;
	}

	// Gets the minimum random stream length
	unsigned long int RankTest::GetMinimumLength(void) {

		return this->minimumLength;
	}

	// Gets the "chiSquared" result
	double RankTest::GetChiSquared(void) {

		return this->chiSquared;
	}

	// Gets the "matrixNumber" result
	unsigned long int RankTest::GetMatrixNumber(void) {

		return this->matrixNumber;
	}

	// Gets the "bitsDiscarded" result
	unsigned long int RankTest::GetBitsDiscarded(void) {

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
	unsigned char** RankTest::CreateMatrix(unsigned long int M, unsigned long int Q) {
		unsigned long int i;
		unsigned char** matrix;	

		if ((matrix = (unsigned char**) calloc(M, sizeof(unsigned char *))) == NULL) {
			this->error = InsufficientMemory;
			return matrix;	
		}
		else {
			for (i = 0; i < M; i++) {
				if ((matrix[i] = (unsigned char*)calloc(Q, sizeof(unsigned char))) == NULL) {
					this->error = InsufficientMemory;
        			return NULL;
				}
			}
			return matrix;
		}
	}

	// Define Matrix 
	void RankTest::DefineMatrix(BaseCryptoRandomStream* stream, signed long int M, signed long int Q, unsigned char** m, signed long int k) {
		signed long int i,j;
  
		for (i = 0; i < M; i++) 
			for (j = 0; j < Q; j++) { 
				m[i][j] = stream->GetBitPosition(k*(M*Q)+j+i*M);
			}
	}

	// Deletes matrix 
	void RankTest::DeleteMatrix(signed long int M, unsigned char** matrix) {
		signed long int i;
  
		for (i = 0; i < M; i++)
			free(matrix[i]);
		free(matrix);
	}

	// Computes rank 
	signed long int RankTest::ComputeRank(signed long int M, signed long int Q, unsigned char** matrix) {
		signed long int i;
		signed long int rank;
		signed long int m = MIN(M,Q);

		for(i = 0; i < m-1; i++) {
			if (matrix[i][i] == 1) 
				PerformElementaryRowOperations(0, i, M, Q, matrix);
			else { 	
				if (FindUnitElementAndSwap(0, i, M, Q, matrix) == 1) 
					PerformElementaryRowOperations(0, i, M, Q, matrix);
			}	
	   }	
		for(i = m-1; i > 0; i--) {
			if (matrix[i][i] == 1)
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
	void RankTest::PerformElementaryRowOperations(signed long int flag, signed long int i, signed long int M, signed long int Q, unsigned char** A) {
		signed long int j,k;

		switch(flag) { 
			case 0: for(j = i+1; j < M;  j++)
						if (A[j][i] == 1) 
							for(k = i; k < Q; k++) 
								A[j][k] = (A[j][k] + A[i][k]) % 2;
					break;
			case 1: for(j = i-1; j >= 0;  j--)
						if (A[j][i] == 1)
							for(k = 0; k < Q; k++)
								A[j][k] = (A[j][k] + A[i][k]) % 2;
					break;
		}
	}

	// Find Unit Element And Swap
	signed long int	RankTest::FindUnitElementAndSwap(signed long int flag, signed long int i, signed long int M, signed long int Q, unsigned char** A) { 
		signed long int index;
		signed long int row_op = 0;

		switch(flag) {
			case 0: index = i+1;
					while ((index < M) && (A[index][i] == 0)) 
						index++;
					if (index < M) 
					row_op = SwapRows(i,index,Q,A);
					break;
			case 1:
					index = i-1;
					while ((index >= 0) && (A[index][i] == 0)) 
						index--;
					if (index >= 0) 
						row_op = SwapRows(i,index,Q,A);
					break;
		}
		return row_op;
	}

	// Swap Rows 
	signed long int	RankTest::SwapRows(signed long int i, signed long int index, signed long int Q, unsigned char** A) {
		signed long int p;
		unsigned char temp;

		for(p = 0; p < Q; p++) {
			temp = A[i][p];
			A[i][p] = A[index][p];
			A[index][p] = temp;
		}
		return 1;
	}

	// Determine Rank 
	signed long int	RankTest::DetermineRank(signed long int m, signed long int M, signed long int Q, unsigned char** A) {
		signed long int i, j, rank, allZeroes;

		rank = m;
		for(i = 0; i < M; i++) {
			allZeroes = 1; 
			for(j=0; j < Q; j++) {
				if (A[i][j] == 1) {
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
