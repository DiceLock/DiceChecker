//
// Creator:    http://www.dicelocksecurity.com
// Version:    vers.4.0.0.1
//
// Copyright © 2008-2010 DiceLock Security, LLC. All rigths reserved.
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

#include <stdexcept>
#include <stdlib.h>
#include "baseCryptoRandomStream.h"


using namespace std;


namespace DiceLockSecurity {

  namespace CryptoRandomStream {

	// Constructor
	BaseCryptoRandomStream::BaseCryptoRandomStream() {

		this->cryptoStream = NULL;
		this->bitLength = 0;
		this->reducedBitLength = 0;
		this->position = 0;
	}

	// Destructor
	BaseCryptoRandomStream::~BaseCryptoRandomStream() {

		this->cryptoStream = NULL;
		this->bitLength = 0;
		this->reducedBitLength = 0;
		this->position = 0;
	}

	// Sets the BaseCryptoRandomStream position, minimum value 0
	void BaseCryptoRandomStream::SetBitPosition(unsigned long int newPosition) {

		this->position = newPosition;
	}

	// Gets the current bit position
	unsigned long int BaseCryptoRandomStream::GetBitPosition(void) {

		return this->position; 
	}

	// Gets the stream length in bits
	unsigned long int BaseCryptoRandomStream::GetBitLength(void) {

		if ( this->reducedBitLength ) {
			return this->reducedBitLength; 
		}
		else {
			return this->bitLength; 
		}
	}

	// Gets the stream length in unsigned char type
	unsigned long int BaseCryptoRandomStream::GetUCLength(void) {

		if ( this->reducedBitLength ) {
			return (this->reducedBitLength / (BYTEBITS * sizeof(unsigned char))); 
		}
		else {
			return (this->bitLength / (BYTEBITS * sizeof(unsigned char)));  
		}
	} 

	// Gets the stream length in unsigned short type
	unsigned long int BaseCryptoRandomStream::GetUSLength(void) {

		if ( this->reducedBitLength ) {
			return (this->reducedBitLength / (BYTEBITS * sizeof(unsigned short int))); 
		}
		else {
			return (this->bitLength / (BYTEBITS * sizeof(unsigned short int))); 
		}
	}

	// Gets the stream length in unsigned long type
	unsigned long int BaseCryptoRandomStream::GetULLength(void) {

		if ( this->reducedBitLength ) {
			return (this->reducedBitLength / (BYTEBITS * sizeof(unsigned long int))); 
		}
		else {
			return (this->bitLength / (BYTEBITS * sizeof(unsigned long int))); 
		}
	}

	// Gets the stream length in unsigned 64 bits
	unsigned __int64 BaseCryptoRandomStream::Get64Length(void) {

		if ( this->reducedBitLength ) {
			return (this->reducedBitLength / (BYTEBITS * sizeof(unsigned __int64))); 
		}
		else {
			return (this->bitLength / (BYTEBITS * sizeof(unsigned __int64))); 
		}
	}

	// Gets the pointer to the memory stream 
	void* BaseCryptoRandomStream::GetCryptoRandomStreamMemory(void) {

		return this->cryptoStream; 	
	}

	// Sets the BaseCryptoRandomStream bit at current position and moves pointer to the following bit
	void BaseCryptoRandomStream::SetBitForward(unsigned char newBit) {

		this->SetBitPosition(this->position++, newBit);
	}

	// Sets the BaseCryptoRandomStream bit at current position and moves pointer to the previous bit
	void BaseCryptoRandomStream::SetBitReverse(unsigned char newBit) {

		this->SetBitPosition(this->position--, newBit);
	}

	// Gets the BaseCryptoRandomStream bit at current position and moves pointer to the following bit
	unsigned char BaseCryptoRandomStream::GetBitForward(void) {
		unsigned char bit;

		bit = ((this->cryptoStream[((this->position) / BYTEBITS)] >> (this->position % BYTEBITS)) & 0x01);
		this->position++;
		return bit;
	}

	// Gets the BaseCryptoRandomStream bit at current position and moves pointer to the previous bit
	unsigned char BaseCryptoRandomStream::GetBitReverse(void) {
		unsigned char bit;

		bit = ((this->cryptoStream[((this->position) / BYTEBITS)] >> (this->position % BYTEBITS)) & 0x01);
		this->position--;
		return bit;
	}

