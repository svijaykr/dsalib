//
//  graph.h
//  MyDSALib
//
//  Created by Siddharth Vijayakrishnan on 12/10/12.
//  Copyright (c) 2012 Siddharth Vijayakrishnan. All rights reserved.
//

#ifndef __MyDSALib__graph__
#define __MyDSALib__graph__

#include <iostream>
#include <set>

using namespace std;
template <class T> class Edge;
template <class T> class Vertex;


template <class T>
class Edge {
public:
    struct Undirected  {
        bool operator() (const Edge<T>* e_l, const Edge<T>* e_r) {
            if (e_l->value == e_r->value && 
                e_l->head == e_r->tail && 
                e_l->tail == e_r->head) {
                return false;
            } else if (e_l->head == e_r->head && 
                       e_l->head == e_r->tail ) { 
                return e_l->value < e_r->value;  
            } else if (e_l->head == e_r->head) {
                return e_l->tail < e_r->tail;
            } else {
                return e_l->head < e_r->head;
            }
        }

    };
    /*Compare head and tail. X,Y == Y,X for the Undirected graph case
    which is what we are dealing with here 
    */
    bool operator< (const Edge& e) const {
        if (this->value == e.value && 
            this->head == e.tail && 
            this->tail == e.head) {
            return false;
        } else if (this->head == e.head && 
                   this->tail == e.tail) {
            return this->value < e.value;
        } else if (this->head == e.head) {
            return this->tail < e.tail;
        } else {
            return this->head < e.head;
        }
    }
        
    Edge() {}
    Edge(T v, Vertex<T>& h, Vertex<T>& t)  : value(v), head(h), tail(t) { }
    ~Edge() {}

    //Convenience methods
    T GetEdgeValue() const { return this->value; }
    Vertex<T> GetHeadVertex() const { return this->head; }
    Vertex<T> GetTailVertex() const { return this->tail; }
    
private:
    T value;
    Vertex<T> head;
    Vertex<T> tail;
};

template <class T>
class Vertex {
    
public:
    struct VertexCmp {
        bool operator() (const Vertex<T>* v_l, const Vertex<T>* v_r) {
            return v_l->value < v_r->value;
        }

    };
    bool operator< (const Vertex& v) const { return this->value > v.value; }
    bool operator> (const Vertex& v) const { return this->value < v.value; }
    bool operator== (const Vertex& v) const { return this->value == v.value; } 
    
    Vertex& operator= (const Vertex& v) {
        this->value = v.value;
        this->edge_set = v.edge_set;
        return *this; 
    }
    
    Vertex() {}
    Vertex(T v) : value(v) { }
    Vertex(const Vertex& v) {  
        value = v.value;
        edge_set = v.edge_set;
    }
    
    ~Vertex() {}
    
    //Convenience methods
    void AddEdge(Edge<T>*);
    set<Edge<T>*,typename Edge<T>::Undirected> GetEdgeSet() const;
    T GetValue() const { return this->value; }
    

private:
    T value;
    set<Edge<T>*,typename Edge<T>::Undirected> edge_set;
};

template<class T>
void Vertex<T>::AddEdge(Edge<T>* e) {
    this->edge_set.insert(e);
}

template<class T>
set<Edge<T>*,typename Edge<T>::Undirected> Vertex<T>::GetEdgeSet()  const {
    return this->edge_set;
}


template <class T>
class Graph {
    class Iterator;
    
public:
    //Iterators
    class BreadFirstIterator : public Iterator {
    public:
        BreadFirstIterator();
        Vertex<T>& operator*();
        BreadFirstIterator operator++(); //TODO(implement)
            
    private:

    };
    
    class DepthFirstIterator : public Iterator {
    public:
        DepthFirstIterator();
        DepthFirstIterator operator++(); //TODO(implement)
    };
    
    //Constructors etc
    Graph() {}

    Graph(set<Vertex<T>*,typename Vertex<T>::VertexCmp>& v, 
          set<Edge<T>*,typename Edge<T>::Undirected>& e) 
        : vertices_(v), edges_(e) {}

    ~Graph() {}

    //Convenience methods
    set<Edge<T>*,typename Edge<T>::Undirected>& GetEdgeSet();
    set<Vertex<T>*, typename Vertex<T>::VertexCmp>& GetVertexSet();

private:
    set<Vertex<T>*,typename Vertex<T>::VertexCmp > vertices_;
    set<Edge<T>*,typename Edge<T>::Undirected> edges_;
    
};

//implementations follow
template<class T>
set<Edge<T>*,typename Edge<T>::Undirected>& Graph<T>::GetEdgeSet() {
    return edges_;
}

template<class T>
set<Vertex<T>*,typename Vertex<T>::VertexCmp>& Graph<T>::GetVertexSet() {
    return vertices_;
}

#endif /* defined(__MyDSALib__graph__) */
