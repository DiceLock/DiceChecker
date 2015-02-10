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
// 
// DICELOCK IS A REGISTERED TRADEMARK OR TRADEMARK OF THE OWNERS.
// 

#ifndef RUNSTEST_HPP

#define RUNSTEST_HPP

#ifdef DICELOCKCIPHER_EXPORTS
   #define CLASS_DECLSPEC    __declspec(dllexport)
#else
   #define CLASS_DECLSPEC    __declspec(dllimport)
#endif

#include "baseRandomTest.h"
#include "mathematicalFunctions.h"


namespace DiceLockSecurity {

  namespace RandomTest {

	  class RunsTest : public BaseRandomTest {

		protected:

			/// Random Test Class enumerator name
			static const RandomTests	test;
			/// Random Test Class minimum stream length
			static const unsigned long int	minimumLength;

			double      pi;
			double      totalNumberRuns;
			double		argument;

		public:

			/// Constructor, default 
			CLASS_DECLSPEC RunsTest();

			/// Constructor with a MathematicalFunctions object instantiated 
			CLASS_DECLSPEC RunsTest(MathematicalFunctions*);

			/// Destructor
			CLASS_DECLSPEC ~RunsTest();

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

			/// Gets the "pi" result
			CLASS_DECLSPEC double GetPi(void);

			/// Gets the total number of runs result 
			CLASS_DECLSPEC double GetTotalNumberRuns(void);

			/// Gets the argument result
			CLASS_DECLSPEC double GetArgument(void);
	};
  }
}

#endif