	// Sets the stream to an specified bit value (0 or 1)
	void BaseCryptoRandomStream::FillBit(unsigned char bit) {
		unsigned long int i;

		for ( i = 0; i < this->GetBitLength(); i++ )
			this->SetBitPosition(i, bit);
	}

	// Sets the stream to an specified bit unsigned char value
	void BaseCryptoRandomStream::FillUC(unsigned char value) {

		if (this->cryptoStream != NULL)
			memset(this->cryptoStream, value, this->GetUCLength()); 
	}
			
	// Sets the stream to an specified bit unsigned short value
	void BaseCryptoRandomStream::FillUS(unsigned short int value) {

		if (this->cryptoStream != NULL)
			memset(this->cryptoStream, value, this->GetUCLength()); 
	}
			
	// Sets the stream to an specified bit unsigned long int value
	void BaseCryptoRandomStream::FillUL(unsigned long int value) {

		if (this->cryptoStream != NULL)
			memset(this->cryptoStream, value, this->GetUCLength()); 
	}

	// Sets the bit unsigned char (value 0 or 1) at specified postion, position based in array of bits
	void BaseCryptoRandomStream::SetBitPosition(unsigned long int pos, unsigned char bitData) {

		switch ( pos % 8 ) {
			case 7 : ((byteBits *)&(this->cryptoStream[pos/BYTEBITS]))->bit7 = bitData;
				break;
			case 6 : ((byteBits *)&(this->cryptoStream[pos/BYTEBITS]))->bit6 = bitData;
				break;
			case 5 : ((byteBits *)&(this->cryptoStream[pos/BYTEBITS]))->bit5 = bitData;
				break;
			case 4 : ((byteBits *)&(this->cryptoStream[pos/BYTEBITS]))->bit4 = bitData;
				break;
			case 3 : ((byteBits *)&(this->cryptoStream[pos/BYTEBITS]))->bit3 = bitData;
				break;
			case 2 : ((byteBits *)&(this->cryptoStream[pos/BYTEBITS]))->bit2 = bitData;
				break;
			case 1 : ((byteBits *)&(this->cryptoStream[pos/BYTEBITS]))->bit1 = bitData;
				break;
			case 0 : ((byteBits *)&(this->cryptoStream[pos/BYTEBITS]))->bit0 = bitData;
				break;
		}
	}

	// Sets the unsigned char at specified position, position based in array of unsigned char
	void BaseCryptoRandomStream::SetUCPosition(unsigned long int pos, unsigned char charData) {
		unsigned char* pointer;

		try {
			if ( pos >= this->GetUCLength() )
				throw "Positions exceeded stream length !";
			else {
				pointer = (unsigned char *)(this->cryptoStream + (pos * sizeof(unsigned char)));
				(*pointer) = charData;
			}
		}
		catch (char* str) {
			throw str;
		}
	}

	// Sets the unsigned short at specified position, position based in array of unsigned short
	void BaseCryptoRandomStream::SetUSPosition(unsigned long int pos, unsigned short int shortData) {
		unsigned short int* pointer;

		try {
			if ( pos >= this->GetUSLength() )
				throw "Positions exceeded stream length !";
			else {
				pointer = (unsigned short int *)(this->cryptoStream + (pos * sizeof(unsigned short int)));
				(*pointer) = shortData;
			}
		}
		catch (char* str) {
			throw str;
		}
	}
			
	// Sets the unsigned long at specified position, position based in array of unsigned long
	void BaseCryptoRandomStream::SetULPosition(unsigned long int pos, unsigned long int longData) {
		unsigned long int* pointer;

		try {
			if ( pos >= this->GetULLength() )
				throw "Positions exceeded stream length !";
			else {
				pointer = (unsigned long int *)(this->cryptoStream + (pos * sizeof(unsigned long int)));
				(*pointer) = longData;
			}
		}
		catch (char* str) {
			throw str;
		}
	}

