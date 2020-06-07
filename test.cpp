#include <iostream>
#include "dna_sequence.h"

int main()
{
	char* s = new char [10];
	strcpy(s, "A");
	
	DnaSequence d1(s);
	std::cout << d1 << std::endl;
	DnaSequence d2(d1);
	std::cout << d2 << std::endl;
	DnaSequence d3 = d2;
	std::cout << d3 << std::endl;
	d3="TACG";
	std::cout << d3 << std::endl;
	DnaSequence d4 = "ATCG";
	std::cout << d4 << std::endl;
	//d3 = NULL;
	std::cout << d3 << std::endl;
	std::cout << d3[22] << std::endl;
	std::cout << d3.length() << std::endl;
	std::cout << bool(d3 != d2) << std::endl;
	d3[1] = 'A';
	//d3[1] = 'k';  //throws
	delete [] s;
}
