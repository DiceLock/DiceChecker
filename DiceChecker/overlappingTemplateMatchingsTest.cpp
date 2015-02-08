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

#include <stdexcept>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "overlappingTemplateMatchingsTest.h"


using namespace std;


namespace DiceLockSecurity {
	
  namespace RandomTest {

	// Random Test Class enumerator name
	const RandomTests OverlappingTemplateMatchingsTest::test = OverlappingTemplateMatchings;
	// Random Test Class minimum stream length
	const unsigned int	OverlappingTemplateMatchingsTest::minimumLength = 1000000;

	// Random Test Class block sizes
	const short	OverlappingTemplateMatchingsTest::numberWindowLengths = 2;
	const short	OverlappingTemplateMatchingsTest::windowLengths[2] = {9, 10};

	const int OverlappingTemplateMatchingsTest::NumAssignments = 6;	
	const int OverlappingTemplateMatchingsTest::OverlappingStringTested = 1032;

	// Constructor, default 
	OverlappingTemplateMatchingsTest::OverlappingTemplateMatchingsTest() {
		int i;

		windowLength = 0; 
		substringLength = 0;
		substringNumber = 0;
		chiSquared = 0.0;
		eta = 0.0;
		lambda = 0.0;
		for (i=0; i<NumAssignments; i++)
			assignment[i] = 0;
	}

	// Constructor with a MathematicalFunctions object instantiated 
	OverlappingTemplateMatchingsTest::OverlappingTemplateMatchingsTest(MathematicalFunctions* mathFuncObj) {
		int i;

		windowLength = 0; 
		substringLength = 0;
		substringNumber = 0;
		chiSquared = 0.0;
		eta = 0.0;
		lambda = 0.0;
		for (i=0; i<NumAssignments; i++)
			assignment[i] = 0;
	}

	// Destructor
	OverlappingTemplateMatchingsTest::~OverlappingTemplateMatchingsTest() {
		int i;

		windowLength = 0; 
		substringLength = 0;
		substringNumber = 0;
		chiSquared = 0.0;
		eta = 0.0;
		lambda = 0.0;
		for (i=0; i<NumAssignments; i++)
			assignment[i] = 0;
	}
	
	// Tests the BaseCryptoRandomStream executed and returns the random value
	bool OverlappingTemplateMatchingsTest::IsRandom(BaseCryptoRandomStream* bitStream) {
		int    i, k, match;
		double W_obs, sum;
		int    j, K = 5;
		unsigned int nu[6] = {0,0,0,0,0,0};
		double pi[6] = {0.143783,0.139430,0.137319,0.124314,0.106209,0.348945};
		bitItem*   patern;			

		if ((bitStream->GetBitLength() < this->GetMinimumLength())) {
			this->error = InsufficientNumberOfBits;
			this->random = false;
			return this->random; 
		}
		this->error = NoError;
		this->substringLength = OverlappingStringTested;
		this->substringNumber = (int)floor((long double)(bitStream->GetBitLength()/this->substringLength));
		if ((patern = (bitItem*) calloc(this->windowLength,sizeof(bitItem))) == NULL) {
			this->error = InsufficientMemory;
			this->random = false;
			return this->random; 
		}
		else
			for(i = 0; i < this->windowLength; i++)
				patern[i].bit = 1;
		this->lambda = (double)(this->substringLength-this->windowLength+1)/pow((double)2,this->windowLength);
		this->eta = this->lambda/2.0;
		sum = 0.0;
		for(i = 0; i < K; i++) {			
			pi[i] = Probability(i,this->eta);
			sum += pi[i];
		}
		pi[K] = 1 - sum;
		for(i = 0; i < this->substringNumber; i++) {
			W_obs = 0;
			for(j = 0; j < this->substringLength-this->windowLength+1; j++) {
				match = 1;
				for(k = 0; k < this->windowLength; k++) {
					if ((int)patern[k] != (int)bitStream->GetBitPosition(i*this->substringLength+j+k))
						match = 0;
				}
				if (match == 1)
					W_obs++;
			}
			if (W_obs <= 4)
				nu[(int)W_obs]++;
			else
				nu[K]++;
		}	
		sum = 0;
		this->chiSquared = 0.0;                              
		for(i = 0; i < K+1; i++) {
			this->chiSquared += pow((double)nu[i]-(double)this->substringNumber*pi[i],2)/((double)this->substringNumber*pi[i]);
		    sum += nu[i];
		}
		this->pValue = this->mathFuncs->IGammaC(K/2.,this->chiSquared/2.);
		for (i = 0; i < 6; i++)
			this->assignment[i] = nu[i];
		if (_isnan(this->pValue)) {
			this->pValue = 0;
			this->error = MathematicianNAN;
			this->random = false;
		}
		else {
			if (isNegative(this->pValue) || isGreaterThanOne(this->pValue)) {
   				this->error = PValueOutOfRange;
				this->random = false;
			}
			else {
				if (this->pValue < this->alpha) {     
					this->error = NoError;
					this->random = false;
				}
				else {
					this->error = NoError;
					this->random = true;
				}
			}
		}
		free(patern);
		return this->random;
	}

