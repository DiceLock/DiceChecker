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
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// DICELOCK IS A REGISTERED TRADEMARK OR TRADEMARK OF THE OWNERS.
// 

#ifndef BASECRYPTORANDOMSTREAM_HPP

#define BASECRYPTORANDOMSTREAM_HPP

#ifdef DICELOCKCIPHER_EXPORTS
   #define CLASS_DECLSPEC    __declspec(dllexport)
#else
   #define CLASS_DECLSPEC    __declspec(dllimport)
#endif


#define BYTEBITS		 8 
#define SHORTBITS		16 
#define LONGBITS		32 
#define LONG64BITS		64 

#define LONGBYTES		 4 


namespace DiceLockSecurity {

  namespace CryptoRandomStream {

	enum CryptoRandomStreams {
		DefaultStream,
		PhysicalStream,
		NumberOfStreams,		// Indication of the number of CryptoRandomStream types, any added CryptoRandomStream type must be inserted before
		NotDefined,
	};

	struct byteBits {
		unsigned char bit0:1;
		unsigned char bit1:1;
		unsigned char bit2:1;
		unsigned char bit3:1;
		unsigned char bit4:1;
		unsigned char bit5:1;
		unsigned char bit6:1;
		unsigned char bit7:1;
	};

	class BaseCryptoRandomStream abstract {

		protected:

			unsigned long int	bitLength;
			unsigned long int	reducedBitLength;
			unsigned long int	position;
			unsigned char * 	cryptoStream;

		public:

			/// Constructor, deafult 
			CLASS_DECLSPEC BaseCryptoRandomStream();

			/// Constructor, sets an empty stream with the indicated length in unsigned long ints
			CLASS_DECLSPEC BaseCryptoRandomStream(unsigned long int) {};

			/// Constructor, sets the pointed stream of the indicated length 
			CLASS_DECLSPEC BaseCryptoRandomStream(void*, unsigned long int) {};

			/// Destructor
			CLASS_DECLSPEC virtual ~BaseCryptoRandomStream();

			/// Sets the BaseCryptoRandomStream position, minimum value 0
			CLASS_DECLSPEC void SetBitPosition(unsigned long int);

			/// Gets the current bit position
			CLASS_DECLSPEC unsigned long int GetBitPosition(void);

			/// Gets the stream length in bits
			CLASS_DECLSPEC unsigned long int GetBitLength(void);

			/// Gets the stream length in unsigned char type
			CLASS_DECLSPEC unsigned long int GetUCLength(void);

			/// Gets the stream length in unsigned short type
			CLASS_DECLSPEC unsigned long int GetUSLength(void);

			/// Gets the stream length in unsigned long type
			CLASS_DECLSPEC unsigned long int GetULLength(void);

			/// Gets the stream length in unsigned 64 bits
			CLASS_DECLSPEC unsigned __int64 Get64Length(void);

			/// Sets an empty stream with the indicated length in bits
			CLASS_DECLSPEC virtual void SetCryptoRandomStreamBit(unsigned long int) {};

			/// Set the pointed stream of indicated length in bits
			CLASS_DECLSPEC virtual void SetCryptoRandomStreamBit(void*, unsigned long int) {};

			/// Sets an empty stream with the indicated length in unsigned chars
			CLASS_DECLSPEC virtual void SetCryptoRandomStreamUC(unsigned long int) {};

			/// Set the pointed stream of indicated length in unsigned chars
			CLASS_DECLSPEC virtual void SetCryptoRandomStreamUC(void*, unsigned long int) {};

			/// Sets an empty stream with the indicated length in unsigned shorts
			CLASS_DECLSPEC virtual void SetCryptoRandomStreamUS(unsigned long int) {};

			/// Set the pointed stream of indicated length in unsigned shorts
			CLASS_DECLSPEC virtual void SetCryptoRandomStreamUS(void*, unsigned long int) {};

			/// Sets an empty stream with the indicated length in unsigned long int
			CLASS_DECLSPEC virtual void SetCryptoRandomStreamUL(unsigned long int) {};

