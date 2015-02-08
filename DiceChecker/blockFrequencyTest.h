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
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// DICELOCK IS A REGISTERED TRADEMARK OR TRADEMARK OF THE OWNERS
// 

#ifndef BLOCKFREQUENCYTEST_HPP

#define BLOCKFREQUENCYTEST_HPP

#ifdef DICELOCKCIPHER_EXPORTS
   #define CLASS_DECLSPEC    __declspec(dllexport)
#else
   #define CLASS_DECLSPEC    __declspec(dllimport)
#endif

#include "baseRandomTest.h"
#include "mathematicalFunctions.h"


namespace DiceLockSecurity {

  namespace RandomTest {

	  class BlockFrequencyTest : public BaseRandomTest {

		protected:

			// Random Test Class enumerator name
			static const RandomTests	test;
			// Random Test Class minimum stream length
			static const unsigned int	minimumLength;

			int 	blockLength;
			double	chiSquared;
			int		blockNumber;
			int 	bitsDiscarded;

		public:

			// Constructor, default 
			CLASS_DECLSPEC BlockFrequencyTest();

			// Constructor, setting the block length 
			CLASS_DECLSPEC BlockFrequencyTest(unsigned int);

			// Constructor with a MathematicalFunctions object instantiated 
			CLASS_DECLSPEC BlockFrequencyTest(MathematicalFunctions*);

			// Destructor
			CLASS_DECLSPEC ~BlockFrequencyTest();

			// Tests randomness of the BaseCryptoRandomStream and returns the random value
			CLASS_DECLSPEC bool IsRandom(BaseCryptoRandomStream*);

			// Initializes the object
			CLASS_DECLSPEC void Initialize(void);

			// Gets the type of the object
			CLASS_DECLSPEC RandomTests GetType(void);

			// Gets the minimum random stream length
			CLASS_DECLSPEC unsigned int GetMinimumLength(void);

			// Sets the blockLength
			CLASS_DECLSPEC void SetBlockLength(unsigned int);

			// Gets the blockLength
			CLASS_DECLSPEC unsigned int GetBlockLength(void);

			// Gets chiSquared
			CLASS_DECLSPEC double GetChiSquared(void);

			// Gets blocksNumber tested
			CLASS_DECLSPEC int GetBlockNumber(void);

			// Gets the bitsDiscarded not tested
			CLASS_DECLSPEC int GetBitsDiscarded(void);
	};
  }
}

#endif

