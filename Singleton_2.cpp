#include <iostream>
using namespace std;

class Singleton{
public:
    static Singleton &getInstance(){
        static Singleton instance;//静态局部变量instance的引用，保证单例只创建一次。
        return instance;
    }

private:
    Singleton(){//构造函数私有化，外部无法 new 或创建对象
        cout << "Singleton constructor"<<endl;
    }

    Singleton(const Singleton &rhs)=delete;// 禁止拷贝构造
    Singleton &operator=(const Singleton &rhs)=delete;// 禁止赋值运算
};

int main()
{
    cout << &Singleton::getInstance() << endl;
    cout << &Singleton::getInstance() << endl;
    cout << &Singleton::getInstance() << endl;
    return 0;
}

