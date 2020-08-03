#include <iostream>
#include <gtest/gtest.h>
#include "dna_sequence.h"


int main(int argc, char* argv[])
{	
	//my_tests();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/////////////////////////////////////

TEST(Phase2BasicTests, basics)
{
	char* s = new char [10];
	strcpy(s, "TTTTTCGGGGCTTT");
	
	DnaSequence d1("GTTG");
	d1 = "C";
	DnaSequence d2(d1);
	DnaSequence d3 = d2;
	d3="ATCG";
	d3 = "G";
	ASSERT_EQ(d3[1], 'T');
	ASSERT_EQ(d3.length(), 4);
	ASSERT_TRUE(d3 != d2);
	d1[1] = 'A';
	//d3[1] = 'k';
	delete [] s;
}

TEST(Phase2BasicTests, readDnaFromFile)
{
    ASSERT_NO_THROW(DnaSequence(readDnaFromFile("dna.txt")));
    
    DnaSequence dna(readDnaFromFile("dna.txt"));
    std::ostringstream out;
    out << dna;
    
    EXPECT_EQ("ATCCCG", out.str());
}

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

TEST(Phase2BasicTests, find)
{
	
	DnaSequence dna("ATCGGGT");
	ASSERT_EQ(1, dna.find("TCG"));
	ASSERT_EQ(-1, dna.find("GTT"));
}

TEST(Phase2BasicTests, countSubs)
{
	
	DnaSequence dna("ATCGGGT");
	ASSERT_EQ(3, dna.countOccurrences("G"));
	ASSERT_EQ(0, dna.countOccurrences("GTT"));
}

TEST(Phase2BasicTests, findAll)
{
	size_t arr[] = {0,5,9,12};
	std::vector<size_t> indices(arr, arr+4);
	std::vector<size_t> v;
	DnaSequence dna("ATCGGATGGATCATGT");
	
	ASSERT_EQ(indices, dna.findAll("AT"));
	ASSERT_EQ(v, dna.findAll("GTT"));
}

TEST(Phase2BasicTests, cosensus)
{
	DnaSequence dna("ATGTAGGGATTAAGGATCTGAATATGTAA");

	std::vector<DnaSequence> c;
	c.push_back("ATGTAG");
	c.push_back("ATGTAGGGATTAAGGATCTGA");
	c.push_back("ATGTAA");
	ASSERT_EQ(c, dna.findConsesus());
	//ASSERT_EQ(v, dna.findAll("GTT"));
}

//g++ -ansi -pedantic -Wall -Wconversion  test_stack.cpp -lgtest -lgtest_main -pthread -o testStack
