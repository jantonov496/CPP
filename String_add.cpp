#include <string>
#include <iostream>

//The number below is the maximum whose square is less than the max positive int for my compiler.
//Without the implementation of comparison for string represented integers, I will need to work
//with 9999 as the maximum integer which can be multiplied then converted back to string without working too hard.

const int MAX_MULT = 46340;
//The function pwr10(k) returns the integer 10^k.
int pwr10(int k) {
	int p = 1;
	if (k > 0) {
		for (int i = 1; i <= k; i++) {
			p = p*10;
		}
	}
	return p;
}

//The function str_pwr10(a,k) returns a*10^k as string.
std::string str_pwr10mult(std::string a, int k) {
	std::string power = "";
	if (a == "0") return "0";
	if (k > 0) {
		for (int i = 0; i < k; i++) {
			power += "0";
		}
	}
	return a + power;
}
//The function Int_out(a) takes as argument the string a and returns a as an int.

int Int_out(std::string a) {
	int a_int = 0;
	for (int i = a.length() - 1, j = 0; i >= 0; i--, j++) {
		 a_int += (((int)(a[i])) - 48)*pwr10(j);
	}
	return a_int;
}

//The function Str_out(a) takes as an argument an integer and returns it as string.

std::string Str_out(int a) {
	int x = a;
	std::string outputR = "", output = "";
	while (x != 0) {
		int digit = (x % 10);
		outputR += (char)(digit + 48);
		x = (x - digit)/10;
	}
	for(int i = outputR.length() - 1; i >= 0; i--) {
		output += outputR[i];
	}
	return output;
}

//The function ZeroPad(a,n) inserts n zeros in the beginning of the string a and returns the padded string.

std::string ZeroPad(std::string a, int n) {
	if (n == 0) return a;
	std::string output = "";
	for(int i = 0; i < n; i++) {
		output += "0";
	}
	for(int i = 0; i < a.length(); i++) {
		output += a[i];
	}
	return output;
}

//The function StrAdd(a,b) assumes that a and b are strings of the same length.
//It adds them as if they are numbers, and returns the result as a string.

std::string StrAdd(std::string A, std::string B) {
	std::string a, b;
	if (A.length() > B.length()) {
		a = ZeroPad(A,0);
		b = ZeroPad(B, A.length() - B.length());
	}
	if (B.length() > A.length()) {
		a = ZeroPad(A, B.length() - A.length());
		b = ZeroPad(B, 0);
	}
	if (A.length() == B.length()) {
		a = ZeroPad(A, 0);
		b = ZeroPad(B, 0);
	}
	
	std::string c = "";
	std::string d = "";
	int carry = 0;
	for(int i = a.length() - 1; i >= 0; i--) {
		int x = (int)(a[i]) - 48;
		int y = (int)(b[i]) - 48;
		int z = (x + y + carry) % 10;
		if ((x + y + carry) >= 10) {
			carry = 1;
		} else carry = 0;
		c += (char)(z + 48);
	}

	if (carry == 1) c+= "1";
	for (int i = c.length() - 1; i >= 0; i--) {
		d += c[i];
	}
	return d;
}

//The function below splits a string represented integer into two such having half the digits of the original
//Use std::vector<std::string> Splitter(std::string).  Search Google for "returning an array of strings in c++ from a function" to get examples of usage

//The function Mult(a,b) implements recursive multiplication of string represented integers.


std::string Mult(std::string a, std::string b) {
	if ((a == "0")||(b == "0")) return "0";
	if ((a.length() < 5)&&(b.length() < 5)) {
		return Str_out(Int_out(a)*Int_out(b));
	}
	if (a.length() >= 5) {
		if (b.length() < 5) {
			std::string a_lower = "", a_upper = "";
			int a_midpt = a.length()/2;
			for (int i = 0; i < a_midpt; i++) {
				a_upper += a[i];
			}
			for (int i = a_midpt; i < a.length(); i++) {
				a_lower += a[i];
			}
			std::string z1 = Mult(a_upper,b);
			std::string z0 = Mult(a_lower,b);
			int m = a.length() - a_midpt;
			std::string result = StrAdd(str_pwr10mult(z1,m), z0);
			return result;
		} else {		
			std::string a_lower = "", a_upper = "",
						b_lower = "", b_upper = "";
			int a_midpt = a.length()/2, b_midpt = b.length()/2;
			for (int i = 0; i < a_midpt; i++) {
				a_upper += a[i];
			}
			for (int i = a_midpt; i < a.length(); i++) {
				a_lower += a[i];
			}
			for (int i = 0; i < b_midpt; i++) {
				b_upper += b[i];
			}
			for (int i = b_midpt; i < b.length(); i++) {
				b_lower += b[i];
			}

			int m = a.length() - a_midpt;
			std::string z2 = Mult(a_upper,b_upper);
			std::string z1 = StrAdd(Mult(a_upper, b_lower), Mult(a_lower, b_upper));
			std::string z0 = Mult(a_lower, b_lower);
			std::string result = StrAdd(str_pwr10mult(z2, 2*m), StrAdd(str_pwr10mult(z1,m), z0));
			return result;
		}
	} else {
		if (b.length() >= 5) {
			std::string b_lower = "", b_upper = "";
			int b_midpt = b.length()/2;
			for (int i = 0; i < b_midpt; i++) {
				b_upper += b[i];
			}
			for (int i = b_midpt; i < b.length(); i++) {
				b_lower += b[i];
			}
			int m = b.length() - b_midpt;
			std::string z1 = Mult(a, b_upper);
			std::string z0 = Mult(a, b_lower);
			std::string result = StrAdd(str_pwr10mult(z1,m), z0);
			return result;
		}
	}
}



int main() {
	std::cout << "Enter first integer: ";
	std::string int1;
	std::getline(std::cin, int1);
	std::cout << "Enter second integer: ";
	std::string int2;
	std::getline(std::cin, int2);
	std::cout << Mult(int1, int2) << std::endl;
	return 0 ;
}
