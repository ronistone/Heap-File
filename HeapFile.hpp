#ifndef _HEAP_FILE_
#define _HEAP_FILE_
#include <bits/stdc++.h>
using namespace std;

#include "page.hpp"

struct RID{
  private:
    int slotId,pageId;
  public:
    RID(){}
    RID(int slot, int page): slotId(slot), pageId(page){}
    int setSlot(int slot){
      return slotId = slot;
    }
    int setPage(int page){
      return pageId = page;
    }
    int getSlot(){
      return slotId;
    }
    int getPage(){
      return pageId;
    }
};

template<class T>
class heap_file{

  private:
    string _PATH;
    streampos size;

  public:
    heap_file();
    heap_file(string p);

    RID insert_reg(T data);
    void remove_reg(RID reg);
    void remove_reg(int slotId, int pageId);
    void update_reg(RID reg, T data);
    void update_reg(int slotId, int pageId, T data);
    void scan();

};

template<class T>
heap_file<T>::heap_file(){}

template<class T>
heap_file<T>::heap_file(string p){
  ifstream fi(p.c_str());
  if(!fi.good()){
    fi.close();
    ofstream f(p.c_str());
    if(f.good()){
      cout << "HEAP FILE CREATE" << endl;
    }else{
      cout << "HEAP FILE CREATION FAILED" << endl;
    }
    fi.seekg(0,fi.end);
    size = fi.tellg();
    f.close();
  }else{
    cout << "HEAP FILE LOADED" << endl;
    fi.seekg(0,fi.end);
    size = fi.tellg();
    fi.close();
  }
  _PATH = p;
}

template<class T>
RID heap_file<T>::insert_reg(T data){

  page<T> p;
  RID in;
  fstream f(_PATH.c_str());

  f.seekp(0, f.end);
  if(f.tellg() >= sizeof(page<T>)){
    f.seekp(-sizeof(page<T>),f.end);
    f.read((char *) &p,sizeof(page<T>));
  }

  // Tenta inserir na ultima pagina
  if(in.setSlot(p.insert(data))==-1){
    page<T> p1;
    in.setSlot(p1.insert(data));

    f.seekg(0,f.end);
    f.write((char *) &p1, sizeof(p));
    f.seekg(0, f.end);
    size = f.tellg();
    in.setPage((size/p1.sizePage())-1);
    cout << "NEW PAGE INSERTION" << endl;
  }else{ // Caso não consiga inserir na ultima pagina insere uma pagina nova no arquivo

    if(f.tellg() >= sizeof(page<T>)){
      f.seekg(-sizeof(page<T>),f.end);
    }else{
      f.seekg(0,f.end);
    }
    f.write((char *) &p, sizeof(p));
    cout << "RECORD INSERTED IN THE LAST PAGE" << endl;
    f.seekg(0,f.end);
    size = f.tellg();
    in.setPage((size/p.sizePage())-1);
  }
  f.close();
  return in;
}


template<class T>
void heap_file<T>::remove_reg(RID reg){
  if(reg.getPage()>=0 and reg.getPage() <= size and reg.getSlot() >=0){
    fstream f(_PATH.c_str());
    page<T> p;

    f.seekp(reg.getPage()*sizeof(page<T>),f.beg);
    f.read((char*) &p, sizeof(page<T>));
    p.remove(reg.getSlot());

    f.seekg(reg.getPage()*sizeof(page<T>),f.beg);
    f.write((char*) &p,sizeof(page<T>));
    cout << "REMOVE REGISTER PAGEID " << reg.getPage() << " SLOTID " << reg.getSlot() << endl;

    f.close();
  }
}
template<class T>
void heap_file<T>::remove_reg(int slotId, int pageId){
  RID reg(slotId,pageId);
  remove_reg(reg);
}

template<class T>
void heap_file<T>::update_reg(RID reg, T data){
  if(reg.getPage() >=0 and reg.getPage() <= size){
      fstream f(_PATH.c_str());
      page<T> p;

      f.seekp(reg.getPage()*sizeof(page<T>),f.beg);
      f.read((char*) & p, sizeof(page<T>));
      p.update(reg.getSlot(),data);

      f.seekg(reg.getPage()*sizeof(page<T>),f.beg);
      f.write((char*) &p, sizeof(page<T>));
      cout << "REGISTER UPDATED" << endl;
      f.close();
  }else{
    cout << "INVALID PAGE" << endl;
  }
}
template<class T>
void heap_file<T>::update_reg(int slotId, int pageId, T data){
  RID reg(slotId,pageId);
  update_reg(reg,data);
}

template<class T>
void heap_file<T>::scan(){
  ifstream f(_PATH.c_str());
  if(f.good()){
    page<T> p;
    while(f.read((char *) &p,sizeof(p))){
      p.scan();
    }
  }else{
    cout << "READ FAILED" << endl;
  }
  f.close();
}


#endif