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
// 
// DICELOCK IS A REGISTERED TRADEMARK OR TRADEMARK OF THE OWNERS.
// 

#ifndef SERIALTEST_HPP

#define SERIALTEST_HPP

#ifdef DICELOCKCIPHER_EXPORTS
   #define CLASS_DECLSPEC    __declspec(dllexport)
#else
   #define CLASS_DECLSPEC    __declspec(dllimport)
#endif

#include "baseRandomTest.h"
#include "mathematicalFunctions.h"


namespace DiceLockSecurity {

  namespace RandomTest {

	  class SerialTest : public BaseRandomTest {

		protected:

			/// Random Test Class enumerator name
			static const RandomTests	test;
			/// Random Test Class minimum stream length
			static const unsigned long int	minimumLength;

			unsigned long int blockLength;
			double	pvalue2;				
			double	psim; 
			double	psim1; 
			double	psim2; 
			double	delta1; 
			double	delta2;

			/// Psi2 function 
			CLASS_DECLSPEC double psi2(signed long int, BaseCryptoRandomStream*);

		public:

			/// Constructor, default 
			CLASS_DECLSPEC SerialTest();

			/// Constructor with a MathematicalFunctions object instantiated 
			CLASS_DECLSPEC SerialTest(MathematicalFunctions*);

			/// Destructor
			CLASS_DECLSPEC ~SerialTest();

			/// Gets the BaseRandomTest random state of the last executed BaseCryptoRandomStream
			CLASS_DECLSPEC bool IsRandom(void);

			/// Tests randomness of the BaseCryptoRandomStream and returns the random value
			CLASS_DECLSPEC bool IsRandom(BaseCryptoRandomStream *);

			/// Initializes the object
			CLASS_DECLSPEC void Initialize(void);

			/// Gets the type of the object
			CLASS_DECLSPEC RandomTests GetType(void);

			/// Gets the minimum random stream length
			CLASS_DECLSPEC unsigned long int GetMinimumLength(void);

			/// Sets the "blockLength" parameter 
			CLASS_DECLSPEC void SetBlockLength(unsigned long int);

			/// Gets the "blockLength" parameter 
			CLASS_DECLSPEC unsigned long int GetBlockLength(void);

			/// Gets the pvalue1 result  
			CLASS_DECLSPEC double GetPvalue(void);				

			/// Gets the pvalue2 result  
			CLASS_DECLSPEC double GetPValue2(void);				

			/// Gets the "psim" result  
			CLASS_DECLSPEC double GetPsim(void); 

			/// Gets the "psim1" result  
			CLASS_DECLSPEC double GetPsim1(void); 

			/// Gets the "psim2" result  
			CLASS_DECLSPEC double GetPsim2(void); 

			/// Gets the "delta1" result  
			CLASS_DECLSPEC double GetDelta1(void); 

			/// Gets the "delta2" result  
			CLASS_DECLSPEC double GetDelta2(void);

			/// Gets the "BlockSizeRecommended" for the indicated stream length
			CLASS_DECLSPEC unsigned long int MaximumBlockSizeRecommended(unsigned long int);
	};
  }
}

#endif