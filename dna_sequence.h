#ifndef __DNA_SEQUENCE_H__
#define __DNA_SEQUENCE_H__

#include <string>
#include <cstring>
#include <ostream>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>

class DnaSequence
{

friend std::ostream& operator<<(std::ostream&, const DnaSequence&);

private:
	class DnaChar{
	public:
		DnaChar(){}
		DnaChar(char c);
		DnaChar& operator=(DnaChar rv);
		operator char()const;
   		char getPair()const;
                                                                                                                                                                      
	private:
		char m_nucleotide;
		
	};
	
public:
	DnaSequence(const char *sequence);
	DnaSequence(const std::string &sequence);
	DnaSequence(const DnaSequence &other);
	~DnaSequence();

	DnaSequence& operator=(const DnaSequence &other);
	
	bool operator==(const DnaSequence &other)const;
	bool operator!=(const DnaSequence &other)const;
	
	const char operator[](size_t index)const;
	DnaChar& operator[](size_t index);
	
	size_t length()const;
//phase2
	DnaSequence slice(size_t, size_t)const;
	DnaSequence getPair()const;
	size_t find(const DnaSequence&, size_t start = 0)const;
	size_t countOccurrences(const DnaSequence&)const;
	std::vector<size_t> findAll(const DnaSequence&, size_t start = 0,bool by_codons = false)const;
	std::vector<DnaSequence> findConsesus()const;
	
private:
	void initField(const DnaChar *sequence, bool isOverriding);
	DnaChar *m_sequence;
	size_t m_length;
	
	void initField(const char* sequence, bool isOverriding = false);
	void checkIfNull(const void*)const;
	void checkIndexValidity(size_t)const;
	
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

inline std::ostream& operator<<(std::ostream& os, const DnaSequence& dna)
{
	for(size_t i=0; i<dna.m_length; os<<char(dna.m_sequence[i]), ++i);
	return os;
}


inline const char DnaSequence::operator[](size_t index)const
{
	checkIndexValidity(index);
	return m_sequence[index];
}
inline DnaSequence::DnaChar& DnaSequence::operator[](size_t index)
{
	checkIndexValidity(index);
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

inline size_t DnaSequence::find(const DnaSequence& sub, size_t start)const
{
	size_t len = m_length-sub.m_length;
	for(size_t i = start; i<len; ++i)
	{
		if(m_sequence[i] == sub[0])
		{
			size_t j = 1;
			for(; j < sub.m_length; ++j)
				if(m_sequence[i+j] != sub[j])
					break;
			if(j == sub.m_length)
				return i;
		}
	}
	return -1;
}

inline size_t DnaSequence::countOccurrences(const DnaSequence& sub)const
{	
	size_t count = 0;
	for(size_t i = find(sub); i != (size_t)-1; ++count, i=find(sub,i+1))
		std::cout<<"count:"<<count<<std::endl;
	return count;
}

inline std::vector<size_t> DnaSequence::findAll(const DnaSequence& sub,size_t start, bool by_codon)const
{
	std::vector<size_t> occurrIndex;
	for(size_t i = find(sub, start); i != (size_t)-1; occurrIndex.push_back(i), i=find(sub,i+1));///
	return occurrIndex;
}

inline std::vector<DnaSequence>  DnaSequence::findConsesus()const
{
	DnaSequence start_codon = "ATG";
	DnaSequence end_codons[] = {"TAG", "TAA", "TGA"};
	std::vector<DnaSequence> consensus;
	std::vector<size_t> startIndices = findAll(start_codon);
	for(std::vector<size_t>::const_iterator start = startIndices.begin();start < startIndices.end(); start++)
		for(int i=0; i<3;i++)
		{
			std::vector<size_t> end_indices = findAll(end_codons[i],*start, true);
			for(std::vector<size_t>::const_iterator end = end_indices.begin();end < end_indices.end(); end++)
			{
				if((*end-*start)%3==0)
					{std::cout<<*end<<","<<*start<<": "<<slice(*start, *end+3)<<std::endl;
					consensus.push_back(slice(*start, *end+2));}
			}
		}
	return consensus;
}

#endif
