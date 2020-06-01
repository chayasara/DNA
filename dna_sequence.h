#ifndef __DNA_SEQUENCE_H__
#define __DNA_SEQUENCE_H__

#include <string>
#include <cstring>
#include <ostream>
#include <iostream>

class DnaSequence
{
	friend std::ostream& operator<<(std::ostream&, DnaSequence&);
	
public:
	DnaSequence(const char *sequence);
	DnaSequence(const std::string &sequence);
	DnaSequence(const DnaSequence &other);
	~DnaSequence();
	
	DnaSequence& operator=(const DnaSequence &other);
	DnaSequence& operator=(const std::string &sequence);
	DnaSequence& operator=(const char* sequence);
	
	bool operator==(const DnaSequence &other)const;
	bool operator!=(const DnaSequence &other)const;
	
	char operator[](size_t index)const;
	size_t length()const;
	
private:
	char *m_sequence;
	size_t m_sequence_length;
	
	void initField(const char* sequence, bool isOverriding = false);
	void checkIfNull(const char*)const;
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
	initField(other.m_sequence);
}

inline DnaSequence::~DnaSequence()
{	
	std::cout<<"in dtor, sequence: "<< m_sequence << std::endl;
	delete [] m_sequence;
}

inline DnaSequence& DnaSequence::operator=(const DnaSequence &other)
{
	if(this != &other)
	{
		initField(other.m_sequence, true);
	}
	
	return *this;
}

inline DnaSequence& DnaSequence::operator=(const std::string &sequence)
{
	initField(sequence.c_str(), true);
}

inline DnaSequence& DnaSequence::operator=(const char* sequence)
{
	initField(sequence, true);
}

inline bool DnaSequence::operator==(const DnaSequence &other)const
{
	return (strcmp(m_sequence, other.m_sequence) == 0);
}

inline bool DnaSequence::operator!=(const DnaSequence &other)const
{
	return (strcmp(m_sequence, other.m_sequence) != 0);
}

inline std::ostream& operator<<(std::ostream& os, DnaSequence& dna)
{
	return os << dna.m_sequence;
}

inline char DnaSequence::operator[](size_t index)const
{
	return m_sequence[index];
}

inline size_t DnaSequence::length()const
{
	return m_sequence_length;;
}
#endif
