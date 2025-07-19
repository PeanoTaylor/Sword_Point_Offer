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
