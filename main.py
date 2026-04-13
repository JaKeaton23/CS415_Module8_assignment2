import math, random

# ─── Part 2: Task 2.2 – Mixed-Mode ──────────────────────────────────────────
i, d, f = 5, 3.7, 2.1
x = i + d       # float; no truncation
y = d / i       # float division always in Python 3
y_int = d // i  # integer division
z = f + i
print(f"2.2 x={x}, y={y}, y_int={y_int}, z={z}")

# ─── Part 2: Task 2.3 – Explicit Casting ─────────────────────────────────────
d = 9.8
truncated = int(d)
rounded   = round(d)
print(f"2.3 truncated={truncated}, rounded={rounded}")

# ─── Part 3: Task 3.1 – Short-Circuit ────────────────────────────────────────
def check(x, y):
    return x > 0 and (y := y + 1) > 0

y = 5
result = check(-1, y)
# walrus only runs if x>0; since x=-1, y is NOT incremented
print(f"3.1 result={result}, y={y}")  # y stays 5 (walrus local to check)

# ─── Part 3: Task 3.2 – De Morgan's Law ──────────────────────────────────────
a, b = True, False
print(f"3.2 !(a&&b)==(!a||!b): {not(a and b) == (not a or not b)}")
print(f"3.2 !(a||b)==(!a&&!b): {not(a or b)  == (not a and not b)}")

# ─── Part 4: Task 4.1 – Grade Calculator ─────────────────────────────────────
def grade(score):
    if   score >= 90: return 'A'
    elif score >= 80: return 'B'
    elif score >= 70: return 'C'
    elif score >= 60: return 'D'
    else:             return 'F'

print(f"4.1 grade(85)={grade(85)}")

# ─── Part 4: Task 4.2 – Loop Comparison ──────────────────────────────────────
print("4.2 for:", list(range(1, 11)))
# while
i, out = 1, []
while i <= 10:
    out.append(i); i += 1
print("4.2 while:", out)
# evens with continue
evens = []
for j in range(1, 11):
    if j % 2 != 0: continue
    evens.append(j)
print("4.2 evens:", evens)

# ─── Part 4: Task 4.3 – Multiplication Table ──────────────────────────────────
print("4.3 5x5 table:")
for r in range(1, 6):
    print("\t".join(str(r*c) for c in range(1, 6)))

# ─── Part 5: Task 5.2 – Guarded Commands ─────────────────────────────────────
a, b = 7, 3
guards = []
if a > b:  guards.append('swap')
if a <= b: guards.append('double')

choice = random.choice(guards) if guards else None
if choice == 'swap':   a, b = b, a
elif choice == 'double': a *= 2; b *= 2
print(f"5.2 a={a}, b={b}")