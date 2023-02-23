def solution(s):
    changed, deleted = 0, 0

    while True:
        changed += 1
        deleted += s.count('0')     # 0 카운트
        s = s.replace('0', '')      # 0 제거
        s = bin(len(s))[2:]         # int to binary, 앞에 '0b'가 붙어나오므로 제거

        if s == '1':
            break

    return [changed, deleted]