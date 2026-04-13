# Recursive descent expression evaluator
# Grammar:
#   expr   -> term (('+' | '-') term)*
#   term   -> factor (('*' | '/') factor)*
#   factor -> NUMBER | '(' expr ')'

class Parser:
    def __init__(self, text):
        self.tokens = self.tokenize(text)
        self.pos = 0

    def tokenize(self, text):
        tokens = []
        i = 0
        while i < len(text):
            if text[i].isspace():
                i += 1
            elif text[i].isdigit() or (text[i] == '.' and i+1 < len(text) and text[i+1].isdigit()):
                j = i
                while j < len(text) and (text[j].isdigit() or text[j] == '.'):
                    j += 1
                tokens.append(('NUM', float(text[i:j]) if '.' in text[i:j] else int(text[i:j])))
                i = j
            elif text[i] in '+-*/()':
                tokens.append(('OP', text[i]))
                i += 1
            else:
                raise ValueError(f"Unknown character: {text[i]}")
        tokens.append(('EOF', None))
        return tokens

    def peek(self):
        return self.tokens[self.pos]

    def consume(self):
        tok = self.tokens[self.pos]
        self.pos += 1
        return tok

    def parse(self):
        result = self.expr()
        if self.peek()[0] != 'EOF':
            raise ValueError("Unexpected token")
        return result

    # Addition and subtraction (lowest precedence)
    def expr(self):
        left = self.term()
        while self.peek() == ('OP', '+') or self.peek() == ('OP', '-'):
            op = self.consume()[1]
            right = self.term()
            if op == '+':
                left += right
            else:
                left -= right
        return left

    # Multiplication and division (higher precedence)
    def term(self):
        left = self.factor()
        while self.peek() == ('OP', '*') or self.peek() == ('OP', '/'):
            op = self.consume()[1]
            right = self.factor()
            if op == '*':
                left *= right
            else:
                if right == 0:
                    raise ZeroDivisionError("Division by zero")
                left = left / right
        return left

    # Numbers and parenthesized expressions
    def factor(self):
        tok = self.peek()
        if tok[0] == 'NUM':
            self.consume()
            return tok[1]
        elif tok == ('OP', '('):
            self.consume()          # eat '('
            val = self.expr()
            if self.peek() != ('OP', ')'):
                raise ValueError("Expected ')'")
            self.consume()          # eat ')'
            return val
        else:
            raise ValueError(f"Unexpected token: {tok}")


def evaluate(expr_str):
    # Type conversion: result is int if no remainder, float otherwise
    result = Parser(expr_str).parse()
    return int(result) if isinstance(result, float) and result.is_integer() else result


# Short-circuit conditional: "if <cond_expr> then <expr> else <expr>"
def evaluate_conditional(expr_str):
    if expr_str.strip().startswith("if "):
        parts = expr_str.split(" then ")
        cond_part = parts[0].replace("if ", "").strip()
        then_else = parts[1].split(" else ")
        cond = evaluate(cond_part)
        # short-circuit: only evaluate the branch we need
        if cond:
            return evaluate(then_else[0].strip())
        else:
            return evaluate(then_else[1].strip())
    return evaluate(expr_str)


# ── Tests 
tests = [
    "3 + 5 * (2 - 1)",   # precedence: 5*(1)=5, 3+5=8
    "10 / 2 + 3",        # 5 + 3 = 8
    "2 * (3 + 4) * 2",   # 2*7*2 = 28
    "9.0 / 4",           # float result: 2.25
    "100 / 10",          # int result:   10
]

print("=== Expression Evaluator ===")
for t in tests:
    print(f"  {t!r:25} => {evaluate(t)}")

print("\n=== Short-Circuit Conditionals ===")
cond_tests = [
    "if 1 then 42 else 0",       # cond true  -> 42 (0 never evaluated)
    "if 0 then 99 else 7 + 1",   # cond false -> 8  (99 never evaluated)
]
for t in cond_tests:
    print(f"  {t!r:40} => {evaluate_conditional(t)}")