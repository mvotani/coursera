#include <iostream>
#include <math.h>

using namespace std;

void check(uint64_t expect, uint64_t actual)
{
	if ( expect != actual) {
		cout << "Should be " << expect
		     << " but it's " << actual
		     << endl;
	}
}

uint64_t NoDigits(uint64_t no)
{
	uint64_t i = 0;
	for(; no != 0; ++i)
	{
		no = no/10;
	}
	return i;
}

uint64_t Karatsuba(uint64_t n1, uint64_t n2)
{
	uint16_t dig = NoDigits(n1)/2;
	// n1 = n1a*10^(dig1/2) + n1b
	uint64_t n1a = n1/pow(10, dig);
	uint64_t n1b = n1 - n1a*pow(10, dig);
	
	uint64_t n2a = n2/pow(10, dig);
	uint64_t n2b = n2 - n2a*pow(10, dig);
	
	/*cout << n1 << " is " << n1a << "*10^"
	     << dig << " + " << n1b << endl;
	cout << n2 << " is " << n2a << "*10^"
	     << dig << " + " << n2b << endl;*/
	     
	// n1*n2 = z2*10^(2*dig) + z1*10^dig + z0
	uint64_t z2 = n1a * n2a;
	uint64_t z0 = n1b * n2b;
	uint64_t z1 = ((n1a + n1b) * (n2a + n2b)) - z2 - z0;
	
	uint64_t res = z2*pow(10, (2*dig)) + z1*pow(10, dig) + z0;

	cout << "z2 " << z2 << " z1 " << z1
		 << " z0 " << z0 << endl
		 << "res " << res << endl;

	return res;
}


void mul(uint64_t n1, uint64_t n2)
{
	check((n1*n2), Karatsuba(n1, n2));
}

int main()
{
	mul(82, 98);
	mul(8182, 9392);
	mul(3515, 95553);
	mul(94426655259, 62563551547);
	mul(6255525355, 9255232514522);
	//mul(12655152565245225, 95452336522662);
	//mul(3654795236586321593276169, 3215946732516954269523259);
	
	return 0;
}









