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
#include <math.h>
#include "mathematicalFunctions.h"


using namespace std;


namespace DiceLockSecurity {

  namespace RandomTest {

		const double MathematicalFunctions::MACHEP =  1.11022302462515654042E-16;	// 2**-53 
		const double MathematicalFunctions::MAXLOG =  7.09782712893383996732E2;		// log(MAXNUM) 
		const double MathematicalFunctions::MAXNUM =  1.79769313486231570815E308;    // 2**1024*(1-MACHEP) 
		const double MathematicalFunctions::PI     =  3.14159265358979323846;		// pi
		const double MathematicalFunctions::LOGPI = 1.14472988584940017414;			// log(pi) 
		const double MathematicalFunctions::LS2PI  =  0.91893853320467274178;		//( log( sqrt( 2*pi ) ) 
		const double MathematicalFunctions::big = 4.503599627370496e15;
		const double MathematicalFunctions::biginv =  2.22044604925031308085e-16;
		// A[]: Stirling's formula expansion of log gamma
		// B[], C[]: log gamma function between 2 and 3
		double MathematicalFunctions::A_lgam[] = {
			8.11614167470508450300E-4,
			-5.95061904284301438324E-4,
 			7.93650340457716943945E-4,
			-2.77777777730099687205E-3,
 			8.33333333333331927722E-2
		};
		double MathematicalFunctions::B_lgam[] = {
			-1.37825152569120859100E3,
			-3.88016315134637840924E4,
			-3.31612992738871184744E5,
			-1.16237097492762307383E6,
			-1.72173700820839662146E6,
			-8.53555664245765465627E5
		};
		double MathematicalFunctions::C_lgam[] = {
			-3.51815701436523470549E2,
			-1.70642106651881159223E4,
			-2.20528590553854454839E5,
			-1.13933444367982507207E6,
			-2.53252307177582951285E6,
			-2.01889141433532773231E6
		};
		const double MathematicalFunctions::MAXLGM = 2.556348e305;

		// Constructor
		MathematicalFunctions::MathematicalFunctions() {
		}

		// Destructor
		MathematicalFunctions::~MathematicalFunctions() {
		}

		// Logarithm of gamma function
		double MathematicalFunctions::LGamma(double x) {
			double p, q, u, w, z;
			int i;
			int sgngam = 0;

			sgngam = 1;
			this->Error = false;
			this->MathError = None;
			if (x < -34.0) {
       			q = -x;
       			w = this->LGamma(q); /* note this modifies sgngam! */
       			p = floor(q);
				if( p == q ) {
				lgsing:
					goto loverf;
				}
				i = (int)p;
			    if ((i & 1) == 0)
					sgngam = -1;
				else
					sgngam = 1;
				z = q - p;
				if (z > 0.5) {
					p += 1.0;
					z = p - q;
				}
				z = q * sin( this->PI * z );
				if (z == 0.0)
					goto lgsing;
				z = this->LOGPI - log( z ) - w;
				return (z);
			}
			if (x < 13.0) {
				z = 1.0;
				p = 0.0;
				u = x;
				while (u >= 3.0) {
					p -= 1.0;
					u = x + p;
					z *= u;
				}
				while (u < 2.0) {
					if (u == 0.0)
						goto lgsing;
					z /= u;
					p += 1.0;
					u = x + p;
				}
				if (z < 0.0) {
					sgngam = -1;
					z = -z;
				}
				else
					sgngam = 1;
				if (u == 2.0)
					return (log(z));
				p -= 2.0;
				x = x + p;
				p = x * this->PolEvl(x, &this->B_lgam[0], 5)/this->P1Evl( x, &this->C_lgam[0], 6);
				return (log(z) + p);
			}
			if (x > this->MAXLGM) {
				loverf:
				this->Error = true;
				this->MathError = Overflow;
				return ( sgngam * this->MAXNUM );
			}
			q = (x - 0.5) * log(x) - x + this->LS2PI;
			if (x > 1.0e8)
				return(q);
			p = 1.0/(x*x);
			if (x >= 1000.0)
				q += ((   7.9365079365079365079365e-4 * p
					- 2.7777777777777777777778e-3) *p
					+ 0.0833333333333333333333) / x;
			else
				q += this->PolEvl(p, &this->A_lgam[0], 4)/x;
			return (q);
		}

		// incomplete gamma function
		double MathematicalFunctions::IGamma(double a, double x ) {
			double ans, ax, c, r;

			this->Error = false;
			this->MathError = None;
			if ((x <= 0) || (a <= 0))
				return (0.0);
			if ((x > 1.0) && (x > a))
				return (1.e0 - this->IGammaC(a,x));
			ax = a * log(x) - x - this->LGamma(a);
			if (ax < -(this->MAXLOG)) {
				this->Error = true;
				this->MathError = Underflow;
				return( 0.0 );
			}
			ax = exp(ax);
			r = a;
			c = 1.0;
			ans = 1.0;
			do {
				r += 1.0;
				c *= x/r;
				ans += c;
			} while(c/ans > this->MACHEP);
			return(ans * ax/a);
		}

