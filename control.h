#ifndef CONTROL_H_
#define CONTROL_H_

#include <string>
#include <vector>
#include <QObject>

#include "editor.h"
#include "history.h"
#include "converter_p_10.h"

namespace Converter{
	enum State {
		Editing,
		Converted
	};

    class Control : public QObject {

        Q_OBJECT

    signals:
        void signal_number_changed(std::string& number);

	public:
		// Конструктор
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
            std::string result;
			if (j == 20)
			{
				std::string current_number = _ed.GetNumber();
                if(!current_number.empty())
                {
                    size_t dotPos = current_number.find('.');
                    if(dotPos != std::string::npos)
                        acc = current_number.size() - dotPos - 1;
                    else
                        acc = 0;
                    double r = Converter_P_10::Do(current_number, _Pin);
                    result = Converter_10_P::Do(r, _Pout, acc);
                    _st = Converted;
                    _his.AddRecord(_Pin, _Pout, current_number, result);
                    emit signal_number_changed(current_number);
                    return result;
                }
                else
                    return "";
            }
            else
			{
                if(j >= 1 && j <= 15 && j >= _Pin)
                {
                    result = _ed.DoEdit(-1);
                    emit signal_number_changed(result);
                    return result;
                }
                _st = Editing;
                result = _ed.DoEdit(j);
                emit signal_number_changed(result);
                return result;
			}
		}

	private:
		// С.сч. исходного числа
		int _Pin;

		// С.сч результата
		int _Pout;

		// Точность результата
		int acc;

		// Редактор
		Editor _ed;

		// История
		History _his;

		// Состояние конвертера
		State _st;
	};
}

#endif
