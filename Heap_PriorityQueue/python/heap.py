# -*- coding: utf-8 -*-

class Heap():    
    def __init__(self, iterable=None):
        if iterable is not None:
            self._data = list(iterable)
            self._heapify()
        else:
            self._data = list()
    
    @staticmethod
    def _lchild(idx):
        return 2*idx + 1
    @staticmethod
    def _rchild(idx):
        return 2*idx + 2
    @staticmethod
    def _parent(idx):
        return (idx-1)//2
    
    def insert(self, val):
        self._data.append(val)
        self._upheap(len(self._data) - 1)
    
    def peekTop(self):
        return self._data[0]
    
    def extractTop(self):
        self._swap(0, -1)
        val = self._data.pop()
        self._downheap(0)
        return val
    
    def _swap(self, i, j):
        self._data[i], self._data[j] = self._data[j], self._data[i]
    
    def _upheap(self, idx):
        while(True):
            if idx == 0:
                return
            parent = self._parent(idx)
            if not self._data[idx] < self._data[parent]:
                return
            self._swap(idx, parent)
            idx = parent # same effect as doing _upheap(parent)
    
    def _downheap(self, idx):
        lc = self._lchild(idx)
        rc = self._rchild(idx)
        size = len(self._data)

        if lc >= size or self._data[idx] < self._data[lc]:
            # idx is OK wrt to left-child
            if rc >= size or self._data[idx] < self._data[rc]:
                # idx is OK wrt both children
                return
            else:
                # left-child is OK, right-child is not
                self._swap(idx, rc)
                self._downheap(rc)
        else:
            # idx is inconsistent wrt left-child
            # swap with smaller of the two children
            if rc >= size:
                swapIdx = lc # there is no right-child
            elif self._data[lc] < self._data[rc]:
                swapIdx = lc # lc is smaller
            else:
                swapIdx = rc
                
            self._swap(idx, swapIdx)
            self._downheap(swapIdx)
    
    def _heapify(self):
        for idx in xrange(len(self._data)-1, -1, -1):
            self._downheap(idx)
    
    def __len__(self):
        return len(self._data)
    
if __name__ == "__main__":
    h = Heap([ 4, 10, 21, 56, 95, 38, 54,  9])
    