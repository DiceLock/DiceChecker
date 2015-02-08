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
// 
// DICELOCK IS A REGISTERED TRADEMARK OR TRADEMARK OF THE OWNERS
// 

#ifndef OVERLAPPINGTEMPLATEMATCHINGSTEST_HPP

#define OVERLAPPINGTEMPLATEMATCHINGSTEST_HPP

#ifdef DICELOCKCIPHER_EXPORTS
   #define CLASS_DECLSPEC    __declspec(dllexport)
#else
   #define CLASS_DECLSPEC    __declspec(dllimport)
#endif

#include "baseRandomTest.h"
#include "mathematicalFunctions.h"


namespace DiceLockSecurity {

  namespace RandomTest {

	  class OverlappingTemplateMatchingsTest : public BaseRandomTest {

		protected:

			// Random Test Class enumerator name
			static const RandomTests	test;
			// Random Test Class minimum stream length
			static const unsigned int	minimumLength;

			// Random Test Class block sizes
			static const short	numberWindowLengths;
			static const short	windowLengths[2];

			static const int NumAssignments;	// 6
			static const int OverlappingStringTested;	// 1032
			int         windowLength; // m
			int         substringLength;
			int         substringNumber;
			double      chiSquared;
			double      eta;
			double      lambda;
			unsigned int assignment[6];

			// Computes probability
			double Probability(int, double);

		public:

			// Constructor, default 
			CLASS_DECLSPEC OverlappingTemplateMatchingsTest();

			// Constructor with a MathematicalFunctions object instantiated 
			CLASS_DECLSPEC OverlappingTemplateMatchingsTest(MathematicalFunctions*);

			// Destructor
			CLASS_DECLSPEC ~OverlappingTemplateMatchingsTest();

			// Tests randomness of the BaseCryptoRandomStream and returns the random value
			CLASS_DECLSPEC bool IsRandom(BaseCryptoRandomStream*);

			// Initializes the object
			CLASS_DECLSPEC void Initialize(void);

			// Gets the type of the object
			CLASS_DECLSPEC RandomTests GetType(void);

			// Gets the minimum random stream length
			CLASS_DECLSPEC unsigned int GetMinimumLength(void);

			// Gets the available window lengths
			CLASS_DECLSPEC int GetWindowLengths(void);

			// Gets the window length based on the index
			CLASS_DECLSPEC int GetWindowLengthOfIndex(int);

			// Sets the "windowLength" parameter
			CLASS_DECLSPEC void SetWindowLength(int);

			// Gets the "windowLength" parameter
			CLASS_DECLSPEC int GetWindowLength(void);

			// Gets the "substringLength" result
			CLASS_DECLSPEC int GetSubstringLength(void);

			// Gets the "substringNumber" result
			CLASS_DECLSPEC int GetSubstringNumber(void);

			// Gets the "chiSquared" result
			CLASS_DECLSPEC double GetChiSquared(void);

			// Gets the "eta" result
			CLASS_DECLSPEC double GetEta(void);

			// Gets the "lambda" result
			CLASS_DECLSPEC double GetLambda(void);

			// Gets the Assignment result
			CLASS_DECLSPEC void GetAssignment(unsigned int*);

			// Gets the Assignment result based on the index
			CLASS_DECLSPEC unsigned int GetAssignmentOfIndex(int);
	};
  }
}

#endif

