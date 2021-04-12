#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>

using namespace std::string_literals;

// logging functionality

template<typename First, typename Second>
std::ostream& operator<<(std::ostream& out, const std::pair<First, Second>& container) {
    out << container.first << ": "s << container.second;
    return out;
}

template<typename Container>
void Print(std::ostream& out, const Container& container) {
    bool isFirst = true;
    for (const auto& element : container) {
        if(isFirst) {
            out << element;
            isFirst = false;
            continue;
        }
        out << ", "s << element;
    }
}

// [элемент1, элемент2, элемент3, ... элементN]
template<typename Element>
std::ostream& operator<<(std::ostream& out, const std::vector<Element>& container) {
    out << '[';
    Print(out, container);
    out << ']';
    return out;
}

// {элемент1, элемент2, элемент3, ... элементN}
template<typename Element>
std::ostream& operator<<(std::ostream& out, const std::set<Element>& container) {
    out << '{';
    Print(out, container);
    out << '}';
    return out;
}

// {ключ1: значение1, ключ2: значение2, ... ключN: значениеN}
template<typename Key, typename Value>
std::ostream& operator<<(std::ostream& out, const std::map<Key, Value>& container) {
    out << '{';
    Print(out, container);
    out << '}';
    return out;
}

// logging functionality ^^^^^

template <typename T, typename U>
void AssertEqualImpl(const T& t, const U& u, const std::string& t_str, const std::string& u_str, const std::string& file,
                     const std::string& func, unsigned line, const std::string& hint) {
    if (t != u) {
        std::cout << std::boolalpha;
        std::cout << file << "("s << line << "): "s << func << ": "s;
        std::cout << "ASSERT_EQUAL("s << t_str << ", "s << u_str << ") failed: "s;
        std::cout << t << " != "s << u << "."s;
        if (!hint.empty()) {
            std::cout << " Hint: "s << hint;
        }
        std::cout << std::endl;
        abort();
    }
}

template <typename T>
void AssertTrueImpl(const T& t, const std::string& t_str, const std::string& file,
                     const std::string& func, unsigned line, const std::string& hint) {
    if (!t) {
        std::cout << std::boolalpha;
        
        std::cout << file << "("s << line << "): "s << func << ": "s;
        std::cout << "ASSERT("s << t_str << ") failed."s;
        
        if (!hint.empty()) {
            std::cout << " Hint: "s << hint;
        }
        
        std::cout << std::endl;
        
        abort();
    }
}


#define ASSERT_EQUAL(a, b) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, ""s)

#define ASSERT_EQUAL_HINT(a, b, hint) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, (hint))

#define ASSERT(expr) AssertTrueImpl((expr), #expr, __FILE__, __FUNCTION__, __LINE__, ""s)

#define ASSERT_HINT(expr, hint) AssertTrueImpl((expr), #expr, __FILE__, __FUNCTION__, __LINE__, (hint))

std::vector<int> TakeEvens(const std::vector<int>& numbers) {
    std::vector<int> evens;
    for (int x : numbers) {
        if (x % 2 == 0) {
            evens.push_back(x);
        }
    }
    return evens;
}

std::map<std::string, int> TakeAdults(const std::map<std::string, int>& people) {
    std::map<std::string, int> adults;
    for (const auto& [name, age] : people) {
        if (age >= 18) {
            adults[name] = age;
        }
    }
    return adults;
}

bool IsPrime(int n) {
    if (n < 2) {
        return false;
    }
    int i = 2;
    while (i * i <= n) {
        if (n % i == 0) {
            return false;
        }
        ++i;
    }
    return true;
}

std::set<int> TakePrimes(const std::set<int>& numbers) {
    std::set<int> primes;
    for (int number : numbers) {
        if (IsPrime(number)) {
            primes.insert(number);
        }
    }
    return primes;
}

int main() {
    {
        const std::set<int> numbers = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        const std::set<int> expected_primes = {2, 3, 5, 7, 11, 13};
        ASSERT_EQUAL(TakePrimes(numbers), expected_primes);
    }

    {
        const std::map<std::string, int> people = {{"Ivan"s, 19}, {"Sergey"s, 16}, {"Alexey"s, 18}};
        const std::map<std::string, int> expected_adults = {{"Alexey"s, 18}, {"Ivan"s, 19}};
        ASSERT_EQUAL(TakeAdults(people), expected_adults);
    }

    {
        const std::vector<int> numbers = {3, 2, 1, 0, 3, 6};
        const std::vector<int> expected_evens = {2, 0, 6};
        ASSERT_EQUAL(TakeEvens(numbers), expected_evens);
    }
    
    std::cout << "Tests finished ok\n";
}