	// Initializes the object
	void OverlappingTemplateMatchingsTest::Initialize(void) {
		int i;

		BaseRandomTest::Initialize();
		windowLength = 0; 
		substringLength = 0;
		substringNumber = 0;
		chiSquared = 0.0;
		eta = 0.0;
		lambda = 0.0;
		for (i=0; i<NumAssignments; i++)
			assignment[i] = 0;
	}

	// Gets the type of the object
	RandomTests OverlappingTemplateMatchingsTest::GetType(void) {

		return this->test;
	}

	// Gets the minimum random stream length
	unsigned int OverlappingTemplateMatchingsTest::GetMinimumLength(void) {

		return this->minimumLength;
	}

	// Gets an array of block sizes
	int OverlappingTemplateMatchingsTest::GetWindowLengths(void) {

		return this->numberWindowLengths;
	}

	// Gets the window length based on the index
	int OverlappingTemplateMatchingsTest::GetWindowLengthOfIndex(int index) {

		return this->windowLengths[index];
	}

	// Sets the "WindowLength" parameter
	void OverlappingTemplateMatchingsTest::SetWindowLength(int window) {

		this->windowLength = window;
	}

	// Gets the "WindowLength" parameter
	int OverlappingTemplateMatchingsTest::GetWindowLength(void) {

		return this->windowLength;
	}

	// Gets the "substringLength" result
	int OverlappingTemplateMatchingsTest::GetSubstringLength(void) {

		return this->substringLength;
	}

	// Gets the "substringNumber" result
	int OverlappingTemplateMatchingsTest::GetSubstringNumber(void) {

		return this->substringNumber;
	}

	// Gets the "chiSquared" result
	double OverlappingTemplateMatchingsTest::GetChiSquared(void) {

		return this->chiSquared;
	}

	// Gets the "eta" result
	double OverlappingTemplateMatchingsTest::GetEta(void) {

		return this->eta;
	}

	// Gets the "lambda" result
	double OverlappingTemplateMatchingsTest::GetLambda(void) {

		return this->lambda;
	}

	// Gets the Assignment result
	void OverlappingTemplateMatchingsTest::GetAssignment(unsigned int *assign) {

		memcpy (assign, assignment, sizeof(unsigned int)*NumAssignments);
	}

	// Gets the Assignment result based on the index
	unsigned int OverlappingTemplateMatchingsTest::GetAssignmentOfIndex(int index) {

		return this->assignment[index];
	}

	// Computes probability
	double OverlappingTemplateMatchingsTest::Probability(int u, double eta) {
		int    l;
		double sum, p;

		if (u == 0)
			p = exp(-eta);
		else {
			sum = 0.0;
			for(l = 1; l <= u; l++)
				sum += exp(-eta-u*log((double)2)+l*log((long double)eta)-this->mathFuncs->LGamma(l+1) 
					   + this->mathFuncs->LGamma(u) - this->mathFuncs->LGamma(l)- this->mathFuncs->LGamma(u-l+1));
			p = sum;
		}
		return p;
	}
  }
}

