//
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

#include "physicalCryptoRandomStream.h"


namespace DiceLockSecurity {

  namespace CryptoRandomStream {

	// Enumerator name
	const CryptoRandomStreams	PhysicalCryptoRandomStream::cryptoRandomStreamType = PhysicalStream;

	// Function to obtain the privilege of locking physical pages.
	BOOL PhysicalCryptoRandomStream::LoggedSetLockPagesPrivilege (void) {
		struct {
			DWORD Count;
			LUID_AND_ATTRIBUTES Privilege[1];
		} Info;
		HANDLE Token;
		BOOL Result;

		// Open the token.
		Result = OpenProcessToken ( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, & Token);
		if( Result != TRUE ) {
			return FALSE;
		}
		// Enable or disable?
		Info.Count = 1;
		Info.Privilege[0].Attributes = SE_PRIVILEGE_ENABLED;
		// Get the LUID.
		Result = LookupPrivilegeValue ( NULL, SE_LOCK_MEMORY_NAME, &(Info.Privilege[0].Luid));
		if( Result != TRUE ) {
			return FALSE;
		}
		// Adjust the privilege.
		Result = AdjustTokenPrivileges ( Token, FALSE, (PTOKEN_PRIVILEGES)&Info, 0, NULL, NULL);
		// Check the result.
		if( Result != TRUE ) {
			return FALSE;
		} 
		else {
			if(GetLastError() != ERROR_SUCCESS) {
				return FALSE;
			}
		}
		CloseHandle( Token );
		return TRUE;
	}

	// Allocates physical memory pages, memoryLengthRequested parameter in bytes 
	void PhysicalCryptoRandomStream::AllocatePhysical(unsigned long int memoryLengthRequested) {

		GetSystemInfo(&(this->sSysInfo));  // fill the system information structure
		// Calculate the number of pages of memory to request.
		if ( memoryLengthRequested % this->sSysInfo.dwPageSize ) {
			this->NumberOfPages = (memoryLengthRequested / this->sSysInfo.dwPageSize) + 1;
		}
		else {
			this->NumberOfPages = memoryLengthRequested / this->sSysInfo.dwPageSize;
		}
		// Calculate the size of the user PFN array.
		this->PFNArraySize = this->NumberOfPages * sizeof (ULONG_PTR);
		this->aPFNs = (ULONG_PTR *)HeapAlloc(GetProcessHeap(), 0, this->PFNArraySize);
		if ( this->aPFNs == NULL ) {
			throw("Failed to allocate on heap.\n");
			return;
		}
		// Enable the privilege.
		if( ! this->LoggedSetLockPagesPrivilege() ) {
			return;
		}
		// Allocate the physical memory.
		this->NumberOfPagesInitial = this->NumberOfPages;
		this->bResult = AllocateUserPhysicalPages(GetCurrentProcess(), &(this->NumberOfPages), this->aPFNs);
		if( this->bResult != TRUE ) {
			throw("Cannot allocate physical pages (%u)\n", GetLastError());
			return;
		}
		if ( this->NumberOfPagesInitial != this->NumberOfPages ) {
			throw("Allocated only %p pages.\n", this->NumberOfPages);
			return;
		}
		// Reserve the virtual memory.
		this->cryptoStream = (unsigned char *)VirtualAlloc(NULL, memoryLengthRequested, MEM_RESERVE | MEM_PHYSICAL, PAGE_READWRITE);
		if( this->cryptoStream == NULL ) {
			throw("Cannot reserve virtual memory.\n");
			return;
		}
		// Map the physical memory into the physical memory window.
		this->bResult = MapUserPhysicalPages(this->cryptoStream, this->NumberOfPages, this->aPFNs);
		if( this->bResult != TRUE ) {
			throw("MapUserPhysicalPages failed (%u)\n", GetLastError());
			return;
		}
		this->autoMemory = true;
	}

	void PhysicalCryptoRandomStream::FreePhysical() {

		// Unmap the physical memory from the physical memory window.
		this->bResult = MapUserPhysicalPages(this->cryptoStream, this->NumberOfPages, NULL);
		if( this->bResult != TRUE ) {
			throw("MapUserPhysicalPages failed (%u)\n", GetLastError());
			return;
		}
		// Free the physical pages.
		this->bResult = FreeUserPhysicalPages( GetCurrentProcess(), &(this->NumberOfPages), this->aPFNs);
		if( this->bResult != TRUE ) {
			throw("Cannot free physical pages, error %u.\n", GetLastError());
			return;
		}
		// Free virtual memory.
		this->bResult = VirtualFree(this->cryptoStream, 0, MEM_RELEASE);
		// Release the aPFNs array.
		this->bResult = HeapFree(GetProcessHeap(), 0, this->aPFNs);
		if( this->bResult != TRUE ) {
			throw("Call to HeapFree has failed (%u)\n", GetLastError());
		}
	}

