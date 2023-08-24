data class Point(val x: Long, val y:Long) {}

class Solution {
    fun solution(line: Array<IntArray>): Array<String> {
        val pointSet: HashSet<Point> = hashSetOf()

        var maxX: Long = Long.MIN_VALUE
        var maxY: Long = Long.MIN_VALUE
        var minX: Long = Long.MAX_VALUE
        var minY: Long = Long.MAX_VALUE

        for(i in 0 until (line.size - 1)) {
            val (A, B, E) = line[i].map { it.toLong() }
            for(j in i+1 until line.size) {
                val (C, D, F) = line[j].map { it.toLong() }

                if(A*D - B*C == 0L) continue
                if((B*F - E*D) % (A*D - B*C) != 0L) continue
                if((E*C - A*F) % (A*D - B*C) != 0L) continue

                val x: Long = (B*F - E*D) / (A*D - B*C)
                val y: Long = (E*C - A*F) / (A*D - B*C)

                pointSet.add(Point(x, y))

                maxX = maxOf(maxX, x)
                minX = minOf(minX, x)

                maxY = maxOf(maxY, y)
                minY = minOf(minY, y)
            }
        }

        val N: Int = (maxY - minY + 1).toInt()
        val M: Int = (maxX - minX + 1).toInt()

        val answer: Array<Array<Char>> = Array(N){ Array(M) { '.' } }
        pointSet.forEach{
            answer[(maxY - it.y).toInt()][(it.x - minX).toInt()] = '*'
        }
        return answer.map{ it.joinToString("") }.toTypedArray()
    }
}

fun main(){
    check(arrayOf(intArrayOf(2, -1, 4), intArrayOf(-2, -1, 4), intArrayOf(0, -1, 1), intArrayOf(5, -8, -12), intArrayOf(5, 8, 12)),
          arrayOf("....*....", ".........", ".........", "*.......*", ".........", ".........", ".........", ".........", "*.......*"))

    check(arrayOf(intArrayOf(0, 1, -1), intArrayOf(1, 0, -1), intArrayOf(1, 0, 1)),
          arrayOf("*.*"))

    check(arrayOf(intArrayOf(1, -1, 0), intArrayOf(2, -1, 0)),
          arrayOf("*"))

    check(arrayOf(intArrayOf(1, -1, 0), intArrayOf(2, -1, 0), intArrayOf(4, -1, 0)),
          arrayOf("*"))
}

private fun check(input: Array<IntArray>, expected: Array<String>) {
    val answer: Array<String> = Solution().solution(input)
    var correct: Boolean = true
    answer.forEachIndexed { idx, it ->
        if (expected[idx] != it) {
            correct = false
            return@forEachIndexed
        }
    }

    println(correct)
}