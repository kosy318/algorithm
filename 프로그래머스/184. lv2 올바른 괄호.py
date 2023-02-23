def solution(s):
    stack = []
    for ch in s:
        if len(stack) != 0 and stack[-1] != ch and ch == ')':
            stack.pop()
        elif len(stack) == 0 and ch == ')':
            return False
        else:
            stack.append(ch)

    return len(stack) == 0