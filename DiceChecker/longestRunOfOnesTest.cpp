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
#include "longestRunOfOnesTest.h"


using namespace std;


namespace DiceLockSecurity {
	
  namespace RandomTest {

	// Random Test Class enumerator name
	const RandomTests LongestRunOfOnesTest::test = LongestRunOfOnes;
	// Random Test Class minimum stream length
	const unsigned long int	LongestRunOfOnesTest::minimumLength = 128;

	// Random Test Class block sizes and minimum lengths
	const unsigned short int LongestRunOfOnesTest::numberBlockSizes = 3;
	const LongestRunOfOnesTest::blockSizeMinimumLength LongestRunOfOnesTest::blockSizes[] = {{8, 128}, {128, 6272}, {10000, 750000}};

	const unsigned short int LongestRunOfOnesTest::NumAssignments = 7;	

	// Constructor, default 
	LongestRunOfOnesTest::LongestRunOfOnesTest() {

		this->longRunCase = 0;
		this->substringNumber = 0;
		this->substringLength = 0;
		this->chiSquared = 0.0;
		this->assignment = (unsigned long int*)calloc(NumAssignments, sizeof(unsigned long int));
		if (this->assignment == NULL) {
			this->error = InsufficientMemory;
		}
		else {
			memset(this->assignment, 0, sizeof(unsigned long int)*NumAssignments);
		}
	}


	// Constructor with a MathematicalFunctions object instantiated 
	LongestRunOfOnesTest::LongestRunOfOnesTest(MathematicalFunctions* mathFuncObj) {

		this->longRunCase = 0;
		this->substringNumber = 0;
		this->substringLength = 0;
		this->chiSquared = 0.0;
		this->assignment = (unsigned long int*)calloc(NumAssignments, sizeof(unsigned long int));
		if (this->assignment == NULL) {
			this->error = InsufficientMemory;
		}
		else {
			memset(this->assignment, 0, sizeof(unsigned long int)*NumAssignments);
		}
	}

	// Destructor
	LongestRunOfOnesTest::~LongestRunOfOnesTest() {

		this->longRunCase = 0;
		this->substringNumber = 0;
		this->substringLength = 0;
		this->chiSquared = 0.0;
		memset(this->assignment, 0, sizeof(unsigned long int)*NumAssignments);
		free(this->assignment);
	}
	
	// Gets the BaseRandomTest random state of the last executed BaseCryptoRandomStream
	bool LongestRunOfOnesTest::IsRandom(void) {

		return BaseRandomTest::IsRandom();
	}

