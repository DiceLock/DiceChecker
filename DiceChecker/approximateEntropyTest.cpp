//
// Creator:    http://www.dicelocksecurity.com
// Version:    vers.4.0.0.1
//
// Copyright © 2008-2010 DiceLock Security, LLC. All rigths reserved.
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
#include <float.h>

#include "approximateEntropyTest.h"


namespace DiceLockSecurity {
	
  namespace RandomTest {

	// Random Test Class enumerator name
	const RandomTests ApproximateEntropyTest::test = ApproximateEntropy;
	// Random Test Class minimum stream length
	const unsigned int	ApproximateEntropyTest::minimumLength = 1024;

	// Constructor, default 
	ApproximateEntropyTest::ApproximateEntropyTest() {

		blockLength = 0;
		chiSquared = 0.0;
		phi = 0.0;
		phiPlusOne = 0.0;
		apEn = 0.0;
		blockSizeExceeded = false;		
		maximumBlockSizeRecommended = 0;	 
	}


	// Constructor with a MathematicalFunctions object instantiated 
	ApproximateEntropyTest::ApproximateEntropyTest(MathematicalFunctions* mathFuncObj) {

		blockLength = 0;
		chiSquared = 0.0;
		phi = 0.0;
		phiPlusOne = 0.0;
		apEn = 0.0;
		blockSizeExceeded = false;		
		maximumBlockSizeRecommended = 0;	 
	}

	// Destructor
	ApproximateEntropyTest::~ApproximateEntropyTest() {

		blockLength = 0;
		chiSquared = 0.0;
		phi = 0.0;
		phiPlusOne = 0.0;
		apEn = 0.0;
		blockSizeExceeded = false;		
		maximumBlockSizeRecommended = 0;	 
	}
	
	// Gets the BaseRandomTest random state of the last executed BaseCryptoRandomStream
	bool ApproximateEntropyTest::IsRandom(void) {

		return BaseRandomTest::IsRandom();
	}

	// Tests the BaseCryptoRandomStream executed and returns the random value
	bool ApproximateEntropyTest::IsRandom(BaseCryptoRandomStream* bitStream) {
		int           i, j, k, r, blockSize;
		int           powLen, index;
		double        sum, numOfBlocks, ApEn[2];
		unsigned int* P;

		if (bitStream->GetBitLength() < (unsigned long)this->GetMinimumLength()) {
			this->error = InsufficientNumberOfBits;
			this->random = false;
			return this->random;
		}
		this->error = NoError;
		if (this->blockLength > (int)this->MaximumBlockSizeRecommended(bitStream->GetBitLength())) {
    		this->blockSizeExceeded = true;
    		this->maximumBlockSizeRecommended = this->MaximumBlockSizeRecommended(bitStream->GetBitLength());
    		this->error = ResultsInaccurate;
    		this->random = false;
    		return this->random ;
		} 
		r = 0;
		for(blockSize = this->blockLength; blockSize <= this->blockLength+1; blockSize++) {
			if (blockSize == 0) {
				ApEn[0] = 0.00;
				r++;
			}
			else {
	    		numOfBlocks = (double)bitStream->GetBitLength();
				powLen = (int)pow((long double)2,blockSize+1)-1;
				if ((P = (unsigned int*)calloc(powLen,sizeof(unsigned int)))== NULL){
	        		this->error = InsufficientMemory;
	        		this->random = false;
					return this->random ;
				}
				for(i = 1; i < powLen-1; i++) P[i] = 0;
				for(i = 0; i < numOfBlocks; i++) { 
	        		k = 1;
					for(j = 0; j < blockSize; j++) {
						if ((int)bitStream->GetBitPosition((i+j)%bitStream->GetBitLength()) == 0)
							k *= 2;
						else if ((int)bitStream->GetBitPosition((i+j)%bitStream->GetBitLength()) == 1)
		                    k = 2*k+1;
					}
					P[k-1]++;
				}
				sum = 0.0;
				index = (int)pow((long double)2,blockSize)-1;
				for(i = 0; i < (int)pow((long double)2,blockSize); i++) {
					if (P[index] > 0) sum += P[index]*log(P[index]/numOfBlocks);
					index++;
				}
				sum /= numOfBlocks;
				ApEn[r] = sum;
				r++;
				free(P);
			}
		}
		this->apEn = ApEn[0] - ApEn[1];
		this->phi = ApEn[0];
		this->phiPlusOne = ApEn[1];
		this->chiSquared = 2.0*bitStream->GetBitLength()*(log((long double)2) - this->apEn);
		this->pValue = this->mathFuncs->IGammaC(pow((long double)2,this->blockLength-1),this->chiSquared/2.);
		if (_isnan(this->pValue)) {
			this->pValue = 0;
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
		return this->random;
	}

	// Initializes the object
	void ApproximateEntropyTest::Initialize(void) {

		BaseRandomTest::Initialize();
		chiSquared = 0.0;
		phi = 0.0;
		phiPlusOne = 0.0;
		apEn = 0.0;
		blockSizeExceeded = false;		
		maximumBlockSizeRecommended = 0;	 
	}

	// Gets the type of the object
	RandomTests ApproximateEntropyTest::GetType(void) {

		return this->test;
	}

	// Gets the minimum random stream length
	unsigned int ApproximateEntropyTest::GetMinimumLength(void) {

		return this->minimumLength;
	}

	// Sets the "blockLength" param
	void ApproximateEntropyTest::SetBlockLength(int blockLength) {

		this->blockLength = blockLength;
	}

	// Gets the "blockLength" param
	int ApproximateEntropyTest::GetBlockLength(void) {

		return this->blockLength;
	}

	// Gets the "ChiSquared" result
	double ApproximateEntropyTest::GetChiSquared(void) {

		return this->chiSquared;
	}

	// Gets the "Phi" result
	double ApproximateEntropyTest::GetPhi(void) {

		return this->phi;
	}

	// Gets the "PhiPlusOne" result
	double ApproximateEntropyTest::GetPhiPlusOne(void) {

		return this->phiPlusOne;
	}

	// Gets the "apEn" result
	double ApproximateEntropyTest::GetApEn(void) {

		return this->apEn;
	}

	// Gets the "BlockSizeExceeded" result
	bool ApproximateEntropyTest::GetBlockSizeExceeded(void) {

		return this->blockSizeExceeded;
	}

	// Gets the "BlockSizeRecommended" result
	unsigned int ApproximateEntropyTest::GetMaximumBlockSizeRecommended(void) {

		return this->maximumBlockSizeRecommended;
	}

	// Gets the "BlockSizeRecommended" for the indicated stream length
	unsigned int ApproximateEntropyTest::MaximumBlockSizeRecommended(unsigned int length) {

		return MAX(1,(int)(log((long double)length)/log((long double)2)-2));
	}
  }
}
