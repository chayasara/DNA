#include <stdexcept>
#include "dna_sequence.h"


void DnaSequence::initField(const char *sequence, bool isOverriding)
{
	checkIfNull(sequence);
	
	if(!is_seq_valid(sequence))
		throw std::invalid_argument("necleotide must be A,T,C or G");
		
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
		throw (std::invalid_argument("NULL sequence invalid"));

}

/*static*/ bool is_char_valid(char c)
{
	if(c!='A' && c!='T' && c!='C' && c!='G')
		return false;
	return true;
}

bool is_seq_valid(const char* seq)
{
	size_t len = strlen(seq);
	for(size_t i=0; i<len; i++)
		if(!is_char_valid(seq[i]))
			return false;
	return true;
}
