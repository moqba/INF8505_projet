#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <unordered_map>
#ifdef USE_STREAMS
#include <iostream>
#else
#include <cstdio>
#endif

using namespace std;

class Animal {
public:
    virtual ~Animal() { }
    virtual string speak() = 0;
};

class Cat: public Animal {
public:
    virtual string speak() { return "Meow"; }
};

class Dog: public Animal {
public:
    virtual string speak() { return "Woef"; }
};

namespace {

void populate(vector<shared_ptr<Animal>>& f) {
    f.push_back(make_shared<Cat>());
    f.push_back(make_shared<Cat>());
    f.push_back(make_shared<Dog>());
    f.push_back(make_shared<Dog>());
    f.push_back(make_shared<Dog>());
}

void report_noise(string t, string s) {
#ifdef USE_STREAMS
    cout << t << ": " << s << endl;
#else
    printf("%s: %s\n", t.c_str(), s.c_str());
#endif
}

void report_count(string s, int n) {
#ifdef USE_STREAMS
    cout << s << ": " << n << endl;
#else
    printf("%s: %d\n", s.c_str(), n);
#endif
}

void report_single(const shared_ptr<Animal>& a) {
#ifdef USE_STREAMS
    cout << a->speak() << " (" << a.use_count() << ")" << endl;
#else
    printf("%s (%ld)\n", a->speak().c_str(), a.use_count());
#endif
}

} // anonymous namespace

int main() {
    vector<shared_ptr<Animal>> farm;

    populate(farm);

    reverse(begin(farm), end(farm));

    unordered_map<string,int> count_per_noise;

    for (auto a: farm) {
        string t;
        if (dynamic_cast<Cat*>(a.get()))
            t = "cat";
        else if (dynamic_cast<Dog*>(a.get()))
            t = "dog";
        else
            t = "other";

        string s = a->speak();
        count_per_noise[s]++;
        report_noise(t, s);
    }

    for (auto p: count_per_noise)
        report_count(p.first, p.second);

    auto a = farm.at(2);

    farm.clear();

    report_single(a);

    return 0;
}
