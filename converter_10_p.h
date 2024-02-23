#ifndef CONVERTER_10_P_H_
#define CONVERTER_10_P_H_

#include <string>
#include <algorithm>

namespace Converter {
	class Converter_10_P {
	public:
		// ������������� ����� � ������
		static char int_to_char(int n);

		// ������������� ���������� ����� � �.��. � ���������� p
		static std::string int_to_P(int n, int p);

		// ������������� ���������� ����� � �.��. � ���������� p
		static std::string double_to_P(double n, int  p, int c);

		// ������������� ���������� �������������� ����� � �.��. � ���������� p
		static std::string Do(double n, int p, int c);
	};
}

#endif