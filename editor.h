#ifndef EDITOR_H_
#define EDITOR_H_

#include <string>
#include <algorithm>

#include "converter_10_p.h"

namespace Converter {
	class Editor {
	public:
		// �������� �����
		inline void AddDigit(int n) { _number.push_back(Converter_10_P::int_to_char(n)); };

		// �������� ����
        inline void AddZero() { if (!_number.empty()) _number += _zero; };

        // �������� �����������
        inline void AddDelim() { if (_number.find('.') == std::string::npos && !_number.empty()) _number += _delim; };

        // ������� ������
        inline void Bs() { if(!_number.empty()) _number.pop_back(); };

		// �������� ������������� �����
		inline void Clear() { _number.clear(); };

		// ����� ������ �������
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

		// �������� ����������������� �����
		inline std::string GetNumber() { return _number; };

	private:
		// ���� ��� �������� �������������� �����
		std::string _number = "";

		// ����������� ����� � ������� �����
		const std::string _delim = ".";

		// ����
		const std::string _zero = "0";
	};
}

#endif
