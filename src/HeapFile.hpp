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
    map<int,bool> notFullPage;  // (PageID,isFull?)

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
    f.close();
  }else{
    int pag = 0;
    bool b;
    page<T> p;
    fi.seekg(0, fi.beg);
    while(fi.read((char*)&b,sizeof(bool)) and fi.read((char*) &p, sizeof(page<T>))){
      if(!b){
        notFullPage[pag] = true;
      }
      pag++;
    }
    cout << "HEAP FILE LOADED" << endl;
    fi.close();
  }
  _PATH = p;
}

template<class T>
RID heap_file<T>::insert_reg(T data){

  page<T> p;
  RID in;
  bool b;
  fstream f(_PATH.c_str());
  map<int,bool>::iterator it;

  f.seekp(0, f.end);

  // Get first page not Full
  if(notFullPage.size()){
    it = notFullPage.begin();
    while(it!=notFullPage.end()){
      if(it->second){
        f.seekp((it->first)*(sizeof(page<T>) + sizeof(bool)),f.beg);
        f.read((char*)&b, sizeof(bool));
        f.read((char*)&p, sizeof(page<T>));

        in.setSlot(p.insert(data));
        if(f.tellg() >= sizeof(page<T>)){
          f.seekg((it->first)*(sizeof(bool) + sizeof(page<T>)),f.beg);
        }else{
          f.seekg(0,f.end);
        }
        b = p.isFull();
        f.write((char* )&b, sizeof(bool));
        f.write((char *) &p, sizeof(p));
        cout << "RECORD INSERTED" << endl;
        f.seekg(0,f.end);
        in.setPage((f.tellg()/(p.sizePage()+sizeof(bool)))-1);

        // if full erase in map
        if(b){
          notFullPage.erase(in.getPage());
        }
        break;
      }else{
        it++;
      }
    }
    // create new empty page
  }else{
    page<T> p1;
    in.setSlot(p1.insert(data));
    b = false;
    f.seekg(0,f.end);
    f.write((char *)&b,sizeof(bool));
    f.write((char *) &p1, sizeof(page<T>));
    f.seekg(0, f.end);
    in.setPage((f.tellg()/(p1.sizePage()+sizeof(bool)))-1);
    if(!p1.isFull()){
      notFullPage[in.getPage()] = true;
    }
    cout << "NEW PAGE INSERTION" << endl;
  }

  f.close();
  return in;
}


template<class T>
void heap_file<T>::remove_reg(RID reg){

  if(reg.getPage()>=0 and reg.getSlot() >=0){
    fstream f(_PATH.c_str());
    page<T> p;
    bool b;

    f.seekp(reg.getPage()*(sizeof(page<T>) + sizeof(bool)),f.beg);
    f.read((char*) &b, sizeof(bool));
    f.read((char*) &p, sizeof(page<T>));
    p.remove(reg.getSlot());

    b = p.isFull();
    if(!b){
      notFullPage[reg.getPage()] = true;
    }
    f.seekg(reg.getPage()*(sizeof(page<T>) + sizeof(bool)),f.beg);
    f.write((char*) &b, sizeof(bool));
    f.write((char*) &p, sizeof(page<T>));
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
  if(reg.getPage() >=0){
      fstream f(_PATH.c_str());
      page<T> p;

      f.seekp(sizeof(bool) + (reg.getPage()*(sizeof(page<T>) + sizeof(bool))),f.beg);
      f.read((char*) &p, sizeof(page<T>));
      p.update(reg.getSlot(),data);

      f.seekg(sizeof(bool) + (reg.getPage()*(sizeof(page<T>) + sizeof(bool))),f.beg);
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
  bool b;
  if(f.good()){
    page<T> p;
    while(f.read((char*)&b,sizeof(bool)) and f.read((char *) &p,sizeof(p))){
      p.scan();
    }
  }else{
    cout << "READ FAILED" << endl;
  }
  f.close();
}


#endif