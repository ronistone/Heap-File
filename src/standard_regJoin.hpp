#ifndef _STANDARD_REG_JOIN_
#define _STANDARD_REG_JOIN_

#include <bits/stdc++.h>
using namespace std;

#include "standard_reg.hpp"

template<size_t T> struct standard_reg_join{
  private:
      long int aA;
      unsigned short int aSize;
      char aB[T];
      long int  aC;
      long int bA;
      unsigned short int bSize;
      char bB[T];
      long int  bC;

  public:
      standard_reg_join();
      standard_reg_join(standard_reg <T> a, standard_reg<T> b);

      bool operator==(standard_reg_join b);

      void clear();
      bool empty();
      void scan();
      int getKey();
};

template<size_t T>
standard_reg_join<T>::standard_reg_join(){
  this->clear();
}
template<size_t T>
standard_reg_join<T>::standard_reg_join(standard_reg <T> a, standard_reg<T> b){
  aA = a.getKey();
  strcpy(aB,a.getB());
  aSize = T;
  aC = a.getC();

  bA = b.getKey();
  strcpy(bB,b.getB());
  bSize = T;
  bC = b.getC();
}

template<size_t T>
bool standard_reg_join<T>::operator==(standard_reg_join<T> b){
  return (this->aA == b.aA) and (this->aC == b.aC) and (this->aSize == b.aSize) and (!strcmp(this->aB, b.aB)) and
          (this->bA == b.bA) and (this->bC == b.bC) and (this->bSize == b.bSize) and (!strcmp(this->bB, b.bB));
}

template<size_t T>
void standard_reg_join<T>::clear(){
  aA = INT_MIN;
  aSize = USHRT_MAX;
  aB[0] = '\0';
  aC = INT_MIN;
  bA = INT_MIN;
  bSize = USHRT_MAX;
  bB[0] = '\0';
  bC = INT_MIN;
}

template<size_t T>
bool standard_reg_join<T>::empty(){
  return ((this->aA==INT_MIN) and (this->aSize == USHRT_MAX) and (this->aB[0] == '\0') and (this->aC == INT_MIN)) and
          ((this->bA==INT_MIN) and (this->bSize == USHRT_MAX) and (this->bB[0] == '\0') and (this->bC == INT_MIN));
}

template<size_t T>
void standard_reg_join<T>::scan(){
  cout << "aA: " << aA << endl
       << "aSize: " << aSize << endl
       << "aB: " << aB << endl
       << "aC: " << aC << endl
       << "bA: " << bA << endl
       << "bSize: " << bSize << endl
       << "bB: " << bB << endl
       << "bC: " << bC << endl;
}

template<size_t T>
int standard_reg_join<T>::getKey(){
  return aA;
}

#endif