#ifndef EDITOR_H_
#define EDITOR_H_

#include <string>
#include <algorithm>

#include "converter_10_p.h"

namespace Converter {
	class Editor {
	public:
		// Добавить цифру
		inline void AddDigit(int n) { _number.push_back(Converter_10_P::int_to_char(n)); };

		// Добавить ноль
        inline void AddZero() { if (!_number.empty()) _number += _zero; };

        // Добавить разделитель
        inline void AddDelim() { if (_number.find('.') == std::string::npos && !_number.empty()) _number += _delim; };

        // Удалить символ
        inline void Bs() { if(!_number.empty()) _number.pop_back(); };

		// Очистить редактируемое число
		inline void Clear() { _number.clear(); };

		// Вызов нужной команды
		std::string DoEdit(int j) 
		{
            if(j == -1)
                return _number;

            if (j <= 15 && j != 0)
			{
				AddDigit(j);
				return _number;
			}

			switch (j)
			{
            case 0:
				AddZero();
				return _number;

			case 17:
				AddDelim();
				return _number;

			case 18:
				Bs();
				return _number;

			case 19:
				Clear();
				return _number;

			default:
                return _number;
			}
		}

		// Получить отредактированное число
		inline std::string GetNumber() { return _number; };

	private:
		// Поле для хранения редактируемого числа
		std::string _number = "";

		// Разделитель целой и дробной части
		const std::string _delim = ".";

		// Ноль
		const std::string _zero = "0";
	};
}

#endif
