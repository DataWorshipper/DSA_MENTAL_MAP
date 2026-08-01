# Dynamic Programming Playbook

## 1. Before Writing DP

Don't write a single line of code until you can answer:

> dp(state) stores _____________________

If I can't complete this sentence precisely, my DP is probably wrong.

## 1. Game DP

If there are two players, ask:

Can I store the score difference instead?

Example:

Stone Game III

Wrong idea

dp(i, turn) = Alice's score

Problem:
Whose score am I returning?

Better

dp(i, turn) = Alice - Bob

### Lesson: The return value must compose correctly.

Suppose I write

dp(state) = ______

Then every transition should combine values of the SAME meaning.

Example

Good

dp = maximum score difference

Transition

take - dp(next)

Both terms represent "score difference".

---

Bad

dp = maximum score of current player

Transition

take + dp(next)

Problem:

dp(next) is the opponent's score, not mine.

I am adding two unrelated quantities.