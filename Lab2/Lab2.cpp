#include <iostream>
#include <string>
#include <cmath> 
#include <windows.h>
// (m/n)
class Ratio {
    // Объявляем дружественные функции
    friend std::ostream& operator<<(std::ostream& os, const Ratio& r);
    friend std::istream& operator>>(std::istream& is, Ratio& r);
private:
    int m;
    int n;
public:
    Ratio() {
        m = 0;
        n = 0;
    }
    std::string Get() {
        return std::to_string(m) + " " + std::to_string(n);
    }
    void Set(int r_m, int r_n) {
        if (r_n == 0 && r_m != 0) {
            throw "Ошибка! Знаменатель не может быть равен 0!";
        }
        else {
            if (r_n < 0) {
                r_m = -r_m;
                r_n = -r_n;
            }

            m = r_m;
            n = r_n;
        }
    }
    //сокращение дроби
    void Reduce() {
        int gcd_value = gcd(m, n);
        m /= gcd_value;
        n /= gcd_value;
    }
    // Алгоритм Евклида для нахождения НОД
    int gcd(int a, int b) {
        try {
            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        }
        catch (const char* error_message)
        {
            std::cout << error_message << std::endl;
            return 0;
        }     
    }

    void Print() {
        std::cout << std::to_string(m) << "/" << std::to_string(n);
    }
    void Enter() {
        int m;
        int n;
        std::cin >> m >> n;
        Set(m, n);
    }
    double ToDouble() const{
        return static_cast<double>(m) / n;
    }
    static void Compare(Ratio rat1, Ratio rat2) {
        if (rat1.ToDouble() == rat2.ToDouble()) {
            std::cout << "Дроби равны\n";
        }
        else if (rat1.ToDouble() > rat2.ToDouble()) {
            std::cout << "Дробь ";
            rat1.Print();
            std::cout << " больше чем дробь ";
            rat2.Print();
        }
        else {
            std::cout << "Дробь ";
            rat1.Print();
            std::cout << " меньше чем дробь ";
            rat2.Print();
        }
    }
#pragma region Calculations
    static void Sum(Ratio rat1, Ratio rat2) {
        Ratio result;
        if (rat1.n == rat2.n) {
            result.Set(rat1.m + rat2.m, rat1.n);
        }
        else {
            result.Set((rat1.m * rat2.n) + (rat2.m * rat1.n), rat1.n * rat2.n);
        }
        result.Reduce();
        result.Print();
    }
    static void Subtraction(Ratio rat1, Ratio rat2) {
        Ratio result;
        if (rat1.n == rat2.n) {
            result.Set(rat1.m - rat2.m, rat1.n);
        }
        else {
            result.Set((rat1.m * rat2.n) - (rat2.m * rat1.n), rat1.n * rat2.n);
        }
        result.Reduce();
        result.Print();
    }
    static void Division(Ratio rat1, Ratio rat2) {
        Ratio result;

        result.Set(rat1.m * rat2.n, rat1.n * rat2.m);

        result.Reduce();
        result.Print();
    }
    static void Multiplication(Ratio rat1, Ratio rat2) {
        Ratio result;

        result.Set(rat1.m * rat2.m, rat1.n * rat2.n);

        result.Reduce();
        result.Print();
    }
    void Pow(int p) {
        Ratio result;

        result.Set(std::pow(m, p), std::pow(n, p));

        result.Reduce();
        result.Print();
    }
#pragma endregion
#pragma region Overload
    Ratio operator+(const Ratio& rat2) const {
        Ratio result;
        if (n == rat2.n) {
            result.Set(m + rat2.m, n);
        }
        else {
            result.Set((m * rat2.n) + (rat2.m * n), n * rat2.n);
        }
        result.Reduce();
        return result;
    }
    Ratio operator-(Ratio& rat2) {
        Ratio result;
        if (n == rat2.n) {
            result.Set(m - rat2.m, n);
        }
        else {
            result.Set((m * rat2.n) - (rat2.m * n), n * rat2.n);
        } 
        result.Reduce();
        return result;
    }
    Ratio operator*(const Ratio& rat2) const {
        Ratio result;
        result.Set(m * rat2.m, n * rat2.n);
        result.Reduce();
        return result;
    }
    Ratio operator/(const Ratio& rat2) const {
        Ratio result;
        result.Set(m * rat2.n, n * rat2.m);
        result.Reduce();
        return result;
    }
    Ratio operator^(const int& p) const {
        Ratio result;
        result.Set(std::pow(m, p), std::pow(n, p));
        result.Reduce();
        return result;
    }
    Ratio operator-() const {
        Ratio result;
        if (m != 0) {
            result.Set(-m, n);
        }
        else {
            throw "Нулевая дробь не имеет знака";
        }
        result.Reduce();
        return result;
    }
    Ratio operator++() const {
        Ratio result;
        result.Set(m + n, n);

        result.Reduce();
        return result;
    }
    Ratio operator--() const {
        Ratio result;
        result.Set(m - n, n);

        result.Reduce();
        return result;
    }
    bool operator==(const Ratio& rat2) const {
        bool result;
        if (ToDouble() == rat2.ToDouble()) {
            result = true;
        }
        else {
            result = false;
        }

        return result;
    }
    bool operator!=(const Ratio& rat2) const {
        bool result;
        Ratio rat1;
        rat1.Set(m, n);
        if (rat1.ToDouble() != rat2.ToDouble()) {
            result = true;
        }
        else {
            result = false;
        }

        return result;
    }
    bool operator>(const Ratio& rat2) const {
        bool result;
        Ratio rat1;
        rat1.Set(m, n);
        if (rat1.ToDouble() > rat2.ToDouble()) {
            result = true;
        }
        else {
            result = false;
        }

        return result;
    }
    bool operator<(const Ratio& rat2) const {
        bool result;
        Ratio rat1;
        rat1.Set(m, n);
        if (rat1.ToDouble() < rat2.ToDouble()) {
            result = true;
        }
        else {
            result = false;
        }

        return result;
    }
    bool operator>=(const Ratio& rat2) const {
        bool result;
        Ratio rat1;
        rat1.Set(m, n);
        if (rat1.ToDouble() >= rat2.ToDouble()) {
            result = true;
        }
        else {
            result = false;
        }

        return result;
    }
    bool operator<=(const Ratio& rat2) const {
        bool result;
        Ratio rat1;
        rat1.Set(m, n);
        if (rat1.ToDouble() <= rat2.ToDouble()) {
            result = true;
        }
        else {
            result = false;
        }

        return result;
    }
   
#pragma endregion
};
std::ostream& operator<<(std::ostream& os, const Ratio& r) {
    if (r.m != 0) {
        os << r.m << "/" << r.n;
    }
    else {
        os << 0;
    }
    return os;
}
std::istream& operator>>(std::istream& is, Ratio& r) {
    int m_val, n_val;
    is >> m_val >> n_val;

    // Если ввод прошел успешно
    if (is) {
        try {
            r.Set(m_val, n_val);
        }
        catch (const char* error_message) {
            is.setstate(std::ios::failbit);
            std::cout << error_message << std::endl;
        }
    }
    return is;
}
int main()
{
    try {
        while (true) {
            SetConsoleCP(1251);
            SetConsoleOutputCP(1251);
            Ratio rat1;
            Ratio rat2;
            Ratio res;
            char sign;

            std::cout << "Рациональный Калькулятор (+, -, /, *)" << std::endl;
            std::cout << "Введите a, операцию, b: ";
            std::cin >> rat1 >> sign >> rat2;
            

            switch (sign) {
            case '+':
                res = rat1 + rat2;
                break;
            case '-':
                res = rat1 - rat2;
                break;
            case '*':
                res = rat1 * rat2;
                break;
            case '/':
                res = rat1 / rat2;
                break;
            default:
                throw "Неизвестное выражение";
                break;
            }
            std::cout << "Результат: " << rat1 << " " << sign << " " << rat2 << " = " << res;
            std::cout <<"\n";


            /*res = --rat1;
            res.print();*/
            //std::cout << (rat1 != rat2) << "\n";
        }
    }
    catch (const char* error_message)
    {
        std::cout << error_message << std::endl;
        return 0;
    }
}
