/** Distinct representatives */
#include<algorithm>
#include<fstream>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<string>
#include<limits>
#include<list>
#include<iterator>

#include "gbst.hpp"

// --- forward declarations

class VertexArrayRecord;
class LocalTree;
class Network;


// ----------------------------------------------------------------------
// ----- class Vertex                                               -----
// ----------------------------------------------------------------------
class Vertex{
public:
    // --- default ctor
    Vertex(){}
    // --- ctor
    Vertex(int id, int c, int ef, bool f, Vertex *t=nullptr)
    : idnum(id), capacity(c), edgeFlow(ef), forward(f), twin(t) {}

    // ---- operator==
    bool operator==(const Vertex& other) const{
        return idnum == other.idnum;
    }

    bool operator!=(const Vertex& other) const{
        return idnum != other.idnum;
    }

    bool operator<(const Vertex& other) const{
        return idnum < other.idnum;
    }

    bool operator>(const Vertex& other) const{
        return idnum > other.idnum;
    }

private:
    int idnum;
    int capacity;
    int edgeFlow;
    bool forward; // direction
    Vertex *twin; // edget in the opposite direction
    friend class Network;
    friend std::ostream& operator<<(std::ostream& const Vertex&);
};

// ----------------------------------------------------------------------
// ----- class NetTreeNode                                          -----
// ----------------------------------------------------------------------
class NetTreeNode{
public:
    NetTreeNode(VertexArrayRecord **v=nullptr){
        verticesPtr = v;
        adjacent = new std::list<Vertex>;
    }

    bool operator<(const NetTreeNode& other) const{
        return idname < other.idname;
    }

    bool operator==(const NetTreeNode& other) const{
        return idname == other.idname;
    }

private:
    int idnum;
    std::string idname;
    VertexArrayRecord **verticesPtr;
    std::list<Vertex> *adjacent;
    friend class Network;
    friend class LocalTree;
    friend std::ostream& operator<<(std::ostream&, const NetTreeNode&);
};

// ----------------------------------------------------------------------
// ----- class VertexArrayRecord                                    -----
// ----------------------------------------------------------------------
class VertexArrayRecord{
public:
    VertexArrayRecord(){
        adjacent = nullptr;
    }

private:
    std::string idname;
    int vertexFlow;
    bool labeled;
    int parent;
    Vertex *corrVer;    // corresponding vertex: vertex on parents
    std::list<Vertex> *adjacent;
    friend class Network;
    friend class LocalTree;
    friend std::ostream& operator<<(std::ostream&, const Network&);
};

// ----------------------------------------------------------------------
// ----- class LocalTree                                            -----
// ----------------------------------------------------------------------
class LocalTree: public BST<NetTreeNode>{
    void visit(BSTNode<NetTreeNode> *node){
        (*(node->item.verticesPtr))[node->item.idnum].idname = 
            node->item.idname;
        (*(node->item.verticesPtr))[node->item.idnum].adjacent =
            node->item.adjacent;
    }
}

// ----------------------------------------------------------------------
// ----- class Network                                              -----
// ----------------------------------------------------------------------
class Network{
public:
    Network() : sink(1), source(0), none(-1), nvertices(2){
        verticePtr = new VertexArrayRecord*;
    }

    void read_committees(std::string& committees);
    void ford_fulkerson_max_flow();


private:
    const int sink;
    const int source;
    const int none;
    int nvertices;
    VertexArrayRecord *vertices;
    VertexArrayRecord **verticePtr;

    // -- edgeSlack()
    int edgeSlack(Vertex *vertex) const{
        return vertex->capacity - vertex->edgeFlow;
    }

    // -- min()
    int min(int a, int b) const {
        return a < b ? a : b;
    }

    // -- labeled()
    bool labeled(Vertex *vertex) const{
        return vertices[vertex->idnum].labeled;
    }

    void label(Vertex*, int);
    void augment_path();

    friend class LocalTree;
    friend std::ostream(std::ostream&, const Network&);
};

// ----------------------------------------------------------------------
// ----- operator<< for NetTreeNode                                 -----
// ----------------------------------------------------------------------
std::ostream& operator<<(std::ostream& out, const NetTreeNode& node){
    out << node.idnum << " " << node.idname << " ";
    return out;
}

// ----------------------------------------------------------------------
// ----- operator<< for Vertex                                      -----
// ----------------------------------------------------------------------
std::ostream& operator<<(std::ostream& out, const Vertex& vertex){
    out << vertex.idnum << " " << vertex.capacity << " " << vertex.edgeFlow
        << " " << vertex.forward << "| ";
    return out;
}

// ----------------------------------------------------------------------
// ----- operator<< for Network                                     -----
// ----------------------------------------------------------------------
std::ostream& operator<<(std::ostream& out, const Network& net){
    std::ostream_iterator<Vertex> output(out, " ");
    for(int i=0; i < net.nvertices; i++){
        out << i << ": "
            << net.vertices[i].idname << "|"
            << net.vertices[i].vertexFlow << "|"
            << net.vertices[i].labeled << "|"
            << net.vertices[i].parent << "|"
            << "-> ";
        if(net.vertices[i].adjacent != nullptr){
            std::copy(
                net.vertices[i].adjacent->begin(),
                net.vertices[i].adjacent->end(),
                output
            );
        }
        out << std::endl;
    }

    return out;
}