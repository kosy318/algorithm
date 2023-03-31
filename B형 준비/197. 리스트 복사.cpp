#include <memory.h>
#include <string>
#include <unordered_map>

using namespace ::std;

const int MAX_MAKE_LIST = 10;
const int MAX_LENGTH = 200000;
const int MAX_ADDRESS = 6000;
const int MAX_CHANGE = 110000;

int init_number; // ���� �迭�� ��ȣ
int init_value[MAX_MAKE_LIST + 1][MAX_LENGTH + 1]; // ���� �迭(makeList() ���) ������ �״�� �����ϴ� �迭

int address_number; // ���ο� �迭�� ��ȣ(������ �迭 ��ȣ + 1)
unordered_map<string, int> address; // �迭 �̸� -> ���� �迭 ��ȣ mapping

int change_number; // ������� �߻��� "��ȭ event" ����(makeList, copyList, updateElement ��� ����)

pair<int, int> change_log[MAX_CHANGE + 1]; // ������� �߻��� "��ȭ event" ����
// makeList      : (-1, ���� �迭 ��ȣ)
// copyList      : (-1, -1) ���� �߰��ϱ�. (deepcopy�� �ǹ���)
// updateElement : (�ε���, ��); �ε����� ���� �����ߴ�.

int last_change[MAX_ADDRESS + 1]; // last_change[i] := i�� ���� �迭�� ������ ��ȭ event ��ȣ
int prev_change[MAX_CHANGE + 1]; // prev_change[i] := i�� ��ȭ�� ���� ��ȭ event ��ȣ

/*
 * [�������]
 * 1. �� �׽�Ʈ ���̽� ���� �� init() �Լ��� ȣ��ȴ�.
 * 2. �� �׽�Ʈ ���̽����� makeList() �Լ��� ȣ�� Ƚ���� 10 �����̴�.
 * 3. �� �׽�Ʈ ���̽����� copyList() �Լ��� ȣ�� Ƚ���� 5,000 �����̴�.
 * 4. �� �׽�Ʈ ���̽����� updateElement() �Լ��� ȣ�� Ƚ���� 100,000 �����̴�.
 * 5. �� �׽�Ʈ ���̽����� element() �Լ��� ȣ�� Ƚ���� 400 �����̴�.
 * 6. ����Ʈ�� �̸��� ���� 1 �̻�, 20 ������ ���ĺ� �ҹ��ڷ� �̷���� ���ڿ��̸�, ���ڿ��� ������ ����0���� �߰��Ǿ� �ִ�.
 * 7. �޸� ������ 256MB�̴�.
 */

 /*
  * �� �׽�Ʈ ���̽��� ó���� ȣ��ȴ�.
  * �׽�Ʈ ���̽��� ���� �� �����Ǿ� �ִ� ����Ʈ�� ����.
  */
void init() {
	// ���� �迭 �ʱ�ȭ
	init_number = 0;

	address_number = 0;
	address.clear();

	change_number = 0;
}

/*
 * mName ����Ʈ�� �����Ǿ� ���� ������ ����ȴ�.
 * mName ����Ʈ�� ���� �����Ѵ�.
 * mName ����Ʈ�� ���� ������ mLength���� �ȴ�.
 * mName ����Ʈ�� i��° ������ ���� mListValue[i]�� �ȴ�. ( 0 �� i �� mLength - 1 )

 * �����ؾ��� �۾��� ������ ���ÿ� ���� ��Ÿ����, �Ʒ��� ����.
 * > mName = [mListValue[0], mListValue[1], ��, mListValue[mLength - 1]]

 * Parameters
 * mName : ����Ʈ�� �̸� ( 1 �� ���� �� 20 )
 * mLength : ����Ʈ�� ���� ( 1 �� mLength �� 200,000 )
 * mListValue : ���ҵ��� �� ( 0 �� mListValue[i] �� 32,767 )
 */
