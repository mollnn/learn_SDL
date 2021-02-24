# std::thread

## 创建线程（基本）

``` cpp
#include <bits/stdc++.h>
using namespace std;

void a()
{
    for (int i = 0; i < 10; i++)
        cout << "a";
}
void b(bool flag)
{
    for (int i = 0; i < 10; i++)
        cout << (flag ? "c" : "b");
}

signed main()
{
    thread ta(a);
    thread tb(b, 0);
    thread tc(b, 1);
    // 等待子线程执行完再退出
    ta.join();
    tb.join();
    tc.join();
    cout << "m" << endl;
}
```

线程对象执行了join后就不再joinable了，所以只能调用join一次

传引用时需要 `std::ref`



## 互斥量 mutex

构造函数，std::mutex不允许拷贝构造

lock()，调用线程将锁住该互斥量

注意：如果当前互斥量被其他线程锁住，则当前的调用线程被阻塞住；如果当前互斥量被当前调用线程锁住，则会产生死锁

unlock()， 解锁

try_lock()，尝试锁住互斥量，如果互斥量被其他线程占有，则当前线程也不会被阻塞。但是，如果当前互斥量被当前调用线程锁住，依然会产生死锁

``` cpp
#include <bits/stdc++.h>
using namespace std;

mutex m;
int cnt = 0;

void a()
{
    while (cnt < 5000)
    {
        m.lock();
        ++cnt;
        cout << "a: " << cnt << "\t";
        m.unlock();
    }
}
void b()
{
    while (cnt < 5000)
    {
        m.lock();
        ++cnt;
        cout << "b: " << cnt << "\t";
        m.unlock();
    }
}

signed main()
{
    thread ta(a);
    thread tb(b);
    // 等待子线程执行完再退出
    ta.join();
    tb.join();
    cout << "m" << endl;
}
```

使用mutex是不安全的，当一个线程在解锁之前异常退出了，那么其它被阻塞的线程就无法继续下去



### 使用 lock_guard

能够自解锁，该对象创建时，它会像m.lock()一样获得互斥锁，当生命周期结束时，它会自动析构(unlock)

``` cpp
#include <bits/stdc++.h>
using namespace std;

mutex m;
int cnt = 0;

void a()
{
    while (cnt < 5000)
    {
        lock_guard<mutex> lgmutex(m);
        ++cnt;
        cout << "a: " << cnt << "\t";
    }
}
void b()
{
    while (cnt < 5000)
    {
        lock_guard<mutex> lgmutex(m);
        ++cnt;
        cout << "b: " << cnt << "\t";
        if (cnt > 4000)
            break;
    }
}

signed main()
{
    thread ta(a);
    thread tb(b);
    // 等待子线程执行完再退出
    ta.join();
    tb.join();
    cout << "m" << endl;
}
```

