// https://jolly-note.tistory.com/55

using namespace std;

int gcd(int x, int y) {
	if (y == 0) return x;
	else if (x == 0) return y;

	return gcd(x%y, y%x);
}

long long solution(int w, int h) {
	if (w == h) return (long long)w*(h - 1);
	int gcd_val = gcd(w, h);

	int deleted = h / gcd_val + w / gcd_val - 1;
	long long answer = (long long)w*h - deleted * gcd_val;
	return answer;
}