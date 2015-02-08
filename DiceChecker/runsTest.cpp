//
// Creator:    http://www.dicelocksecurity.com
// Version:    vers.3.0.0.1
//
// Copyright � 2008-2010 DiceLock Security, LLC. All rights reserved.
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
#include "runsTest.h"


using namespace std;


namespace DiceLockSecurity {
	
  namespace RandomTest {

	// Random Test Class enumerator name
	const RandomTests RunsTest::test = Runs;
	// Random Test Class minimum stream length
	const unsigned int	RunsTest::minimumLength = 100;

	// Constructor, default 
	RunsTest::RunsTest() {

		pi = 0.0;
		totalNumberRuns = 0.0;
		argument = 0.0;
	}


	// Constructor with a MathematicalFunctions object instantiated 
	RunsTest::RunsTest(MathematicalFunctions* mathFuncObj) {

		pi = 0.0;
		totalNumberRuns = 0.0;
		argument = 0.0;
	}

	// Destructor
	RunsTest::~RunsTest() {

		pi = 0.0;
		totalNumberRuns = 0.0;
		argument = 0.0;
	}
	
	// Tests randomness of the BaseCryptoRandomStream and returns the random value
	bool RunsTest::IsRandom(BaseCryptoRandomStream* bitStream) {
		unsigned int    i, *r;
		double product, sum;
	
		if (bitStream->GetBitLength() < this->GetMinimumLength()) {
			this->error = InsufficientNumberOfBits;
			this->random = false;
			return this->random;
		}
		bitStream->SetBitPosition(0);
		this->error = NoError;
		if ((r = (unsigned int *) calloc(bitStream->GetBitLength(),sizeof(int))) == NULL) {
			this->error = InsufficientMemory;
			this->random = false;
		}
		else {
			sum = 0.0;
			for(i = 0; i < bitStream->GetBitLength(); i++)
				sum += (int)bitStream->GetBitForward();
			this->pi = sum/bitStream->GetBitLength();
			for(i = 0; i < bitStream->GetBitLength()-1; i++) {
				if ((int)bitStream->GetBitPosition(i) == (int)bitStream->GetBitPosition(i+1))
					r[i] = 0;
				else
					r[i] = 1;
			} 
			this->totalNumberRuns = 0;
			for(i = 0; i < bitStream->GetBitLength()-1; i++)
	        	this->totalNumberRuns += r[i];
		    this->totalNumberRuns++;
			product = this->pi * (1.e0 - this->pi);
			this->argument = fabs(this->totalNumberRuns - 2.e0*bitStream->GetBitLength()*product)/(2.e0*sqrt(2.e0*bitStream->GetBitLength())*product);
			this->pValue = this->mathFuncs->ErFc(this->argument);
			if (this->pValue < this->alpha) {				    
				this->random = false;
			}
			else {
				this->random = true;
			}
			free(r);
			if (isNegative(this->pValue) || isGreaterThanOne(this->pValue)) {
				this->random = false;
		        this->error = PValueOutOfRange;
			}
		}
		return this->random;
	}

	// Initializes the object
	void RunsTest::Initialize(void) {

		BaseRandomTest::Initialize();
		pi = 0.0;
		totalNumberRuns = 0.0;
		argument = 0.0;
	}

	// Gets the type of the object
	RandomTests RunsTest::GetType(void) {

		return this->test;
	}

	// Gets the minimum random stream length
	unsigned int RunsTest::GetMinimumLength(void) {

		return this->minimumLength;
	}

	// Gets the "pi" result
	double RunsTest::GetPi(void) {

		return this->pi;
	}

	// Gets the total number of runs result 
	double RunsTest::GetTotalNumberRuns(void) {

		return this->totalNumberRuns;
	}

	// Gets the argument result
	double RunsTest::GetArgument(void) {

		return this->argument;
	}
  }
}
