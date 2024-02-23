#ifndef CONTROL_H_
#define CONTROL_H_

#include <string>
#include <vector>

#include "editor.h"
#include "history.h"

namespace Converter {
	enum State {
		Editing,
		Converted
	};

	class Control {
	public:
		// �����������
		Control() : _Pin(10), _Pout(16), acc(3), _ed(), _his(), _st(Editing) {};

		inline int get_Pin() const { return _Pin; };

		inline void set_Pin(int pin) { _Pin = pin; };

		inline int get_Pout() const { return _Pout; };

		inline void set_Pout(int pout) { _Pout = pout; };

		inline int get_state() const { return _st; };

		inline void set_state(State st) { _st = st; };

		inline std::vector<Record> get_history() { return _his.get_allRecord(); };

		std::string DoCommand(int j) 
		{
			if (j == 20)
			{
				std::string current_number = _ed.GetNumber();
				double r = Converter_P_10::Do(current_number, _Pin);
				std::string res = Converter_10_P::Do(r, _Pout, acc);
				_st = Converted;
				_his.AddRecord(_Pin, _Pout, current_number, res);
				return res;
			}
			else 
			{
                if(j >= 1 && j <= 15 && j >= _Pin)
                    return _ed.DoEdit(-1);
                _st = Editing;
                return _ed.DoEdit(j);
			}
		}

	private:
		// �.��. ��������� �����
		int _Pin;

		// �.�� ����������
		int _Pout;

		// �������� ����������
		int acc;

		// ��������
		Editor _ed;

		// �������
		History _his;

		// ��������� ����������
		State _st;
	};
}

#endif