#ifndef TESTING_H
#define TESTING_H

template <class T>
struct ValuePair {
    T a;
    T b;
};

template <class T>
struct ValuePair<T> create_pair(T a, T b) {
    struct ValuePair<T> pair = {a, b};
    return pair;
}

template <class T>
int is_greater(struct ValuePair<T> values) {
    return values.a > values.b;
}

template <class T>
int is_less(struct ValuePair<T> values) {
    return values.a < values.b;
}

template <class T>
int is_greater_eq(struct ValuePair<T> values) {
    return values.a >= values.b;
}

template <class T>
int is_less_eq(struct ValuePair<T> values) {
    return values.a <= values.b;
}

template<class T>
int is_eq(struct ValuePair<T> values) {
    return values.a == values.b;
}

template <class T>
void test(const char* name, struct ValuePair<T> (*test_func)(), int (*assertion)(struct ValuePair<T>)) {
    std::cout << "========== Test ==========" << std::endl << "Name: " << name << std::endl;
    
    struct ValuePair<T> values = test_func();

    if (assertion(values)) {
        std::cout << "\033[1;32mPassed\033[0m ";
    }
    else {
        std::cout << "\033[1;31mFailed\033[0m ";
    }

    std::cout << "Values were: " << values.a << ", " << values.b << std::endl << std::endl;
}

#endif