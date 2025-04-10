// set을 재정의하여 풀면 되는 문제였다.

#include <unordered_map>
#include <algorithm>
#include <set>
#include <string>
#include <queue>

using namespace std;

struct Student {
	int score;
	int id;
  
	bool operator< (const Student &other) const {
		if (score == other.score) return id < other.id;
		return score < other.score;
	}
};

struct StudentInfo {
	int gender;
	int grade;
	int score;
	bool isRemove;
};

set<Student> student[2][4]; // 성별, 학년
unordered_map<int, StudentInfo> table;

void init() {
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j < 4; j++) {
			student[i][j].clear();
		}
	}
	table.clear();
}

int add(int mId, int mGrade, char mGender[7], int mScore) {
	if (string(mGender) == "male") {
		student[0][mGrade].insert({ mScore, mId });
		table[mId] = { 0, mGrade, mScore, false };
		return student[0][mGrade].rbegin()->id;
	}
	else {
		student[1][mGrade].insert({ mScore, mId });
		table[mId] = { 1, mGrade, mScore, false };
		return student[1][mGrade].rbegin()->id;
	}
}

int remove(int mId) {
	if (table.find(mId) == table.end() || table[mId].isRemove) return 0;
	int gender = table[mId].gender;
	int grade = table[mId].grade;
	int score = table[mId].score;
	table[mId].isRemove = true;
	student[gender][grade].erase(student[gender][grade].find({score, mId}));
	if (student[gender][grade].empty()) return 0;
	else return student[gender][grade].begin()->id;
}

int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7], int mScore) {
	set<Student> s;
	if (mGenderCnt == 2) {
		for (int i = 0; i < mGradeCnt; i++) {
			auto iter = student[0][mGrade[i]].lower_bound({ mScore, 0 });
			if (iter != student[0][mGrade[i]].end()) s.insert(*iter);
		}
		for (int i = 0; i < mGradeCnt; i++) {
			auto iter = student[1][mGrade[i]].lower_bound({ mScore, 0 });
			if (iter != student[1][mGrade[i]].end()) s.insert(*iter);
		}
	}
	else {
		if (string(mGender[0]) == "male") {
			for (int i = 0; i < mGradeCnt; i++) {
				auto iter = student[0][mGrade[i]].lower_bound({ mScore, 0 });
				if (iter != student[0][mGrade[i]].end()) s.insert(*iter);
			}
		}
		else {
			for (int i = 0; i < mGradeCnt; i++) {
				auto iter = student[1][mGrade[i]].lower_bound({ mScore, 0 });
				if (iter != student[1][mGrade[i]].end()) s.insert(*iter);
			}
		}
	}

	if (s.empty()) return 0;
	else return s.begin()->id;
}