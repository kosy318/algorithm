#include <memory.h>
#include <string>
#include <unordered_map>

using namespace ::std;

const int MAX_MAKE_LIST = 10;
const int MAX_LENGTH = 200000;
const int MAX_ADDRESS = 6000;
const int MAX_CHANGE = 110000;

int init_number; // 원본 배열의 번호
int init_value[MAX_MAKE_LIST + 1][MAX_LENGTH + 1]; // 원본 배열(makeList() 당시) 정보를 그대로 저장하는 배열

int address_number; // 새로운 배열의 번호(마지막 배열 번호 + 1)
unordered_map<string, int> address; // 배열 이름 -> 원본 배열 번호 mapping

int change_number; // 현재까지 발생한 "변화 event" 개수(makeList, copyList, updateElement 모두 포함)

pair<int, int> change_log[MAX_CHANGE + 1]; // 현재까지 발생한 "변화 event" 정보
// makeList      : (-1, 원본 배열 번호)
// copyList      : (-1, -1) 정보 추가하기. (deepcopy를 의미함)
// updateElement : (인덱스, 값); 인덱스의 값을 변경했다.

int last_change[MAX_ADDRESS + 1]; // last_change[i] := i번 원본 배열의 마지막 변화 event 번호
int prev_change[MAX_CHANGE + 1]; // prev_change[i] := i번 변화의 직전 변화 event 번호

/*
 * [제약사항]
 * 1. 각 테스트 케이스 시작 시 init() 함수가 호출된다.
 * 2. 각 테스트 케이스에서 makeList() 함수의 호출 횟수는 10 이하이다.
 * 3. 각 테스트 케이스에서 copyList() 함수의 호출 횟수는 5,000 이하이다.
 * 4. 각 테스트 케이스에서 updateElement() 함수의 호출 횟수는 100,000 이하이다.
 * 5. 각 테스트 케이스에서 element() 함수의 호출 횟수는 400 이하이다.
 * 6. 리스트의 이름은 길이 1 이상, 20 이하의 알파벳 소문자로 이루어진 문자열이며, 문자열의 끝에는 ‘＼0’이 추가되어 있다.
 * 7. 메모리 제한은 256MB이다.
 */

 /*
  * 각 테스트 케이스의 처음에 호출된다.
  * 테스트 케이스의 시작 시 생성되어 있는 리스트는 없다.
  */
void init() {
	// 원본 배열 초기화
	init_number = 0;

	address_number = 0;
	address.clear();

	change_number = 0;
}

/*
 * mName 리스트가 생성되어 있지 않음이 보장된다.
 * mName 리스트를 새로 생성한다.
 * mName 리스트의 원소 개수는 mLength개가 된다.
 * mName 리스트의 i번째 원소의 값은 mListValue[i]가 된다. ( 0 ≤ i ≤ mLength - 1 )

 * 수행해야할 작업을 본문의 예시와 같이 나타내면, 아래와 같다.
 * > mName = [mListValue[0], mListValue[1], …, mListValue[mLength - 1]]

 * Parameters
 * mName : 리스트의 이름 ( 1 ≤ 길이 ≤ 20 )
 * mLength : 리스트의 길이 ( 1 ≤ mLength ≤ 200,000 )
 * mListValue : 원소들의 값 ( 0 ≤ mListValue[i] ≤ 32,767 )
 */
void makeList(char mName[], int mLength, int mListValue[]) {
	// init_number 번째의 init_value에 mListValue를 복사하여 넣는다.
	memcpy(init_value[init_number], mListValue, mLength * sizeof(int));
	init_number++; // 원본 배열 번호 증가

	address[string(mName)] = address_number; // string(mName)에 해당하는 address_number를 부여함
	address_number++;

	// 현재 이벤트 번호에 해당하는 change_log와 prev_chanage에 값을 넣는다.
	// makeList      : (-1, 원본 배열 번호)
	// 원본 배열 번호를 1 증가시켰기 때문에 1 뺀다.
	change_log[change_number] = { -1, init_number - 1 };
	prev_change[change_number] = -1; // 리스트가 만들어져 새로 생성된 것이므로 이전에 바뀐 것은 없다는 표시로 -1을 넣어준다.
	last_change[address[string(mName)]] = change_number; // 만들어진 배열의 마지막 변화 event 번호는 change_number이다.
	change_number++; // 이벤트 변화 번호 증가
}

