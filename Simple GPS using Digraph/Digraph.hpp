// Digraph.hpp
//
// ICS 46 Spring 2018
// Project #5: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph.  The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <exception>
#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <queue>


// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException : public std::runtime_error
{
public:
    DigraphException(const std::string& reason);
};


inline DigraphException::DigraphException(const std::string& reason)
    : std::runtime_error{reason}
{
}



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a struct template.

template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a struct template.

template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The move constructor initializes a new Digraph from an expiring one.
    Digraph(Digraph&& d) noexcept;

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph() noexcept;

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    // The move assignment operator assigns the contents of an expiring
    // Digraph into "this" Digraph.
    Digraph& operator=(Digraph&& d) noexcept;

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const noexcept;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const noexcept;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the precedessor of that vertex chosen by
    // the algorithm.  For any vertex without a predecessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;
private:
    // Add whatever member variables you think you need here.  One
    // possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.

    std::map<int, DigraphVertex<VertexInfo, EdgeInfo>> mymap;
    int edgeNum;    

public:
    class Compare
    {
        public:
        bool operator()(std::pair<int, double> lhs, std::pair<int, double> rhs)
        {
            return lhs.second < rhs.second;
        }
    };

    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.
};


// You'll need to implement the member functions below.  There's enough
// code in place to make them compile, but they'll all need to do the
// correct thing instead.

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph()
{
    edgeNum = 0;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(const Digraph& d)
{
    mymap = d.mymap;
    edgeNum = d.edgeNum;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(Digraph&& d) noexcept
{
    std::swap(mymap, d.mymap);
    edgeNum = d.edgeNum;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::~Digraph() noexcept
{
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(const Digraph& d)
{
    if(this != &d)
    {
        mymap.clear();
        mymap = d.mymap;
        edgeNum = d.edgeNum;
    }
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(Digraph&& d) noexcept
{
    std::swap(mymap, d.mymap);
    edgeNum = d.edgeNum;
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo, EdgeInfo>::vertices() const
{
    std::vector<int> result;
    for(auto x = mymap.begin(); x != mymap.end(); ++x)
        result.push_back(x->first);
    return result;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges() const
{
    std::vector<std::pair<int, int>> result;
    std::pair<int, int> XtoY;

    for(auto i = mymap.begin(); i != mymap.end(); ++i)
        for(auto x = mymap.at(i->first).edges.begin(); x != mymap.at(i->first).edges.end(); ++x)
        {
            XtoY.first = x->fromVertex;
            XtoY.second = x->toVertex;
            result.push_back(XtoY);     
        }
    return result;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges(int vertex) const
{
    std::vector<std::pair<int, int>> result;
    if(mymap.find(vertex) == mymap.end())
        throw DigraphException("Vertex does not exist");
    else
    {
        for(auto x = mymap.at(vertex).edges.begin(); x != mymap.at(vertex).edges.end(); ++x)
        {
            std::pair<int, int> XtoY;
            XtoY.first = x->fromVertex;
            XtoY.second = x->toVertex;
            result.push_back(XtoY);
        }
    }
    return result;
}


template <typename VertexInfo, typename EdgeInfo>
VertexInfo Digraph<VertexInfo, EdgeInfo>::vertexInfo(int vertex) const
{
    if(mymap.find(vertex) == mymap.end())
        throw DigraphException("Vertex does not exist");
    else
        return mymap.at(vertex).vinfo;
}


template <typename VertexInfo, typename EdgeInfo>
EdgeInfo Digraph<VertexInfo, EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{
    if(mymap.find(fromVertex) == mymap.end())
        throw DigraphException("Vertex does not exist");
    else
    {
    EdgeInfo result;
    int counter = 0;
    int sz = mymap.at(fromVertex).edges.size();
    
    for(auto x = mymap.at(fromVertex).edges.begin(); x != mymap.at(fromVertex).edges.end(); ++x)
    {
        if(x->toVertex != toVertex)
            ++counter;
        else
            if((x->fromVertex == fromVertex) && (x->toVertex == toVertex))
                result = x->einfo;
    }
    
    if(counter == sz)
        throw DigraphException("Edge does not exist");
    return result;
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addVertex(int vertex, const VertexInfo& vinfo)
{
    DigraphVertex<VertexInfo, EdgeInfo> tempvertex;
    if(mymap.find(vertex) != mymap.end())
        throw DigraphException("Vertex already exists");
    else
    {
        tempvertex.vinfo = vinfo;
        mymap.emplace(vertex, tempvertex);
    }

}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo)
{
    DigraphEdge<EdgeInfo> tempedge;
    if(mymap.find(fromVertex) == mymap.end())
        throw DigraphException("Vertex does not exist");
    else
    {
        tempedge.fromVertex = fromVertex;
        tempedge.toVertex = toVertex;
        tempedge.einfo = einfo;
        
        for(auto x = mymap.at(fromVertex).edges.begin(); x != mymap.at(fromVertex).edges.end(); ++x)
            if((x->fromVertex == fromVertex) && (x->toVertex == toVertex))
                throw DigraphException("Edge already exists");
        
        mymap.at(fromVertex).edges.push_back(tempedge);
        ++edgeNum;
    }    
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeVertex(int vertex)
{
    if(mymap.find(vertex) == mymap.end())
        throw DigraphException("Vertex does not exist");
    else
        mymap.erase(vertex);
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeEdge(int fromVertex, int toVertex)
{
    if(mymap.find(fromVertex) == mymap.end())
        throw DigraphException("Vertex does not exist");
    else
    {
        for(auto x = mymap.at(fromVertex).edges.begin(); x != mymap.at(fromVertex).edges.end(); ++x)
            if((x->fromVertex == fromVertex) && (x->toVertex == toVertex))
            {
                mymap.at(fromVertex).edges.erase(x);
                --edgeNum;
                return;
            }
        throw DigraphException("Edge does not exist");
    }
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::vertexCount() const noexcept
{
    return mymap.size();
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount() const noexcept
{
    return edgeNum;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount(int vertex) const
{
    try
    {
        return mymap.at(vertex).edges.size();
    }
    catch(...)
    {
        throw DigraphException("Vertex does not exist");
    }
}


template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::isStronglyConnected() const
{
    bool isAllConnected = false;
    std::map<int, bool> paths;
    std::vector<int> myvector;
    std::vector<int> Vertices = vertices();

    if(Vertices.size() > 0)
        myvector.push_back(Vertices[0]);
    else
        return false;
    
    for(int i = 0; i < Vertices.size(); ++i)
        paths.emplace(Vertices[i], false);

    while(myvector.size() > 0)
    {
        int temp = myvector.back();
        myvector.pop_back();

        if(!paths.at(temp))
        {
            paths.at(temp) = true;
            for(auto x = mymap.at(temp).edges.begin(); x != mymap.at(temp).edges.end(); ++x)
                for(int i = 0; i < Vertices.size(); ++i)
                    if(x->toVertex == Vertices[i] && !paths.at(Vertices[i]))
                        myvector.push_back(Vertices[i]);
        }
    }

    for(auto x = paths.begin(); x != paths.end(); ++x)
    {
        if(x->second)
            isAllConnected = true;
        else
            return false;
    }

    return isAllConnected;
}


template <typename VertexInfo, typename EdgeInfo>
std::map<int, int> Digraph<VertexInfo, EdgeInfo>::findShortestPaths(
    int startVertex,
    std::function<double(const EdgeInfo&)> edgeWeightFunc) const
{   
    std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, Compare> pq;
    std::vector<int> Vertices = vertices();
    std::map<int, double> dist;
    std::map<int, bool> shortestKnown;
    std::map<int, int> prev;
    int max = 1000000;
    std::pair<int, double> vertex_score;
    double score;

    vertex_score.first = startVertex;
    vertex_score.second = 0.0;
    pq.push(vertex_score);

    prev.emplace(startVertex, startVertex);
    dist.emplace(startVertex, 0);
   
    for(int i = 0; i < Vertices.size(); ++i)
    {
        shortestKnown.emplace(Vertices[i], false);
        if(Vertices[i] != startVertex)
        {
            prev.emplace(Vertices[i], -1);
            dist.emplace(Vertices[i], max);
        }
    }

    while(pq.size() > 0)
    {
        int temp = pq.top().first;
        pq.pop();

        if(!shortestKnown.at(temp))
        {
            shortestKnown.at(temp) = true;
            for(auto x = mymap.at(temp).edges.begin(); x != mymap.at(temp).edges.end(); ++x)
            {
                score = edgeWeightFunc(x->einfo);
                for(int i = 0; i < Vertices.size(); ++i)
                    if(!shortestKnown.at(Vertices[i]) && x->toVertex == Vertices[i])
                    {
                        int temp1 = Vertices[i];
                        if(dist.at(temp1) > score)
                        {
                            prev.at(temp1) = temp;
                            dist.at(temp1) = score;
                            vertex_score.first = temp1;
                            vertex_score.second = dist.at(temp1);
                            pq.push(vertex_score);
                        }
                    }
            }
        }
    }
    return prev; 
}



#endif // DIGRAPH_HPP