	// Sets the unsigned 64 bit at specified postion, position based in array of unsigned __int64
	void BaseCryptoRandomStream::Set64Position(unsigned __int64 pos, unsigned __int64 longData) {
		unsigned __int64* pointer;

		try {
			if ( pos >= this->Get64Length() )
				throw "Positions exceeded stream length !";
			else {
				pointer = (unsigned __int64 *)(this->cryptoStream + (pos * sizeof(unsigned __int64)));
				(*pointer) = longData;
			}
		}
		catch (char* str) {
			throw str;
		}
	}

	// Gets the bit unsigned char (vakue  0 or 1) at specified postion, position based in array of bits
	unsigned char BaseCryptoRandomStream::GetBitPosition(unsigned long int pos) {

		try {
			if ( pos >= this->GetBitLength() )
				throw "Positions exceeded stream length !";
			else
				return ( ((this->cryptoStream[(pos / BYTEBITS)] >> (pos % BYTEBITS)) & 0x01) );
		}
		catch (char* str) {
			throw str;
		}
	}

	// Gets the unsigned char at specified postion, position based in array of unsigned char
	unsigned char BaseCryptoRandomStream::GetUCPosition(unsigned long int pos) {

		try {
			if ( pos >= this->GetUCLength() )
				throw "Positions exceeded stream length !";
			else
				return *((unsigned char *)(&(this->cryptoStream[pos * sizeof(unsigned char)])));
		}
		catch (char* str) {
			throw str;
		}
	}

	// Gets the unsigned short at specified postion, position based in array of unsigned short
	unsigned short int BaseCryptoRandomStream::GetUSPosition(unsigned long int pos) {

		try {
			if ( pos >= this->GetUSLength() )
				throw "Positions exceeded stream length !";
			else
				return *((unsigned short int *)(&(this->cryptoStream[pos * sizeof(unsigned short int)])));
		}
		catch (char* str) {
			throw str;
		}
	}
			
	// Gets the unsigned long at specified position, position based in array of unsigned long
	unsigned long int BaseCryptoRandomStream::GetULPosition(unsigned long int pos) {

		try {
			if ( pos >= this->GetULLength() )
				throw "Positions exceeded stream length !";
			else 
				return *((unsigned long int *)(&(this->cryptoStream[pos * sizeof(unsigned long int)])));
		}
		catch (char* str) {
			throw str;
		}
	}
			
	// Gets the unsigned 64 bit at specified position, position based in array of unsigned 64 bit
	unsigned __int64 BaseCryptoRandomStream::Get64Position(unsigned __int64 pos) {

		try {
			if ( pos >= this->Get64Length() )
				throw "Positions exceeded stream length !";
			else 
				return *((unsigned __int64 *)(&(this->cryptoStream[pos * sizeof(unsigned __int64)])));
		}
		catch (char* str) {
			throw str;
		}
	}
			
	// Gets the unsigned char at specified postion, position based in array of unsigned char
	unsigned char* BaseCryptoRandomStream::GetUCAddressPosition(unsigned long int pos) {

		if ( pos >= this->GetUCLength() )
			return NULL;
		else
			return (unsigned char *)(&(this->cryptoStream[pos * sizeof(unsigned char)]));
	}

	// Gets the unsigned short at specified postion, position based in array of unsigned short
	unsigned short int* BaseCryptoRandomStream::GetUSAddressPosition(unsigned long int pos) {

		if ( pos >= this->GetUSLength() )
			return NULL;
		else
			return (unsigned short int *)(&(this->cryptoStream[pos * sizeof(unsigned short int)]));
	}
			
	// Gets the unsigned long at specified postion, position based in array of unsigned long
	unsigned long int* BaseCryptoRandomStream::GetULAddressPosition(unsigned long int pos) {

		if ( pos >= this->GetULLength() )
			return NULL;
		else
			return (unsigned long int *)(&(this->cryptoStream[pos * sizeof(unsigned long int)]));
	}
			
	// Gets the unsigned 64 bit at specified postion, position based in array of unsigned 64 bit
	unsigned __int64* BaseCryptoRandomStream::Get64AddressPosition(unsigned __int64 pos) {

		if ( pos >= this->Get64Length() )
			return NULL;
		else
			return (unsigned __int64 *)(&(this->cryptoStream[pos * sizeof(unsigned __int64)]));
	}

