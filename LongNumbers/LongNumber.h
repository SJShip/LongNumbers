#define LONG_NUMBERS_INSIDE

#pragma once
#include <vector>
#include <ostream>
#include <istream>

namespace sjship
{
	typedef unsigned long long ull;

#if defined(LONG_NUMBERS_INSIDE) 
	class __declspec(dllexport) LongNumber
#else 
	class __declspec(dllimport) LongNumber
#endif
	{
		static const unsigned DEFAULT_BASE = 1000000000;

		unsigned m_base;

		std::vector<unsigned> *m_ptrData;

#if defined(LONG_NUMBERS_INSIDE) 
		friend __declspec(dllexport) std::istream& operator>>(std::istream& is, const LongNumber& longNumber);
		friend __declspec(dllexport) std::ostream& operator<<(std::ostream& os, const LongNumber& longNumber);
#else 
		friend __declspec(dllimport) std::istream& operator>>(std::istream& is, const LongNumber& longNumber);
		friend __declspec(dllimport) std::ostream& operator<<(std::ostream& os, const LongNumber& longNumber);
#endif

	public:

		LongNumber();
		explicit LongNumber(unsigned base);
		LongNumber(int value);
		~LongNumber();
	};
}