	// Tests randomness of the BaseCryptoRandomStream and returns the random value
	bool LongestRunOfOnesTest::IsRandom(BaseCryptoRandomStream* bitStream) {
		double	run = 0, v_n_obs = 0;
		double	pi[7];
		unsigned long int K;
		unsigned long int i = 0, j = 0;
		signed long int	k[7];
		unsigned long int nu[7] = {0, 0, 0, 0, 0, 0, 0};

		if ( bitStream->GetBitLength() < 128 ) {
			this->error = InsufficientNumberOfBits;
			this->random = false;
			return this->random;
		}
		if ( bitStream->GetBitLength() < 6272 ) {
		  	K = 3;
	  		substringLength = 8;
	  		pi[0] = 0.21484375;
	  		pi[1] = 0.3671875;
	  		pi[2] = 0.23046875;
	  		pi[3] = 0.1875;
	  		k[0] = 1;
	  		k[1] = 2;
	  		k[2] = 3;
	  		k[3] = 4;
		}
		else {
			if ( bitStream->GetBitLength() < 750000 ) {
		  		K = 5;
				substringLength = 128;
				pi[0] = 0.1174035788;
				pi[1] = 0.242955959;
				pi[2] = 0.249363483;
				pi[3] = 0.17517706;
				pi[4] = 0.102701071;
				pi[5] = 0.112398847;
				k[0] = 4;
				k[1] = 5;
				k[2] = 6;
				k[3] = 7;
				k[4] = 8;
				k[5] = 9;
			}
			else {
		  		K = 6;
		  		substringLength = 10000;
		  		pi[0] = 0.0882;
		  		pi[1] = 0.2092;
		  		pi[2] = 0.2483;
		  		pi[3] = 0.1933;
		  		pi[4] = 0.1208;
		  		pi[5] = 0.0675;
		  		pi[6] = 0.0727;
				k[0] = 10;
				k[1] = 11;
				k[2] = 12;
				k[3] = 13;
				k[4] = 14;
				k[5] = 15;
				k[6] = 16;
			}
		}
	  
		this->error = NoError;
		this->substringNumber = (int)floor((long double)(bitStream->GetBitLength()/substringLength));
		bitStream->SetBitPosition(0);
		for(i = 0; i < this->substringNumber; i++)  {
			v_n_obs = 0.e0;
			run = 0.e0;
			for(j = 0; j < substringLength; j++) {
				if ((int)bitStream->GetBitPosition(i * substringLength + j) == 1) {
					run++;
					v_n_obs = MAX(v_n_obs, run); 
				}
				else {
					run = 0.e0;
				}
			}
			if ( v_n_obs < k[0] ) {
				nu[0]++;
			}
			for (j = 0; j <= K; j++) {
				if ( v_n_obs == k[j] ) {
					nu[j]++;
				}
			}
			if ( v_n_obs > k[K] ) {
				nu[K]++;
			}
		}
		this->chiSquared = 0.0;					
		for(i = 0; i <= K; i++) {
			this->chiSquared += (((double)nu[i] - (double)this->substringNumber * pi[i]) * (nu[i] - (double)this->substringNumber * pi[i])) / ((double)this->substringNumber * pi[i]);
		}
		this->pValue = mathFuncs->IGammaC((double)(K/2.0),(this->chiSquared/2.0));
		if (isNegative(this->pValue) || isGreaterThanOne(this->pValue)) {
			this->error = PValueOutOfRange;
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
		for (i = 0; i < K+1; i++)
			this->assignment[i] = nu[i];
		return this->random;
	}

	// Initializes the object
	void LongestRunOfOnesTest::Initialize(void) {

		BaseRandomTest::Initialize();
		this->longRunCase = 0;
		this->substringNumber = 0;
		this->substringLength = 0;
		this->chiSquared = 0.0;
		memset(this->assignment, 0, sizeof(unsigned long int)*NumAssignments);
	}

	// Gets the type of the object
	RandomTests LongestRunOfOnesTest::GetType(void) {

		return this->test;
	}

	// Gets the minimum random stream length
	unsigned long int LongestRunOfOnesTest::GetMinimumLength(void) {

		return this->minimumLength;
	}

	// Sets the longRunCase parameter 
	void LongestRunOfOnesTest::SetLongRunCase(unsigned long int run) {

		this->longRunCase = run;
	}

	// Gets the longRunCase parameter 
	unsigned long int LongestRunOfOnesTest::GetLongRunCase(void) {

		return this->longRunCase;
	}

	// Gets the "substringNumber" result 
	unsigned long int LongestRunOfOnesTest::GetSubstringNumber(void) {

		return this->substringNumber;
	}

	// Gets the "substringLength" result
	unsigned long int LongestRunOfOnesTest::GetSubstringLength(void) {

		return this->substringLength;
	}

	// Gets the chiSquared result
	double LongestRunOfOnesTest::GetChiSquared(void) {

		return this->chiSquared;
	}

	// Gets the Assignment result
	void LongestRunOfOnesTest::GetAssignment(unsigned long int *assign) {

		memcpy(assign, this->assignment, sizeof(unsigned long int)*NumAssignments);
	}

	// Gets the Assignment result based on the index
	unsigned long int LongestRunOfOnesTest::GetAssignmentOfIndex(unsigned long int index)  {

		return this->assignment[index];
	}
  }
}
