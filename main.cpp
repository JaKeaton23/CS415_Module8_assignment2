#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// ─── Part 1: Task 1.1 – Operator Precedence ───────────────────────────────
void task1_1() {
    int result = 8 + 4 * 3 - 6 / 2;           // default: 8 + 12 - 3 = 17
    int v1     = (8 + 4) * (3 - 6) / 2;        // 12 * -3 / 2 = -18
    int v2     = 8 + (4 * 3 - 6) / 2;          // 8 + 6/2 = 11  (wait: 12-6=6, 6/2=3... = 11)
    int v3     = (8 + 4) * 3 - (6 / 2);        // 36 - 3 = 33
    cout << "1.1 default: " << result << endl;
    cout << "1.1 v1: " << v1 << endl;
    cout << "1.1 v2: " << v2 << endl;
    cout << "1.1 v3: " << v3 << endl;
}

// ─── Part 1: Task 1.2 – Complex Number Operator Overloading ───────────────
class Complex {
public:
    double real, imag;
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex& o) const {
        return Complex(real + o.real, imag + o.imag);
    }
    // (a+bi)(c+di) = (ac-bd) + (ad+bc)i
    Complex operator*(const Complex& o) const {
        return Complex(real*o.real - imag*o.imag,
                       real*o.imag + imag*o.real);
    }
    void print(const string& label) const {
        cout << label << real << " + " << imag << "i" << endl;
    }
};

void task1_2() {
    Complex a(1, 2), b(3, 4);
    Complex i(0, 1);
    Complex c = a + b * i;   // * binds tighter than +, so b*i first
    c.print("1.2 a + b*i = ");
    // b*i = (3+4i)(0+1i) = (0-4) + (3+0)i = -4+3i
    // a + b*i = (1-4) + (2+3)i = -3+5i
}

// ─── Part 2: Task 2.1 – Implicit Conversion ───────────────────────────────
void task2_1() {
    int i = 5;
    double d = 3.7;
    float f = 2.1f;

    auto x = i + d;   // int + double -> double
    auto y = d / i;   // double / int -> double (NOT integer division)
    auto z = f + i;   // float + int  -> float

    cout << "2.1 x (i+d): " << x << endl;  // 8.7
    cout << "2.1 y (d/i): " << y << endl;  // 0.74
    cout << "2.1 z (f+i): " << z << endl;  // 7.1
}

// ─── Part 2: Task 2.3 – Explicit Casting ──────────────────────────────────
void task2_3() {
    double d = 9.8;
    int truncated = (int)d;
    int rounded   = (int)(d + 0.5);
    cout << "2.3 truncated: " << truncated << endl;  // 9
    cout << "2.3 rounded:   " << rounded   << endl;  // 10
}

// ─── Part 3: Task 3.1 – Short-Circuit ─────────────────────────────────────
bool check(int x, int y_ref, int& y) {
    y = y_ref;
    bool result = (x > 0) && (y++ > 0);
    return result;
}

void task3_1() {
    int y = 5;
    bool r = ((-1) > 0) && (y++ > 0);  // x <= 0, short-circuits; y stays 5
    cout << "3.1 result: " << r << ", y after (should stay 5): " << y << endl;
}

// ─── Part 3: Task 3.2 – De Morgan's Law ───────────────────────────────────
void task3_2() {
    bool a = true, b = false;
    cout << "3.2 !(a&&b)==(!a||!b): " << (!(a&&b) == (!a||!b)) << endl;
    cout << "3.2 !(a||b)==(!a&&!b): " << (!(a||b) == (!a&&!b)) << endl;
}

// ─── Part 4: Task 4.1 – Grade Calculator ──────────────────────────────────
void task4_1(int score) {
    // if-else
    char grade;
    if      (score >= 90) grade = 'A';
    else if (score >= 80) grade = 'B';
    else if (score >= 70) grade = 'C';
    else if (score >= 60) grade = 'D';
    else                  grade = 'F';
    cout << "4.1 if-else grade for " << score << ": " << grade << endl;

    // switch (bucket into tens)
    switch (score / 10) {
        case 10: case 9: grade = 'A'; break;
        case 8:          grade = 'B'; break;
        case 7:          grade = 'C'; break;
        case 6:          grade = 'D'; break;
        default:         grade = 'F';
    }
    cout << "4.1 switch grade for  " << score << ": " << grade << endl;
}

// ─── Part 4: Task 4.2 – Loop Comparison ───────────────────────────────────
void task4_2() {
    // for loop 1-10
    cout << "4.2 for: ";
    for (int i = 1; i <= 10; i++) cout << i << " ";
    cout << endl;

    // while loop 1-10
    cout << "4.2 while: ";
    int i = 1;
    while (i <= 10) { cout << i++ << " "; }
    cout << endl;

    // do-while 1-10
    cout << "4.2 do-while: ";
    i = 1;
    do { cout << i++ << " "; } while (i <= 10);
    cout << endl;

    // evens with continue
    cout << "4.2 evens: ";
    for (int j = 1; j <= 10; j++) {
        if (j % 2 != 0) continue;
        cout << j << " ";
    }
    cout << endl;
}

// ─── Part 4: Task 4.3 – Multiplication Table ──────────────────────────────
void task4_3() {
    cout << "4.3 5x5 table:" << endl;
    for (int r = 1; r <= 5; r++) {
        for (int c = 1; c <= 5; c++)
            cout << r*c << "\t";
        cout << endl;
    }
}

// ─── Part 5: Task 5.1 – goto vs for ──────────────────────────────────────
void task5_1() {
    cout << "5.1 goto: ";
    int i = 0;
    loop_start:
        if (i > 5) goto loop_end;
        cout << i++ << " ";
        goto loop_start;
    loop_end:
    cout << endl;

    cout << "5.1 for:  ";
    for (int j = 0; j <= 5; j++) cout << j << " ";
    cout << endl;
}

// ─── Part 5: Task 5.2 – Guarded Commands ──────────────────────────────────
void task5_2() {
    srand(time(0));
    int a = 7, b = 3;
    cout << "5.2 before: a=" << a << " b=" << b << endl;

    // Both guards checked; if both true, pick randomly
    bool g1 = (a > b);   // swap
    bool g2 = (a <= b);  // double both

    if (g1 && g2) {
        // shouldn't happen for distinct values, but handle it
        if (rand() % 2) swap(a, b);
        else { a *= 2; b *= 2; }
    } else if (g1) {
        swap(a, b);
    } else if (g2) {
        a *= 2; b *= 2;
    }
    cout << "5.2 after:  a=" << a << " b=" << b << endl;
}

int main() {
    task1_1();
    task1_2();
    task2_1();
    task2_3();
    task3_1();
    task3_2();
    task4_1(85);
    task4_2();
    task4_3();
    task5_1();
    task5_2();
    return 0;
}