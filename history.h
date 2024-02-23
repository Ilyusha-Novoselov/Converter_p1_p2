#ifndef HISTORY_H_
#define HISTORY_H_

#include <string>
#include <vector>

namespace Converter {
	struct Record 
	{
		int p_1;
		int p_2;
		std::string number_1;
		std::string number_2;
	};

	class History {
	public:
		// �����������
		History() : _allRecords() {};

		// ���������� ������
		inline void AddRecord(int p_1, int p_2, std::string& number_1, std::string& number_2) { 
			//std::cout << number_1;
			Record record = { p_1, p_2, number_1, number_2 }; 
			_allRecords.push_back(record); 
		};

		// ������� �������
		inline void Clear() { _allRecords.clear(); };

		// ������� ������ ������ � ����� �������
		inline size_t Count() { return _allRecords.size(); };

		// �������� ������ �������
		inline std::vector<Record> get_allRecord() { return _allRecords; };

	private:
		// ������, ���������� ��� ������� ��������
		std::vector<Record> _allRecords;
	};
}

#endif