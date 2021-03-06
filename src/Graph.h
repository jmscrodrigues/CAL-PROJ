/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <queue>
#include <iterator>
#include <deque>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"
#include "Location.h"
#include "graphviewer.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	bool processing;       // auxiliary field used by isDAG
	int indegree;          // auxiliary field used by topsort
	Vertex * path;
	double dist;

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	int queueIndex;
	T getInfo() const;
	double getDist();
	Vertex *getPath() const;
	Vertex(T in);
	friend class Graph<T>;
};

template <class T>
bool operator<(Vertex<T> v, Vertex<T> v2);

template <class T>
bool operator!=(T v, T v2);

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
class Graph {
	vector<vector<double>> minDist;
	vector<vector<Vertex<T>*>> next;


	void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
	Vertex<T> *findVertex(const T &in) const;
	bool dfsIsDAG(Vertex<T> *v) const;
public:
	vector<Vertex<T> *> vertexSet;
	vector<vector<Vertex<T>*>> getnext() const;
	vector<int> Ids;
	GraphViewer * gv;
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(const T &source) const;
	vector<T> topsort() const;
	int maxNewChildren(const T &source, T &inf) const;
	bool isDAG() const;
	void dijkstraShortestPath(const T &origin, const T &dest);
	void unweightedShortestPath(const T &orig);
	vector<T> getPath(const T &origin, const T &dest) const;
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &orig, const T &dest) const;
	vector<T> getSingleDeliveryPath(const T & origin, const T & dest, vector<T> deliveryPoints);
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in), path(NULL), dist(0) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<vector<Vertex<T>*>> Graph<T>::getnext() const
{
	return next;
}


/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}


/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	Ids.push_back(in.getID());
	return true;
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}


/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	return v1->removeEdgeTo(v2);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	for (auto it = adj.begin(); it != adj.end(); it++)
		if (it->dest  == d) {
			adj.erase(it);
			return true;
		}
	return false;
}


/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
	for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
		if ((*it)->info  == in) {
			auto v = *it;
			vertexSet.erase(it);
			for (auto u : vertexSet)
				u->removeEdgeTo(v);
			delete v;
			return true;
		}
	return false;
}

template<class T>
double Vertex<T>::getDist() {
	return this->dist;
}


template <class T>
bool operator<(Vertex<T> v, Vertex<T> v2) {
	return v.getDist() < v2.getDist();
}

template <class T>
bool operator!=(T v, T v2) {
	return v.getID() == v2.getID();
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
	vector<T> res;
	for (auto v : vertexSet)
		v->visited = false;
	for (auto v : vertexSet)
	    if (! v->visited)
	    	dfsVisit(v, res);
	return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
	v->visited = true;
	res.push_back(v->info);
	for (auto & e : v->adj) {
		auto w = e.dest;
	    if ( ! w->visited)
	    	dfsVisit(w, res);
	}
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
	vector<T> res;
	auto s = findVertex(source);
	if (s == NULL)
		return res;
	queue<Vertex<T> *> q;
	for (auto v : vertexSet)
		v->visited = false;
	q.push(s);
	s->visited = true;
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		res.push_back(v->info);
		for (auto & e : v->adj) {
			auto w = e.dest;
		    if ( ! w->visited ) {
				q.push(w);
				w->visited = true;
		    }
		}
	}
	return res;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
vector<T> Graph<T>::topsort() const {
	vector<T> res;

	for (auto v : vertexSet)
		v->indegree = 0;
	for (auto v : vertexSet)
		for (auto & e : v->adj)
			e.dest->indegree++;

	queue<Vertex<T>*> q;
	for (auto v : vertexSet)
		if (v->indegree == 0)
			q.push(v);

	while( !q.empty() ) {
		Vertex<T>* v = q.front();
		q.pop();
		res.push_back(v->info);
		for(auto & e : v->adj) {
			auto w = e.dest;
			w->indegree--;
			if(w->indegree == 0)
				q.push(w);
		}
	}

	if ( res.size() != vertexSet.size() ) {
		printf("Impossivel\n");
		res.clear();
		return res;
	}

	return res;
}

/****************** 3a) maxNewChildren  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex and the number of new children.
 */

template <class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {
	auto s = findVertex(source);
	if (s == NULL)
			return 0;
	queue<Vertex<T> *> q;
	int maxChildren = 0;
	inf = s->info;
	for (auto v : vertexSet)
		v->visited = false;
	q.push(s);
	s->visited = true;
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		int nChildren=0;
		for (auto & e : v->adj) {
			auto w = e.dest;
			if ( ! w->visited ) {
				w->visited = true;
				q.push(w);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren = nChildren;
			inf = v->info;
		}
	}
	return maxChildren;
}