			/// Set the pointed stream of indicated length in unsigned long int
			CLASS_DECLSPEC virtual void SetCryptoRandomStreamUL(void*, unsigned long int) {};

			/// Set the pointed stream as hexadecimal string
			CLASS_DECLSPEC virtual void SetCryptoRandomStreamHexString(const char*) {};

			/// Gets the pointer to the memory stream 
			CLASS_DECLSPEC void* GetCryptoRandomStreamMemory(void);

			/// Sets the BaseCryptoRandomStream bit at current position and moves pointer to the following bit
			CLASS_DECLSPEC void SetBitForward(unsigned char);

			/// Sets the BaseCryptoRandomStream bit at current position and moves pointer to the previous bit
			CLASS_DECLSPEC void SetBitReverse(unsigned char);

			/// Gets the BaseCryptoRandomStream bit at current position and moves pointer to the following bit
			CLASS_DECLSPEC unsigned char GetBitForward(void);

			/// Gets the BaseCryptoRandomStream bit at current position and moves pointer to the previous bit
			CLASS_DECLSPEC unsigned char GetBitReverse(void);

			/// Sets the stream to an specified bit value (0 or 1)
			CLASS_DECLSPEC void FillBit(unsigned char);
			
			/// Sets the stream to an specified bit unsigned char value
			CLASS_DECLSPEC void FillUC(unsigned char);
			
			/// Sets the stream to an specified bit unsigned short value
			CLASS_DECLSPEC void FillUS(unsigned short int);
			
			/// Sets the stream to an specified bit unsigned long int value
			CLASS_DECLSPEC void FillUL(unsigned long int);

			/// Sets the bit unsigned char (value 0 or 1) at specified position, position based in array of bits
			CLASS_DECLSPEC void SetBitPosition(unsigned long int, unsigned char);

			/// Sets the unsigned char at specified position, position based in array of unsigned char
			CLASS_DECLSPEC void SetUCPosition(unsigned long int, unsigned char);

			/// Sets the unsigned short at specified position, position based in array of unsigned short
			CLASS_DECLSPEC void SetUSPosition(unsigned long int, unsigned short int);
			
			/// Sets the unsigned long at specified position, position based in array of unsigned long
			CLASS_DECLSPEC void SetULPosition(unsigned long int, unsigned long int);
			
			/// Sets the unsigned 64 bit at specified position, position based in array of unsigned __int64
			CLASS_DECLSPEC void Set64Position(unsigned __int64, unsigned __int64);
			
			/// Gets the bit unsigned char (vakue  0 or 1) at specified position, position based in array of bits
			CLASS_DECLSPEC unsigned char GetBitPosition(unsigned long int);

			/// Gets the unsigned char at specified position, position based in array of unsigned char
			CLASS_DECLSPEC unsigned char GetUCPosition(unsigned long int);

			/// Gets the unsigned short at specified position, position based in array of unsigned short
			CLASS_DECLSPEC unsigned short int GetUSPosition(unsigned long int);
			
			/// Gets the unsigned long at specified position, position based in array of unsigned long
			CLASS_DECLSPEC unsigned long int GetULPosition(unsigned long int);
			
			/// Gets the unsigned 64 bit at specified position, position based in array of unsigned 64 bit
			CLASS_DECLSPEC unsigned __int64 Get64Position(unsigned __int64);
			
			/// Gets the unsigned char address at specified position, position based in array of unsigned char
			CLASS_DECLSPEC unsigned char* GetUCAddressPosition(unsigned long int);

			/// Gets the unsigned short int address at specified position, position based in array of unsigned short
			CLASS_DECLSPEC unsigned short int* GetUSAddressPosition(unsigned long int);

			/// Gets the unsigned long int address at specified position, position based in array of unsigned long
			CLASS_DECLSPEC unsigned long int* GetULAddressPosition(unsigned long int);

			/// Gets the unsigned __int64 address at specified position, position based in array of unsigned 64 bit
			CLASS_DECLSPEC unsigned __int64* Get64AddressPosition(unsigned __int64);

