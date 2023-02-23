def solution(n):
    dp = [0 for _ in range(n + 1)]  # dp[n] : n칸까지 뛰기 위한 방법의 수
    dp[0] = dp[1] = 1

    for total in range(2, n + 1):
        # 1칸 전 위치까지 올 수 있는 방법의 수 + 2칸 전 위치까지 올 수 있는 방법의 수
        dp[total] = (dp[total - 1] + dp[total - 2]) % 1234567

    return dp[n]