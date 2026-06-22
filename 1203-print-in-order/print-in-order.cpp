#include <semaphore>

class Foo {
private:
    binary_semaphore sem1{0};
    binary_semaphore sem2{0};

public:
    Foo() {}

    void first(function<void()> printFirst) {
        printFirst();
        sem1.release();
    }

    void second(function<void()> printSecond) {
        sem1.acquire();
        printSecond();
        sem2.release();
    }

    void third(function<void()> printThird) {
        sem2.acquire();
        printThird();
    }
};