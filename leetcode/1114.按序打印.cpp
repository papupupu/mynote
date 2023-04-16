/*
 * @lc app=leetcode.cn id=1114 lang=cpp
 *
 * [1114] 按序打印
 */

// @lc code=start
#include <pthread.h>

class Foo {
public:
    pthread_cond_t second_cond, third_cond;
    pthread_mutex_t lock;
    Foo() {
        pthread_cond_init(&second_cond, NULL);
        pthread_cond_init(&third_cond, NULL);
        pthread_t p1, p2, p3; 
        pthread_create(&p1, NULL, first, nullptr);
        pthread_create(&p2, NULL, second, nullptr);
        pthread_create(&p3, NULL, third, nullptr);

        
    }

    void first(function<void()> printFirst) {
         
         pthread_mutex_lock(&lock);
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        ptread_mutex_unlock(&lock);
    }

    void second(function<void()> printSecond) {
        
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
    }

    void third(function<void()> printThird) {
        
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};
// @lc code=end

