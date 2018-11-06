#include "LongNumber.h"

using std::vector;
using std::ostream;
using std::istream;

using namespace sjship;

LongNumber::LongNumber(): LongNumber(DEFAULT_BASE) {}

LongNumber::LongNumber(unsigned base): m_base(base)
{
	m_ptrData = new vector<unsigned>;
}

sjship::LongNumber::LongNumber(int value)
{

}

LongNumber::~LongNumber()
{
	delete m_ptrData;
	m_ptrData = 0;
}

ostream& sjship::operator<<(ostream& os, const LongNumber& longNumber)
{
	for (auto it = longNumber.m_ptrData->rbegin(); it != longNumber.m_ptrData->rend(); ++it)
	{
		os << *it;
	}
	return os;
}

istream& sjship::operator>>(istream & is, const LongNumber & longNumber)
{
	vector<unsigned>* ptrV = longNumber.m_ptrData;
	char ch;
	while (is >> ch && ch >= '0' and ch <='9')
	{
		auto size = ptrV->size();
		for (auto i = size; i > 0; i--)
		{
			ull large = static_cast<ull>(ptrV->at(i - 1)) * 10;
			unsigned tempDiv =  large / longNumber.m_base;
			unsigned tempMod = large % longNumber.m_base;

			if (tempDiv > 0)
			{
				if (i == size)
				{
					ptrV->resize(size + 1, 0);
				}
				ptrV->at(i) +=  tempDiv;
			}

			ptrV->at(i - 1) = tempMod;
		}

		if (size > 0)
		{
			ptrV->at(0) += ch - '0';		
		} else 
		{
			ptrV->push_back(ch- '0');
		}
	}
	return is;
}
