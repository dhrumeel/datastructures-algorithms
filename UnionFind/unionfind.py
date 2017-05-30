# -*- coding: utf-8 -*-
class UnionFind:
    """
    Union-Find (disjoint-set) datastructure with path-compression and union-by-rank.
    """
    def __init__(self, objs = []):
        self._data = {}
        self.num_disjoint_sets = 0
        for obj in objs:
            self.add_singleton(obj)
            
    def num_items(self):
        """
        Returns the total number of objects in the universe.
        Note: This is not the current number of disjoint-sets.
        """
        return len(self._data.keys())

    def add_singleton(self, obj):
        """
        Add a new singleton-set containing obj.
        """
        if obj in self._data:
            raise ValueError("object {} already exists in the universe".format(obj,))
        self._data[obj] = [obj, 1] # [parent-node, rank]
        self.num_disjoint_sets += 1

    def find_root(self, obj):
        """
        Returns the root (i.e. the representative) of the set containing object obj.
        """
        path = []
        root = self._data[obj][0]
        while root != obj:
            path.append(obj)
            obj = root
            root = self._data[obj][0]
        for obj in path: 
            self._data[obj][0] = root
        return root
    
    def union(self, a, b):
        """
        Unite the sets containing objects a and b.
        """
        a = self.find_root(a)
        b = self.find_root(b)
        if(a == b): return
        ra = self._data[a][1]
        rb = self._data[b][1]
        if(ra >= rb):
            self._data[b][0] = a
        else:
            self._data[a][0] = b
        if(ra == rb): self._data[a][1] += 1
        self.num_disjoint_sets -= 1

    def get_disjoint_sets(self):
        """
        Returns the disjoint sets as a list of lists.
        The first element of each list is the root of that set.
        """
        rootSets = {}
        for obj in self._data.keys():
            root = self.find_root(obj)
            if(root not in rootSets):
                rootSets[root] = [root]
            if (obj != root): rootSets[root].append(obj)
        return rootSets.values()
