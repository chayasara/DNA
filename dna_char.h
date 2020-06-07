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
	char m_necleotide;
};

inline DnaChar::DnaChar(char c)
:m_necleotide(c)
{}

inline DnaChar::operator char()const
{
	return m_necleotide;
}

inline DnaChar& DnaChar::operator=(char rv)
{
	if(rv!='A' && rv!='T' && rv!='C' && rv!='G')
		throw std::invalid_argument("necleotide must be A,T,C or g");
	m_necleotide = rv;
	return *this;
}

#endif
