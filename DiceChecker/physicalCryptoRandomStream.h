//
// Creator:    http://www.dicelocksecurity.com
// Version:    vers.6.0.0.1
//
// Copyright © 2008-2012 DiceLock Security, LLC. All rigths reserved.
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

#ifndef PHYSICALCRYPTORANDOMSTREAM_HPP

#define PHYSICALCRYPTORANDOMSTREAM_HPP

#ifdef DICELOCKCIPHER_EXPORTS
   #define CLASS_DECLSPEC    __declspec(dllexport)
#else
   #define CLASS_DECLSPEC    __declspec(dllimport)
#endif

#include <windows.h>
#include "baseCryptoRandomStream.h"


namespace DiceLockSecurity {

  namespace CryptoRandomStream {

	class PhysicalCryptoRandomStream : public BaseCryptoRandomStream  {

		private:

			// CryptoRandomStream type enumerator name
			static const CryptoRandomStreams	cryptoRandomStreamType;

			bool	autoMemory;

			BOOL bResult;                   // generic Boolean value
			ULONG_PTR NumberOfPages;        // number of pages to request
			ULONG_PTR NumberOfPagesInitial; // initial number of pages requested
			ULONG_PTR *aPFNs;               // page info; holds opaque data
			SYSTEM_INFO sSysInfo;           // useful system information
			signed long int PFNArraySize;   // memory to request for PFN array

			CLASS_DECLSPEC void AllocatePhysical(unsigned long int);

			CLASS_DECLSPEC void FreePhysical();

		public:

			// Constructor, default 
			CLASS_DECLSPEC PhysicalCryptoRandomStream(void);

			// Constructor, creates an empty stream with the indicated length 
			CLASS_DECLSPEC PhysicalCryptoRandomStream(unsigned long int);

			// Constructor, sets the pointed stream of the indicated length 
			CLASS_DECLSPEC PhysicalCryptoRandomStream(void *, unsigned long int);

			// Destructor
			CLASS_DECLSPEC ~PhysicalCryptoRandomStream();

			// Verifies if the user has privileges to block pages in RAM memory
			CLASS_DECLSPEC static BOOL LoggedSetLockPagesPrivilege ();

			// Sets an empty stream with the indicated length in bits
			CLASS_DECLSPEC void SetCryptoRandomStreamBit(unsigned long int);

			// Sets the pointed stream of indicated length in bits
			CLASS_DECLSPEC void SetCryptoRandomStreamBit(void *, unsigned long int);

			// Sets an empty stream with the indicated length in unsigned chars
			CLASS_DECLSPEC void SetCryptoRandomStreamUC(unsigned long int);

			// Sets the pointed stream of indicated length in unsigned chars
			CLASS_DECLSPEC void SetCryptoRandomStreamUC(void *, unsigned long int);

			// Sets an empty stream with the indicated length in unsigned shorts
			CLASS_DECLSPEC void SetCryptoRandomStreamUS(unsigned long int);

			// Sets the pointed stream of indicated length in unsigned shorts
			CLASS_DECLSPEC void SetCryptoRandomStreamUS(void *, unsigned long int);

			// Sets an empty stream with the indicated length in unsigned longs
			CLASS_DECLSPEC void SetCryptoRandomStreamUL(unsigned long int);

			// Sets the pointed stream of indicated length in unsigned longs
			CLASS_DECLSPEC void SetCryptoRandomStreamUL(void *, unsigned long int);

			// Set the pointed stream as hexadecimal string
			CLASS_DECLSPEC void SetCryptoRandomStreamHexString(const char*);

			// Gets the CryptoRandomStream type of the object
			CLASS_DECLSPEC CryptoRandomStreams GetCryptoRandomStreamType(void);

	};
  }
}

#endif
