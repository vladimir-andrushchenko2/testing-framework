#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std::string_literals;

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

int main() {
    std::string hello = "hello"s;
    ASSERT(!hello.empty());
    ASSERT_HINT(2 + 2 == 5, "This will fail"s);
}