/****************** 3a) isDAG  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
	for (auto v : vertexSet) {
		v->visited = false;
		v->processing = false;
	}
	for (auto v : vertexSet)
	    if (! v->visited)
	    	if ( ! dfsIsDAG(v) )
	    		return false;
	return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
	v->visited = true;
	v->processing = true;
	for (auto & e : v->adj) {
		auto w = e.dest;
    	if (w->processing)
    		return false;
	    if (! w->visited)
	    	if (! dfsIsDAG(w))
	    		return false;
	}
	v->processing = false;
	return true;
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin, const T &dest) {
    for(Vertex<T>* v: this->vertexSet){
        v->visited = false;
        v->dist = INF;
        v->path = NULL;
    }
    Vertex<T>* v = this->findVertex(origin);
    v->dist = 0;
    MutablePriorityQueue<Vertex<T>> queue;
    queue.insert(v);

    while (!queue.empty()){
        Vertex<T>* v= queue.extractMin();

        for(Edge<T> edge: v->adj){
            if(edge.dest->dist > v->getDist() + edge.weight){
                edge.dest->dist = v->getDist() + edge.weight;
                edge.dest->path = v;
                if(queue.find(edge.dest)){
                	queue.decreaseKey(edge.dest);
                } else{
                	queue.insert(edge.dest);
                }
            }
        }

        if(v == this->findVertex(dest)) {
        	return;
        }

    }

    queue.elements();
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
	vector<T> res;
	Vertex<T> * v = this->findVertex(dest);
	cout << v->getInfo().getID() << "\n";
	while (true){
		if (v->getInfo().getID() == origin.getID()) {
			break;
		}
		else {
			res.push_back(v->getInfo());
			v = v->getPath();
		}
	}
	res.push_back(v->getInfo());
	reverse(res.begin(), res.end());
	return res;
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    for(Vertex<T>* v: this->vertexSet){
        v->visited = false;
        v->dist = INF;
        v->path = NULL;
    }
    Vertex<T>* v = this->findVertex(orig);
    v->dist = 0;
    queue<Vertex<T> *> nextVertex;
    nextVertex.push(v);

    while (!nextVertex.empty()){
        Vertex<T>* v = nextVertex.front();
        nextVertex.pop();
        for(Edge<T> edge: v->adj){
            if(edge.dest->dist == INF){
                edge.dest->dist = v->getDist() + 1;
                edge.dest->path = v;
                nextVertex.push(edge.dest);
            }
        }

    }
}


template<class T>
void Graph<T>::floydWarshallShortestPath() {
	const int infinity = 999999;
	int nVert = vertexSet.size();
	cout << "nVert" << nVert << endl;
	minDist.resize(nVert);
	for (auto & ele : minDist) ele.resize(nVert);

	next.resize(nVert);
	for (auto & ele : next) ele.resize(nVert);

	for (int i = 0; i < nVert; i++) {
		for (int j = 0; j < nVert; j++) {
			minDist.at(i).at(j) = infinity;
			next.at(i).at(j) = NULL;
		}
	}

	cout << "adsfghj" << endl;

	for (Vertex<T> * vertex : vertexSet) {
		for (const Edge<T> & edge : vertex->adj) {
			int i1=-1, i2=-1;
			for (int i = 0; i < nVert; i++)
				if (vertexSet.at(i)->info == vertex->info)
					i1 = i;
			for (int i = 0; i < nVert; i++)
				if (vertexSet.at(i)->info == edge.dest->info)
					i2 = i;

			minDist.at(i1).at(i2) = edge.weight;
			next.at(i1).at(i2) = edge.dest;
		}
	}

	for (int i = 0 ; i < nVert; i++) {
		minDist.at(i).at(i) = 0;
		next.at(i).at(i) = vertexSet.at(i);
	}

	cout << "ihgfds" << endl;

	for (int k = 0 ; k < nVert; k++) {
		cout << "k" << endl;
		for (int i = 0; i < nVert; i++) {
			cout << "i" << endl;
			for (int j = 0 ; j < nVert; j++) {
				cout << "j" << endl;
				if (minDist.at(i).at(k) + minDist.at(k).at(j) < minDist.at(i).at(j)) {
					minDist.at(i).at(j) =  minDist.at(i).at(k) + minDist.at(k).at(j);
					cout << minDist.at(i).at(j) << endl;
					next.at(i).at(j) = next.at(i).at(k);
				}
			}
		}
	}
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	int nVert = vertexSet.size();

	Vertex<T> * v1, * v2;
	v1 = findVertex(orig);
	v2 = findVertex(dest);


	if (v1 == NULL || v2 == NULL) {
		cout << "null" << endl;
		return res;}

	int i1, i2;
	for (int i = 0; i < nVert; i++)
		if (vertexSet.at(i)->info == v1->info)
			i1 = i;
	for (int i = 0; i < nVert; i++)
		if (vertexSet.at(i)->info == v2->info)
			i2 = i;


	if (next.at(i1).at(i2) == NULL) return res;
	res.push_back(v1->info);
	while(v1->info != v2->info) {
		v1 = next.at(i1).at(i2);
		res.push_back(v1->info);
		for (int i = 0; i < nVert; i++)
			if (vertexSet.at(i)->info == v1->info)
				i1 = i;
	}

	for(unsigned int i = 0; i < res.size(); i++)
	{
		cout << res.at(i).getID() << endl;
	}


	return res;
}

template <class T>
vector<T> Graph<T>::getSingleDeliveryPath(const T & origin, const T & dest, vector<T> deliveryPoints){
	vector<T> result;
	Location currentVertexL = (Location) origin;
	T currentVertexT = origin;
	vector<Location> delPL;
	for(size_t i = 0; i < deliveryPoints.size(); i++){
		delPL.push_back((Location) deliveryPoints.at(i));
	}
	cout << "filled delPL" << endl;
	while(!deliveryPoints.empty() && !delPL.empty()){
		int i = findClosestLocation(currentVertexL, delPL);
		cout << "found closest" << endl;
		T tempvert = deliveryPoints.at(i);
		cout << "definitely floydWarshall's fault" << endl;
		vector<T> temp = getfloydWarshallPath(currentVertexT, deliveryPoints.at(i));
		cout << "got floydWarshall" << endl;
		result.insert(result.end(), temp.begin(), temp.end());
		currentVertexL = delPL.at(i);
		currentVertexT = deliveryPoints.at(i);
		delPL.erase(delPL.begin() + i);
		deliveryPoints.erase(deliveryPoints.begin() + i);
	}
	vector<T> temp = getfloydWarshallPath(currentVertexT, dest);
	result.insert(result.end(), temp.begin(), temp.end());

	return result;
}



#endif /* GRAPH_H_ */