void makeList(char mName[], int mLength, int mListValue[]) {
	// init_number ��°�� init_value�� mListValue�� �����Ͽ� �ִ´�.
	memcpy(init_value[init_number], mListValue, mLength * sizeof(int));
	init_number++; // ���� �迭 ��ȣ ����

	address[string(mName)] = address_number; // string(mName)�� �ش��ϴ� address_number�� �ο���
	address_number++;

	// ���� �̺�Ʈ ��ȣ�� �ش��ϴ� change_log�� prev_chanage�� ���� �ִ´�.
	// makeList      : (-1, ���� �迭 ��ȣ)
	// ���� �迭 ��ȣ�� 1 �������ױ� ������ 1 ����.
	change_log[change_number] = { -1, init_number - 1 };
	prev_change[change_number] = -1; // ����Ʈ�� ������� ���� ������ ���̹Ƿ� ������ �ٲ� ���� ���ٴ� ǥ�÷� -1�� �־��ش�.
	last_change[address[string(mName)]] = change_number; // ������� �迭�� ������ ��ȭ event ��ȣ�� change_number�̴�.
	change_number++; // �̺�Ʈ ��ȭ ��ȣ ����
}

/*
 * mDest ����Ʈ�� �����Ǿ� ���� ������ ����ȴ�.
 * mSrc ����Ʈ�� �����Ǿ� ������ ����ȴ�.

 * mDest ����Ʈ�� ���� �����Ѵ�.
 * mSrc ����Ʈ�� mDest ����Ʈ�� �����Ѵ�.

 * mCopy�� true�� ���, ���� ��� �����ϴ� ����� ����Ѵ�.
 * �̶� �����ؾ��� �۾��� ������ ���ÿ� ���� ��Ÿ����, �Ʒ��� ����.
 * > mDest = mSrc.copy()

 * mCopy�� false�� ���, �ּҸ� �����ϴ� ����� ����Ѵ�.
 * �̶� �����ؾ��� �۾��� ������ ���ÿ� ���� ��Ÿ����, �Ʒ��� ����.
 * > mDest = mSrc

 * Parameters
 * mDest : ����Ʈ�� �̸� ( 1 �� ���� �� 20 )
 * mSrc : ����Ʈ�� �̸� ( 1 �� ���� �� 20 )
 * mCopy : ���� ��� ( mCopy = true or false )
 */
void copyList(char mDest[], char mSrc[], bool mCopy) {
	if (mCopy) { // ���� ����
		address[string(mDest)] = address_number; // string(mName)�� �ش��ϴ� address_number�� �ο���
		address_number++;

		// ���� �̺�Ʈ ��ȣ�� �ش��ϴ� change_log�� prev_chanage�� ���� �ִ´�.
		// copyList      : (-1, -1) ���� �߰��ϱ�. (deepcopy�� �ǹ���)
		change_log[change_number] = { -1, -1 };
		prev_change[change_number] = last_change[address[string(mSrc)]]; // change_number�� ���� ��ȭ�� mSrc�� ������ ��ȭ�� ����.
		last_change[address[string(mDest)]] = change_number; // ������� �迭�� ������ ��ȭ event ��ȣ�� change_number�̴�.
		change_number++;
	}
	else { // ���� ����
		address[string(mDest)] = address[string(mSrc)]; // mDest�� address ��ȣ�� mSrc�� address ��ȣ�� �����ϸ� �ȴ�.
	}
}

/*
 * mName ����Ʈ�� mIndex��° ������ ���� mValue�� �����Ѵ�.

 * �����ؾ��� �۾��� ������ ���ÿ� ���� ��Ÿ����, �Ʒ��� ����.
 * > mName[mIndex] = mValue

 * mName ����Ʈ�� �����Ǿ� ������ ����ȴ�.

 * Parameters
 * mName : ����Ʈ�� �̸� ( 1 �� ���� �� 20 )
 * mIndex : ������ �ε��� ( 0 �� mIndex �� mName ����Ʈ�� ���� - 1 )
 * mValue : ������ ���� ���� �� ( 0 �� mValue �� 32,767 )
 */
void updateElement(char mName[], int mIndex, int mValue) {
	change_log[change_number] = { mIndex, mValue }; // mIndex�� mValue ������ �ٲܰŶ�� ���� ���
	prev_change[change_number] = last_change[address[string(mName)]]; // change_number�� ���� ��ȭ�� mSrc�� ������ ��ȭ�� ����.
	last_change[address[string(mName)]] = change_number; // ������� �迭�� ������ ��ȭ event ��ȣ�� change_number�̴�.
	change_number++;
}

