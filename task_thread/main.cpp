#include <iostream>
#include <zconf.h>
#include "task_thread.h"

void print() {
    std::cout << "hello world" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int main() {
    {
        auto t = std::make_shared<task_thread>(std::bind(print));
        sleep(2);
        std::cout << "test  " << t->get_thread_id()<< std::endl;
        t->stop();
        sleep(5);
        std::cout << "test  " << t->get_thread_id()<< std::endl;
    }


    std::cout << "hello world ENDL" << std::endl;
    std::cin.get();
    /* t->stop(); */

    return 0;
}

