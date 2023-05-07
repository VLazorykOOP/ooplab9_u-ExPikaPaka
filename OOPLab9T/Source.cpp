#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>

struct GymUsers {
	int id;
	int year;
	int month;
	int duration;

	struct ByYear {
		bool operator ()(const GymUsers& a, const GymUsers& b) const {
			return a.year < b.year;
		}
	};
	struct ByMonth {
		bool operator ()(const GymUsers& a, const GymUsers& b) const {
			return a.month < b.month;
		}
	};
};

struct TimeStat {
	TimeStat(int _avgDur, int _year, int _month) {
		avgDur = _avgDur;
		year = _year;
		month = _month;
	}

	int avgDur;
	int year;
	int month;

	struct ByAvgDur {
		bool operator ()(const TimeStat& a, const TimeStat& b) const {
			return a.avgDur < b.avgDur;
		}
	};
	struct ByYear {
		bool operator ()(const TimeStat& a, const TimeStat& b) const {
			return a.year > b.year;
		}
	};
	struct ByMonth {
		bool operator ()(const TimeStat& a, const TimeStat& b) const {
			return a.month < b.month;
		}
	};
};


void task1() {
	std::string fileName = "input.txt";
	std::ifstream ifs(fileName);

	if (!ifs.is_open()) { // No file check
		std::cout << "Can't open file " << fileName;
		exit(-1);
	}

	// Parsing file
	std::vector<GymUsers> users;
	std::string line;
	while (!ifs.eof()) {
		GymUsers user;
		ifs >> user.id;
		ifs >> user.year;
		ifs >> user.month;
		ifs >> user.duration;

		users.push_back(user);
	}




	// Statistics
	std::vector<TimeStat> tst;
	int minYear = std::min_element(users.begin(), users.end(), GymUsers::ByYear())->year;
	int maxYear = std::max_element(users.begin(), users.end(), GymUsers::ByYear())->year;
	int maxMonthLastYear = users.back().month;

	for (int year = minYear; year <= maxYear; year++) {
		for (int month = 1; month < (year == maxYear ? maxMonthLastYear + 1 : 13); month++) {
			int avgDur = 0;
			for (auto& user : users) {
				avgDur += user.year == year && user.month == month ? user.duration : 0;
			}
			tst.push_back(TimeStat(avgDur, year, month));
		}
	}


	// Sorting
	std::sort(tst.begin(), tst.end(), TimeStat::ByAvgDur());


	bool fmatch = true;
	int sortFrom = 0;
	int sortTo = 0;

	for (int i = 0; i < tst.size() - 1; i++) {
		if (tst.at(i).avgDur == tst.at(i + 1).avgDur) {
			if (fmatch) {
				sortFrom = i;
				fmatch = false;
			}
			sortTo = i + 1;
		} else {
			fmatch = true;
			std::cout << "Sorting in [" << sortFrom << "-" << sortTo << "]\n";
			std::sort(tst.begin() + sortFrom, tst.begin() + sortTo + 1, TimeStat::ByYear());
		}
	}


	// Output
	for (auto& stat : tst) {
		std::cout << "Avg.: " << stat.avgDur << "  year: " << stat.year << "  month: " << stat.month << '\n';
	}
	std::cout << "\nTotal entries " << tst.size() << '\n';
	std::cout << "Min year " << minYear << "\nMax year " << maxYear << "\nLast month " << maxMonthLastYear << '\n';
	ifs.close();
}



void task2() {
	std::vector<int> v = { 11, 14, 15, 16, 17, 17, 18, 10 };
	std::deque<int> d = { 1, 2, 3, 4, 5, 6 };

	std::cout << "vec:          ";
	for (auto& el : v) {
		std::cout << el << " ";
	}
	std::cout << "\n              ";
	for (auto& el : v) {
		std::cout << el % 2 << (el > 9 ? "  " : " ");
	}


	std::cout << "\n\ndec:          ";
	for (auto& el : d) {
		std::cout << el << " ";
	}
	std::cout << "\n              ";
	for (auto& el : d) {
		std::cout << el % 2 << " ";
	}
	std::cout << '\n';
	


	// Definig order in deque
	std::cout << "\nDeqOrder:     ";
	bool* deqOddOrder = new bool[d.size() / 2];
	for (int i = 0; i < d.size() / 2; i++) {
		deqOddOrder[i] = d.at(i) % 2;
		std::cout << deqOddOrder[i] << ' ';
	}
	std::cout << "\n\n";


	// Clearing last group in vector, if it matches deque
	int matchCnt = 0;
	for (int i = v.size() - 1; i > 0; i--) {
		std::cout << "Check " << i << "    " << (v.at(i) % 2 ? 1 : 0) << " == " << deqOddOrder[d.size() / 2 - 1 - matchCnt];
		if ((v.at(i) % 2 ? 1 : 0) == deqOddOrder[d.size() / 2 - 1 - matchCnt]) {
			std::cout << "  true" << '\n';
			matchCnt++;

			if (((v.at(i - 1) % 2 ? 1 : 0) != deqOddOrder[d.size() / 2 - 1 - matchCnt]) && matchCnt != d.size() / 2) {
				matchCnt--;
			}
		} else {
			std::cout << "  false" << '\n';
			matchCnt = 0;
		
		}
		if (matchCnt == d.size() / 2) {
			std::cout << "Found group in [" << i << "-" << i + matchCnt - 1 << "]\n";
			v.erase(v.begin() + i, v.begin() + i + matchCnt);
			break;
		}
	}



	// Output
	std::cout << "\nModified vec: ";
	for (auto elem : v) {
		std::cout << elem << ' ';
	}

	delete[] deqOddOrder;
}






void task3() {
	std::vector<int> V = { 5, 7, 2, 8, 4, 7, 3, 1, 9 };
	std::cout << "Vector:   ";
	std::copy(V.begin(), V.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << '\n';

	std::sort(V.begin(), V.end());

	auto max_first = std::lower_bound(V.begin(), V.end(), V.back());
	auto max_last = std::upper_bound(V.begin(), V.end(), V.back());

	auto min_first = std::lower_bound(V.begin(), V.end(), V.front());
	auto min_last = std::upper_bound(V.begin(), V.end(), V.front());

	std::cout << "Sorted:   ";
	std::copy(V.begin(), V.end(), std::ostream_iterator<int>(std::cout, " "));

	std::cout << "\nModified: ";
	std::copy(min_last, max_first, std::ostream_iterator<int>(std::cout, " "));
}
 


int main() {
	std::string ch;

	while (ch != "4") {
		std::cout << "\n\nEnter task number. (1-3)  (4 to exit): ";
		std::cin >> ch;

		if (ch == "1") {
			task1();
		}
		if (ch == "2") {
			task2();
		}
		if (ch == "3") {
			task3();
		}
	}
}