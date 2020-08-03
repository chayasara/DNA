#ifndef __DNA_CHAR_H__
#define __DNA_CHAR_H__

#include <stdexcept>

class DnaChar
{
public:
	DnaChar(char);
	operator char()const;
	DnaChar& operator=(char rv);

private:
	char m_nucleotide;
};

inline DnaChar::DnaChar(char c)
:m_nucleotide(c)
{}

inline DnaChar::operator char()const
{
	return m_nucleotide;
}

inline DnaChar& DnaChar::operator=(char rv)
{
	if(rv!='A' && rv!='T' && rv!='C' && rv!='G')
		throw std::invalid_argument("nucleotide must be A,T,C or g");
	m_nucleotide = rv;
	return *this;
}

#endif
