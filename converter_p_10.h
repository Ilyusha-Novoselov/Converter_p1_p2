#ifndef CONVERTER_P_10_H_
#define CONVERTER_P_10_H_

#include <string>
#include <algorithm>

namespace Converter {
	class Converter_P_10 {
	public:
		// ������������� ����� � �����
		static double char_to_num(char ch);

		// ������������� �� �.��. � ���������� p � �.��. � ���������� 10
		static double Do(std::string& P_num, int P);

	private:
		// ������������� ������ � �����
		static double convert(std::string& P_num, int P, double weight);
	};
}

#endif