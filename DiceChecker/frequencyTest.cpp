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
#include "frequencyTest.h"


using namespace std;


namespace DiceLockSecurity {
	
  namespace RandomTest {

	// Random Test Class enumerator name
	const RandomTests FrequencyTest::test = Frequency;
	// Random Test Class minimum stream length
	const unsigned int	FrequencyTest::minimumLength = 100;

	// Constructor, default 
	FrequencyTest::FrequencyTest() {

		sum = 0;
		sumDiv_n = 0.0;
	}


	// Constructor with a MathematicalFunctions object instantiated 
	FrequencyTest::FrequencyTest(MathematicalFunctions* mathFuncObj) {

		sum = 0;
		sumDiv_n = 0.0;
	}

	// Destructor
	FrequencyTest::~FrequencyTest() {

		sum = 0;
		sumDiv_n = 0.0;
	}
	
	// Tests randomness of the BaseCryptoRandomStream and returns the random value
	bool FrequencyTest::IsRandom(BaseCryptoRandomStream* bitStream) {
		unsigned long i;
		double f, s_obs, sum;
		double sqrt2 = 1.41421356237309504880;

		if (bitStream->GetBitLength() < this->GetMinimumLength()) {
			this->error = InsufficientNumberOfBits;
			this->random = false;
			return this->random;
		}
		bitStream->SetBitPosition(0);
		this->error = NoError;
		sum = 0.0;
		for(i = 0; i < bitStream->GetBitLength(); i++)
			sum += 2*((int)bitStream->GetBitForward())-1;
		s_obs = fabs(sum)/sqrt((double)bitStream->GetBitLength());
		f = s_obs/sqrt2;
		this->pValue = this->mathFuncs->ErFc(f);
		if (this->pValue < this->GetAlpha()) { 
			this->random = false;
		}
		else {
			this->random = true;
		}
		this->sum = (int)sum;
		this->sumDiv_n = sum/bitStream->GetBitLength();
		return this->random;
	}

	// Initializes the object
	void FrequencyTest::Initialize(void) {

		BaseRandomTest::Initialize();
		sum = 0;
		sumDiv_n = 0.0;
	}

	// Gets the type of the object
	RandomTests FrequencyTest::GetType(void) {

		return this->test;
	}

	// Gets the minimum random stream length
	unsigned int FrequencyTest::GetMinimumLength(void) {

		return this->minimumLength;
	}

	// Gets the "sum" result
	int FrequencyTest::GetSum(void) {

		return this->sum;
	}

	// Gets the "sumDiv_n" result
	double FrequencyTest::GetSumDiv_n(void) {

		return this->sumDiv_n;
	}
  }
}

