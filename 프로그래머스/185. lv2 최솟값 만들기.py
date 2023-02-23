def solution(A, B):
    # 큰 값과 큰 값을 곱하면 숫자가 커지기만 함
    # 작은 값과 큰 값을 곱하자
    # 두 배열은 길이가 같음!
    A = sorted(A, reverse=True)
    B = sorted(B)

    answer = 0
    for i in range(len(A)):
        answer += A[i] * B[i]

    return answer