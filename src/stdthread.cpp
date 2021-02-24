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