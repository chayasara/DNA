#include <stdexcept>
#include <string>
#include <fstream>
#include "dna_sequence.h"


void DnaSequence::initField(const char *sequence, bool isOverriding)
{	
	//std::cout << "in init: " << sequence<<std::endl;
	checkIfNull(sequence);
	size_t len = strlen(sequence);
	DnaChar *tmp = new DnaChar [sizeof(DnaChar)*(len)];
	
	try{
		for(size_t i = 0; i < len; ++i)
			tmp[i] = sequence[i];
		}
		
	catch(std::exception &e){
		delete [] tmp;
		throw;
	}
		
	if(isOverriding)
		delete [] m_sequence;
		
	m_sequence = tmp;
	m_length = len;
}

void DnaSequence::checkIfNull(const void *sequence)const
{
	if(sequence == NULL)
		throw (std::invalid_argument("invalid NULL pointer sequence"));
}

void DnaSequence::checkIndexValidity(size_t index)const
{
	if(index >= m_length || index < 0)
		throw std::invalid_argument("index out of range");
}

bool DnaSequence::strcmp(const DnaChar *lv, const DnaChar *rv) const
{
	for(size_t i=0; i < m_length; ++i)
		if(char(lv[i]) != char(rv[i]))
			return false;
	return true;
}

DnaSequence::DnaChar::DnaChar(char c)
:m_nucleotide(c)
{
	if(m_nucleotide != 'A' && m_nucleotide != 'T' && m_nucleotide != 'C' && m_nucleotide != 'G')
		{std::cout<<m_nucleotide<<std::endl;
		throw (std::invalid_argument("nucleotide must be A, T, C or G"));}
}

DnaSequence::DnaChar& DnaSequence::DnaChar::operator=(DnaChar rv)
{
	m_nucleotide = char(rv);
	return *this;
}

DnaSequence::DnaChar::operator char()const
{
	return m_nucleotide;
}

std::string readDnaFromFile(const char* file_name)
{
	std::ifstream file(file_name);
	
	std::string dna((std::istreambuf_iterator<char>(file)),
					(std::istreambuf_iterator<char>()));
	file.close();
	return dna.substr(0, dna.size()-1);
}

void writeDnaToFile(DnaSequence &dna, const char* file_name)
{
	std::ofstream file(file_name);
	file << dna;
	file.close();
}

char DnaSequence::DnaChar::getPair()const
{
	switch (m_nucleotide)
	{
		case'A':return 'T';
		case'T':return 'A';
		case 'C':return 'G';
		default:return 'C';
		
	}
}
