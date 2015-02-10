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

#include <stdexcept>
#include <stdlib.h>
#include "randomTestSuite.h"


using namespace std;


namespace DiceLockSecurity {
	
  namespace RandomTest {

		// Points the first random test in the suite
		const RandomTests RandomTestSuite::firstTest = Frequency;

		// Constructor, default, initializes suite and instantiates MathematicalFunctions  
		RandomTestSuite::RandomTestSuite() {
			int i;

			for (i=this->GetFirstTest(); i<this->GetMaximumNumberOfTests(); i++) {
				this->suite[i] = NULL;
				this->selfCreatedTest[i] = false;
			}
			this->random = false;
			mathFunctions = new MathematicalFunctions();
			selfCreatedMaths = true;
			this->error = NoError;
			this->instantiatedTests = 0;
			this->numberOfErrors = 0;
			this->errorTest = NotDefined;
			this->nonRandomTest = NotDefined;
		}

		// Constructor, initializes suite and assigns MathematicalFunctions parameter
		RandomTestSuite::RandomTestSuite(MathematicalFunctions* mathFuncs) {
			int i;

			for (i=this->GetFirstTest(); i<this->GetMaximumNumberOfTests(); i++) {
				this->suite[i] = NULL;
				this->selfCreatedTest[i] = false;
			}
			this->random = false;
			mathFunctions = mathFuncs;
			selfCreatedMaths = false;
			this->error = NoError;
			this->instantiatedTests = 0;
			this->numberOfErrors = 0;
			this->errorTest = NotDefined;
			this->nonRandomTest = NotDefined;
		}

		// Destructor
		RandomTestSuite::~RandomTestSuite() {
			int i;

			for (i=this->GetFirstTest(); i<this->GetMaximumNumberOfTests(); i++) {
				if (this->suite[i] != NULL) {
					delete this->suite[i];
					this->suite[i] = NULL;
				    this->selfCreatedTest[i] = false;
				}
			}
			this->random = false;
			if (selfCreatedMaths) {
				delete mathFunctions;
			}
			this->error = NoError;
			this->instantiatedTests = 0;
			this->numberOfErrors = 0;
			this->errorTest = NotDefined;
			this->nonRandomTest = NotDefined;
		}

		// ADDING RANDOM TESTS
			
		// Adds a random test to the suite
		void RandomTestSuite::Add(BaseRandomTest* test) {

			if (test != NULL) {
				this->suite[test->GetType()] = test;
				this->selfCreatedTest[test->GetType()] = false;
				this->instantiatedTests++;
			}
		}

		// Creates and adds a random test to the suite based in the enumerated random tests
		void RandomTestSuite::Add(RandomTests test) {

			switch (test) {
				case Frequency: 
					if (this->suite[Frequency] == NULL) {
						this->suite[Frequency] = new FrequencyTest(this->mathFunctions);
						this->instantiatedTests++;
					}
					break;
				case BlockFrequency: 
					if (this->suite[BlockFrequency] == NULL) {
						this->suite[BlockFrequency] = new BlockFrequencyTest(this->mathFunctions);
						this->instantiatedTests++;
					}
					break;
				case Runs: 
					if (this->suite[Runs] == NULL) {
						this->suite[Runs] = new RunsTest(this->mathFunctions);
						this->instantiatedTests++;
					}
					break;
				case LongestRunOfOnes: 
					if (this->suite[LongestRunOfOnes] == NULL) {
						this->suite[LongestRunOfOnes] = new LongestRunOfOnesTest(this->mathFunctions);
						this->instantiatedTests++;
					}
					break;
				case CumulativeSumForward: 
					if (this->suite[CumulativeSumForward] == NULL) {
						this->suite[CumulativeSumForward] = new CumulativeSumForwardTest(this->mathFunctions);
						this->instantiatedTests++;
					}
					break;
				case CumulativeSumReverse: 
					if (this->suite[CumulativeSumReverse] == NULL) {
						this->suite[CumulativeSumReverse] = new CumulativeSumReverseTest(this->mathFunctions);
						this->instantiatedTests++;
					}
					break;
				case Rank: 
					if (this->suite[Rank] == NULL) {
						this->suite[Rank] = new RankTest(this->mathFunctions);
						this->instantiatedTests++;
					}
					break;
				case Universal: 
					if (this->suite[Universal] == NULL) {
						this->suite[Universal] = new UniversalTest(this->mathFunctions);
						this->instantiatedTests++;
					}
					break;
				case ApproximateEntropy: 
					if (this->suite[ApproximateEntropy] == NULL) {
						this->suite[ApproximateEntropy] = new ApproximateEntropyTest(this->mathFunctions);
						this->instantiatedTests++;
					}
					break;
				case Serial: 
					if (this->suite[Serial] == NULL) {
						this->suite[Serial] = new SerialTest(this->mathFunctions);
						this->instantiatedTests++;
					}
					break;
				case DiscreteFourierTransform: 
					if (this->suite[DiscreteFourierTransform] == NULL) {
						this->suite[DiscreteFourierTransform] = new DiscreteFourierTransformTest(this->mathFunctions);
						this->instantiatedTests++;
					}
					break;
				default:
					break;
			}
			this->selfCreatedTest[test] = true;
		}

