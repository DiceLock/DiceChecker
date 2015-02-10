//
// Creator:    http://www.dicelocksecurity.com
// Version:    vers.5.0.0.1
//
// Copyright � 2008-2011 DiceLock Security, LLC. All rights reserved.
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

#ifndef LONGESTRUNOFONES_HPP

#define LONGESTRUNOFONES_HPP

#ifdef DICELOCKCIPHER_EXPORTS
   #define CLASS_DECLSPEC    __declspec(dllexport)
#else
   #define CLASS_DECLSPEC    __declspec(dllimport)
#endif

#include "baseRandomTest.h"
#include "mathematicalFunctions.h"


namespace DiceLockSecurity {

  namespace RandomTest {

	  class LongestRunOfOnesTest : public BaseRandomTest {

		protected:

			/// Random Test Class enumerator name
			static const RandomTests	test;
			/// Random Test Class minimum stream length
			static const unsigned long int	minimumLength;

			/// Random Test Class block sizes and minimum lengths
			struct blockSizeMinimumLength {
				unsigned long int blockSize;
				unsigned long int minimumLength;
			};
			static const unsigned short int numberBlockSizes;
			static const blockSizeMinimumLength	blockSizes[3];

			static const unsigned short int NumAssignments;	// 7 
			unsigned long int longRunCase;
			unsigned long int substringNumber;
			unsigned long int substringLength;
			unsigned long int *assignment;
			double       chiSquared;
			
		public:

			/// Constructor, default 
			CLASS_DECLSPEC LongestRunOfOnesTest();

			/// Constructor with a MathematicalFunctions object instantiated 
			CLASS_DECLSPEC LongestRunOfOnesTest(MathematicalFunctions*);

			/// Destructor
			CLASS_DECLSPEC ~LongestRunOfOnesTest();

			/// Gets the BaseRandomTest random state of the last executed BaseCryptoRandomStream
			CLASS_DECLSPEC bool IsRandom(void);

			/// Tests randomness of the BaseCryptoRandomStream and returns the random value
			CLASS_DECLSPEC bool IsRandom(BaseCryptoRandomStream*);

			/// Initializes the object
			CLASS_DECLSPEC void Initialize(void);

			/// Gets the type of the object
			CLASS_DECLSPEC RandomTests GetType(void);

			/// Gets the minimum random stream length
			CLASS_DECLSPEC unsigned long int GetMinimumLength(void);

			/// Sets the longRunCase parameter 
			CLASS_DECLSPEC void SetLongRunCase(unsigned long int);

			/// Gets the longRunCase parameter 
			CLASS_DECLSPEC unsigned long int GetLongRunCase(void);

			/// Gets the "substringNumber" result 
			CLASS_DECLSPEC unsigned long int GetSubstringNumber(void);

			/// Gets the "substringLength" result
			CLASS_DECLSPEC unsigned long int GetSubstringLength(void);

			/// Gets the chiSquared result
			CLASS_DECLSPEC double GetChiSquared(void);

			/// Gets the Assignment result
			CLASS_DECLSPEC void GetAssignment(unsigned long int *);

			/// Gets the Assignment result based on the index
			CLASS_DECLSPEC unsigned long int GetAssignmentOfIndex(unsigned long int);
	};
  }
}

#endif
