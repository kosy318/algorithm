// solution1 : https://jolly-note.tistory.com/55
// solution2 : https://jolly-note.tistory.com/56

using namespace std;

int gcd(int x, int y) {
	if (y == 0) return x;
	else if (x == 0) return y;

	return gcd(x%y, y%x);
}

long long solution1(int w, int h) {
	if (w == h) return (long long)w*(h - 1);
	int gcd_val = gcd(w, h);

	int deleted = h / gcd_val + w / gcd_val - 1;
	long long answer = (long long)w*h - deleted * gcd_val;
	return answer;
}


long long solution2(int w, int h) {
	long long answer = 0;
	for (int i = 0; i < w; i++) {
		answer += (int)((double)h*i / w);
	}
	return 2 * answer;
}