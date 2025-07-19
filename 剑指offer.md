#### 面试题1：赋值运算符

```
#include <iostream>
#include <cstring>
using namespace std;

class CMyString
{
public:
    // 构造函数
    CMyString(const char *string){
        m_string = new char[strlen(string) + 1];
        strcpy(m_string, string);
    }
    // 拷贝构造函数
    CMyString(const CMyString &rhs){
        m_string = new char[strlen(rhs.m_string) + 1];
        strcpy(m_string, rhs.m_string);
    }
    // 拷贝赋值运算符
    CMyString &operator=(const CMyString &rhs){
        if(this!=&rhs){
            delete[] m_string;
            m_string = new char[strlen(rhs.m_string) + 1];
            strcpy(m_string, rhs.m_string);
        }
        return *this;
    }
    ~CMyString(){
        delete [] m_string;
        m_string = nullptr;
    }
    void display(){
        cout << m_string << endl;
    }
private:
    char *m_string;
};


int main()
{
    CMyString myStr = "Hello";
    CMyString copyStr = myStr;
    copyStr.display();
    return 0;
}

```

- 拷贝赋值运算符返回值类型声明为引用，并在函数结束时返回实例自身引用（*this），若返回类型为void，则无法连续赋值。
- 传入的参数应当为引用类型，否则每次赋值时，都会**额外构造一个临时 CMyString 对象**，这会导致一次多余的深拷贝，性能变差。（可能的副作用：编译器实现可能会**反复调用 operator= 和拷贝构造**，导致栈溢出（递归自调用）或者程序崩溃）
- 分配心内存前释放自身实例，避免造成内存泄露。
- 判断传入参数与自身实例是否相同，如果不同则进行相关操作，避免二次析构等问题。





### 面试题2：实现Singleton模式

```
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
```

C++ 的 Meyers Singleton（局部静态变量）实现方式兼具**延迟加载、线程安全、语法极简、效率高**。