		// Creates and adds all random tests to the suite 
		void RandomTestSuite::AddAll(void) {
			int i;

			this->suite[Frequency] = new FrequencyTest(this->mathFunctions);
			this->suite[BlockFrequency] = new BlockFrequencyTest(this->mathFunctions);
			this->suite[Runs] = new RunsTest(this->mathFunctions);
			this->suite[LongestRunOfOnes] = new LongestRunOfOnesTest(this->mathFunctions);
			this->suite[CumulativeSumForward] = new CumulativeSumForwardTest(this->mathFunctions);
			this->suite[CumulativeSumReverse] = new CumulativeSumReverseTest(this->mathFunctions);
			this->suite[Rank] = new RankTest(this->mathFunctions);
			this->suite[Universal] = new UniversalTest(this->mathFunctions);
			this->suite[ApproximateEntropy] = new ApproximateEntropyTest(this->mathFunctions);
			this->suite[Serial] = new SerialTest(this->mathFunctions);
			this->suite[DiscreteFourierTransform] = new DiscreteFourierTransformTest(this->mathFunctions);
			for (i=this->GetFirstTest(); i<this->GetMaximumNumberOfTests(); i++) {
				this->selfCreatedTest[i] = true;
			}
			this->instantiatedTests = NumberOfTests;

		}

		// Creates and adds the defined random test to the suite
		void RandomTestSuite::AddFrequencyTest(void) {

			this->suite[Frequency] = new FrequencyTest(this->mathFunctions);
			this->selfCreatedTest[Frequency] = true;
			this->instantiatedTests++;
		}

		// Creates and adds the defined random test to the suite
		void RandomTestSuite::AddBlockFrequencyTest(void) {

			this->suite[BlockFrequency] = new BlockFrequencyTest(this->mathFunctions);
			this->selfCreatedTest[BlockFrequency] = true;
			this->instantiatedTests++;
		}

		// Creates and adds the defined random test to the suite
		void RandomTestSuite::AddRunsTest(void) {

			this->suite[Runs] = new RunsTest(this->mathFunctions);
			this->selfCreatedTest[Runs] = true;
			this->instantiatedTests++;
		}

		// Creates and adds the defined random test to the suite
		void RandomTestSuite::AddLongestRunOfOnesTest(void) {

			this->suite[LongestRunOfOnes] = new LongestRunOfOnesTest(this->mathFunctions);
			this->selfCreatedTest[LongestRunOfOnes] = true;
			this->instantiatedTests++;
		}

