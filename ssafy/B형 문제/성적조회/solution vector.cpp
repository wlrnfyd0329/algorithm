#include <unordered_map>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct Student {
	int score;
	int id;
  
	bool operator< (const Student &other) const {
		if (score == other.score) return id > other.id;
		return score > other.score;
	}
};

struct StudentInfo {
	int gender;
	int grade;
	int score;
	bool isRemove;
};

vector<Student> student[2][4]; // 성별, 학년
unordered_map<int, StudentInfo> table;

void init() {
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j < 4; j++) {
			student[i][j].clear();
		}
	}
	table.clear();
}

int bs(int score, int id, int gender, int grade) {
	int lf = 0, rg = student[gender][grade].size() - 1;
	while (lf <= rg) {
		int mid = (lf + rg) >> 1;
		if (student[gender][grade][mid].score == score) {
			if (student[gender][grade][mid].id < id) {
				lf = mid + 1;
			}
			else {
				rg = mid - 1;
			}
		}
		else {
			if (student[gender][grade][mid].score < score) {
				lf = mid + 1;
			}
			else {
				rg = mid - 1;
			}
		}
	}

	return lf;
}

int bs2(int score, int gender, int grade) {
	int lf = 0, rg = student[gender][grade].size() - 1;
	while (lf <= rg) {
		int mid = (lf + rg) >> 1;
		if (student[gender][grade][mid].score < score) {
			lf = mid + 1;
		}
		else {
			rg = mid - 1;
		}
	}

	return lf;
}

int add(int mId, int mGrade, char mGender[7], int mScore) {
	if (string(mGender) == "male") {
		int idx = bs(mScore, mId, 0, mGrade);
		student[0][mGrade].insert(student[0][mGrade].begin() + idx, { mScore, mId });
		table[mId] = { 0, mGrade, mScore, false };
		return student[0][mGrade].back().id;
	}
	else { // vector를 insert할때 end 범위까지는 해주는데 그거보다 초과하면 안됨
		int idx = bs(mScore, mId, 1, mGrade);
		// if (idx == student[1][mGrade].size()) {
		// 	student[1][mGrade].push_back({ mScore, mId });
		// 	table[mId] = { 1, mGrade, mScore, false };
		// }
		// else {
		// 	student[1][mGrade].insert(student[1][mGrade].begin() + idx, { mScore, mId });
		// 	table[mId] = { 1, mGrade, mScore, false };
		// }
		student[1][mGrade].insert(student[1][mGrade].begin() + idx, { mScore, mId });
		table[mId] = { 1, mGrade, mScore, false };
		return student[1][mGrade].back().id;
	}
}

int remove(int mId) {
	if (table.find(mId) == table.end() || table[mId].isRemove) return 0;
	int gender = table[mId].gender;
	int grade = table[mId].grade;
	int score = table[mId].score;
	table[mId].isRemove = true;
	int idx = bs(score, mId, gender, grade);
	student[gender][grade].erase(student[gender][grade].begin() + idx);
	if (student[gender][grade].empty()) return 0;
	else return student[gender][grade].front().id;
}

int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7], int mScore) {
	priority_queue<Student> pq;
	if (mGenderCnt == 2) {
		for (int i = 0; i < mGradeCnt; i++) {
			int idx = bs2(mScore, 0, mGrade[i]);
			if (idx != student[0][mGrade[i]].size()) pq.push(student[0][mGrade[i]][idx]);
		}
		for (int i = 0; i < mGradeCnt; i++) {
			int idx = bs2(mScore, 1, mGrade[i]);
			if (idx != student[1][mGrade[i]].size()) pq.push(student[1][mGrade[i]][idx]);
		}
	}
	else {
		if (string(mGender[0]) == "male") {
			for (int i = 0; i < mGradeCnt; i++) {
				int idx = bs2(mScore, 0, mGrade[i]);
				if (idx != student[0][mGrade[i]].size()) pq.push(student[0][mGrade[i]][idx]);
			}
		}
		else {
			for (int i = 0; i < mGradeCnt; i++) {
				int idx = bs2(mScore, 1, mGrade[i]);
				if (idx != student[1][mGrade[i]].size()) pq.push(student[1][mGrade[i]][idx]);
			}
		}
	}

	if (pq.empty()) return 0;
	else return pq.top().id;
}