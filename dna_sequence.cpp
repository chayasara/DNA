#include <stdexcept>
#include "dna_sequence.h"


void DnaSequence::initField(const char *sequence, bool isOverriding)
{
	checkIfNull(sequence);
	size_t len = strlen(sequence);
	char *tmp = new char [len+1];
	
	strcpy(tmp, sequence);
	
	if(isOverriding)
		delete [] m_sequence;
		
	m_sequence = tmp;
	m_sequence_length = len;
}

void DnaSequence::checkIfNull(const char *sequence)const
{
	if(sequence == NULL)
		throw (std::invalid_argument("invalid sequence"));
	
}
