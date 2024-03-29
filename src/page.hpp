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
        }else if(reg[i].getKey()==data.getKey()){
          return -2;
        }
      }
      return -1;
    }

    int remove(T data){
      for(int i=0;i<REG_N;i++){
        if(data == reg[i]){
          reg[i].clear();
          return 1;
        }
      }
      return 0;
    }
    int removeByKey(int key){
      int flag = 0;
      for(int i=0;i<REG_N;i++){
        if(reg[i].getKey()==key){
          reg[i].clear();
          flag = 1;
        }
      }
      return flag;
    }
    int remove(int slotId){
      if(slotId < REG_N and !reg[slotId].empty()){
        reg[slotId].clear();
        return 1;
      }
      return 0;
    }
    void update(int slotId, T data){
      if(slotId < REG_N and slotId >=0){
        reg[slotId] = data;
      }
    }

    void scan(){
      for(int i=0;i<REG_N;i++){
        if(!reg[i].empty()){
            cout << endl;
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

    T search(int key){
        for(int i=0;i<REG_N;i++){
          if(reg[i].getKey() == key)
            return reg[i];
        }
        T aux;
        return aux;
    }
    T getAt(int slotID){
      if(slotID >= 0 and slotID < REG_N)
        return reg[slotID];
      else
        return T();
    }
};

#endif