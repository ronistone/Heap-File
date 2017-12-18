#ifndef __REG_ID__
#define __REG_ID__

#include <bits/stdc++.h>
#include "RID.hpp"

struct regID{
  int key;
  RID r;

  regID(){
    key = -1;
  }
  regID(int slot, int page, int _key): key(_key){
    r.setPage(page);
    r.setSlot(slot);
  }
  regID(int _key, RID _r){
    key = _key;
    r = _r;
  }
  int setSlot(int slot){
    return r.setSlot(slot);
  }
  int setPage(int page){
    return r.setPage(page);
  }
  int getSlot(){
    return r.getSlot();
  }
  int getPage(){
    return r.getPage();
  }
  void setKey(int _key){
    key = _key;
  }
  int getKey(){
    return key;
  }
  RID getRID(){
    return r;
  }
  bool empty(){
    return key==-1;
  }
  void print(){
    cout << "Key: " << key << endl;
    r.print();
  }
  bool operator <(regID b){ this->key < b.key; }
  bool operator >(regID b){ this->key > b.key; }
  bool operator ==(regID b){ this->key == b.key; }
};

#endif