	// Gets the baseCryptoRandomStream portion at specified postion with 
	// from baseCryptoRandomStream object, position and length based in array of unsigned char
	void BaseCryptoRandomStream::GetUCSubRandomStream(BaseCryptoRandomStream* subStream, unsigned long int pos) {

		try {
			if ( pos >= this->GetUCLength() ) {
				throw "Positions exceeded stream length !";
			}
			else {
				subStream->bitLength = this->GetBitLength() - (pos * BYTEBITS);
				subStream->cryptoStream = (unsigned char *)(&(this->cryptoStream[pos * sizeof(unsigned char)]));
			}
		}
		catch (char* str) {
			throw str;
		}
	}

	// Gets the baseCryptoRandomStream portion at specified postion
	// from baseCryptoRandomStream object, position and length based in array of unsigned short int
	void BaseCryptoRandomStream::GetUSSubRandomStream(BaseCryptoRandomStream* subStream, unsigned long int pos) {

		try {
			if ( pos >= this->GetUSLength() ) {
				throw "Positions exceeded stream length !";
			}
			else {
				subStream->bitLength = this->GetBitLength() - (pos * BYTEBITS * sizeof(unsigned short int));
				subStream->cryptoStream = (unsigned char *)(&(this->cryptoStream[pos * sizeof(unsigned short int)]));
			}
		}
		catch (char* str) {
			throw str;
		}
	}

	// Gets the baseCryptoRandomStream portion at specified postion
	// from baseCryptoRandomStream object, position and length based in array of unsigned long int
	void BaseCryptoRandomStream::GetULSubRandomStream(BaseCryptoRandomStream* subStream, unsigned long int pos) {

		try {
			if ( pos >= this->GetULLength() ) {
				throw "Positions exceeded stream length !";
			}
			else {
				subStream->bitLength = this->GetBitLength() - (pos * BYTEBITS * sizeof(unsigned long int));
				subStream->cryptoStream = (unsigned char *)(&(this->cryptoStream[pos * sizeof(unsigned long int)]));
			}
		}
		catch (char* str) {
			throw str;
		}
	}


	// Gets the baseCryptoRandomStream portion at specified postion with a specified length 
	// from baseCryptoRandomStream object, position and length based in array of unsigned char
	void BaseCryptoRandomStream::GetUCSubRandomStream(BaseCryptoRandomStream* subStream, unsigned long int pos, unsigned long int length) {

		try {
			if ( pos >= this->GetUCLength() ) {
				throw "Positions exceeded stream length !";
			}
			else {
				if ( (pos + length) > (this->GetBitLength() / (BYTEBITS * sizeof(unsigned char))) ) {
					throw "Positions plus length exceeded stream length !";
				}
				else {
					subStream->bitLength = length * BYTEBITS;
					subStream->cryptoStream = (unsigned char *)(&(this->cryptoStream[pos * sizeof(unsigned char)]));
				}
			}
		}
		catch (char* str) {
			throw str;
		}
	}

	// Gets the baseCryptoRandomStream portion at specified postion with a specified length 
	// from baseCryptoRandomStream object, position and length based in array of unsigned short int
	void BaseCryptoRandomStream::GetUSSubRandomStream(BaseCryptoRandomStream* subStream, unsigned long int pos, unsigned long int length) {

		try {
			if ( pos >= this->GetUSLength() ) {
				throw "Positions exceeded stream length !";
			}
			else {
				if ( (pos + length) > (this->GetBitLength() / (BYTEBITS * sizeof(unsigned short int))) ) {
					throw "Positions plus length exceeded stream length !";
				}
				else {
					subStream->bitLength = length * BYTEBITS * sizeof(unsigned short int);
					subStream->cryptoStream = (unsigned char *)(&(this->cryptoStream[pos * sizeof(unsigned short int)]));
				}
			}
		}
		catch (char* str) {
			throw str;
		}
	}

	// Gets the baseCryptoRandomStream portion at specified postion with a specified length 
	// from baseCryptoRandomStream object, position and length based in array of unsigned long int
	void BaseCryptoRandomStream::GetULSubRandomStream(BaseCryptoRandomStream* subStream, unsigned long int pos, unsigned long int length) {

		try {
			if ( pos >= this->GetULLength() ) {
				throw "Positions exceeded stream length !";
			}
			else {
				if ( (pos + length) > (this->GetBitLength() / (BYTEBITS * sizeof(unsigned long int))) ) {
					throw "Positions plus length exceeded stream length !";
				}
				else {
					subStream->bitLength = length * BYTEBITS * sizeof(unsigned long int);
					subStream->cryptoStream = (unsigned char *)(&(this->cryptoStream[pos * sizeof(unsigned long int)]));
				}
			}
		}
		catch (char* str) {
			throw str;
		}
	}

