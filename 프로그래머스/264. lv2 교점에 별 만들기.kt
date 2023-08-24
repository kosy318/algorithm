data class Point(val x: Float, val y:Float) {}

class Solution {
    fun findInteraction(A: Int, B: Int, E: Int, C: Int, D: Int, F: Int): Point? {
        if(A*D - B*C == 0)  return null
        else return Point((B*F - E*D).toFloat() / (A*D - B*C), (E*C - A*F).toFloat() / (A*D - B*C))
    }

    fun solution(line: Array<IntArray>): Array<String> {
        println(findInteraction(line[0][0], line[0][1], line[0][2], line[1][0], line[1][1], line[1][2]))

        var answer: Array<String> = arrayOf<String>()
        return answer
    }
}

fun main() {
}