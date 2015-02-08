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
	    const double MathematicalFunctions::a_erf[65] = {
		    5.958930743e-11, -1.13739022964e-9, 
			1.466005199839e-8, -1.635035446196e-7, 
			1.6461004480962e-6, -1.492559551950604e-5, 
			1.2055331122299265e-4, -8.548326981129666e-4, 
			0.00522397762482322257, -0.0268661706450773342, 
			0.11283791670954881569, -0.37612638903183748117, 
			1.12837916709551257377, 
			2.372510631e-11, -4.5493253732e-10, 
			5.90362766598e-9, -6.642090827576e-8, 
			6.7595634268133e-7, -6.21188515924e-6, 
			5.10388300970969e-5, -3.7015410692956173e-4, 
			0.00233307631218880978, -0.0125498847718219221, 
			0.05657061146827041994, -0.2137966477645600658, 
			0.84270079294971486929, 
			9.49905026e-12, -1.8310229805e-10, 
			2.39463074e-9, -2.721444369609e-8, 
			2.8045522331686e-7, -2.61830022482897e-6, 
			2.195455056768781e-5, -1.6358986921372656e-4, 
			0.00107052153564110318, -0.00608284718113590151, 
			0.02986978465246258244, -0.13055593046562267625, 
			0.67493323603965504676, 
			3.82722073e-12, -7.421598602e-11, 
			9.793057408e-10, -1.126008898854e-8, 
			1.1775134830784e-7, -1.1199275838265e-6, 
			9.62023443095201e-6, -7.404402135070773e-5, 
			5.0689993654144881e-4, -0.00307553051439272889, 
			0.01668977892553165586, -0.08548534594781312114, 
			0.56909076642393639985, 
			1.55296588e-12, -3.032205868e-11, 
			4.0424830707e-10, -4.71135111493e-9, 
			5.011915876293e-8, -4.8722516178974e-7, 
			4.30683284629395e-6, -3.445026145385764e-5, 
			2.4879276133931664e-4, -0.00162940941748079288, 
			0.00988786373932350462, -0.05962426839442303805, 
			0.49766113250947636708
		};
		const double MathematicalFunctions::b_erf[65] = {
			-2.9734388465e-10, 2.69776334046e-9, 
			-6.40788827665e-9, -1.6678201321e-8, 
			-2.1854388148686e-7, 2.66246030457984e-6, 
			1.612722157047886e-5, -2.5616361025506629e-4, 
			1.5380842432375365e-4, 0.00815533022524927908, 
			-0.01402283663896319337, -0.19746892495383021487, 
			0.71511720328842845913, 
			-1.951073787e-11, -3.2302692214e-10, 
			5.22461866919e-9, 3.42940918551e-9, 
			-3.5772874310272e-7, 1.9999935792654e-7, 
			2.687044575042908e-5, -1.1843240273775776e-4, 
			-8.0991728956032271e-4, 0.00661062970502241174, 
			0.00909530922354827295, -0.2016007277849101314, 
			0.51169696718727644908, 
			3.147682272e-11, -4.8465972408e-10, 
			6.3675740242e-10, 3.377623323271e-8, 
			-1.5451139637086e-7, -2.03340624738438e-6, 
			1.947204525295057e-5, 2.854147231653228e-5, 
			-0.00101565063152200272, 0.00271187003520095655, 
			0.02328095035422810727, -0.16725021123116877197, 
			0.32490054966649436974, 
			2.31936337e-11, -6.303206648e-11, 
			-2.64888267434e-9, 2.050708040581e-8, 
			1.1371857327578e-7, -2.11211337219663e-6, 
			3.68797328322935e-6, 9.823686253424796e-5, 
			-6.5860243990455368e-4, -7.5285814895230877e-4, 
			0.02585434424202960464, -0.11637092784486193258, 
			0.18267336775296612024, 
			-3.67789363e-12, 2.0876046746e-10, 
			-1.93319027226e-9, -4.35953392472e-9, 
			1.8006992266137e-7, -7.8441223763969e-7, 
			-6.75407647949153e-6, 8.428418334440096e-5, 
			-1.7604388937031815e-4, -0.0023972961143507161, 
			0.0206412902387602297, -0.06905562880005864105, 
			0.09084526782065478489
		};

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
       			w = LGamma(q); /* note this modifies sgngam! */
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
				z = q * sin( PI * z );
				if (z == 0.0)
					goto lgsing;
				z = LOGPI - log( z ) - w;
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
				p = x * PolEvl(x, &B_lgam[0], 5)/P1Evl( x, &C_lgam[0], 6);
				return (log(z) + p);
			}
			if (x > MAXLGM) {
				loverf:
				this->Error = true;
				this->MathError = Overflow;
				return ( sgngam * MAXNUM );
			}
			q = (x - 0.5) * log(x) - x + LS2PI;
			if (x > 1.0e8)
				return(q);
			p = 1.0/(x*x);
			if (x >= 1000.0)
				q += ((   7.9365079365079365079365e-4 * p
					- 2.7777777777777777777778e-3) *p
					+ 0.0833333333333333333333) / x;
			else
				q += PolEvl(p, &A_lgam[0], 4)/x;
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
				return (1.e0 - IGammaC(a,x));
			ax = a * log(x) - x - LGamma(a);
			if (ax < -MAXLOG) {
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
			} while(c/ans > MACHEP);
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
				return (1.e0 - IGamma(a,x));
			ax = a * log(x) - x - LGamma(a);
			if (ax < -MAXLOG) {
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
				if (fabs(pk) > big) {
					pkm2 *= biginv;
					pkm1 *= biginv;
					qkm2 *= biginv;
					qkm1 *= biginv;
				}
			} while (t > MACHEP);
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
			int k;
			double w, t, y;

			w = x < 0 ? -x : x;
			if (w < 2.2) {
				t = w * w;
				k = (int) t;
				t -= k;
				k *= 13;
				y = ((((((((((((a_erf[k] * t + a_erf[k + 1]) * t + 
					a_erf[k + 2]) * t + a_erf[k + 3]) * t + a_erf[k + 4]) * t + 
					a_erf[k + 5]) * t + a_erf[k + 6]) * t + a_erf[k + 7]) * t + 
					a_erf[k + 8]) * t + a_erf[k + 9]) * t + a_erf[k + 10]) * t + 
					a_erf[k + 11]) * t + a_erf[k + 12]) * w;
			} 
			else 
				if (w < 6.9) {
					k = (int) w;
					t = w - k;
					k = 13 * (k - 2);
					y = (((((((((((b_erf[k] * t + b_erf[k + 1]) * t + 
						b_erf[k + 2]) * t + b_erf[k + 3]) * t + b_erf[k + 4]) * t + 
						b_erf[k + 5]) * t + b_erf[k + 6]) * t + b_erf[k + 7]) * t + 
						b_erf[k + 8]) * t + b_erf[k + 9]) * t + b_erf[k + 10]) * t + 
						b_erf[k + 11]) * t + b_erf[k + 12];
					y *= y;
					y *= y;
					y *= y;
					y = 1 - y * y;
				} 
				else {
					y = 1;
				}
			return x < 0 ? -y : y;
		}
			
		// Error function in double precision 
		double MathematicalFunctions::ErFc(double x) {
			double t, u, y;

			t = 3.97886080735226 / (fabs(x) + 3.97886080735226);
			u = t - 0.5;
			y = (((((((((0.00127109764952614092 * u + 1.19314022838340944e-4) * u - 
				0.003963850973605135) * u - 8.70779635317295828e-4) * u + 
				0.00773672528313526668) * u + 0.00383335126264887303) * u - 
				0.0127223813782122755) * u - 0.0133823644533460069) * u + 
				0.0161315329733252248) * u + 0.0390976845588484035) * u + 
				0.00249367200053503304;
			y = ((((((((((((y * u - 0.0838864557023001992) * u - 
				0.119463959964325415) * u + 0.0166207924969367356) * u + 
				0.357524274449531043) * u + 0.805276408752910567) * u + 
				1.18902982909273333) * u + 1.37040217682338167) * u + 
				1.31314653831023098) * u + 1.07925515155856677) * u + 
				0.774368199119538609) * u + 0.490165080585318424) * u + 
				0.275374741597376782) * t * exp(-x * x);
			return x < 0 ? 2 - y : y;
		}

		// Statistical Normal function
		double MathematicalFunctions::Normal(double x) {
			double arg, result, sqrt2=1.414213562373095048801688724209698078569672;

			if (x > 0) {
				arg = x/sqrt2;
				result = 0.5 * ( 1 + ErF(arg) );
			}	
			else {
				arg = -x/sqrt2;
				result = 0.5 * ( 1 - ErF(arg) );
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

