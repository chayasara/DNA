#ifndef __DNA_SEQUENCE_H__
#define __DNA_SEQUENCE_H__

#include <string>
#include <cstring>
#include <ostream>
#include <iostream>
#include <stdexcept>

class DnaSequence
{

friend std::ostream& operator<<(std::ostream&, DnaSequence&);

private:
	class DnaChar{
	public:
		DnaChar(){}
		DnaChar(char c);
		DnaChar& operator=(DnaChar rv);
		operator char()const;
		                                                                                                                                                                           
	private:
		char m_necleotide;
	};
	
public:
	DnaSequence(const char *sequence);
	DnaSequence(const std::string &sequence);
	DnaSequence(const DnaSequence &other);
	~DnaSequence();

	DnaSequence& operator=(const DnaSequence &other);
	
	bool operator==(const DnaSequence &other)const;
	bool operator!=(const DnaSequence &other)const;
	
	char const operator[](size_t index)const;
	DnaChar& operator[](size_t index);
	size_t length()const;
	
private:
	DnaChar *m_sequence;
	size_t m_length;
	
	void initField(const char* sequence, bool isOverriding = false);
	void checkIfNull(const void*)const;
	
	bool strcmp(const DnaChar *, const DnaChar *) const;
	
};


inline DnaSequence::DnaSequence(const char *sequence)
{
	initField(sequence);
}

inline DnaSequence::DnaSequence(const std::string &sequence)
{
	initField(sequence.c_str());
}

inline DnaSequence::DnaSequence(const DnaSequence &other)
{
	initField((char*)other.m_sequence);
}

inline DnaSequence::~DnaSequence()
{	
	delete [] m_sequence;
}

inline DnaSequence& DnaSequence::operator=(const DnaSequence &other)
{
	if(this != &other)
	{
		initField((char*)other.m_sequence, true);
	}
	
	return *this;
}

inline bool DnaSequence::operator==(const DnaSequence &other)const
{
	return (strcmp(m_sequence, other.m_sequence));
}

inline bool DnaSequence::operator!=(const DnaSequence &other)const
{
	return (!strcmp(m_sequence, other.m_sequence));
}

inline std::ostream& operator<<(std::ostream& os, DnaSequence& dna)
{
	for(size_t i=0; i<dna.m_length; os<<char(dna.m_sequence[i]), ++i);
	return os;
}


inline const char DnaSequence::operator[](size_t index)const
{
	if(index >= m_length || index < 0)
		throw std::invalid_argument("index out of range");
	
	return m_sequence[index];
}

inline DnaSequence::DnaChar& DnaSequence::operator[](size_t index)
{
	if(index >= m_length || index < 0)
		throw std::invalid_argument("index out of range");
		
	return m_sequence[index];
}

inline size_t DnaSequence::length()const
{
	return m_length;
}



#endif
