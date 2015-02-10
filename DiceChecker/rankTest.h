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

#ifndef RANKTEST_HPP

#define RANKTEST_HPP

#ifdef DICELOCKCIPHER_EXPORTS
   #define CLASS_DECLSPEC    __declspec(dllexport)
#else
   #define CLASS_DECLSPEC    __declspec(dllimport)
#endif

#include "baseRandomTest.h"
#include "mathematicalFunctions.h"


namespace DiceLockSecurity {

  namespace RandomTest {

	  class RankTest : public BaseRandomTest {

		protected:

			/// Random Test Class enumerator name
			static const RandomTests	test;
			/// Random Test Class minimum stream length
			static const unsigned long int minimumLength;

			double  chiSquared;
			unsigned long int matrixNumber;
			unsigned long int bitsDiscarded;
			double  p30, p31, p32;		 	/// Probabilities 
			double	f30, f31, f32;			/// Frequencies

			/// Create Matrix 
			unsigned char**	CreateMatrix(unsigned long int, unsigned long int);

			/// Define Matrix 
			void DefineMatrix(BaseCryptoRandomStream*, signed long int, signed long int, unsigned char**, signed long int);

			/// Deletes matrix 
			void DeleteMatrix(signed long int, unsigned char**);

			/// Computes rank 
			signed long int ComputeRank(signed long int, signed long int, unsigned char**);

			/// Perform Elementary Row Operations
			void PerformElementaryRowOperations(signed long int, signed long int, signed long int, signed long int, unsigned char**);

			/// Find Unit Element And Swap
			signed long int FindUnitElementAndSwap(signed long int, signed long int, signed long int, signed long int, unsigned char**);

			/// Swap Rows 
			signed long int SwapRows(signed long int, signed long int, signed long int, unsigned char**);

			/// Determine Rank 
			signed long int DetermineRank(signed long int, signed long int, signed long int, unsigned char**);

		public:

			/// Constructor, default 
			CLASS_DECLSPEC RankTest();

			/// Constructor with a MathematicalFunctions object instantiated 
			CLASS_DECLSPEC RankTest(MathematicalFunctions*);

			/// Destructor
			CLASS_DECLSPEC ~RankTest();

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

			/// Gets the "chiSquared" result
			CLASS_DECLSPEC double GetChiSquared(void);

			/// Gets the "matrixNumber" result
			CLASS_DECLSPEC unsigned long int GetMatrixNumber(void);

			/// Gets the "bitsDiscarded" result
			CLASS_DECLSPEC unsigned long int GetBitsDiscarded(void);

			/// Gets the "p30" result
			CLASS_DECLSPEC double GetP30(void);

			/// Gets the "p31" result
			CLASS_DECLSPEC double GetP31(void);

			/// Gets the "p32" result
			CLASS_DECLSPEC double GetP32(void);

			/// Gets the "f30" result
			CLASS_DECLSPEC double GetF30(void);

			/// Gets the "f31" result
			CLASS_DECLSPEC double GetF31(void);

			/// Gets the "f32" result
			CLASS_DECLSPEC double GetF32(void);

	};
  }
}

#endif
