# Greedy Playbook

---

## Lexicographic Construction

Recognition

- Lexicographically smallest/largest string
- Next greater string
- Construct smallest valid answer

Typical Pattern
## this is the soln of lc 2663, but u get it ,  for this google OA qsn , getting the idea wasnt tricky, what was tricky , was checking for how many palidnromes of len=l , l=2  and 3 are trivial , since whatever character u are replacing , just dotn use the same characters as s[i-1] and s[i-2], think about 4 ,5  stuff like that.
## Key Thing-every palindrome of len>=4 has a pali of len=2 or 3  (pretty obv).
## Also given s is beautiful , u can think of substrings of len>=4,u will figure it out quickly 
## do not always go for proofs , greedy is very intuiton based as well , trust ur intuition sometimes
## try proofs for exchange args , where optimal sorting order needs to be determined
1. Traverse from right to left.
2. Find the first position that can be increased.
3. Increase it by the smallest possible amount.
4. Rebuild the suffix greedily using the smallest valid choices.

Reason

The earliest changed position dominates lexicographic order.
After fixing that position, the suffix should be as small as possible.

Example

Leetcode 2663 - Lexicographically Smallest Beautiful String
## Exchange Args
1. Basic thing u know , take a sequence ,  ____i,___j,___ and ____j,___,i___ , assume first is better , and then get ideal sorting pattern , most cases shud work-try lc 1665 , shud cover  lot of concepts (GS OA) , the inequality gets a bit weird tho , so no matter trust ur intuition
## Rearrangement Inequality
Theorem

Given two sequences sorted in the same order

a₁ ≤ a₂ ≤ ... ≤ aₙ

b₁ ≤ b₂ ≤ ... ≤ bₙ

Then

Maximum

a₁b₁ + a₂b₂ + ... + aₙbₙ

is obtained by pairing

largest ↔ largest

smallest ↔ smallest.

Minimum

is obtained by pairing

largest ↔ smallest.

---

Recognition Clues

- Assign values to multipliers
- Match workers to jobs
- Pair profits with weights
- Schedule tasks with different coefficients

Whenever the objective is

Σ(ai × bj)

ask

"How should I pair the two sequences?"

---

Proof Technique

Usually proved using an exchange argument.

If two adjacent pairs are crossed,

swapping them never decreases (or never increases) the objective.

---

Examples

- Maximum Total Sum of K Selected Elements (LC 3974)
- Scheduling / assignment problems

## Binary Search + Greedy

Recognition

Minimize maximum

Maximize minimum

Smallest possible answer

Question

Can I write

check(mid)

?

Must prove

check()

is monotone.


