#ifndef CONVERTER_P_10_H_
#define CONVERTER_P_10_H_

#include <string>
#include <algorithm>

namespace Converter {
	class Converter_P_10 {
	public:
		// Преобразовать цифру в число
		static double char_to_num(char ch);

		// Преобразовать из с.сч. с основанием p в с.сч. с основанием 10
		static double Do(std::string& P_num, int P);

	private:
		// Преобразовать строку в число
		static double convert(std::string& P_num, int P, double weight);
	};
}

#endif