	// Reduces considered length of BaseCryptoRandomStream, real length is mantained, 
	// but any access to BaseCryptoRandomStream through the interface will be limited to 
	// the new considered length. BaseCryptoRandomStream will remain with its original 
	// length and using the specified memory.
	// Reduces length in bits.
	void BaseCryptoRandomStream::ReduceBitLength(unsigned long int value) {

		if ( this->reducedBitLength ) {
			this->reducedBitLength -= value; 
		}
		else {
			this->reducedBitLength = this->bitLength - value;
		}
	}

	// Reduces considered length of BaseCryptoRandomStream, real length is mantained, 
	// but any access to BaseCryptoRandomStream through the interface will be limited to 
	// the new considered length. BaseCryptoRandomStream will remain with its original 
	// length and using the specified memory.
	// Reduces length in unsigned chars.
	void BaseCryptoRandomStream::ReduceUCLength(unsigned long int value) {

		if ( this->reducedBitLength ) {
			this->reducedBitLength -= (value * BYTEBITS); 
		}
		else {
			this->reducedBitLength = this->bitLength - (value * BYTEBITS);
		}
	}

	// Reduces considered length of BaseCryptoRandomStream, real length is mantained, 
	// but any access to BaseCryptoRandomStream through the interface will be limited to 
	// the new considered length. BaseCryptoRandomStream will remain with its original 
	// length and using the specified memory.
	// Reduces length in unsigned short ints.
	void BaseCryptoRandomStream::ReduceUSLength(unsigned long int value) {

		if ( this->reducedBitLength ) {
			this->reducedBitLength -= (value * BYTEBITS * sizeof(unsigned short int)); 
		}
		else {
			this->reducedBitLength = this->bitLength - (value * BYTEBITS * sizeof(unsigned short int));
		}
	}

	// Reduces considered length of BaseCryptoRandomStream, real length is mantained, 
	// but any access to BaseCryptoRandomStream through the interface will be limited to 
	// the new considered length. BaseCryptoRandomStream will remain with its original 
	// length and using the specified memory.
	// Reduces length in unsigned long ints.
	void BaseCryptoRandomStream::ReduceULLength(unsigned long int value) {

		if ( this->reducedBitLength ) {
			this->reducedBitLength -= (value * BYTEBITS * sizeof(unsigned long int)); 
		}
		else {
			this->reducedBitLength = this->bitLength - (value * BYTEBITS * sizeof(unsigned long int));
		}
	}

	// Indicates if BaseCryptoRandomStream's length has been reduced in a 
	// fictitious way
	bool BaseCryptoRandomStream::ReducedLength(void) {
		return (this->reducedBitLength != 0);
	}


	// Restores original length of BaseCryptoRandomStream and removes any 
	// fictitious reduced length 
	void BaseCryptoRandomStream::RestoreLength(void) {

		this->reducedBitLength = 0;
	}

	// Operator equal, compares the BaseCryptoRandomStream object with the 
	// BaseCryptoRandomStream parameter
	bool BaseCryptoRandomStream::Equals(BaseCryptoRandomStream* otherStream) {

		if (otherStream == NULL) {
			return false;
		}
		else {
			if (this->GetBitLength() != otherStream->GetBitLength()) {
				return false;
			}
			else {
				return (! memcmp(this->cryptoStream, otherStream->cryptoStream, this->GetUCLength()));
			}
		}
	}

	// Operator copy, copies the content of BaseCryptoRandomStream object
	// to the BaseCryptoRandomStream object passed as parameter
	void BaseCryptoRandomStream::Copy(BaseCryptoRandomStream* target) {
		try {
			if ( this->GetUCLength() != target->GetUCLength() )
				throw "Streams have different lengths !";
			else {
				memcpy(target->cryptoStream, this->cryptoStream, this->GetUCLength());
			}
		}
		catch (char* str) {
			throw str;
		}
	}
  }
}