#ifndef MYCLASS_H
#define MYCLASS_H

class MyClass {

private:
    int m_nb;

public:
    MyClass(int nb);
    int getValue() const;
    void increment();

};

#endif
