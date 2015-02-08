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

#ifndef APPROXIMATEENTROPYTEST_HPP

#define APPROXIMATEENTROPYTEST_HPP

#ifdef DICELOCKCIPHER_EXPORTS
   #define CLASS_DECLSPEC    __declspec(dllexport)
#else
   #define CLASS_DECLSPEC    __declspec(dllimport)
#endif

#include "baseRandomTest.h"
#include "mathematicalFunctions.h"


namespace DiceLockSecurity {

  namespace RandomTest {

	  class ApproximateEntropyTest : public BaseRandomTest {

		protected:

			// Random Test Class enumerator name
			static const RandomTests	test;
			// Random Test Class minimum stream length
			static const unsigned int	minimumLength;

			int     blockLength;
			double	chiSquared;
			double	phi;
			double	phiPlusOne;
			double	apEn;
			bool	blockSizeExceeded;		
			unsigned int	maximumBlockSizeRecommended;	 

		public:

			// Constructor, default 
			CLASS_DECLSPEC ApproximateEntropyTest();

			// Constructor with a MathematicalFunctions object instantiated 
			CLASS_DECLSPEC ApproximateEntropyTest(MathematicalFunctions*);

			// Destructor
			CLASS_DECLSPEC ~ApproximateEntropyTest();

			// Gets the BaseRandomTest random state of the last executed BaseCryptoRandomStream
			CLASS_DECLSPEC bool IsRandom(void);

			// Tests the BaseCryptoRandomStream executed and returns the random value
			CLASS_DECLSPEC bool IsRandom(BaseCryptoRandomStream*);

			// Initializes the object
			CLASS_DECLSPEC void Initialize(void);

			// Gets the type of the object
			CLASS_DECLSPEC RandomTests GetType(void);

			// Gets the minimum random stream length
			CLASS_DECLSPEC unsigned int GetMinimumLength(void);

			// Sets the "m" parameter
			CLASS_DECLSPEC void SetBlockLength(int);

			// Gets the "m" parameter
			CLASS_DECLSPEC int GetBlockLength(void);

			// Gets the "ChiSquared" result
			CLASS_DECLSPEC double GetChiSquared(void);

			// Gets the "Phi" result
			CLASS_DECLSPEC double GetPhi(void);

			// Gets the "PhiPlusOne" result
			CLASS_DECLSPEC double GetPhiPlusOne(void);

			// Gets the "apEn" result
			CLASS_DECLSPEC double GetApEn(void);

			// Gets the "BlockSizeExceeded" result
			CLASS_DECLSPEC bool GetBlockSizeExceeded(void);		

			// Gets the "BlockSizeRecommended" result
			CLASS_DECLSPEC unsigned int GetMaximumBlockSizeRecommended(void);	 

			// Gets the "BlockSizeRecommended" for the indicated stream length
			CLASS_DECLSPEC unsigned int MaximumBlockSizeRecommended(unsigned int);
	};
  }
}

#endif