		// Creates and adds the defined random test to the suite
		void RandomTestSuite::AddCumulativeSumForwardTest(void) {

			this->suite[CumulativeSumForward] = new CumulativeSumForwardTest(this->mathFunctions);
			this->selfCreatedTest[CumulativeSumForward] = true;
			this->instantiatedTests++;
		}

		// Creates and adds the defined random test to the suite
		void RandomTestSuite::AddCumulativeSumReverseTest(void) {

			this->suite[CumulativeSumReverse] = new CumulativeSumReverseTest(this->mathFunctions);
			this->selfCreatedTest[CumulativeSumReverse] = true;
			this->instantiatedTests++;
		}

		// Creates and adds the defined random test to the suite
		void RandomTestSuite::AddRankTest(void) {

			this->suite[Rank] = new RankTest(this->mathFunctions);
			this->selfCreatedTest[Rank] = true;
			this->instantiatedTests++;
		}

		// Creates and adds the defined random test to the suite
		void RandomTestSuite::AddUniversalTest(void) {

			this->suite[Universal] = new UniversalTest(this->mathFunctions);
			this->selfCreatedTest[Universal] = true;
			this->instantiatedTests++;
		}

		// Creates and adds the defined random test to the suite
		void RandomTestSuite::AddApproximateEntropyTest(void) {

			this->suite[ApproximateEntropy] = new ApproximateEntropyTest(this->mathFunctions);
			this->selfCreatedTest[ApproximateEntropy] = true;
			this->instantiatedTests++;
		}

		// Creates and adds the defined random test to the suite
		void RandomTestSuite::AddSerialTest(void) {

			this->suite[Serial] = new SerialTest(this->mathFunctions);
			this->selfCreatedTest[Serial] = true;
			this->instantiatedTests++;
		}

		// Creates and adds the defined random test to the suite
		void RandomTestSuite::AddDiscreteFourierTransformTest(void) {

			this->suite[DiscreteFourierTransform] = new DiscreteFourierTransformTest(this->mathFunctions);
			this->selfCreatedTest[DiscreteFourierTransform] = true;
			this->instantiatedTests++;
		}

		// GETTING RANDOM TESTS
			
		// Gets a random test to the suite based in the enumerated random tests
		BaseRandomTest* RandomTestSuite::GetRandomTest(RandomTests test) {

			return this->suite[test];
		}

		// Gets the defined random test to the suite
		FrequencyTest* RandomTestSuite::GetFrequencyTest(void) {

			return (FrequencyTest *)this->suite[Frequency];
		}

		// Gets the defined random test to the suite
		BlockFrequencyTest* RandomTestSuite::GetBlockFrequencyTest(void) {

			return (BlockFrequencyTest *)this->suite[BlockFrequency];
		}

		// Gets the defined random test to the suite
		RunsTest* RandomTestSuite::GetRunsTest(void) {

			return (RunsTest *)this->suite[Runs];
		}

		// Gets the defined random test to the suite
		LongestRunOfOnesTest* RandomTestSuite::GetLongestRunOfOnesTest(void) {

			return (LongestRunOfOnesTest *)this->suite[LongestRunOfOnes];
		}

		// Gets the defined random test to the suite
		CumulativeSumForwardTest* RandomTestSuite::GetCumulativeSumForwardTest(void) {

			return (CumulativeSumForwardTest *)this->suite[CumulativeSumForward];
		}

		// Gets the defined random test to the suite
		CumulativeSumReverseTest* RandomTestSuite::GetCumulativeSumReverseTest(void) {

			return (CumulativeSumReverseTest *)this->suite[CumulativeSumReverse];
		}

		// Gets the defined random test to the suite
		RankTest* RandomTestSuite::GetRankTest(void) {

			return (RankTest *)this->suite[Rank];
		}

		// Gets the defined random test to the suite
		UniversalTest* RandomTestSuite::GetUniversalTest(void) {

			return (UniversalTest *)this->suite[Universal];
		}