	// Constructor, default 
	PhysicalCryptoRandomStream::PhysicalCryptoRandomStream(void) {

		this->cryptoStream = NULL;
		this->autoMemory = false;
		this->bitLength = 0;
		this->position = 0;
	}

	// Constructor, creates an empty stream with the indicated bit length 
	PhysicalCryptoRandomStream::PhysicalCryptoRandomStream(unsigned long int streamLength) {

		try {
			if (streamLength % BYTEBITS) {
				this->AllocatePhysical(streamLength/BYTEBITS + 1);
			}
			else {
				this->AllocatePhysical(streamLength/BYTEBITS);
			}
			this->bitLength = streamLength;
			this->position = 0;
		}
		catch (char* str) {
			throw str;
		}
	}

	// Constructor, sets the pointed stream of the indicated length in bits
	PhysicalCryptoRandomStream::PhysicalCryptoRandomStream(void* stream, unsigned long int streamLength) {
		unsigned long int streamLengthBytes;

		if ( stream != NULL ) {
			if (streamLength % BYTEBITS) {
				streamLengthBytes = streamLength/BYTEBITS + 1;
			}
			else {
				streamLengthBytes = streamLength/BYTEBITS;
			}
			this->AllocatePhysical(streamLengthBytes);
			memcpy(this->cryptoStream, stream, streamLengthBytes);
			this->bitLength = streamLength;
			this->position = 0;
		}
	}

	// Destructor
	PhysicalCryptoRandomStream::~PhysicalCryptoRandomStream() {

		if ( this->autoMemory ) {
			this->FreePhysical(); 
		}
		this->cryptoStream = NULL;
		this->bitLength = 0;
		this->position = 0;
		this->autoMemory = false;
	}

	// Sets an empty stream with the indicated length in bits
	void PhysicalCryptoRandomStream::SetCryptoRandomStreamBit(unsigned long int streamLength) {

		if (this->cryptoStream == NULL) {
			try {
				if (streamLength % BYTEBITS) {
					this->AllocatePhysical(streamLength/BYTEBITS + 1);
				}
				else {
					this->AllocatePhysical(streamLength/BYTEBITS);
				}
				this->bitLength = streamLength;
				this->position = 0;
			}
			catch (char* str) {
				throw str;
			}
		}
	}

	// Sets the pointed stream of indicated length in bits
	void PhysicalCryptoRandomStream::SetCryptoRandomStreamBit(void* stream, unsigned long int streamLength) {
		unsigned long int streamLengthBytes;

		if ( stream != NULL ) {
			if (streamLength % BYTEBITS) {
				streamLengthBytes = streamLength/BYTEBITS + 1;
			}
			else {
				streamLengthBytes = streamLength/BYTEBITS;
			}
			this->AllocatePhysical(streamLengthBytes);
			memcpy(this->cryptoStream, stream, streamLengthBytes);
			this->bitLength = streamLength;
			this->position = 0;
		}
	}

	// Sets an empty stream with the indicated length in unsigned chars
	void PhysicalCryptoRandomStream::SetCryptoRandomStreamUC(unsigned long int streamLength) {

		if (this->cryptoStream == NULL) {
			try {
				this->AllocatePhysical(streamLength);
				this->bitLength = streamLength * BYTEBITS * sizeof(unsigned char);
				this->position = 0;
			}
			catch (char* str) {
				throw str;
			}
		}
	}

	// Sets the pointed stream of indicated length in unsigned chars
	void PhysicalCryptoRandomStream::SetCryptoRandomStreamUC(void* stream, unsigned long int streamLength) {

		if (stream != NULL) {
			this->AllocatePhysical(streamLength);
			memcpy(this->cryptoStream, stream, streamLength);
			this->bitLength = streamLength * BYTEBITS * sizeof(unsigned char);
			this->position = 0;
		}
	}

	// Sets an empty stream with the indicated length in unsigned shorts
	void PhysicalCryptoRandomStream::SetCryptoRandomStreamUS(unsigned long int streamLength) {

		if (this->cryptoStream == NULL) {
			try {
				this->AllocatePhysical(streamLength * sizeof(unsigned short int));
				this->bitLength = streamLength * BYTEBITS * sizeof(unsigned short int);
				this->position = 0;
			}
			catch (char* str) {
				throw str;
			}
		}
	}

