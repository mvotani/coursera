
def NoDigits(no):
    i = 0
    while no != 0:
    	    no = int(no/10)
    	    i = i + 1
    return int(i)

def Karatsuba(n1, n2):
    if NoDigits(n1) == 1 or NoDigits(n2) == 1:
        return n1 * n2

    dig = int(NoDigits(n1)/2)
    # n1 = n1a*10^(dig1/2) + n1b
    n1a = int(n1/(10**dig))
    n1b = n1 - n1a*(10**dig)
	
    n2a = int(n2/(10**dig))
    n2b = n2 - n2a*(10**dig);
	
    # print(str(n1) + " is " + str(n1a) + "*10^" +
	   #       str(dig) + " + " + str(n1b))
    # print(str(n2) + " is " + str(n2a) + "*10^" +
	   #       str(dig) + " + " + str(n2b))
  
    # n1*n2 = z2*10^(2*dig) + z1*10^dig + z0
    z2 = Karatsuba(n1a, n2a)
    z0 = Karatsuba(n1b, n2b)
    z1 = Karatsuba((n1a + n1b), (n2a + n2b)) - z2 - z0
    
    res = z2*(10**(2*dig)) + z1*(10**dig) + z0

    # print("z2 " + str(z2) + " z1 " + str(z1) +
    	#       " z0 " + str(z0))
    print("res " + str(res))

    return res


def check(expect, actual):
    if expect != actual:
    	    print("Should be " + repr(expect) + 
    	    	    " but it's " + repr(actual))

def mul(n1, n2):
    print("Checking " + repr(n1) + "*" + repr(n2))
    check((n1*n2), Karatsuba(n1, n2))

def main():
    mul(1, 4)
    mul(167, 65)
    mul(924625, 92453281)
    mul(3515, 95553)
    mul(94426655259, 62563551547)
    #mul(6255525355, 9255232514522)
    #mul(12655152565245225, 95452336522662)
    #mul(3654795236586321593276169,
    	#    3215946732516954269523259)
    	

if __name__ == "__main__":
    main()