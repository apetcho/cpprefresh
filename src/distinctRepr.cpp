/** Distinct representatives */
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
