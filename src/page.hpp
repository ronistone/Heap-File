#ifndef __PAGE__
#define __PAGE__
#include <bits/stdc++.h>
using namespace std;

//#define PAGE_SIZE 64000
#define REG_N (size_t)(PAGE_SIZE/sizeof(T))
#include "standard_reg.hpp"

template<typename T, int PAGE_SIZE> class page{
  private:
    T reg[REG_N];

  public:
    int insert(T data){
      for(int i=0;i<REG_N;i++){
        if(reg[i].empty()){
          reg[i] = data;
          return i;
        }
      }
      return -1;
    }

    void remove(T data){
      for(int i=0;i<REG_N;i++){
        if(data == reg[i]){
          reg[i].clear();
        }
      }
    }
    void remove(int slotId){
      if(slotId < REG_N and !reg[slotId].empty()){
        reg[slotId].clear();
      }
    }
    void update(int slotId, T data){
      if(slotId < REG_N and slotId >=0){
        reg[slotId] = data;
      }
    }

    void scan(){
      for(int i=0;i<REG_N;i++){
        if(!reg[i].empty()){
            reg[i].scan();
        }
      }
    }

    bool empty(){
      for(int i=0;i<REG_N;i++){
        if(!reg[i].empty())
          return false;
      }
      return true;
    }
    bool isFull(){
      for(int i=0;i<REG_N;i++){
        if(reg[i].empty())
          return false;
      }
      return true;
    }
    size_t slotsPage(){
      return REG_N;
    }
    size_t sizePage(){
      return PAGE_SIZE;
    }
};

#endif