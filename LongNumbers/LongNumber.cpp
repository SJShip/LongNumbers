#include "LongNumber.h"

using std::vector;
using std::ostream;
using std::istream;

using namespace sjship;

ostream& sjship::operator<<(ostream& os, const LongNumber& longNumber)
{
	for (auto it = longNumber.m_ptrData->rbegin(); it != longNumber.m_ptrData->rend(); ++it)
	{
		int cellValue = *it;

		if (it != longNumber.m_ptrData->rbegin())
		{
			// Don't forget about leading zeros
			std::string s = std::to_string(*it);
			int i = 0;
			while (s.length() + i < longNumber.m_CellSize)
			{
				os << 0;
				i++;
			}
		}
		os << *it;
	}
	return os;
}

LongNumber sjship::operator+(const LongNumber & a, const LongNumber & b)
{
	return LongNumber::sum(a,b);
}

bool sjship::operator==(LongNumber & a, LongNumber & b)
{
	// we cannot rely on cell values comparison because a and b could have different cell size.
	return a.str() == b.str();
}

istream& sjship::operator>>(istream & is, LongNumber & longNumber)
{
	char ch;
	while (is >> ch && ch >= '0' and ch <= '9')
	{
		longNumber.readDigit(ch);
	}
	return is;
}

void LongNumber::readDigit(const char digit)
{
	int base = pow(10, m_CellSize);
	auto size = m_ptrData->size();
	for (auto i = size; i > 0; i--)
	{
		ull large = static_cast<ull>(m_ptrData->at(i - 1)) * 10;
		unsigned tempDiv =  large / base;
		unsigned tempMod = large % base;

		if (tempDiv > 0)
		{
			if (i == size)
			{
				m_ptrData->resize(size + 1, 0);
			}
			m_ptrData->at(i) +=  tempDiv;
		}

		m_ptrData->at(i - 1) = tempMod;
	}

	if (size > 0)
	{
		m_ptrData->at(0) += digit - '0';
	}
	else
	{
		m_ptrData->push_back(digit - '0');
	}
}

LongNumber sjship::LongNumber::sum(const LongNumber& a, const LongNumber& b)
{
	int base = pow(10, a.m_CellSize);

	LongNumber s;
	auto maxSize = std::max(a.m_ptrData->size(), b.m_ptrData->size());
	a.m_ptrData->resize(maxSize, 0);
	b.m_ptrData->resize(maxSize, 0);
	s.m_ptrData->resize(maxSize, 0);

	for (auto i = 0; i< maxSize; i++)
	{
		ull largeSum = static_cast<ull>(a.m_ptrData->at(i)) + b.m_ptrData->at(i) + s.m_ptrData->at(i);

		if (largeSum >= base && i == maxSize - 1)
		{
			s.m_ptrData->resize(maxSize + 1, 0);
		}

		if (largeSum >= base)
		{
			// we are sure that we have already resized the vector to appropriate size.
			s.m_ptrData->at(i + 1) = largeSum / base;
		}

		s.m_ptrData->at(i) = largeSum % base;
	}

	return s;
}

LongNumber::LongNumber(): LongNumber(DEFAULT_CELL_SIZE) {}

LongNumber::LongNumber(unsigned base): m_CellSize(base)
{
	m_ptrData = new vector<unsigned>;
}

LongNumber::LongNumber(int value): LongNumber()
{
	std::stringstream ss;
	ss << value;
	char ch;
	while (ss >> ch)
	{
		readDigit(ch);
	}
}

LongNumber::LongNumber(long long value): LongNumber()
{
	std::stringstream ss;
	ss << value;
	char ch;
	while (ss >> ch)
	{
		readDigit(ch);
	}
}

sjship::LongNumber::LongNumber(const LongNumber & longNumber)
{
	m_CellSize = longNumber.m_CellSize;
	m_ptrData = new vector<unsigned>(*longNumber.m_ptrData);
}

LongNumber& LongNumber::operator=(const LongNumber& longNumber)
{
	if (this != &longNumber)
	{
		delete m_ptrData;

		m_CellSize = longNumber.m_CellSize;
		m_ptrData = new vector<unsigned>(*longNumber.m_ptrData);
	}
	return *this;
}

LongNumber & sjship::LongNumber::operator+=(const LongNumber & longNumber)
{
	LongNumber newValue = sum(*this, longNumber);

	*this = newValue;

	return *this;
}

LongNumber & sjship::LongNumber::operator++()
{
	LongNumber newValue = sum(*this, 1);

	*this = newValue;

	return *this;
}

LongNumber & sjship::LongNumber::operator++(int)
{
	LongNumber* value = new LongNumber(*this);
	*this = sum(*value, 1);

	return *value;
}


std::string sjship::LongNumber::str() const
{
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

LongNumber::~LongNumber()
{
	delete m_ptrData;
	m_ptrData = 0;
}
