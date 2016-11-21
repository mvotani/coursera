#include <iostream>
#include <vector>

using std::vector;

typedef vector<uint64_t> vect;

uint64_t inversion(vect& v)
{
	vect v1 {v.begin(), (v.begin() + 
	           (v.size()/2))};
	vect v2 {v.begin() + ((v.size/2) + 1),
	         v.end()};
	
	std::cout << "size is " << v1.size()
	          << " " << v2.size();
	          << std::endl;
	
	return 0;
}

int main()
{
	vect v1{1, 2, 3, 4};
	
	vect v2{1, 2, 3, 4, 5, 6, 7};
	
	inversion(v1);
	inversion(v2);
	
	
	return 0;
}