		// Gets the defined random test to the suite
		ApproximateEntropyTest* RandomTestSuite::GetApproximateEntropyTest(void) {

			return (ApproximateEntropyTest *)this->suite[ApproximateEntropy];
		}

		// Gets the defined random test to the suite
		SerialTest* RandomTestSuite::GetSerialTest(void) {

			return (SerialTest *)this->suite[Serial];
		}

		// Gets the defined random test to the suite
		DiscreteFourierTransformTest* RandomTestSuite::GetDiscreteFourierTransformTest(void) {

			return (DiscreteFourierTransformTest *)this->suite[DiscreteFourierTransform];
		}

		// REMOVING RANDOM TESTS

		// Removes a pointed random test from the suite
		void RandomTestSuite::Remove(BaseRandomTest* test) {
			RandomTests randomTest;

			randomTest = test->GetType();
			if ((this->suite[randomTest] != NULL) && (this->suite[randomTest] == test)) {
				if (this->selfCreatedTest[randomTest]) {
					delete this->suite[randomTest];
				}
				this->suite[randomTest] = NULL;
				this->selfCreatedTest[randomTest] = false;
				this->instantiatedTests--;
			}
		}

		// Removes a random test to the suite based in the enumerated random tests
		void RandomTestSuite::Remove(RandomTests test) {

			if (this->suite[test] != NULL) {
				if (this->selfCreatedTest[test]) {
					delete this->suite[test];
				}
				this->suite[test] = NULL;
				this->selfCreatedTest[test] = false;
				this->instantiatedTests--;
			}
		}

		// Removes all random test of the suite 
		void RandomTestSuite::RemoveAll(void) {
			int i;

			for (i=this->GetFirstTest(); i<this->GetMaximumNumberOfTests(); i++) {
				if (this->suite[i] != NULL) {
					if (this->selfCreatedTest[i]) {
						delete this->suite[i];
					}
					this->suite[i] = NULL;
				    this->selfCreatedTest[i] = false;
				}
			}
			this->instantiatedTests = 0;
		}

		// Removes the defined random test to the suite
		void RandomTestSuite::RemoveFrequencyTest(void) {

			if (this->suite[Frequency] != NULL) {
				if (this->selfCreatedTest[Frequency]) {
					delete this->suite[Frequency];
				}
				this->suite[Frequency] = NULL;
			    this->selfCreatedTest[Frequency] = false;
				this->instantiatedTests--;
			}
		}

		// Removes the defined random test to the suite
		void RandomTestSuite::RemoveBlockFrequencyTest(void) {

			if (this->suite[BlockFrequency] != NULL) {
				if (this->selfCreatedTest[BlockFrequency]) {
					delete this->suite[BlockFrequency];
				}
				this->suite[BlockFrequency] = NULL;
			    this->selfCreatedTest[BlockFrequency] = false;
				this->instantiatedTests--;
			}
		}

		// Removes the defined random test to the suite
		void RandomTestSuite::RemoveRunsTest(void) {

			if (this->suite[Runs] != NULL) {
				if (this->selfCreatedTest[Runs]) {
					delete this->suite[Runs];
				}
				this->suite[Runs] = NULL;
			    this->selfCreatedTest[Runs] = false;
				this->instantiatedTests--;
			}
		}

		// Removes the defined random test to the suite
		void RandomTestSuite::RemoveLongestRunOfOnesTest(void) {

			if (this->suite[LongestRunOfOnes] != NULL) {
				if (this->selfCreatedTest[LongestRunOfOnes]) {
					delete this->suite[LongestRunOfOnes];
				}
				this->suite[LongestRunOfOnes] = NULL;
			    this->selfCreatedTest[LongestRunOfOnes] = false;
				this->instantiatedTests--;
			}
		}

		// Removes the defined random test to the suite
		void RandomTestSuite::RemoveCumulativeSumForwardTest(void) {

			if (this->suite[CumulativeSumForward] != NULL) {
				if (this->selfCreatedTest[CumulativeSumForward]) {
					delete this->suite[CumulativeSumForward];
				}
				this->suite[CumulativeSumForward] = NULL;
			    this->selfCreatedTest[CumulativeSumForward] = false;
				this->instantiatedTests--;
			}
		}

