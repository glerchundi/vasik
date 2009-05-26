#ifndef TLIST_H__
#define TLIST_H__

//
// lista enlazada usando la 'list' del STL.
// comentario: muy muy lenta.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
class Node
{
public:
	Node()	{};
	~Node()	{};
	
	char*	name;
	T		data;
};

template <class T>
class TList
{
public:
	TList() 	{};
	~TList()	{};
	
	int add(char *name, T element)
	{
		Node<T> *n = new Node<T>();
	
		n->name = putname(name);
		n->data = element;
	
		myvector.push_back(n);
	
		return 0;	
	};
	
	int add(char *name, T element, int number)
	{
		Node<T>*	n = new Node<T>();
		NodeIterator 	iter;	
		
		iter = myvector.begin();
		while(number) { iter++,number--; }
	
		n->name = putname(name);
		n->data = element;
	
		myvector.insert(iter,n);
		
		return 0;			
	}
	
	int del(char *name)
	{
		int number = getnumber(name);
		if(number != -1)
			return del(number);
			
		return 1;
	};	
	
	int del(int number)
	{
		NodeIterator iter;

		if(number >= myvector.size())
			return 1;

		iter = myvector.begin();		
		while(number) { iter++,number--; }
		
		myvector.erase(iter);
		
		return 0;
	};
	
	void clear(void)
	{
		myvector.clear();
	};

	T get(char *name)
	{
		int number = getnumber(name);
		if(number != -1)
			return get(number);
	};

	T get(int number)
	{
		return myvector[number]->data;
	};
	
	int size(void)
	{
		return myvector.size();
	};
	
	T operator [] (int number)
	{
		return myvector[number]->data;
	};
	
	T operator [] (char *name)
	{
		int number = getnumber(name);
		if(number != -1)
			return get(number);
			
		return 0;
	};
	char* getname(int number)
	{
		NodeIterator iter;

		iter = myvector.begin();
		while(number) { iter++,number--; }
	
		return (*iter)->name;
	};
	
	int getnumber(char *name)
	{
		NodeIterator 	iter;
		int 			size;
		
		size	= myvector.size();
		iter 	= myvector.begin();
		
		while(size)
		{
			if((*iter)->name != NULL && (strcmp(name,(*iter)->name) == 0))
				return myvector.size()-size;
			iter++;
			size--; 
		}
		
		return -1;
	};	
private:
	char* putname(char *name)
	{
		if(name != NULL)
		{
			char *ret = new char[strlen(name)+1];
			strncpy(ret,name,strlen(name));
			ret[strlen(name)] = '\0';
			return ret;
		}

		return NULL;
	};
	
private:
	typedef typename std::vector<Node<T> *>::iterator NodeIterator;	
	vector<Node<T> *> myvector;
};

#endif
