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
#include "blockFrequencyTest.h"


using namespace std;


namespace DiceLockSecurity {
	
  namespace RandomTest {

	// Random Test Class enumerator name
	const RandomTests BlockFrequencyTest::test = BlockFrequency;
	// Random Test Class minimum stream length
	const unsigned long int	BlockFrequencyTest::minimumLength = 100;

	// Constructor, default 
	BlockFrequencyTest::BlockFrequencyTest() {

		this->blockLength = 128;
		this->blockNumber = 0;
		this->alpha = 0.0;
		this->pValue = 0.0;
		this->random = false;
		this->error = NoError; 
	}

	// Constructor with a MathematicalFunctions object instantiated 
	BlockFrequencyTest::BlockFrequencyTest(MathematicalFunctions* mathFuncObj) {

		BaseRandomTest::Initialize();
		this->blockLength = 128;
		this->chiSquared = 0.0;
		this->blockNumber = 0;
		this->bitsDiscarded = 0;
	}

	// Destructor
	BlockFrequencyTest::~BlockFrequencyTest() {

		BaseRandomTest::Initialize();
		this->chiSquared = 0.0;
		this->blockNumber = 0;
		this->bitsDiscarded = 0;
	}

	// Gets the BaseRandomTest random state of the last executed BaseCryptoRandomStream
	bool BlockFrequencyTest::IsRandom(void) {

		return BaseRandomTest::IsRandom();
	}

	// Tests randomness of the BaseCryptoRandomStream and returns the random value
	bool BlockFrequencyTest::IsRandom(BaseCryptoRandomStream* bitStream) {
		unsigned long int i, j;
		double blockSum, arg1, arg2;
		double sum, pi, v;

		if (bitStream->GetBitLength() < this->GetMinimumLength()) {
			this->error = InsufficientNumberOfBits;
			this->random = false;
			return this->random;
		}
		bitStream->SetBitPosition(0);
		this->error = NoError;
		this->blockNumber = (int)floor((double)bitStream->GetBitLength()/(double)this->blockLength); 	// Number of Stream blocks      
		sum = 0.0;
		for (i = 0; i < this->blockNumber; i++) {	// N=10000 for each substring block
			pi = 0.0;
			blockSum = 0.0;
			bitStream->SetBitPosition(i*this->blockLength);
			for (j = 0; j < this->blockLength; j++) 	// m=100 compute the "i"th Pi Value */	 
				blockSum += bitStream->GetBitForward();		
			pi = (double)blockSum/(double)this->blockLength;
			v = pi - 0.5;
			sum += v*v;
		}
		this->chiSquared = 4.0 * this->blockLength * sum;
		arg1 = (double) this->blockNumber/2.e0;
		arg2 = this->chiSquared/2.e0;	
		this->pValue = this->mathFuncs->IGammaC(arg1,arg2);
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
		this->bitsDiscarded = bitStream->GetBitLength()%this->blockLength;
		return this->random;
	}

	// Initializes the object
	void BlockFrequencyTest::Initialize(void) {

		BaseRandomTest::Initialize();
	}

	// Gets the type of the object
	RandomTests BlockFrequencyTest::GetType(void) {

		return this->test;
	}

	// Gets the minimum random stream length
	unsigned long int BlockFrequencyTest::GetMinimumLength(void) {

		return this->minimumLength;
	}

	// Sets the blockLength
	void BlockFrequencyTest::SetBlockLength(unsigned int block) {

		this->blockLength = block;
	}

	// Gets the blockLength
	unsigned long int BlockFrequencyTest::GetBlockLength(void) {

		return this->blockLength;
	}

	// Gets chiSquared
	double BlockFrequencyTest::GetChiSquared(void) {

		return this->chiSquared;
	}

	// Gets blockNumber tested
	unsigned long int	BlockFrequencyTest::GetBlockNumber(void) {

		return this->blockNumber;
	}

	// Gets the bitsDiscarded not tested
	unsigned long int BlockFrequencyTest::GetBitsDiscarded(void) {

		return this->bitsDiscarded;
	}
  }
}
