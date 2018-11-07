#define LONG_NUMBERS_INSIDE

#pragma once
#include <vector>
#include <ostream>
#include <istream>
#include <sstream>
#include <cmath>

namespace sjship
{
	typedef unsigned long long ull;

#if defined(LONG_NUMBERS_INSIDE) 
	class __declspec(dllexport) LongNumber
#else 
	class __declspec(dllimport) LongNumber
#endif
	{
		static const unsigned DEFAULT_CELL_SIZE = 9;

		unsigned m_CellSize;
		std::vector<unsigned> *m_ptrData;

		void readDigit(const char digit);

#if defined(LONG_NUMBERS_INSIDE) 
		friend __declspec(dllexport) std::istream& operator>>(std::istream& is, LongNumber& longNumber);
		friend __declspec(dllexport) std::ostream& operator<<(std::ostream& os, const LongNumber& longNumber);
#else 
		friend __declspec(dllimport) std::istream& operator>>(std::istream& is, LongNumber& longNumber);
		friend __declspec(dllimport) std::ostream& operator<<(std::ostream& os, const LongNumber& longNumber);
#endif

	public:
		LongNumber();
		explicit LongNumber(unsigned base);
		LongNumber(int value);
		LongNumber(long long value);
		LongNumber(const LongNumber& longNumber);
		LongNumber& operator=(const LongNumber& longNumber);

		std::string str() const;

		~LongNumber();
	};
}
