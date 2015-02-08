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
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// DICELOCK IS A REGISTERED TRADEMARK OR TRADEMARK OF THE OWNERS
// 

#ifndef LINEARCOMPLEXITYTEST_HPP

#define LINEARCOMPLEXITYTEST_HPP

#ifdef DICELOCKCIPHER_EXPORTS
   #define CLASS_DECLSPEC    __declspec(dllexport)
#else
   #define CLASS_DECLSPEC    __declspec(dllimport)
#endif

#include "baseRandomTest.h"
#include "mathematicalFunctions.h"


namespace DiceLockSecurity {

  namespace RandomTest {

	  class LinearComplexityTest : public BaseRandomTest {

		protected:

			// Random Test Class enumerator name
			static const RandomTests	test;
			// Random Test Class minimum stream length
			static const unsigned int	minimumLength;

			// Minimum Block size
			static const int	minimumBlock;
			// Maximum Block size
			static const int	maximumBlock;

			static const int NumNus;	// 7 
			int		blockLength;
			double  chiSquared;
			int     bitsDiscarded;
			int     substringNumber;
			double*	nu; 

		public:

			// Constructor, default 
			CLASS_DECLSPEC LinearComplexityTest();

			// Constructor, providing BlockLength parameter
			CLASS_DECLSPEC LinearComplexityTest(int);

			// Constructor with a MathematicalFunctions object instantiated 
			CLASS_DECLSPEC LinearComplexityTest(MathematicalFunctions*);

			// Destructor
			CLASS_DECLSPEC ~LinearComplexityTest();

			// Tests randomness of the BaseCryptoRandomStream and returns the random value
			CLASS_DECLSPEC bool IsRandom(BaseCryptoRandomStream*);

			// Initializes the object
			CLASS_DECLSPEC void Initialize(void);

			// Gets the type of the object
			CLASS_DECLSPEC RandomTests GetType(void);

			// Gets the minimum random stream length
			CLASS_DECLSPEC unsigned int GetMinimumLength(void);

			// Gets the "MinimumBlockSize" 
			CLASS_DECLSPEC int GetMinimumBlockSize(void);

			// Gets the "MaximumBlockSize" 
			CLASS_DECLSPEC int GetMaximumBlockSize(void);

			// Sets the "BlockLength" parameter
			CLASS_DECLSPEC void SetBlockLength(int);

			// Gets the "BlockLength" parameter
			CLASS_DECLSPEC	int GetBlockLength(void);

			// Gets the "chiSquared" result
			CLASS_DECLSPEC	double GetChiSquared(void);

			// Gets "bitsDiscarded" result
			CLASS_DECLSPEC	int GetBitsDiscarded(void);

			// Gets the "substringNumber" result
			CLASS_DECLSPEC	double GetSubstringNumber(void);

			// Gets the Nu result array
			CLASS_DECLSPEC void GetNu(double *);

			// Gets the Nu result based on the index 
			CLASS_DECLSPEC double GetNuOfIndex(int);
	};
  }
}

#endif

