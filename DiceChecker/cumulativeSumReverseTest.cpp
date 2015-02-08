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
#include "cumulativeSumReverseTest.h"


using namespace std;


namespace DiceLockSecurity {
	
  namespace RandomTest {

	// Random Test Class enumerator name
	const RandomTests CumulativeSumReverseTest::test = CumulativeSumReverse;
	// Random Test Class minimum stream length
	const unsigned int	CumulativeSumReverseTest::minimumLength = 100;

	// Constructor, default 
	CumulativeSumReverseTest::CumulativeSumReverseTest() {

		cuSum = 0;
	}


	// Constructor with a MathematicalFunctions object instantiated 
	CumulativeSumReverseTest::CumulativeSumReverseTest(MathematicalFunctions* mathFuncObj) {

		cuSum = 0;
	}

	// Destructor
	CumulativeSumReverseTest::~CumulativeSumReverseTest() {

		cuSum = 0;
	}

	// Gets the BaseRandomTest random state of the last executed BaseCryptoRandomStream
	bool CumulativeSumReverseTest::IsRandom(void) {

		return BaseRandomTest::IsRandom();
	}

	// Tests randomness of the BaseCryptoRandomStream and returns the random value
	bool CumulativeSumReverseTest::IsRandom(BaseCryptoRandomStream* bitStream) {
		int    i, k, start, finish;
		double z, sum, sum1, sum2;
 
		if (bitStream->GetBitLength() < this->GetMinimumLength()) {
			this->error = InsufficientNumberOfBits;
			this->random = false;
			return this->random;
		}
		bitStream->SetBitPosition(bitStream->GetBitLength() -1);
		this->error = NoError;
		sum = 0.0;
		this->cuSum = 1;
		for(i = bitStream->GetBitLength() -1; i >= 0; i--) {
			sum += 2*(int)bitStream->GetBitReverse() - 1;
    		this->cuSum = MAX(this->cuSum, fabs(sum));
		}
		z = this->cuSum;
		sum1 = 0.0;
		start = (-(long)bitStream->GetBitLength()/(int)z+1)/4;
		finish = (bitStream->GetBitLength()/(int)z-1)/4;
		for(k = start; k <= finish; k++)
			sum1 += (this->mathFuncs->Normal((4*k+1)*z/sqrt((double)bitStream->GetBitLength()))-this->mathFuncs->Normal((4*k-1)*z/sqrt((double)bitStream->GetBitLength())));
		sum2 = 0.0;
		start = (-(long)bitStream->GetBitLength()/(int)z-3)/4;
		finish = (bitStream->GetBitLength()/(int)z-1)/4;
		for(k = start; k <= finish; k++)
			sum2 += (this->mathFuncs->Normal((4*k+3)*z/sqrt((double)bitStream->GetBitLength()))-this->mathFuncs->Normal((4*k+1)*z/sqrt((double)bitStream->GetBitLength())));
		this->pValue = 1.0 - sum1 + sum2;
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
		return this->random;
	}

	// Initializes the object
	void CumulativeSumReverseTest::Initialize(void) {

		BaseRandomTest::Initialize();
		cuSum = 0;
	}

	// Gets the type of the object
	RandomTests CumulativeSumReverseTest::GetType(void) {

		return this->test;
	}

	// Gets the minimum random stream length
	unsigned int CumulativeSumReverseTest::GetMinimumLength(void) {

		return this->minimumLength;
	}

	// Gets the maximum partial sum
	double CumulativeSumReverseTest::GetCuSum(void) {

		return this->cuSum;
	}
  }
}
