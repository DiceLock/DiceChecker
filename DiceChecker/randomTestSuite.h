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

#ifndef RANDOMTESTSUITE_HPP

#define RANDOMTESTSUITE_HPP

#ifdef DICELOCKCIPHER_EXPORTS
   #define CLASS_DECLSPEC    __declspec(dllexport)
#else
   #define CLASS_DECLSPEC    __declspec(dllimport)
#endif

#include "diceChecker.h"


namespace DiceLockSecurity {

  namespace RandomTest {

	  class RandomTestSuite {

		protected:

			/// Points the first random test in the suite
			static const	RandomTests firstTest;

			BaseRandomTest*			suite[NumberOfTests];
			bool					selfCreatedTest[NumberOfTests];
			bool					usedTests[NumberOfTests];
			bool					random;
			bool					strictRandomnessCheck;
			MathematicalFunctions*  mathFunctions;    
			bool					selfCreatedMaths;
			RandomTestErrors		error;
			unsigned short int		instantiatedTests;
			unsigned short int		numberOfErrors;
			RandomTests				errorTest;
			RandomTests				nonRandomTest;

		public:

			/// Constructor, default, initializes suite and instantiates MathematicalFunctions  
			CLASS_DECLSPEC RandomTestSuite();

			/// Constructor, initializes suite and assigns MathematicalFunctions parameter
			CLASS_DECLSPEC RandomTestSuite(MathematicalFunctions*);

			/// Destructor
			CLASS_DECLSPEC ~RandomTestSuite();

			// ADDING RANDOM TESTS
			
			/// Adds a random test to the suite
			CLASS_DECLSPEC void Add(BaseRandomTest*);

			/// Creates and adds a random test to the suite based in the enumerated random tests
			CLASS_DECLSPEC void Add(RandomTests);

			/// Creates and adds all random test to the suite
			CLASS_DECLSPEC void AddAll(void);

			/// Creates and adds the defined random test to the suite
			CLASS_DECLSPEC void AddFrequencyTest(void);

			/// Creates and adds the defined random test to the suite
			CLASS_DECLSPEC void AddBlockFrequencyTest(void);

			/// Creates and adds the defined random test to the suite
			CLASS_DECLSPEC void AddRunsTest(void);

			/// Creates and adds the defined random test to the suite
			CLASS_DECLSPEC void AddLongestRunOfOnesTest(void);

			/// Creates and adds the defined random test to the suite
			CLASS_DECLSPEC void AddCumulativeSumForwardTest(void);

			/// Creates and adds the defined random test to the suite
			CLASS_DECLSPEC void AddCumulativeSumReverseTest(void);

			/// Creates and adds the defined random test to the suite
			CLASS_DECLSPEC void AddRankTest(void);

			/// Creates and adds the defined random test to the suite
			CLASS_DECLSPEC void AddUniversalTest(void);

			/// Creates and adds the defined random test to the suite
			CLASS_DECLSPEC void AddApproximateEntropyTest(void);

			/// Creates and adds the defined random test to the suite
			CLASS_DECLSPEC void AddSerialTest(void);

			/// Creates and adds the defined random test to the suite
			CLASS_DECLSPEC void AddDiscreteFourierTransformTest(void);

			// GETTING RANDOM TESTS
			
			/// Gets a random test to the suite based in the enumerated random tests
			CLASS_DECLSPEC BaseRandomTest* GetRandomTest(RandomTests);

			/// Gets the defined random test to the suite
			CLASS_DECLSPEC FrequencyTest* GetFrequencyTest(void);

			/// Gets the defined random test to the suite
			CLASS_DECLSPEC BlockFrequencyTest* GetBlockFrequencyTest(void);

			/// Gets the defined random test to the suite
			CLASS_DECLSPEC RunsTest* GetRunsTest(void);

			/// Gets the defined random test to the suite
			CLASS_DECLSPEC LongestRunOfOnesTest* GetLongestRunOfOnesTest(void);

			/// Gets the defined random test to the suite
			CLASS_DECLSPEC CumulativeSumForwardTest* GetCumulativeSumForwardTest(void);

			/// Gets the defined random test to the suite
			CLASS_DECLSPEC CumulativeSumReverseTest* GetCumulativeSumReverseTest(void);

			/// Gets the defined random test to the suite
			CLASS_DECLSPEC RankTest* GetRankTest(void);

			/// Gets the defined random test to the suite
			CLASS_DECLSPEC UniversalTest* GetUniversalTest(void);

			/// Gets the defined random test to the suite
			CLASS_DECLSPEC ApproximateEntropyTest* GetApproximateEntropyTest(void);

			/// Gets the defined random test to the suite
			CLASS_DECLSPEC SerialTest* GetSerialTest(void);

			/// Gets the defined random test to the suite
			CLASS_DECLSPEC DiscreteFourierTransformTest* GetDiscreteFourierTransformTest(void);

			// REMOVING RANDOM TESTS

			/// Removes a random test to the suite
			CLASS_DECLSPEC void Remove(BaseRandomTest*);

			/// Removes a random test to the suite based in the enumerated random tests
			CLASS_DECLSPEC void Remove(RandomTests);

			/// Removes all random test of the suite
			CLASS_DECLSPEC void RemoveAll(void);

			/// Removes the defined random test to the suite
			CLASS_DECLSPEC void RemoveFrequencyTest(void);

			/// Removes the defined random test to the suite
			CLASS_DECLSPEC void RemoveBlockFrequencyTest(void);

			/// Removes the defined random test to the suite
			CLASS_DECLSPEC void RemoveRunsTest(void);

