#ifndef _STANDARD_REG_
#define _STANDARD_REG_

#include <bits/stdc++.h>
using namespace std;

template<size_t T> struct standard_reg{
  private:
      long int a;
      unsigned short int size;
      char b[T];
      long int  c;

  public:
      standard_reg();
      standard_reg(int _a, char _b[], int _c);

      bool operator==(standard_reg b);

      void clear();
      bool empty();
      void scan();
      int getKey();
      char* getB();
      long int getC();
};

template<size_t T>
char* standard_reg<T>::getB(){
  return b;
}
template<size_t T>
long int standard_reg<T>::getC(){
  return c;
}

template<size_t T>
standard_reg<T>::standard_reg(){
  this->clear();
}
template<size_t T>
standard_reg<T>::standard_reg(int _a, char _b[], int _c){
  a = _a;
  strcpy(b,_b);
  size = T;
  c = _c;
}

template<size_t T>
bool standard_reg<T>::operator==(standard_reg<T> b){
  return (this->a == b.a) and (this->c == b.c) and (this->size == b.size) and (!strcmp(this->b, b.b));
}

template<size_t T>
void standard_reg<T>::clear(){
  a = INT_MIN;
  size = USHRT_MAX;
  b[0] = '\0';
  c = INT_MIN;
}

template<size_t T>
bool standard_reg<T>::empty(){
  return ((this->a==INT_MIN) and (this->size == USHRT_MAX) and (this->b[0] == '\0') and (this->c == INT_MIN));
}

template<size_t T>
void standard_reg<T>::scan(){
  cout << "A: " << a << endl
       << "Size: " << size << endl
       << "B: " << b << endl
       << "C: " << c << endl;
}

template<size_t T>
int standard_reg<T>::getKey(){
  return a;
}

#endif