		// Complemented incomplete gamma integral
		double MathematicalFunctions::IGammaC(double a, double x) {
			double ans, ax, c, yc, r, t, y, z;
			double pk, pkm1, pkm2, qk, qkm1, qkm2;

			this->Error = false;
			this->MathError = None;
			if ((x <= 0) || (a <= 0))
				return (1.0);
			if ((x < 1.0) || (x < a))
				return (1.e0 - this->IGamma(a,x));
			ax = a * log(x) - x - this->LGamma(a);
			if (ax < -(this->MAXLOG)) {
				this->Error = true;
				this->MathError = Underflow;
				return( 0.0 );
			}
			ax = exp(ax);
			y = 1.0 - a;
			z = x + y + 1.0;
			c = 0.0;
			pkm2 = 1.0;
			qkm2 = x;
			pkm1 = x + 1.0;
			qkm1 = z * x;
			ans = pkm1/qkm1;
			do {
				c += 1.0;
				y += 1.0;
				z += 2.0;
				yc = y * c;
				pk = pkm1 * z  -  pkm2 * yc;
				qk = qkm1 * z  -  qkm2 * yc;
				if (qk != 0) {
					r = pk/qk;
					t = fabs((ans - r)/r);
					ans = r;
				}
				else
					t = 1.0;
				pkm2 = pkm1;
				pkm1 = pk;
				qkm2 = qkm1;
				qkm1 = qk;
				if (fabs(pk) > this->big) {
					pkm2 *= this->biginv;
					pkm1 *= this->biginv;
					qkm2 *= this->biginv;
					qkm1 *= this->biginv;
				}
			} while (t > this->MACHEP);
			return (ans * ax);
		}

		// Evaluate polynomial of degree N
		double MathematicalFunctions::PolEvl(double x,double coef[], int N) {
			double ans;
			double *p;
			int i;

			p = coef;
			ans = *p++;
			i = N;
			do
				ans = ans * x + *p++;
			while (--i);
			return (ans);
		}

		//                                          N
		// Evaluate polynomial when coefficient of x  is 1.0.
		double MathematicalFunctions::P1Evl(double x, double coef[], int N) {
			double ans;
			double *p;
			int i;

			p = coef;
			ans = x + *p++;
			i = N-1;
			do
				ans = ans * x + *p++;
			while (--i);
			return (ans);
		}
			
		// Error function in double precision 
		double MathematicalFunctions::ErF(double x) {
			static const double two_sqrtpi = 1.128379167095512574;
			static const double	rel_error = 1E-12;
			double	sum = x, term = x, xsqr = x * x;
			int		j = 1;

			if ( fabs(x) > 2.2 )
				return 1.0 - this->ErFc(x);
			do {
				term *= xsqr/j;
				sum -= term/(2*j+1);
				j++;
				term *= xsqr/j;
				sum += term/(2*j+1);
				j++;
			} while ( fabs(term)/sum > rel_error );
			return two_sqrtpi*sum;
		}
			
		// Error function in double precision 
		double MathematicalFunctions::ErFc(double x) {
			static const double one_sqrtpi = 0.564189583547756287;
			static const double	rel_error = 1E-12;
			double	a = 1, b = x, c = x, d = x*x + 0.5;
			double	q1, q2 = b/d, n = 1.0, t;

			if ( fabs(x) < 2.2 )
				return 1.0 - this->ErF(x);
			if ( x < 0 )
				return 2.0 - this->ErFc(-x);
			do {
				t = a*n + b*x;
				a = b;
				b = t;
				t = c*n + d*x;
				c = d;
				d = t;
				n += 0.5;
				q1 = q2;
				q2 = b/d;
			} while ( fabs(q1-q2)/q2 > rel_error );
			return one_sqrtpi * exp(-x*x) * q2;
		}

		// Statistical Normal function
		double MathematicalFunctions::Normal(double x) {
			double arg, result, sqrt2=1.414213562373095048801688724209698078569672;

			if (x > 0) {
				arg = x/sqrt2;
				result = 0.5 * ( 1 + this->ErF(arg) );
			}	
			else {
				arg = -x/sqrt2;
				result = 0.5 * ( 1 - this->ErF(arg) );
			}
			return(result);
		}

		// Class common error handling member
		int	MathematicalFunctions::GetError() {

			return this->Error;
		}

		// Class common error handling member
		MathematicalErrors MathematicalFunctions::GetMathError() {

			return this->MathError;
		}
   }
}