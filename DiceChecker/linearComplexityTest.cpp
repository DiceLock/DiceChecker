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
#include <float.h>
#include "linearComplexityTest.h"


using namespace std;


namespace DiceLockSecurity {
	
  namespace RandomTest {

	// Random Test Class enumerator name
	const RandomTests LinearComplexityTest::test = LinearComplexity;
	// Random Test Class minimum stream length
	const unsigned int	LinearComplexityTest::minimumLength = 1000000;

	// Minimum Block size
	const int	LinearComplexityTest::minimumBlock = 500;
	// Maximum Block size
	const int	LinearComplexityTest::maximumBlock = 5000;

	const int LinearComplexityTest::NumNus = 7;	

	  // Constructor, default 
	LinearComplexityTest::LinearComplexityTest() {

		blockLength = 0;
		chiSquared = 0.0;
		bitsDiscarded = 0;
		substringNumber = 0;
		nu = (double*)calloc(NumNus, sizeof(double));
		if (nu == NULL) {
			this->error = InsufficientMemory;
		}
		else {
			memset(nu, 0, sizeof(double)*NumNus);
		}
	}

	  // Constructor, providing BlockLength parameter
	LinearComplexityTest::LinearComplexityTest(int mparam) {

		blockLength = mparam;
		chiSquared = 0.0;
		bitsDiscarded = 0;
		substringNumber = 0;
		nu = (double*)calloc(NumNus, sizeof(double));
		if (nu == NULL) {
			this->error = InsufficientMemory;
		}
		else {
			memset(nu, 0, sizeof(double)*NumNus);
		}
	}

	// Constructor with a MathematicalFunctions object instantiated 
	LinearComplexityTest::LinearComplexityTest(MathematicalFunctions* mathFuncObj) {

		blockLength = 0;
		chiSquared = 0.0;
		bitsDiscarded = 0;
		substringNumber = 0;
		nu = (double*)calloc(NumNus, sizeof(double));
		if (nu == NULL) {
			this->error = InsufficientMemory;
		}
		else {
			memset(nu, 0, sizeof(double)*NumNus);
		}
	}

	// Destructor
	LinearComplexityTest::~LinearComplexityTest() {

		blockLength = 0;
		chiSquared = 0.0;
		bitsDiscarded = 0;
		substringNumber = 0;
		if (nu != NULL)
			free(nu);
	}
	
