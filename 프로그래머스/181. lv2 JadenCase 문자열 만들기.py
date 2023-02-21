def solution(s):
    arr = s.split(' ') # 공백이 여러개가 존재할 때 주의
    for i in range(len(arr)):
        if arr[i] == '': # 공백이 연속되어 잘라지면 빈 char가 들어가있다, 나중에 공백으로 합쳐줘야하니 continue
            continue
        arr[i] = arr[i][0].upper() + arr[i][1:].lower() # 맨 앞 문자만 대문자 그 뒤 문자는 소문자로 만든다
    return ' '.join(arr)