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
