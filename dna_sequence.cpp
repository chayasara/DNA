#include <stdexcept>
#include "dna_sequence.h"


void DnaSequence::initField(const char *sequence, bool isOverriding)
{
	size_t len = strlen(sequence);
	DnaChar *d = new DnaChar [len];
	
	for(size_t i = 0; i < len; ++i, d[i] = sequence[i]);
	initField(d, isOverriding);
	delete [] d;
}

void DnaSequence::initField(const DnaSequence::DnaChar *sequence, bool isOverriding)
{
	checkIfNull(sequence);
	size_t len = strlen(sequence);
	DnaChar *tmp = new DnaChar [sizeof(DnaChar)*(len+1)];
	
	for(int i = 0; i<len; ++i)
		tmp[i] = sequence[i];
	
	if(isOverriding)
		delete [] m_sequence;
		
	m_sequence = tmp;
	m_sequence_length = len;
}

void DnaSequence::checkIfNull(const DnaSequence::DnaChar& *sequence)const
{
	if(sequence == NULL)
		throw (std::invalid_argument("invalid sequence"));
	
}

DnaSequence::DnaChar::DnaChar(char c)
:m_necleotide(c)
{
	if(m_necleotide != 'A' && m_necleotide != 'T' && m_necleotide != 'C' && m_necleotide != 'G')
		throw (std::invalid_argument("Necleotide must be A, T, C or G"));
}

char DnaSequence::DnaChar::get_char()const
{
	return m_necleotide;
}

DnaChar& operator=(DnaChar rv)
{
	m_necleotide = rv.m_necleotide;
}

bool DnaSequence::strcmp(DnaChar *lv, DnaChar *rv) const
{
	for(int i=0; i<m_sequence_length; ++i)
		if(lv[i].get_necleotide() != rv[i].get_necleotide())
			return false;
	return true;
}

