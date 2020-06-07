#ifndef __DNA_SEQUENCE_H__
#define __DNA_SEQUENCE_H__

#include <string>
#include <cstring>
#include <ostream>
#include <iostream>
#include <stdexcept>
#include <fstream>

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
   		char getPair()const;
                                                                                                                                                                      
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
//phase2
	DnaSequence slice(size_t, size_t)const;
	DnaSequence getPair()const;
	
private:
	DnaChar *m_sequence;
	size_t m_length;
	
	void initField(const char* sequence, bool isOverriding = false);
	void checkIfNull(const void*)const;
	
	bool strcmp(const DnaChar *, const DnaChar *) const;
	
};

std::string readDnaFromFile(const char* file_name);

void writeDnaToFile(DnaSequence&, const char* file_name);

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
//phase2
inline DnaSequence DnaSequence::slice(size_t start, size_t end)const
{
	if(end >= m_length || start < 0 || start > end)
		throw std::invalid_argument("index out of range");
	return DnaSequence(std::string((char*)m_sequence).substr(start, end));
}

inline DnaSequence DnaSequence::getPair()const
{
	char* seq = new char [m_length];
	 
	for(size_t i=0; i < m_length; i++)
	{
		seq[i] = m_sequence[m_length-i-1].getPair();
	}
	DnaSequence d(seq);
	delete [] seq;
	return d;
}

#endif
