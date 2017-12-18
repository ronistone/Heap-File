#ifndef __JOIN_OP__
#define __JOIN_OP__

#include "HeapFile.hpp"
//#include "ExtensibleHash.hpp"


template<typename typeIdx, typename reg, int size_page>
heap_file<reg,sizeof(reg)*size_page> nestedIndex(typeIdx idx,
                                      heap_file<reg,sizeof(reg)*size_page> b,
                                        string path, int* count){
  heap_file<reg,sizeof(reg)*size_page> heap(path);
  page<reg, sizeof(reg)*size_page>* p;
  reg aux;

  for(int i=0;;i++){
      (*count)++;
      p = b.get_page(i);
      if(p == NULL)
        break;
      for(int j=0;j < p->slotsPage();j++){
        aux = p->getAt(j);
        if(aux.empty())
          continue;
        if(idx.verify(aux.getKey())){
          heap.insert_reg(aux,count);
        }
      }

  }
  return heap;
}

template<typename typeIdx, typename reg, int size_page>
heap_file<reg,sizeof(reg)*size_page> hashJoin(typeIdx idx,
                                                string sPath,
                                                  string path, int* count){
  heap_file<reg,sizeof(reg)*size_page> heap(path);
  BucketType* p;
  regID aux;
  typeIdx S(1, (char*)sPath.c_str(), count);

  for(int i=0;;i++){
      p = idx.getAt(i);
      if(p == NULL)
        break;
      for(int j=0;j < p->getSize();j++){
        aux = p->getAt(j);
        if(aux.getKey() != -1 and S.verify(aux.getKey())){
          heap.insert_reg(reg(idx.search(aux.getKey()),
                            S.search(aux.getKey())),
                              count);
          (*count) +=2;
        }
      }
  }
  return heap;
}

#endif