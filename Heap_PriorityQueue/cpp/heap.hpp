#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include "heap.h"

using namespace std;

///////////// MinHeap /////////////

template<typename T>
void MinHeap<T>::swap(size_t idxa, size_t idxb)
{
	if(idxa == idxb)
		return;
	T temp = m_data[idxa];
	m_data[idxa] = m_data[idxb];
	m_data[idxb] = temp;
}

template<typename T>
MinHeap<T>::MinHeap(const vector<T>& vec)
{
	m_data.push_back(T());
	for(MinHeap<T>::data_const_iterator it=vec.begin(); it!=vec.end(); ++it)
	{
		this->insert(*it);
	}
	assert(this->size() == vec.size());
	cout << "constructed heap with size " << this->size() << endl;
}

template<typename T>
void MinHeap<T>::insert(const T& t)
{
	m_data.push_back(t);
	upheap(size());
}

template<typename T>
T MinHeap<T>::extract_min()
{
	if(this->size() == 0)
	{
		cerr << "ERROR: Tried to extract out of empty heap";
		exit(0);
	}
	T ret = m_data[1];
	m_data[1] = m_data.back();
	m_data.pop_back();
	downheap(1);
	return ret;
}

template<typename T>
void MinHeap<T>::remove(const T& t)
{
	for(size_t i=1; i<=size();)
	{
		if(m_data[i] == t)
		{
			swap(i,size());
			m_data.pop_back();
			downheap(i);
			upheap(i);
		}
		else
		{
			i++;
		}
	}
}

template<typename T>
void MinHeap<T>::upheap(size_t idx)
{
	size_t pidx = parent(idx);
	while(pidx != 0 && m_data[idx] < m_data[pidx])
	{
		swap(idx, pidx);
		idx = pidx;
		pidx = parent(idx);
	}
}

template<typename T>
void MinHeap<T>::downheap(size_t idx)
{
	size_t lcidx = lchild(idx);
	size_t rcidx = rchild(idx);
	if(lcidx == 0)
		return;
	bool fL = (m_data[idx] > m_data[lcidx]); // left child inconsistent
	bool fR = (rcidx ? (m_data[idx] > m_data[rcidx]) : false); // right child inconsistent
	if(fL)
	{
		if(fR)
		{	// fL and fR
			size_t swapidx = (m_data[lcidx] <= m_data[rcidx]) ? lcidx : rcidx;
			swap(idx, swapidx);
			downheap(swapidx);
			return;
		}
		else
		{	//fL and !fR
			swap(idx, lcidx);
			downheap(lcidx);
			return;
		}
	}
	else
	{
		if(fR)
		{	// !fL and fR
			swap(idx, rcidx);
			downheap(rcidx);
			return;
		}
	}
}


///////////// MaxHeap /////////////

template<typename T>
void MaxHeap<T>::swap(size_t idxa, size_t idxb)
{
	if(idxa == idxb)
		return;
	T temp = m_data[idxa];
	m_data[idxa] = m_data[idxb];
	m_data[idxb] = temp;
}

template<typename T>
MaxHeap<T>::MaxHeap(const vector<T>& vec)
{
	m_data.push_back(T());
	for(MaxHeap<T>::data_const_iterator it=vec.begin(); it!=vec.end(); ++it)
	{
		this->insert(*it);
	}
	assert(this->size() == vec.size());
	cout << "constructed heap with size " << this->size() << endl;
}

template<typename T>
void MaxHeap<T>::insert(const T& t)
{
	m_data.push_back(t);
	upheap(size());
}

template<typename T>
T MaxHeap<T>::extract_max()
{
	if(this->size() == 0)
	{
		cerr << "ERROR: Tried to extract out of empty heap";
		exit(0);
	}
	T ret = m_data[1];
	m_data[1] = m_data.back();
	m_data.pop_back();
	downheap(1);
	return ret;
}

template<typename T>
void MaxHeap<T>::remove(const T& t)
{
	for(size_t i=1; i<=size();)
	{
		if(m_data[i] == t)
		{
			swap(i,size());
			m_data.pop_back();
			downheap(i);
			upheap(i);
		}
		else
		{
			i++;
		}
	}
}

template<typename T>
void MaxHeap<T>::upheap(size_t idx)
{
	size_t pidx = parent(idx);
	while(pidx != 0 && m_data[idx] > m_data[pidx])
	{
		swap(idx, pidx);
		idx = pidx;
		pidx = parent(idx);
	}
}

template<typename T>
void MaxHeap<T>::downheap(size_t idx)
{
	size_t lcidx = lchild(idx);
	size_t rcidx = rchild(idx);
	if(lcidx == 0)
		return;
	bool fL = (m_data[idx] < m_data[lcidx]); // left child inconsistent
	bool fR = (rcidx ? (m_data[idx] < m_data[rcidx]) : false); // right child inconsistent
	if(fL)
	{
		if(fR)
		{	// fL and fR
			size_t swapidx = (m_data[lcidx] >= m_data[rcidx]) ? lcidx : rcidx;
			swap(idx, swapidx);
			downheap(swapidx);
			return;
		}
		else
		{	//fL and !fR
			swap(idx, lcidx);
			downheap(lcidx);
			return;
		}
	}
	else
	{
		if(fR)
		{	// !fL and fR
			swap(idx, rcidx);
			downheap(rcidx);
			return;
		}
	}
}


#endif

