#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <set>
#include <chrono>

using namespace std;

//thirdTask
class Timer {
private:
    string _funcname;
    std::chrono::steady_clock::time_point _startTime;
public:
    explicit Timer(string funcname) : _funcname(move(funcname)) {
        _startTime = std::chrono::steady_clock::now();
    };

    ~Timer() {
        cout << _funcname << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _startTime).count() << "ms." << endl;
    };
};

int countIfWithFindResult(const string& content, const vector<char>& neededChars) {
    Timer t(__func__);
    return std::count_if(content.begin(), content.end(), [neededChars](char i) {
        return find(neededChars.begin(), neededChars.end(), i) != neededChars.end();
        });
};

int countIfWithForResult(const string& content, const vector<char>& neededChars) {
    Timer t(__func__);
    return std::count_if(content.begin(), content.end(), [neededChars](char i) {
        for (auto ch : neededChars) {
            if (ch == i)
                return true;
        };
        return false;
        });
};

int countForWithFindResult(const string& content, const vector<char>& neededChars) {
    Timer t(__func__);
    int _countForWithFindResult = 0;
    for (auto i : content) {
        if (find(neededChars.begin(), neededChars.end(), i) != neededChars.end()) {
            ++_countForWithFindResult;
        };
    }
    return _countForWithFindResult;
};

int countForWithForResult(const string& content, const vector<char>& neededChars) {
    Timer t(__func__);
    int _countForWithForResult = 0;
    for (auto i : content) {
        for (auto ch : neededChars) {
            if (i == ch) {
                ++_countForWithForResult;
                break;
            }
        }
    }
    return _countForWithForResult;
};

void thirdTask() {
    ifstream in("w_and_p.txt");
    const vector<char> neededChars{ 'à', 'î', 'ý', 'å', 'è', 'û', 'ó', '¸', 'þ', 'ÿ', 'À', 'Î', 'Ý', 'Å', 'È', 'Û', 'Ó', '¨', 'Þ', 'ß' };
    if (!in.is_open())
        throw runtime_error("File not found");
    string wpContent((istreambuf_iterator<char>(in)), (istreambuf_iterator<char>()));
    cout << "countIfWithFindResult: " << countIfWithFindResult(wpContent, neededChars) << endl;
    cout << "countIfWithForResult: " << countIfWithForResult(wpContent, neededChars) << endl;
    cout << "countForWithFindResult: " << countForWithFindResult(wpContent, neededChars) << endl;
    cout << "countForWithForResult: " << countForWithForResult(wpContent, neededChars) << endl;
};
//thirdTask

//secondTask
class classForSort {
private:
    int _value;
public:
    explicit classForSort(int value) : _value(value) {};

    const int getValue() const {
        return _value;
    };

    friend bool operator==(const classForSort& left, const classForSort& right) {
        return left._value == right._value;
    };

    friend bool operator<(const classForSort& left, const classForSort& right) {
        return left._value < right._value;
    };

    friend bool operator<=(const classForSort& left, const classForSort& right) {
        if (left == right) {
            return true;
        }
        return left < right;
    };
};

template<class T>
void sortPointers(vector<T*>& income) noexcept {
    sort(income.begin(), income.end(), [](T* a, T* b) {
            return *a <= *b; 
    });
};

void secondTask() {
    vector<classForSort*> toTest;
    toTest.reserve(10);
    for (int i = 10; i > 0; --i) {
        toTest.push_back(new classForSort(i));
    }
    cout << "Before sort: ";
    for (auto row : toTest) {
        cout << row->getValue() << " ";
    }
    cout << endl;
    sortPointers(toTest);
    cout << "After sort: ";
    for (auto row : toTest) {
        cout << row->getValue() << " ";
    }
    cout << endl;
}
//secondTask

//firstTask
template<class T>
void swap(T*& firstPtr, T*& secondPtr) noexcept {
    T* temp = firstPtr;
    firstPtr = secondPtr;
    secondPtr = temp;
};

void firstTask() {
    vector<int> first{ 1 };
    vector<int> second{ 2 };
    auto firstPtr = &first;
    auto secondPtr = &second;
    cout << "First: " << (*firstPtr)[0] << endl;
    cout << "Second: " << (*secondPtr)[0] << endl;
    swap<vector<int>>(firstPtr, secondPtr);
    cout << "First: " << (*firstPtr)[0] << endl;
    cout << "Second: " << (*secondPtr)[0] << endl;
}
//firstTask


int main()
{
    firstTask();
    secondTask();
    thirdTask();
}