#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>

using namespace std;

template<typename T>
class MinHeap
{
private:
	typedef typename vector<T>::const_iterator data_const_iterator;
	vector<T> m_data;
	size_t parent(size_t idx) const { return (idx >> 1); }
	size_t lchild(size_t idx) const { size_t ret = (idx << 1); return (ret > this->size()) ? 0 : ret; }
	size_t rchild(size_t idx) const { size_t ret = ((idx << 1) + 1); return (ret > this->size()) ? 0 : ret; }
	void swap(size_t idxa, size_t idxb);
	void upheap(size_t idx);
	void downheap(size_t idx);

public:
	MinHeap() { m_data.push_back(T());  assert (m_data.size() == 1); cout << "constructed heap with size " << this->size() << endl; }
	MinHeap(const vector<T>& vec);
	size_t size() const { return (m_data.size() - 1); }
	bool empty() const { return (size() == 0); }
	void reserve(size_t n) const { m_data.reserve(n); }
	void insert(const T& t);
	T extract_min();
	T report_min() const { return m_data[1]; }
	void remove(const T& t);
	
	friend ostream& operator<<(ostream& OUT, const MinHeap<T>& heap) const
	{	OUT << "[ "; for(MinHeap<T>::data_const_iterator it=heap.m_data.begin(); it!=heap.m_data.end(); it++) { OUT << (*it) << " "; } return(OUT << "]");	}
};

template<typename T>
class MaxHeap
{
private:
	typedef typename vector<T>::const_iterator data_const_iterator;
	vector<T> m_data;
	size_t parent(size_t idx) { return (idx >> 1); }
	inline size_t lchild(size_t idx) { size_t ret = (idx << 1); return (ret > this->size()) ? 0 : ret; }
	inline size_t rchild(size_t idx) { size_t ret = ((idx << 1) + 1); return (ret > this->size()) ? 0 : ret; }
	void swap(size_t idxa, size_t idxb);
	void upheap(size_t idx);
	void downheap(size_t idx);

public:
	MaxHeap() { m_data.push_back(T());  assert (m_data.size() == 1); cout << "constructed heap with size " << this->size() << endl; }
	MaxHeap(const vector<T>& vec);
	inline size_t size() const { return (m_data.size() - 1); }
	inline void reserve(size_t n) const { m_data.reserve(n); }
	void insert(const T& t);
	T extract_max();
	inline T report_max() { return m_data[1]; }
	void remove(const T& t);
	
	friend ostream& operator<<(ostream& OUT, const MaxHeap<T>& heap)
	{	OUT << "[ "; for(MaxHeap<T>::data_const_iterator it=heap.m_data.begin(); it!=heap.m_data.end(); it++) { OUT << (*it) << " "; } return(OUT << "]");	}
};

#include "heap.hpp"

#endif