/*
 * mName ����Ʈ�� mIndex��° ���Ҹ� ��ȯ�Ѵ�.

 * mName ����Ʈ�� �����Ǿ� ������ ����ȴ�.

 * Parameters
 * mName : ����Ʈ�� �̸� ( 1 �� ���� �� 20 )
 * mIndex : ������ �ε��� ( 0 �� mIndex �� mName ����Ʈ�� ���� - 1 )
 */
int element(char mName[], int mIndex) { // ȣ�� 400 ����
	int c = last_change[address[string(mName)]]; // ������ ��ȭ �̺�Ʈ�� �̵�
	while (true) {
		if (prev_change[c] == -1) { // ��ȭ�� ����. makeList�� ���� �α׸� ��������
			return init_value[change_log[c].second][mIndex];
		}
		if (change_log[c].first == mIndex) { // mIndex�� ���� ��ȭ event�� ã�� -> �̰� �ֽ� ����
			return change_log[c].second;
		}
		c = prev_change[c];
	}
}

/////////////////////////////////////////////////////////////////////////////////
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <iostream>

#define CMD_INIT 100
#define CMD_MAKE_LIST 200
#define CMD_COPY_LIST 300
#define CMD_UNDATE_ELEMENT 400
#define CMD_ELEMENT 500

extern void init();
extern void makeList(char mName[], int mLength, int mListValue[]);
extern void copyList(char mDest[], char mSrc[], bool mCopy);
extern void updateElement(char mName[], int mIndex, int mValue);
extern int element(char mName[], int mIndex);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static unsigned int mSeed;
static unsigned int pseudo_rand(void)
{
	mSeed = mSeed * 214013 + 2531011;
	return (mSeed >> 16) & 0x7FFF;
}

static char mName[21];
static char mDest[21];
static char mSrc[21];
static int mListValue[200000];

static void generateName(char *name, int seed)
{
	mSeed = seed;
	int name_len = pseudo_rand() % 20 + 1;
	for (int i = 0; i < name_len; ++i)
	{
		name[i] = pseudo_rand() % 26 + 'a';
	}
	name[name_len] = '\0';
}

static int generateList(int *listValue, int seed)
{
	mSeed = seed;
	int length = pseudo_rand() << 15;
	length = (length + pseudo_rand()) % 200000 + 1;
	for (int i = 0; i < length; ++i)
	{
		listValue[i] = pseudo_rand();
	}
	return length;
}

static bool run() {
	int num_query; // query ����

	int seed;
	int mIndex, mValue, mCopy, mLength;
	int user_ans, ans;
	bool is_correct = false;

	scanf_s("%d", &num_query);

	for (int i = 0; i < num_query; ++i) {
		int cmd;
		scanf_s("%d", &cmd);

		switch (cmd) {
		case CMD_INIT:
			init(); // �ʱ�ȭ
			is_correct = true;
			break;
		case CMD_MAKE_LIST:
			scanf_s("%d", &seed);
			generateName(mName, seed);
			scanf_s("%d", &seed);
			mLength = generateList(mListValue, seed);
			makeList(mName, mLength, mListValue);
			break;
		case CMD_COPY_LIST:
			scanf_s("%d", &seed);
			generateName(mDest, seed);
			scanf_s("%d", &seed);
			generateName(mSrc, seed);
			scanf_s("%d", &mCopy);
			copyList(mDest, mSrc, (mCopy != 0));
			break;
		case CMD_UNDATE_ELEMENT:
			scanf_s("%d", &seed);
			generateName(mName, seed);
			scanf_s("%d %d", &mIndex, &mValue);
			updateElement(mName, mIndex, mValue);
			break;
		case CMD_ELEMENT:
			scanf_s("%d", &seed);
			generateName(mName, seed);
			scanf_s("%d", &mIndex);
			user_ans = element(mName, mIndex);
			scanf_s("%d", &ans);
			if (user_ans != ans)
			{
				is_correct = false;
			}
			break;
		default:
			is_correct = false;
			break;
		}
	}
	return is_correct;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input_list_copy.txt", "r", stdin);

	int T, MARK;
	scanf_s("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}