		// Removes the defined random test to the suite
		void RandomTestSuite::RemoveCumulativeSumReverseTest(void) {

			if (this->suite[CumulativeSumReverse] != NULL) {
				if (this->selfCreatedTest[CumulativeSumReverse]) {
					delete this->suite[CumulativeSumReverse];
				}
				this->suite[CumulativeSumReverse] = NULL;
			    this->selfCreatedTest[CumulativeSumReverse] = false;
				this->instantiatedTests--;
			}
		}

		// Removes the defined random test to the suite
		void RandomTestSuite::RemoveRankTest(void) {

			if (this->suite[Rank] != NULL) {
				if (this->selfCreatedTest[Rank]) {
					delete this->suite[Rank];
				}
				this->suite[Rank] = NULL;
			    this->selfCreatedTest[Rank] = false;
				this->instantiatedTests--;
			}
		}

		// Removes the defined random test to the suite
		void RandomTestSuite::RemoveUniversalTest(void) {

			if (this->suite[Universal] != NULL) {
				if (this->selfCreatedTest[Universal]) {
					delete this->suite[Universal];
				}
				this->suite[Universal] = NULL;
			    this->selfCreatedTest[Universal] = false;
				this->instantiatedTests--;
			}
		}

		// Removes the defined random test to the suite
		void RandomTestSuite::RemoveApproximateEntropyTest(void) {

			if (this->suite[ApproximateEntropy] != NULL) {
				if (this->selfCreatedTest[ApproximateEntropy]) {
					delete this->suite[ApproximateEntropy];
				}
				this->suite[ApproximateEntropy] = NULL;
			    this->selfCreatedTest[ApproximateEntropy] = false;
				this->instantiatedTests--;
			}
		}

		// Removes the defined random test to the suite
		void RandomTestSuite::RemoveSerialTest(void) {

			if (this->suite[Serial] != NULL) {
				if (this->selfCreatedTest[Serial]) {
					delete this->suite[Serial];
				}
				this->suite[Serial] = NULL;
			    this->selfCreatedTest[Serial] = false;
				this->instantiatedTests--;
			}
		}

		// Removes the defined random test to the suite
		void RandomTestSuite::RemoveDiscreteFourierTransformTest(void) {

			if (this->suite[DiscreteFourierTransform] != NULL) {
				if (this->selfCreatedTest[DiscreteFourierTransform]) {
					delete this->suite[DiscreteFourierTransform];
				}
				this->suite[DiscreteFourierTransform] = NULL;
			    this->selfCreatedTest[DiscreteFourierTransform] = false;
				this->instantiatedTests--;
			}
		}

		// CHECKING RANDOMNESS

		// Tests the BaseCryptoRandomStream untill an error is found with all instantiated random tests and returns the random value
		bool RandomTestSuite::IsRandom(BaseCryptoRandomStream* stream) {
			int i;
			
			this->random = true;
			i = this->GetFirstTest();
			while ((i < this->GetMaximumNumberOfTests()) && (this->random)) {
				if (this->suite[i] != NULL) {
					this->random &= this->suite[i]->IsRandom(stream);
					nonRandomTest = this->suite[i]->GetType();
					if (this->suite[i]->GetError() != NoError) {
						errorTest = this->suite[i]->GetType();
						this->numberOfErrors = 1;
					}
				}
				i++;
			}
			return this->random;
		}

