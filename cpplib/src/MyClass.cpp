#include "cpplib/MyClass.h"

MyClass::MyClass(int nb)
  : m_nb(nb)
{
}

int MyClass::getValue() const
{
    return m_nb;
}

void MyClass::increment()
{
    m_nb++;
}
