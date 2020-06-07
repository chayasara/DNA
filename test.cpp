#include <iostream>
#include <gtest/gtest.h>
#include "dna_sequence.h"

void my_tests()
{
	char* s = new char [10];
	strcpy(s, "TTTTTCGGGGCTTT");
	
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

int main(int argc, char* argv[])
{	
	//my_tests();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/////////////////////////////////////
// TESTS under this line

/*TEST(Phase2BasicTests, readDnaFromFile)
{
    ASSERT_NO_THROW(DnaSequence(readDnaFromFile("dna.txt")));
    
    DnaSequence dna(readDnaFromFile("dna.txt"));
    std::ostringstream out;
    out << dna;
    
    EXPECT_EQ("ATCCCG", out.str());
}*/

TEST(Phase2BasicTests, writeDnaToFile)
{
	DnaSequence dna("ATCGGGT");
	writeDnaToFile(dna, "dna.txt");
	ASSERT_EQ(DnaSequence(readDnaFromFile("dna.txt")), dna);
}

TEST(Phase2BasicTests, slice)
{
	DnaSequence dna("ATCGGGT");
	ASSERT_EQ(dna.slice(1,4),DnaSequence("TCGG"));
	ASSERT_THROW(dna.slice(-1, 66), std::invalid_argument);
}

TEST(Phase2BasicTests, getPair)
{
	ASSERT_EQ(DnaSequence("ATCGG").getPair(), DnaSequence("CCGAT"));
}


//g++ -ansi -pedantic -Wall -Wconversion  test_stack.cpp -lgtest -lgtest_main -pthread -o testStack
