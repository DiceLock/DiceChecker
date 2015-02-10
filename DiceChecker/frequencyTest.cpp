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

#include <stdlib.h>
#include <math.h>
#include "frequencyTest.h"


namespace DiceLockSecurity {
	
  namespace RandomTest {

	// Random Test Class enumerator name
	const RandomTests FrequencyTest::test = Frequency;
	// Random Test Class minimum stream length
	const unsigned long int	FrequencyTest::minimumLength = 100;

	// Constructor, default 
	FrequencyTest::FrequencyTest() {

		this->sum = 0;
		this->sumDiv_n = 0.0;
	}


	// Constructor with a MathematicalFunctions object instantiated 
	FrequencyTest::FrequencyTest(MathematicalFunctions* mathFuncObj) {

		this->sum = 0;
		this->sumDiv_n = 0.0;
	}

	// Destructor
	FrequencyTest::~FrequencyTest() {

		this->sum = 0;
		this->sumDiv_n = 0.0;
	}
	
	// Gets the BaseRandomTest random state of the last executed BaseCryptoRandomStream
	bool FrequencyTest::IsRandom(void) {

		return BaseRandomTest::IsRandom();
	}

	// Tests randomness of the BaseCryptoRandomStream and returns the random value
	bool FrequencyTest::IsRandom(BaseCryptoRandomStream* bitStream) {
		unsigned long i;
		double f, s_obs, sumDouble;
		double sqrt2 = 1.41421356237309504880;
		unsigned short int bitTemp;

		if (bitStream->GetBitLength() < this->GetMinimumLength()) {
			this->error = InsufficientNumberOfBits;
			this->random = false;
			return this->random;
		}
		bitStream->SetBitPosition(0);
		this->error = NoError;
		sumDouble = 0.0;
		for(i = 0; i < bitStream->GetBitLength(); i++) {
			bitTemp = (unsigned short int)bitStream->GetBitPosition(i);
			sumDouble += ((2 * bitTemp) - 1);
		}
		s_obs = fabs(sumDouble)/sqrt((double)bitStream->GetBitLength());
		f = s_obs/sqrt2;
		this->pValue = this->mathFuncs->ErFc(f);
		if (this->pValue < this->GetAlpha()) { 
			this->random = false;
		}
		else {
			this->random = true;
		}
		this->sum = (int)sumDouble;
		this->sumDiv_n = sumDouble/bitStream->GetBitLength();
		return this->random;
	}

	// Initializes the object
	void FrequencyTest::Initialize(void) {

		BaseRandomTest::Initialize();
		this->sum = 0;
		this->sumDiv_n = 0.0;
	}

	// Gets the type of the object
	RandomTests FrequencyTest::GetType(void) {

		return this->test;
	}

	// Gets the minimum random stream length
	unsigned long int FrequencyTest::GetMinimumLength(void) {

		return this->minimumLength;
	}

	// Gets the "sum" result
	signed long int FrequencyTest::GetSum(void) {

		return this->sum;
	}

	// Gets the "sumDiv_n" result
	double FrequencyTest::GetSumDiv_n(void) {

		return this->sumDiv_n;
	}
  }
}