	// Sets the pointed stream of indicated length in unsigned shorts
	void PhysicalCryptoRandomStream::SetCryptoRandomStreamUS(void* stream, unsigned long int streamLength) {
		unsigned long int streamLengthBytes;

		if (stream != NULL) {
			streamLengthBytes = streamLength * sizeof(unsigned short int);
			this->AllocatePhysical(streamLengthBytes);
			memcpy(this->cryptoStream, stream, streamLengthBytes);
			this->bitLength = streamLengthBytes * BYTEBITS;
			this->position = 0;
		}
	}

	// Sets an empty stream with the indicated length in unsigned longs
	void PhysicalCryptoRandomStream::SetCryptoRandomStreamUL(unsigned long int streamLength) {

		if (this->cryptoStream == NULL) {
			try {
				this->AllocatePhysical(streamLength * sizeof(unsigned long int));
				this->bitLength = streamLength * BYTEBITS * sizeof(unsigned long int);
				this->position = 0;
			}
			catch (char* str) {
				throw str;
			}
		}
	}

	// Sets the pointed stream of indicated length in unsigned longs
	void PhysicalCryptoRandomStream::SetCryptoRandomStreamUL(void* stream, unsigned long int streamLength) {
		unsigned long int streamLengthBytes;

		if (stream != NULL) {
			streamLengthBytes = streamLength * sizeof(unsigned long int);
			this->AllocatePhysical(streamLengthBytes);
			memcpy(this->cryptoStream, stream, streamLengthBytes);
			this->bitLength = streamLengthBytes * BYTEBITS;
			this->position = 0;
		}
	}

	// Set the pointed stream as hexadecimal string
	void PhysicalCryptoRandomStream::SetCryptoRandomStreamHexString(const char* hexStream) {
	unsigned long int lengthUC, i, streamLength;
	unsigned char byte;

		try {
			streamLength = strlen(hexStream);
			if ( streamLength % 2 ) {
				throw "Erroneous hexadecimal string!";
			}
			else {
				lengthUC = streamLength / 2;
				this->AllocatePhysical(lengthUC);
				if (this->cryptoStream == NULL ) 
					throw "Memory allocation failure!";
				else {
					this->autoMemory = true;
					this->bitLength = lengthUC * BYTEBITS * sizeof(unsigned char);
					this->position = 0;
					for ( i = 0; i < lengthUC; i++ ) {
						byte = 0;
						switch ( hexStream[ 2 * i ] ) {
							case '0' : byte = 0x00; break;
							case '1' : byte = 0x10; break;
							case '2' : byte = 0x20; break;
							case '3' : byte = 0x30; break;
							case '4' : byte = 0x40; break;
							case '5' : byte = 0x50; break;
							case '6' : byte = 0x60; break;
							case '7' : byte = 0x70; break;
							case '8' : byte = 0x80; break;
							case '9' : byte = 0x90; break;
							case 'A' : 
							case 'a' : byte = 0xa0; break;
							case 'B' : 
							case 'b' : byte = 0xb0; break;
							case 'C' : 
							case 'c' : byte = 0xc0; break;
							case 'D' : 
							case 'd' : byte = 0xd0; break;
							case 'E' : 
							case 'e' : byte = 0xe0; break;
							case 'F' : 
							case 'f' : byte = 0xf0; break;
							default : 
								throw "Erroneous hexadecimal string!";
								break;
						}
						switch ( hexStream[ (2 * i) + 1 ] ) {
							case '0' : byte = byte | 0x00; break;
							case '1' : byte = byte | 0x01; break;
							case '2' : byte = byte | 0x02; break;
							case '3' : byte = byte | 0x03; break;
							case '4' : byte = byte | 0x04; break;
							case '5' : byte = byte | 0x05; break;
							case '6' : byte = byte | 0x06; break;
							case '7' : byte = byte | 0x07; break;
							case '8' : byte = byte | 0x08; break;
							case '9' : byte = byte | 0x09; break;
							case 'A' : 
							case 'a' : byte = byte | 0x0a; break;
							case 'B' : 
							case 'b' : byte = byte | 0x0b; break;
							case 'C' : 
							case 'c' : byte = byte | 0x0c; break;
							case 'D' : 
							case 'd' : byte = byte | 0x0d; break;
							case 'E' : 
							case 'e' : byte = byte | 0x0e; break;
							case 'F' : 
							case 'f' : byte = byte | 0x0f; break;
							default : 
								throw "Erroneous hexadecimal string!";
								break;
						}
						this->SetUCPosition(i, byte);
					}
				}
			}
		}
		catch (char* str) {
			throw str;
		}
	}

	// Gets the CryptoRandomStream type of the object
	CryptoRandomStreams PhysicalCryptoRandomStream::GetCryptoRandomStreamType(void) {

		return this->cryptoRandomStreamType;
	}
  }
}
