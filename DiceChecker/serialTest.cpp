//
// Creator:    http://www.dicelocksecurity.com
// Version:    vers.5.0.0.1
//
// Copyright © 2008-2011 DiceLock Security, LLC. All rights reserved.
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
#include "serialTest.h"


using namespace std;


namespace DiceLockSecurity {
	
  namespace RandomTest {

	// Random Test Class enumerator name
	const RandomTests SerialTest::test = Serial;
	// Random Test Class minimum stream length
	const unsigned long int	SerialTest::minimumLength = 128;

	// Constructor, default 
	SerialTest::SerialTest() {

		this->blockLength = 16;
		this->pvalue2 = 0.0;				
		this->psim = 0.0; 
		this->psim1 = 0.0; 
		this->psim2 = 0.0; 
		this->delta1 = 0.0; 
		this->delta2 = 0.0;
	}


	// Constructor with a MathematicalFunctions object instantiated 
	SerialTest::SerialTest(MathematicalFunctions* mathFuncObj) {

		this->blockLength = 16;
		this->pvalue2 = 0.0;				
		this->psim = 0.0; 
		this->psim1 = 0.0; 
		this->psim2 = 0.0; 
		this->delta1 = 0.0; 
		this->delta2 = 0.0;
	}

	// Destructor
	SerialTest::~SerialTest() {

		this->blockLength = 0;
		this->pvalue2 = 0.0;				
		this->psim = 0.0; 
		this->psim1 = 0.0; 
		this->psim2 = 0.0; 
		this->delta1 = 0.0; 
		this->delta2 = 0.0;
	}

	// Psi2 function 
	double SerialTest::psi2(signed long int m, BaseCryptoRandomStream* bitStream) {
		signed long int i, j, k, powLen;
		double	sum, numOfBlocks;
		unsigned long int*  P;
  
		if ((m == 0) || (m == -1)) 
			return 0.0;
		numOfBlocks = bitStream->GetBitLength();
		powLen = (int)pow((long double)2,(int)m+1)-1;
		P = (unsigned long int*)calloc(powLen,sizeof(unsigned long int));
		if (P == NULL) {
			this->error = InsufficientMemory;
			return 0.0;
		}
		for(i = 1; i < powLen-1; i++) 
			P[i] = 0;
		for(i = 0; i < numOfBlocks; i++) {		 
			k = 1;
			for(j = 0; j < (int)m; j++) {
				if (bitStream->GetBitPosition((i+j)%bitStream->GetBitLength()) == 0)
					k *= 2;
				else if (bitStream->GetBitPosition((i+j)%bitStream->GetBitLength()) == 1)
					k = 2*k+1;
			}
			P[k-1]++;
		}
		sum = 0.0;
		for(i = (int)pow((long double)2,(int)m)-1; i < (int)pow((long double)2,(int)m+1)-1; i++)
			sum += pow((long double)P[i],2);
		sum = (sum * pow((long double)2,(int)m)/(double)bitStream->GetBitLength()) - (double)bitStream->GetBitLength();
		free(P);
		return sum;
	}

	// Gets the BaseRandomTest random state of the last executed BaseCryptoRandomStream
	bool SerialTest::IsRandom(void) {

		return BaseRandomTest::IsRandom();
	}

	// Tests randomness of the BaseCryptoRandomStream and returns the random value
	bool SerialTest::IsRandom(BaseCryptoRandomStream* bitStream) {

		if (bitStream->GetBitLength() < (unsigned long int)this->GetMinimumLength()) {
			this->error = InsufficientNumberOfBits;
			this->random = false;
			return this->random;
		}
		this->error = NoError;
		this->psim = psi2(this->blockLength, bitStream);
		this->psim1 = psi2(this->blockLength-1, bitStream);
		this->psim2 = psi2(this->blockLength-2, bitStream);
		this->delta1 = this->psim - this->psim1;
		this->delta2 = this->psim - 2.0*this->psim1 + this->psim2;
		this->pValue = this->mathFuncs->IGammaC(pow((long double)2,(int)(this->blockLength-1))/2,this->delta1/2.0);
		if (_isnan(this->pValue)) {
			this->pValue = 0;
			this->error = MathematicianNAN;
			this->random = false;
			return this->random;
		}
		this->pvalue2 = this->mathFuncs->IGammaC(pow((long double)2,(int)(this->blockLength-2))/2,this->delta2/2.0);
		if (_isnan(this->pvalue2)) {
			this->pvalue2 = 0;
			this->error = MathematicianNAN;
			this->random = false;
			return this->random;
		}
		if (this->pValue < this->alpha) {
			this->random = false;
		}
		else {
			this->random = true;
		}
		if (this->pvalue2 < this->alpha) {
			this->random = false;
		}
		return this->random;
	}

	// Initializes the object
	void SerialTest::Initialize(void) {

		BaseRandomTest::Initialize();
		this->pvalue2 = 0.0;				
		this->psim = 0.0; 
		this->psim1 = 0.0; 
		this->psim2 = 0.0; 
		this->delta1 = 0.0; 
		this->delta2 = 0.0;
	}

	// Gets the type of the object
	RandomTests SerialTest::GetType(void) {

		return this->test;
	}

	// Gets the minimum random stream length
	unsigned long int SerialTest::GetMinimumLength(void) {

		return this->minimumLength;
	}

	// Sets the "blockLength" parameter 
	void SerialTest::SetBlockLength(unsigned long int param) {

		this->blockLength = param;
	}

	// Gets the "blockLength" parameter 
	unsigned long int SerialTest::GetBlockLength(void) {

		return this->blockLength;
	}

	// Gets the "pvalue2" result  
	double SerialTest::GetPValue2(void) {

		return this->pvalue2;
	}

	// Gets the "psim" result  
	double SerialTest::GetPsim(void) {

		return this->psim;
	}

	// Gets the "psim1" result  
	double SerialTest::GetPsim1(void) {

		return this->psim1;
	}

	// Gets the "psim2" result  
	double SerialTest::GetPsim2(void) {

		return this->psim2;
	}

	// Gets the "delta1" result  
	double SerialTest::GetDelta1(void) {

		return this->delta1;
	}

	// Gets the "delta2" result  
	double SerialTest::GetDelta2(void) {

		return this->delta2;
	}

	// Gets the "BlockSizeRecommended" for the indicated stream length
	unsigned long int SerialTest::MaximumBlockSizeRecommended(unsigned long int length) {

		return MAX(1,(int)(log((long double)length)/log((long double)2)-2));
	}
  }
}
