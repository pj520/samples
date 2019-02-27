#include <iostream>
#include "ObjectPool.hpp"

class A {
public:
    void print() {
        std::cout << "Hello world" << std::endl;
    }
};

class B {
public:
    void print() {
        std::cout << "Hello world" << std::endl;
    }
};

using namespace std;

template<typename T>
void Check(shared_ptr<T> &t) {
    weak_ptr<T> wp = t;
    shared_ptr<T> sp = wp.lock();
    if (sp != nullptr) {
        cout << "still " << endl;
    } else {
        cout << "pointer is invalid." << endl;
    }
}

int main() {

    shared_ptr<int> sp1(new int(12));
    shared_ptr<int> sp2 = sp1;
    Check(sp2);
    sp2.reset();
    Check(sp2);
    Check(sp1);
    sp1.reset();
    Check(sp1);

    ObjectPool<A> pool;
    pool.add(std::unique_ptr<A>(new A()));
    pool.add(std::unique_ptr<A>(new A()));
    ObjectPool<B> pool2;
    pool2.add(std::unique_ptr<B>(new B()));
    pool2.add(std::unique_ptr<B>(new B()));
    pool2.add(std::unique_ptr<B>(new B()));
    std::cout << "Object pool size: " << pool.size() << std::endl;
    std::cout << "Object pool2 size: " << pool2.size() << std::endl;

    {
        auto a = pool.get();
        a->print();
        pool.get();
        std::cout << "Object pool size: " << pool.size() << std::endl;
    }

    std::cout << "Object pool size: " << pool.size() << std::endl;

    return 0;
}