		// Tests the BaseCryptoRandomStream with all instantiated random tests and returns the random value
		bool RandomTestSuite::TestRandom(BaseCryptoRandomStream* stream) {
			int i;
			
			this->random = true;
			for ( i = this->GetFirstTest(); i < this->GetMaximumNumberOfTests(); i++ ) {
				if (this->suite[i] != NULL) {
					this->random &= this->suite[i]->IsRandom(stream);
					if (!(this->suite[i]->IsRandom())) {
						if (this->suite[i]->GetError() != NoError) {
							if (this->error == NoError)
								this->error = this->suite[i]->GetError();
							else 
								if (this->error != this->suite[i]->GetError())
									this->error = MultipleErrors;
							numberOfErrors++;
						}
					}
				}
			}
			return this->random;
		}

		// INITIALIZE SUITE
			
		// Initializes all random tests in the suite
		void RandomTestSuite::Initialize(void) {
			int i;
			
			for ( i = this->GetFirstTest(); i < this->GetMaximumNumberOfTests(); i++ ) {
				if (this->suite[i] != NULL) {
					this->suite[i]->Initialize();
				}
			}
			this->random = false;
			this->error = NoError;
			this->numberOfErrors = 0;
			this->errorTest = NotDefined;
		}

		// Sets Alpha all random tests in the suite
		void RandomTestSuite::SetAlpha(double alpha) {
			int i;

			for (i=0; i<NumberOfTests; i++)
				if (this->suite[i] != NULL)
					this->suite[i]->SetAlpha(alpha);
		}

		// GETTING SUITE RESULTS

		// Gets the RandomTestSuite random state of the last executed BaseCryptoRandomStream
		bool RandomTestSuite::IsRandom(void) {

			return this->random;
		}

		// Gets the number of Random Tests that contains the suite
		int RandomTestSuite::GetInstantiatedTests(void) {

			return this->instantiatedTests;
		}

		// Gets the minimum random stream length in bits corresponding
		// to random number test with higher random stream length
		unsigned int RandomTestSuite::GetMinimumLength(void) {
			unsigned int minimumMax;
			int i;

			minimumMax = 0;
			for ( i = this->GetFirstTest(); i < this->GetMaximumNumberOfTests(); i++ ) {
				if ( this->Exist((RandomTests)i) ) {
					if ( this->GetRandomTest((RandomTests)i)->GetMinimumLength() > minimumMax ) {
						minimumMax = this->GetRandomTest((RandomTests)i)->GetMinimumLength();
					}
				}
			}
			return minimumMax;
		}

		// Gets the corresponding random number test 
		// with higher minimum random stream length in bits 
		RandomTests RandomTestSuite::GetMinimumLengthRandomTest(void) {
			unsigned int minimumMax;
			int i;
			RandomTests randomTest;

			minimumMax = 0;
			randomTest = NotDefined;
			for ( i = this->GetFirstTest(); i < this->GetMaximumNumberOfTests(); i++ ) {
				if ( this->Exist((RandomTests)i) ) {
					if ( this->GetRandomTest((RandomTests)i)->GetMinimumLength() > minimumMax ) {
						minimumMax = this->GetRandomTest((RandomTests)i)->GetMinimumLength();
						randomTest = (RandomTests)i;
					}
				}
			}
			return randomTest;
		}

		// Gets the failed random test in the RandomTestSuite
		RandomTests RandomTestSuite::GetNonRandomTest(void) {

			return this->nonRandomTest;
		}

		// Gets the RandomTestError error of the last executed BaseCryptoRandomStream
		RandomTestErrors RandomTestSuite::GetError(void) {

			return this->error;
		}

		// Gets the RandomTest that produced the error of the last executed BaseCryptoRandomStream
		RandomTests RandomTestSuite::GetErrorTest(void) {

			return this->errorTest;
		}

		// Indicates if a random test object exists in the suite
		bool RandomTestSuite::Exist(RandomTests test) {

			return (this->suite[test] != NULL);
		}

		// Gets the first random test in the RandomTestSuite
		RandomTests RandomTestSuite::GetFirstTest(void) {

			return this->firstTest;
		}

		// Gets the number of random tests that can be used in the RandomTestSuite
		RandomTests RandomTestSuite::GetMaximumNumberOfTests(void) {

			return NumberOfTests;
		}
	}
}