	// Tests randomness of the BaseCryptoRandomStream and returns the random value
	bool LinearComplexityTest::IsRandom(BaseCryptoRandomStream* bitStream) {
		int       i, ii, j, d;
		int       L, m, N_, parity, sign;
		double    T_, mean;
		double    pi[7]={0.01047,0.03125,0.12500,0.50000,0.25000,0.06250,0.020833};
		bitItem  *T, *P, *B_, *C;

		if (bitStream->GetBitLength() < this->GetMinimumLength()) {
			this->error = InsufficientNumberOfBits;
			this->random = false;
			return this->random;
		}
		this->error = NoError;
		this->substringNumber = (int)floor((long double)(bitStream->GetBitLength()/this->blockLength));
		this->bitsDiscarded = bitStream->GetBitLength()%this->blockLength;
		try {
			if (((B_ = (bitItem*) calloc(this->blockLength,sizeof(bitItem))) == NULL) ||
				((C  = (bitItem*) calloc(this->blockLength,sizeof(bitItem))) == NULL) ||
				((P  = (bitItem*) calloc(this->blockLength,sizeof(bitItem))) == NULL) ||
				((T  = (bitItem*) calloc(this->blockLength,sizeof(bitItem))) == NULL)) {
					if (B_!= NULL) free(B_);
					if (C != NULL) free(C);
					if (P != NULL) free(P);
					if (T != NULL) free(T);
 					this->error = InsufficientMemory;
 					this->random = false;
					return this->random;
				}
			else {
				bitStream->SetBitPosition(0);
				for(i = 0; i < this->NumNus; i++) this->nu[i] = 0.00;
				for(ii = 0; ii < this->substringNumber; ii++) {
					for(i = 0; i < this->blockLength; i++) {
						B_[i].bit = 0;
						C[i].bit = 0;
						T[i].bit = 0;
						P[i].bit = 0;
					}
					L = 0;
					m = -1;
					d = 0;
					C[0].bit = 1;
					B_[0].bit = 1;
					N_ = 0;
					while(N_ < this->blockLength) {
						d = (int)bitStream->GetBitPosition(ii*this->blockLength+N_);
						for(i = 1; i <= L; i++)
						d += (int)C[i].bit*(int)bitStream->GetBitPosition(ii*this->blockLength+N_-i);
						d = d%2;
						if (d == 1) {
							for(i = 0; i < this->blockLength; i++) {
								T[i].bit = C[i].bit;
								P[i].bit = 0;
							}
							for(j = 0; j < this->blockLength; j++)
								if (B_[j].bit == 1) P[j+N_-m].bit = 1;
							for(i = 0; i < this->blockLength; i++)
								C[i].bit = (C[i].bit + P[i].bit)%2;
							if (L <= N_/2) {
								L = N_ + 1 - L;
								m = N_;
								for(i = 0; i < this->blockLength; i++)
								B_[i].bit = T[i].bit;
							}
						}
						N_++;
					}
					if ((parity = (this->blockLength+1)%2) == 0) 
						sign = -1;
					else 
						sign = 1;
					mean = this->blockLength/2. + (9.+sign)/36. - 1./pow((double)2,this->blockLength) * (this->blockLength/3. + 2./9.);
					if ((parity = this->blockLength%2) == 0) 
						sign = 1;
					else 
					sign = -1;
					T_ = sign * (L - mean) + 2./9.;
					if (T_ <= -2.5)
						this->nu[0]++;
					else if (T_ > -2.5 && T_ <= -1.5)
						this->nu[1]++;
					else if (T_ > -1.5 && T_ <= -0.5)
	        			this->nu[2]++;
					else if (T_ > -0.5 && T_ <= 0.5)
	        			this->nu[3]++;
					else if (T_ > 0.5 && T_ <= 1.5)
	        			this->nu[4]++;
					else if (T_ > 1.5 && T_ <= 2.5)
	        			this->nu[5]++;
					else
	        			this->nu[6]++;
				}
				this->chiSquared = 0.00;
				for(i = 0; i < this->NumNus; i++)
	    			this->chiSquared += pow(this->nu[i]-this->substringNumber*pi[i],2)/(this->substringNumber*pi[i]);
				this->pValue = this->mathFuncs->IGammaC((this->NumNus-1)/2.0,this->chiSquared/2.0);
				if (_isnan(this->pValue)) {
					this->pValue = 0.0;
					this->error = MathematicianNAN;
					this->random = false;
				}
				else {
					if (this->pValue < this->alpha) {     
						this->random = false;
					}
					else {
						this->random = true;
					}
				}
			}
			free(B_);
			free(P);
			free(C);
			free(T);
			return this->random;
		}
		catch (char* str) {
			throw str;
		}
	}

	// Initializes the object
	void LinearComplexityTest::Initialize(void) {

		BaseRandomTest::Initialize();
		blockLength = 0;
		chiSquared = 0.0;
		bitsDiscarded = 0;
		substringNumber = 0;
		memset(nu, 0, sizeof(double)*NumNus);
	}

	// Gets the type of the object
	RandomTests LinearComplexityTest::GetType(void) {

		return this->test;
	}

	// Gets the minimum random stream length
	unsigned int LinearComplexityTest::GetMinimumLength(void) {

		return this->minimumLength;
	}

	// Gets the "MinimumBlockSize" 
	int LinearComplexityTest::GetMinimumBlockSize(void) {

		return this->minimumBlock;
	}

	// Gets the "MinimumBlockSize" 
	int LinearComplexityTest::GetMaximumBlockSize(void) {

		return this->maximumBlock;
	}

	// Sets the "blockLength" parameter
	void LinearComplexityTest::SetBlockLength(int length) {

		this->blockLength = length;
	}

	// Gets the "blockLength" parameter
	int LinearComplexityTest::GetBlockLength(void) {

		return this->blockLength;
	}

	// Gets the "chiSquared" result
	double LinearComplexityTest::GetChiSquared(void) {

		return this->chiSquared;
	}

	// Gets "bitsDiscarded" result
	int LinearComplexityTest::GetBitsDiscarded(void) {

		return this->bitsDiscarded;
	}

	// Gets the "substringNumber" result
	double LinearComplexityTest::GetSubstringNumber(void) {

		return this->substringNumber;
	}

	// Gets the Nu result array
	void LinearComplexityTest::GetNu(double* dest) {

		memcpy (dest, nu, sizeof(double)*NumNus);
	}

	// Gets the Nu result of index index
	double LinearComplexityTest::GetNuOfIndex(int index) {

		return this->nu[index];
    }
  }
}

