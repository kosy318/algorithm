class Solution {
    // price : 놀이기구의 원래 이용료
    // 놀이기구를 N번째 이용하면 price * N만큼 받음
    // 놀이기구를 count번 타게 되면 얼마가 모자라는지 return
    // 모자라지 않으면 0 리턴
    fun solution(price: Int, money: Int, count: Int): Long {
        val left: Long = (price.toLong() * count * (count + 1) / 2) - money
        if(left > 0) return left
        return 0
    }
}

fun main() {
    println(Solution().solution(3, 20, 4)) // 답 10
}