/*
 * mDest 리스트가 생성되어 있지 않음이 보장된다.
 * mSrc 리스트가 생성되어 있음이 보장된다.

 * mDest 리스트를 새로 생성한다.
 * mSrc 리스트를 mDest 리스트에 복사한다.

 * mCopy가 true인 경우, 값을 모두 복사하는 방식을 사용한다.
 * 이때 수행해야할 작업을 본문의 예시와 같이 나타내면, 아래와 같다.
 * > mDest = mSrc.copy()

 * mCopy가 false인 경우, 주소만 복사하는 방식을 사용한다.
 * 이때 수행해야할 작업을 본문의 예시와 같이 나타내면, 아래와 같다.
 * > mDest = mSrc

 * Parameters
 * mDest : 리스트의 이름 ( 1 ≤ 길이 ≤ 20 )
 * mSrc : 리스트의 이름 ( 1 ≤ 길이 ≤ 20 )
 * mCopy : 복사 방식 ( mCopy = true or false )
 */
void copyList(char mDest[], char mSrc[], bool mCopy) {
	if (mCopy) { // 깊은 복사
		address[string(mDest)] = address_number; // string(mName)에 해당하는 address_number를 부여함
		address_number++;

		// 현재 이벤트 번호에 해당하는 change_log와 prev_chanage에 값을 넣는다.
		// copyList      : (-1, -1) 정보 추가하기. (deepcopy를 의미함)
		change_log[change_number] = { -1, -1 };
		prev_change[change_number] = last_change[address[string(mSrc)]]; // change_number의 이전 변화는 mSrc의 마지막 변화와 같다.
		last_change[address[string(mDest)]] = change_number; // 만들어진 배열의 마지막 변화 event 번호는 change_number이다.
		change_number++;
	}
	else { // 얕은 복사
		address[string(mDest)] = address[string(mSrc)]; // mDest의 address 번호와 mSrc의 address 번호를 같게하면 된다.
	}
}

/*
 * mName 리스트의 mIndex번째 원소의 값을 mValue로 변경한다.

 * 수행해야할 작업을 본문의 예시와 같이 나타내면, 아래와 같다.
 * > mName[mIndex] = mValue

 * mName 리스트가 생성되어 있음이 보장된다.

 * Parameters
 * mName : 리스트의 이름 ( 1 ≤ 길이 ≤ 20 )
 * mIndex : 원소의 인덱스 ( 0 ≤ mIndex ≤ mName 리스트의 길이 - 1 )
 * mValue : 원소의 수정 후의 값 ( 0 ≤ mValue ≤ 32,767 )
 */
void updateElement(char mName[], int mIndex, int mValue) {
	change_log[change_number] = { mIndex, mValue }; // mIndex에 mValue 값으로 바꿀거라는 것을 등록
	prev_change[change_number] = last_change[address[string(mName)]]; // change_number의 이전 변화는 mSrc의 마지막 변화와 같다.
	last_change[address[string(mName)]] = change_number; // 만들어진 배열의 마지막 변화 event 번호는 change_number이다.
	change_number++;
}

/*
 * mName 리스트의 mIndex번째 원소를 반환한다.

 * mName 리스트가 생성되어 있음이 보장된다.

 * Parameters
 * mName : 리스트의 이름 ( 1 ≤ 길이 ≤ 20 )
 * mIndex : 원소의 인덱스 ( 0 ≤ mIndex ≤ mName 리스트의 길이 - 1 )
 */
int element(char mName[], int mIndex) { // 호출 400 이하
	int c = last_change[address[string(mName)]]; // 마지막 변화 이벤트로 이동
	while (true) {
		if (prev_change[c] == -1) { // 변화가 없음. makeList한 최초 로그만 남아있음
			return init_value[change_log[c].second][mIndex];
		}
		if (change_log[c].first == mIndex) { // mIndex에 대한 변화 event를 찾음 -> 이게 최신 정보
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
	int num_query; // query 개수

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
			init(); // 초기화
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