			/// Removes the defined random test to the suite
			CLASS_DECLSPEC void RemoveLongestRunOfOnesTest(void);

			/// Removes the defined random test to the suite
			CLASS_DECLSPEC void RemoveCumulativeSumForwardTest(void);

			/// Removes the defined random test to the suite
			CLASS_DECLSPEC void RemoveCumulativeSumReverseTest(void);

			/// Removes the defined random test to the suite
			CLASS_DECLSPEC void RemoveRankTest(void);

			/// Removes the defined random test to the suite
			CLASS_DECLSPEC void RemoveUniversalTest(void);

			/// Removes the defined random test to the suite
			CLASS_DECLSPEC void RemoveApproximateEntropyTest(void);

			/// Removes the defined random test to the suite
			CLASS_DECLSPEC void RemoveSerialTest(void);

			/// Removes the defined random test to the suite
			CLASS_DECLSPEC void RemoveDiscreteFourierTransformTest(void);

			// CHECKING RANDOMNESS

			/// Tests the BaseCryptoRandomStream untill an error is found with all instantiated random tests and returns the random value
			CLASS_DECLSPEC bool IsRandom(BaseCryptoRandomStream*);

			/// Tests the BaseCryptoRandomStream with all instantiated random tests and returns the random value
			CLASS_DECLSPEC bool TestRandom(BaseCryptoRandomStream*);

			// INITIALIZE SUITE
			
			/// Initializes all random tests in the suite
			CLASS_DECLSPEC void Initialize(void);

			/// Sets Alpha all random tests in the suite
			CLASS_DECLSPEC void SetAlpha(double);

			// GETTING SUITE RESULTS

			/// Gets the RandomTestSuite random state of the last executed BaseCryptoRandomStream
			CLASS_DECLSPEC bool IsRandom(void);

			/// Gets the number of Random Tests that contains the suite
			CLASS_DECLSPEC unsigned short int GetInstantiatedTests(void);

			/// Gets the minimum random stream length in bits corresponding
			/// to random number test with higher random stream length
			CLASS_DECLSPEC unsigned long int GetMinimumLength(void);

			/// Gets the corresponding random number test 
			/// with higher minimum random stream length in bits 
			CLASS_DECLSPEC RandomTests GetMinimumLengthRandomTest(void);

			/// Gets the failed random test in the RandomTestSuite
			CLASS_DECLSPEC RandomTests GetNonRandomTest(void);

			/// Gets the RandomTestError error of the last executed BaseCryptoRandomStream
			CLASS_DECLSPEC RandomTestErrors GetError(void);

			/// Gets the RandomTest that produced the error of the last executed BaseCryptoRandomStream
			CLASS_DECLSPEC RandomTests GetErrorTest(void);

			/// Indicates if a random test object exists in the suite
			CLASS_DECLSPEC bool Exist(RandomTests);

			/// Gets the first random test in the RandomTestSuite
			CLASS_DECLSPEC RandomTests GetFirstTest(void);

			/// Gets the number of random tests that can be used in the RandomTestSuite
			CLASS_DECLSPEC RandomTests GetMaximumNumberOfTests(void);

			/// STRICT RANDOMNESS METHODS

			/// Sets strict randomness checking, if all random tests instantiated in the suite will be verified
			/// true: all random tests instantiated in the suite will be verified
			/// false: just random tests that can be checked (stream length larger than random test minimum length) will be verified 
			CLASS_DECLSPEC void SetStrictRandomnessCheck(bool);

			/// Gets strict randomness checking, if all random tests instantiated in the suite will be verified
			CLASS_DECLSPEC bool SetStrictRandomnessCheck(void);

			/// USED TEST METHODS WHEN STRICT RANDOMNESS CHECKING IS DISABLED

			/// Gets number of random test that has been used in last random test checking
			CLASS_DECLSPEC unsigned short int GetUsedTestsNumber(void);

			/// Gets if enumerated random test has been used in last random test checking
			CLASS_DECLSPEC bool GetUsedTest(RandomTests);

			/// Gets if frequency random test has been used in last random test checking
			CLASS_DECLSPEC bool GetUsedFrequencyTest(void);

			/// Gets if block frequency random test has been used in last random test checking
			CLASS_DECLSPEC bool GetUsedBlockFrequencyTest(void);

			/// Gets if cumulative sum forward random test has been used in last random test checking
			CLASS_DECLSPEC bool GetUsedCumulativeSumForwardTest(void);

			/// Gets if cumulative sum reverse random test has been used in last random test checking
			CLASS_DECLSPEC bool GetUsedCumulativeSumReverseTest(void);

			/// Gets if runs random test has been used in last random test checking
			CLASS_DECLSPEC bool GetUsedRunsTest(void);

			/// Gets if longest run of ones random test has been used in last random test checking
			CLASS_DECLSPEC bool GetUsedLongestRunOfOnesTest(void);

			/// Gets if rank random test has been used in last random test checking
			CLASS_DECLSPEC bool GetUsedRankTest(void);

			/// Gets if universal random test has been used in last random test checking
			CLASS_DECLSPEC bool GetUsedUniversalTest(void);

			/// Gets if approximate entropy random test has been used in last random test checking
			CLASS_DECLSPEC bool GetUsedApproximateEntropyTest(void);

			/// Gets if serial random test has been used in last random test checking
			CLASS_DECLSPEC bool GetUsedSerialTest(void);

			/// Gets if discrete fourier transform random test has been used in last random test checking
			CLASS_DECLSPEC bool GetUsedDiscreteFourierTransformTest(void);

			/// Resets all random test "used" signal to false 
			CLASS_DECLSPEC void ResetUsedTests(void);

	};
  }
}

#endif
