#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <sstream>

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

class Synonyms {
public:
    void Add(const std::string& first_word, const std::string& second_word) {
        synonyms_[first_word].insert(second_word);
        synonyms_[second_word].insert(first_word);
    }

    size_t GetSynonymCount(const std::string& word) const {
        if (synonyms_.count(word) != 0) {
            return synonyms_.at(word).size();
        }
        return 0;
    }

    bool AreSynonyms(const std::string& first_word, const std::string& second_word) const {
        if (synonyms_.count(first_word) == 0) {
            return false;
        }
        
        if (synonyms_.at(first_word).count(second_word) == 1) {
            return true;
        }
        
        return false;
    }

private:
    std::map<std::string, std::set<std::string>> synonyms_;
};

void TestAddingSynonymsIncreasesTheirCount() {
    Synonyms synonyms;
    assert(synonyms.GetSynonymCount("music"s) == 0);
    assert(synonyms.GetSynonymCount("melody"s) == 0);

    synonyms.Add("music"s, "melody"s);
    assert(synonyms.GetSynonymCount("music"s) == 1);
    assert(synonyms.GetSynonymCount("melody"s) == 1);

    synonyms.Add("music"s, "tune"s);
    assert(synonyms.GetSynonymCount("music"s) == 2);
    assert(synonyms.GetSynonymCount("tune"s) == 1);
    assert(synonyms.GetSynonymCount("melody"s) == 1);
}

void TestAreSynonyms() {
    Synonyms synonyms;
    
    synonyms.Add("color", "hue");
    assert(synonyms.AreSynonyms("color", "hue") == true);
    assert(synonyms.AreSynonyms("hue", "color") == true);
    
    // not added
    assert(synonyms.AreSynonyms("goood", "great") == false);
}

void TestSynonyms() {
    TestAddingSynonymsIncreasesTheirCount();
    TestAreSynonyms();
}

int main() {
    TestSynonyms();

    Synonyms synonyms;

    std::string line;
    while (getline(std::cin, line)) {
        std::istringstream command(line);
        std::string action;
        command >> action;

        if (action == "ADD"s) {
            std::string first_word, second_word;
            command >> first_word >> second_word;
            synonyms.Add(first_word, second_word);
        } else if (action == "COUNT"s) {
            std::string word;
            command >> word;
            std::cout << synonyms.GetSynonymCount(word) << std::endl;
        } else if (action == "CHECK"s) {
            std::string first_word, second_word;
            command >> first_word >> second_word;
            if (synonyms.AreSynonyms(first_word, second_word)) {
                std::cout << "YES"s << std::endl;
            } else {
                std::cout << "NO"s << std::endl;
            }
        } else if (action == "EXIT"s) {
            break;
        }
    }
}
