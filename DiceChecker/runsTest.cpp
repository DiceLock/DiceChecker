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
#include <float.h>
#include "runsTest.h"


namespace DiceLockSecurity {
	
  namespace RandomTest {

	// Random Test Class enumerator name
	const RandomTests RunsTest::test = Runs;
	// Random Test Class minimum stream length
	const unsigned long int	RunsTest::minimumLength = 100;

	// Constructor, default 
	RunsTest::RunsTest() {

		this->pi = 0.0;
		this->totalNumberRuns = 0.0;
		this->argument = 0.0;
	}


	// Constructor with a MathematicalFunctions object instantiated 
	RunsTest::RunsTest(MathematicalFunctions* mathFuncObj) {

		this->pi = 0.0;
		this->totalNumberRuns = 0.0;
		this->argument = 0.0;
	}

	// Destructor
	RunsTest::~RunsTest() {

		this->pi = 0.0;
		this->totalNumberRuns = 0.0;
		this->argument = 0.0;
	}
	
	// Gets the BaseRandomTest random state of the last executed BaseCryptoRandomStream
	bool RunsTest::IsRandom(void) {

		return BaseRandomTest::IsRandom();
	}

	// Tests randomness of the BaseCryptoRandomStream and returns the random value
	bool RunsTest::IsRandom(BaseCryptoRandomStream* bitStream) {
		unsigned long int i;
		unsigned short int *r;
		double product, sum;
	
		if (bitStream->GetBitLength() < this->GetMinimumLength()) {
			this->error = InsufficientNumberOfBits;
			this->random = false;
			return this->random;
		}
		bitStream->SetBitPosition(0);
		this->error = NoError;
		if ((r = (unsigned short int *) calloc(bitStream->GetBitLength(),sizeof(unsigned short int))) == NULL) {
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
		this->pi = 0.0;
		this->totalNumberRuns = 0.0;
		this->argument = 0.0;
	}

	// Gets the type of the object
	RandomTests RunsTest::GetType(void) {

		return this->test;
	}

	// Gets the minimum random stream length
	unsigned long int RunsTest::GetMinimumLength(void) {

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
