#ifndef _B_PLUS_TREE_
#define _B_PLUS_TREE_

#include <bits/stdc++.h>
using namespace std;

#include "HeapFile.hpp"


using ll = long long int;

struct regID{
  int key;
  RID r;

  regID(){}
  regID(int slot, int page, int _key): key(_key){
    r.setPage(page);
    r.setSlot(slot);
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

  bool operator <(regID b){ this->key < b.key; }
  bool operator >(regID b){ this->key > b.key; }
  bool operator ==(regID b){ this->key == b.key; }
};

template<int D, typename T>
class BPlusTree{
  public:
      union{
        T data[2*D];
        regID offset[2*D];
      };
      BPlusTree* pointer[(2*D)+1];
      BPlusTree* next, *ant;
      bool leaf;
      int nElem;

      BPlusTree(){
        nElem = 0;
        leaf = false;
        next = NULL;
        ant = NULL;
      }
      BPlusTree(bool isLeaf){
        nElem = 0;
        leaf = isLeaf;
        next = NULL;
        ant = NULL;
      }

};

template<int D, class T>
BPlusTree<D,T>* find(BPlusTree<D,T> b, int _key){
  if(b.leaf){
    return lower_bound(b.offset,b.offset+b.nElem,_key);
  }else{
    return lower_bound(b.data,b.data,b.nElem,_key);
  }
}

#endif


main(){
  BPlusTree<4,int > B;
  B.offset[0] = regID(2,4,5);
  B.data[0] = 5;
  cout << B.offset[0].getSlot() << "  " << B.offset[0].getPage()  << endl;
  cout << B.data[0] << endl;
  cout << sizeof(B.offset) << endl;
}