#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

template <typename T, typename U>
void AssertEqualImpl(const T& t, const U& u, const string& t_str, const string& u_str, const string& file,
                     const string& func, unsigned line, const string& hint) {
    if (t != u) {
        cout << boolalpha;
        cout << file << "("s << line << "): "s << func << ": "s;
        cout << "ASSERT_EQUAL("s << t_str << ", "s << u_str << ") failed: "s;
        cout << t << " != "s << u << "."s;
        if (!hint.empty()) {
            cout << " Hint: "s << hint;
        }
        cout << endl;
        abort();
    }
}

template <typename T>
void AssertTrueImpl(const T& t, const string& t_str, const string& file,
                     const string& func, unsigned line, const string& hint) {
    if (!t) {
        cout << boolalpha;
        
        cout << file << "("s << line << "): "s << func << ": "s;
        cout << "ASSERT("s << t_str << ") failed."s;
        
        if (!hint.empty()) {
            cout << " Hint: "s << hint;
        }
        
        cout << endl;
        
        abort();
    }
}


#define ASSERT_EQUAL(a, b) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, ""s)

#define ASSERT_EQUAL_HINT(a, b, hint) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, (hint))

#define ASSERT(expr) AssertTrueImpl((expr), #expr, __FILE__, __FUNCTION__, __LINE__, ""s)

#define ASSERT_HINT(expr, hint) AssertTrueImpl((expr), #expr, __FILE__, __FUNCTION__, __LINE__, (hint))

int main() {
    string hello = "hello"s;
    ASSERT(!hello.empty());
    ASSERT_HINT(2 + 2 == 5, "This will fail"s);
}
