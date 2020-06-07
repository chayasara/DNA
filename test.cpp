#include <iostream>
#include "dna_sequence.h"

int main()
{
	char* s = new char [10];
	strcpy(s, "TTTTTCGGGGCTTTA");
	
	DnaSequence d1(s);
	std::cout << d1 << std::endl;
	DnaSequence d2(d1);
	std::cout << d2 << std::endl;
	DnaSequence d3 = d2;
	std::cout << d3 << std::endl;
	d3="ATCG";
	std::cout << "should be ATCG: " << d3 << std::endl;
	//d3 = NULL;
	std::cout << "should be T: " << d3[1] << std::endl;
	std::cout << "should be 4: " << d3.length() << std::endl;
	std::cout << "should be true: " << bool(d3 != d2) << std::endl;
	std::cout << "b4: " << d1 << std::endl;
	d1[1] = 'A';
	std::cout << "after: " << d1 << std::endl;
	//d3[1] = 'k';
	delete [] s;
}
