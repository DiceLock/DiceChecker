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
#include "baseRandomTest.h"


using namespace std;


namespace DiceLockSecurity {
	
  namespace RandomTest {
	
	// Constructor
	BaseRandomTest::BaseRandomTest() {

		this->error = NoError;
		this->alpha = 0.0;
		this->pValue = 0.0;
		this->mathFuncs = new MathematicalFunctions();
		if (this->mathFuncs == NULL) {
			this->error = MathematicalFunctionsError;
			this->autoMathFunc = false;
		}
		else {
			this->autoMathFunc = true;
		}
		this->random = false;
	}

	// Constructor with a MathematicalFunctions object instantiated 
	BaseRandomTest::BaseRandomTest(MathematicalFunctions* mathFuncObj) {

		this->error = NoError;
		if (mathFuncObj != NULL) { 
			mathFuncs = mathFuncObj;
			this->autoMathFunc = false;
		}
		else {
			this->mathFuncs = new MathematicalFunctions();
			if (this->mathFuncs == NULL) {
				this->error = MathematicalFunctionsError;
				this->autoMathFunc = false;
			}
			else {
				this->autoMathFunc = true;
			}
		}
		this->alpha = 0.0;
		this->pValue = 0.0;
		this->mathFuncs = NULL;
		this->random = false;
	}

	// Destructor
	BaseRandomTest::~BaseRandomTest() {

		this->alpha = 0.0;
		this->pValue = 0.0;
		if ((this->autoMathFunc) && (this->mathFuncs != NULL)) {
			delete this->mathFuncs;
			this->mathFuncs = NULL;
		}
		this->mathFuncs = NULL;
		this->random = false;
		this->error = NoError;
	}

	// Sets the BaseRandomTest alpha margin
	void BaseRandomTest::SetAlpha(double newAlpha) {

		this->alpha = newAlpha;
	}

	// Gets the BaseRandomTest alpha margin
	double BaseRandomTest::GetAlpha(void) {

		return this->alpha; 
	}

	// Gets the BaseRandomTest pValue
	double BaseRandomTest::GetPValue(void) {

		return this->pValue; 
	}

	// Gets the BaseRandomTest error of the last executed BaseCryptoRandomStream
	RandomTestErrors BaseRandomTest::GetError(void) {

		return this->error;
	}

	// Gets the BaseRandomTest random state of the last executed BaseCryptoRandomStream
	bool BaseRandomTest::IsRandom(void) {

		return this->random;
	}

	// Initialize the object
	void BaseRandomTest::Initialize(void) {

		this->pValue = 0.0;
		this->random = false;
		this->error = NoError;
	}
  }
}