#ifndef __BUCKET_TYPE__
#define __BUCKET_TYPE__

#include <bits/stdc++.h>
#include "RegID.hpp"

class BucketType{
      int depth, size;
      vector<regID> data;
    public:
      BucketType(){}
      BucketType(int d, int s): depth(d), size(s){
        for(int i=0;i<size;i++){
          data.push_back(regID());
        }
      }
      void clear(){
        data.clear();
        for(int i=0;i<size;i++){
          data.push_back(regID());
        }
      }
      int getDepth(){
        return depth;
      }
      int getSize(){
        return size;
      }
      regID getAt(int i){
        if(i >= 0 and i < size)
          return data[i];
        else
          return regID();
      }
      int insert(regID r){
        for(int i=0;i<size;i++){
          if(data[i].getKey()==-1){
            data[i] = r;
            return 1;
          } else if(data[i].getKey() == r.getKey())
            return -2;
        }
        return -1;
      }
      int remove(int key){
        int a=0;
        for(int i=0;i<size;i++){
          if(data[i].getKey() == key){
            data[i].setKey(-1);
            a++;
          }
        }
        return a;
      }
      RID getReg(int key){
        for(int i=0;i<size;i++){
          if(data[i].getKey()==key)
            return data[i].getRID();
        }
      }
      bool search(int key){
        for(int i=0;i<size;i++){
          if(data[i].getKey()==key)
            return true;
        }
        return false;
      }
      int setDepth(int d){
        return depth = d;
      }
      int setSize(int s){
        return size = s;
      }
      int increaseDepth(){
          depth++;
          return depth;
      }
      int decreaseDepth(){
          depth--;
          return depth;
      }
      vector<regID> copy(){
        vector<regID> aux(data.begin(), data.end());
        return aux;
      }
};

#endif