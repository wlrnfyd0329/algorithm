// updateTeam의 호출 횟수가 굉장히 많은데, 이것을 최적화하는 것이 중요한다.
// 따라서 Team마다 Score LinkedList를 만들어서 Score의 List끼리 합쳐버리면 update되는 것이 굉장히 빠를 것이다.
// 이렇게 구성한다면 updateSoldier가 느려질 가능성도 존재한다. 해당 메소드도 호출 횟수가 많기 때문에 느려지면 안된다.
// 그 병사를 조회하는 것이 느려지기 때문이다. 따라서 병사의 상태를 관리하는 메소드를 만들어두면 빠르게 조회할 수 있다.
// lazy하게 진행하는 것이 중요한 포인트다.

// 해당 코드는 병사 배열을 만들어서 직접 조회한다.

const int MAX_SOLDIER = 100000;
const int  MAX_TEAM = 5;
const int  MAX_SCORE = 5;

struct Node {
	int id;
	int team; //score가 아니고 team, 왜냐면 score는 group에서 관리하니까 병사를 조회할 때, 어디 팀인지 알아야지 group에서 조회 가능하다.

	Node* prev;
	Node* nxt;
} soldier[MAX_SOLDIER + 1];

struct List {
	Node head;
	Node tail;

	void static link(Node* front, Node* back) {
		front->nxt = back;
		back->prev = front;
	}

	void insert(Node* node) { // link를 만든 이유를 잘 생각해 보시라
		link(tail.prev, node);
		// tail.prev->nxt = node;
		// node->prev = tail.prev;
		link(node, &tail);
		// node->nxt = &tail;
		// tail.prev = node;
	}

	void static erase(Node* node) {
		link(node->prev, node->nxt);
	}

	void initialize() {
		link(&head, &tail);
	}

	bool isEmpty() {
		return (head.nxt == &tail);
	}

	void splice(List *list) { //head와 tail은 건드리면 안됨
		if (list->isEmpty()) return;
		link(tail.prev, list->head.nxt);
		link(list->tail.prev, &tail);
		list->initialize();
	}

} group[MAX_TEAM + 1][MAX_SCORE + 1];

void init()
{
	for (int i = 1; i <= MAX_TEAM; i++)
		for (int j = 1; j <= MAX_SCORE; j++)
			group[i][j].initialize();
}

void hire(int mID, int mTeam, int mScore)
{
	soldier[mID].id = mID;
	soldier[mID].team = mTeam;
	group[mTeam][mScore].insert(soldier + mID);
}

void fire(int mID)
{
	List::erase(soldier + mID); // 해당 병사 앞 뒤로만 이어주면 group에서 삭제되는 것임
}

void updateSoldier(int mID, int mScore)
{
	List::erase(soldier + mID);
	group[soldier[mID].team][mScore].insert(soldier + mID);
}

void updateTeam(int mTeam, int mChangeScore)
{
	if (mChangeScore > 0) {
		// updateTeam은 score를 머지하기 때문에 증가할때, 역순으로 하지 않으면
		// 1->2로 붙었는데 2->3으로 붙이면 1->3으로 붙는 것이 되니까 오류가 생김
		for (int i = MAX_SCORE - 1; i >= 1; i--) {
			if (i + mChangeScore >= 5) {
				group[mTeam][5].splice(&group[mTeam][i]);
			}
			else {
				group[mTeam][i + mChangeScore].splice(&group[mTeam][i]);
			}
		}
	}
	else if (mChangeScore < 0) {
		for (int i = 2; i <= MAX_SCORE; i++) {
			if (i + mChangeScore <= 1) {
				group[mTeam][1].splice(&group[mTeam][i]);
			}
			else {
				group[mTeam][i + mChangeScore].splice(&group[mTeam][i]);
			}
		}
	}
}

int bestSoldier(int mTeam)
{
	int max_score;
	int max_id = 0;
	Node* start;
	for (int i = MAX_SCORE; i >= 1; i--) {
		if (!group[mTeam][i].isEmpty()) {
			max_score = i;
			break;
		}
	}
	start = group[mTeam][max_score].head.nxt;
	while (start != &group[mTeam][max_score].tail) {
		if (start->id > max_id) {
			max_id = start->id;
		}
		start = start->nxt;
	}
	return max_id;
}