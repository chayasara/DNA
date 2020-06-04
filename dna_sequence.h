#ifndef __DNA_SEQUENCE_H__
#define __DNA_SEQUENCE_H__

#include <string>
#include <cstring>
#include <ostream>
#include <iostream>

class DnaSequence
{

friend std::ostream& operator<<(std::ostream&, DnaSequence&);

private:
	class DnaChar{
	public:
		DnaChar(){}
		DnaChar(char c);
		DnaChar& operator=(DnaChar rv);
		char get_necleotide()const;
		
		                                                                                                                                                                            
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
	
	DnaChar const operator[](size_t index)const;
	DnaChar operator[](size_t index);
	size_t length()const;
	
	//char* get_sequence()const;
	
private:
	
	DnaChar *m_sequence;
	size_t m_sequence_length;
	
	
	
	void set(size_t index, char value);
	
	void initField(const DnaChar* sequence, bool isOverriding = false);
	void initField(const char* sequence, bool isOverriding = false);
	void checkIfNull(const char*)const;
	
	bool strcmp(DnaChar *, DnaChar *) const;
	
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
	for(size_t i=0; i<dna.m_sequence_length; ++i, os<<dna.m_sequence[i].get_necleotide());
	return os;
}


inline const DnaSequence::DnaChar DnaSequence::operator[](size_t index)const
{
	return m_sequence[index];
}

inline DnaSequence::DnaChar DnaSequence::operator[](size_t index)
{
	return m_sequence[index];
}

inline size_t DnaSequence::length()const
{
	return m_sequence_length;
}



#endif
