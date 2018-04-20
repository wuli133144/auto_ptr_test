#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "tc_shared_ptr.h"
#include "tc_enable_shared_from_this.h"


using namespace std;
using namespace tars;

typedef int int32_t ;

string int2string(int32_t user_id)
{
    stringstream ss;
    ss << user_id;
    return ss.str();
}

int32_t string2int(const string& value)
{
    return (int)atoi(value.c_str());
}



class personDao:public TC_EnableSharedFromThis<personDao>{

 public:

   string getname(){return name;}
   void setname(string &na){name=na;}
   int32_t getage(){return age;}
   void setage(int32_t _age){age=_age;}


//handler

    virtual void eat()=0;
    virtual void run()=0;
	virtual bool isvalid()=0;
    
    ~personDao(){}

//private:
	string name;
	int32_t age;



};


//xiaoming:public personDao
class xiaoming:public personDao{
         public:
		 	 xiaoming(){}
			 xiaoming(string name1="",int32_t age1=0):name(name1),age(age1){}
			 ~xiaoming(){}
		 virtual void eat(){
			   std::cout<<"i can eat everything"<<std::endl;
			   return;
			 }

		virtual	 void run(){
			   std::cout<<"i can run everything"<<std::endl;
			   return;
			 }

		virtual	 bool isvalid(){
			  return true; 
			 }
private:
        string name;
        int32_t age;
		
};



class proxy:public personDao{

public:
	proxy(){
		
		if(NULL==m_xiaoming){
			m_xiaoming=new xiaoming("xxx",12);
		}
	
	    }		
		void eat(){
		 m_xiaoming->eat();
		}
		
		void run(){
		 m_xiaoming->run();
		}
		
		bool isvalid(){
		    return m_xiaoming->isvalid();
		}
		
  private:
  	xiaoming  *m_xiaoming;



};

/*
class xiaomingprox:public personDao{
public:
    typedef   TC_SharedPtr<personDao>  smart_ptr_type;

	xiaomingprox(){
              if(m_ptr.get()==NULL)
              {
                 m_ptr=TC_SharedPtr<personDao>(new proxy());
              }
			  
	}
 	smart_ptr_type get(){
 	     return sharedFromThis();
          //return 
	}
	
  private:
  	 smart_ptr_type m_ptr;        
};
*/
//policy class

template<typename T>
class creator{
 static T * NEW(){
       return new T;
 }

};


template<typename T>
class  creatormalloc{
  static T * NEW(){
      void * p=malloc(sizeof(T));
	  if(p==NULL)return NULL;
	  return new (p) T;
 
  }


};

template <class T>
struct type_2_type{
      typedef   T  type_original_t;
};


template<int v>
struct int2type{

    enum{value=v;}

};



template <class  U,bool isbool>
class animal{
 public:
 	void todo(const U *	u,int2type<true>)
 	{
 	   std::cout<<"int2type[true]"<<std::endl;
 	}

	void todo(const U * u,int2type<false>)
 	{
 	  std::cout<<"int2type[false]"<<std::endl;
 	}

 public:
   void todo(const U *u)
   { 
          todo(u,int2type<isbool>);
       
   }

};












template<class U,class T>

class creator_new{

public:
  static T * create(const U *args,type_2_type<T>);
   


};


template<class U,class T>
T* create(const U *args,type_2_type<T>){
   return new T(args);

}


template<class U,class T>
T*create(const U*args,type_2_type<string>)

{
             return new string(args);
}



int main(int argc, char * argv [ ])
{
       personDao *ming=new proxy();
       ming->isvalid();
       TC_SharedPtr<personDao>dao(new proxy());
	   std::cout<<"hello"<<std::endl;

       std::cout<<"=================test shared_ptr=====================\n";

 	   std::cout<<"dao 具有唯一权限么？:"<<dao.unique()<<dao.usecount()<<std::endl;
	   dao->eat();
	   
	   //TC_EnableSharedFromThis
	   //TC_SharedPtr<personDao>proxyxiaoming(new xiaomingprox());
	   //TC_SharedPtr<personDao> a=proxyxiaoming->get();

       //class template test


	   creator<int> a=new creator<int>();
	   //a.NEW()
	   creator<int>a;
	   int *pint=a.NEW()








	   
	   
       return 0;

}