			/// Gets the baseCryptoRandomStream portion at specified position with 
			/// from baseCryptoRandomStream object, position and length based in array of unsigned char
			CLASS_DECLSPEC void GetUCSubRandomStream(BaseCryptoRandomStream*, unsigned long int);

			/// Gets the baseCryptoRandomStream portion at specified position
			/// from baseCryptoRandomStream object, position and length based in array of unsigned short int
			CLASS_DECLSPEC void GetUSSubRandomStream(BaseCryptoRandomStream*, unsigned long int);

			/// Gets the baseCryptoRandomStream portion at specified position
			/// from baseCryptoRandomStream object, position and length based in array of unsigned long int
			CLASS_DECLSPEC void GetULSubRandomStream(BaseCryptoRandomStream*, unsigned long int);

			/// Gets the baseCryptoRandomStream portion at specified position with a specified length 
			/// from baseCryptoRandomStream object, position and length based in array of unsigned char
			CLASS_DECLSPEC void GetUCSubRandomStream(BaseCryptoRandomStream*, unsigned long int, unsigned long int);

			/// Gets the baseCryptoRandomStream portion at specified position with a specified length 
			/// from baseCryptoRandomStream object, position and length based in array of unsigned short int
			CLASS_DECLSPEC void GetUSSubRandomStream(BaseCryptoRandomStream*, unsigned long int, unsigned long int);

			/// Gets the baseCryptoRandomStream portion at specified position with a specified length 
			/// from baseCryptoRandomStream object, position and length based in array of unsigned long int
			CLASS_DECLSPEC void GetULSubRandomStream(BaseCryptoRandomStream*, unsigned long int, unsigned long int);

			/// Reduces considered length of BaseCryptoRandomStream, real length is mantained, 
			/// but any access to BaseCryptoRandomStream through the interface will be limited to 
			/// the new considered length. BaseCryptoRandomStream will remain with its original 
			/// length and using the specified memory.
			/// Reduces length in bits.
			CLASS_DECLSPEC void ReduceBitLength(unsigned long int);

			/// Reduces considered length of BaseCryptoRandomStream, real length is mantained, 
			/// but any access to BaseCryptoRandomStream through the interface will be limited to 
			/// the new considered length. BaseCryptoRandomStream will remain with its original 
			/// length and using the specified memory.
			/// Reduces length in unsigned chars.
			CLASS_DECLSPEC void ReduceUCLength(unsigned long int);

			/// Reduces considered length of BaseCryptoRandomStream, real length is mantained, 
			/// but any access to BaseCryptoRandomStream through the interface will be limited to 
			/// the new considered length. BaseCryptoRandomStream will remain with its original 
			/// length and using the specified memory.
			/// Reduces length in unsigned short ints.
			CLASS_DECLSPEC void ReduceUSLength(unsigned long int);

			/// Reduces considered length of BaseCryptoRandomStream, real length is mantained, 
			/// but any access to BaseCryptoRandomStream through the interface will be limited to 
			/// the new considered length. BaseCryptoRandomStream will remain with its original 
			/// length and using the specified memory.
			/// Reduces length in unsigned long ints.
			CLASS_DECLSPEC void ReduceULLength(unsigned long int);

			/// Indicates if BaseCryptoRandomStream's length has been reduced in a 
			/// fictitious way
			CLASS_DECLSPEC bool ReducedLength(void);

			/// Restores original length of BaseCryptoRandomStream and removes any 
			/// fictitious reduced length 
			CLASS_DECLSPEC void RestoreLength(void);

			/// Operator equal, compares the BaseCryptoRandomStream object with the 
			/// BaseCryptoRandomStream parameter
			CLASS_DECLSPEC bool Equals(BaseCryptoRandomStream*);

			/// Operator copy, copies the content of BaseCryptoRandomStream object
			/// to the BaseCryptoRandomStream object passed as parameter
			CLASS_DECLSPEC void Copy(BaseCryptoRandomStream*);

			/// Gets the CryptoRandomStream type of the object
			CLASS_DECLSPEC virtual CryptoRandomStreams GetCryptoRandomStreamType(void) {return NotDefined;};

	};

  }
}

#endif
