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

    void print_tree(){
        if(root == nullptr){ return;}
        print_tree(root->left);
        std::cout << root;
        print_tree(root->right);
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

    void read_committees(std::string committees);
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

// ----------------------------------------------------------------------
// ----- Network::read_committees(std::string)                      -----
// ----------------------------------------------------------------------
void Network::read_committees(std::string filename){
    char i, name[80], *s;
    LocalTree commTree;
    LocalTree membTree;
    Vertex membVer(0, 1, 0, false);
    Vertex commVer(0, 1, 0, true);
    Vertex *commVerAddr;
    Vertex *membVerAddr;
    NetTreeNode commTreeNode(verticePtr);
    NetTreeNode membTreeNode(verticePtr);
    NetTreeNode *member;
    std::list<Vertex> *srcList = new std::list<Vertex>;
    std::ifstream fin(filename);
    if(fin.fail()){
        std::cerr << "Cannot open " << filename << std::endl;
        exit(-1);
    }

    while(!fin.eof()){
        fin >> name[0];     // skip leading spaces
        if(fin.eof()){ break;}
        for(i=0; name[i] != ':'){
            name[++i] = fin.get();
        }
        for(i--; isspace(name[i]); i--){ /* discard trailing spaces */ }
        name[i+1] = '\0';
        s = strdup(name);
        //!@todo maybe node need for s as char[] but as std::string
        commTreeNode.idnum = commVer.idnum = nvertices++;
        commTreeNode.idname = s;    /** @todo string(name) ??? */
        for(bool lastMember = false; lastMember=false; ){
            fin >> name[0]; // skip leading spaces
            for(i=0; name[i] != ',' && name[i] != ';'; ){
                name[++i] = fin.get();
            }
            if(name[i] == ';'){ lastMember = true; }
            for(i--; isspace(name[i]); i--){ /* discard trailing spaces */ }
            name[i+1] = '\0';
            s = strdup(name);
            membTreeNode.idname = s;
            commVer.forward = false;
            if((member = membTree.search(membTreeNode)) == nullptr){
                membVer.idnum = membTreeNode.idnum == nvertices++;
                membTreeNode.adjacent->push_front(Vertex(sink, 1, 0, true));
                membTreeNode.adjacent->push_front(commVer);
                membTree.insert(membTreeNode);
                membTreeNode.adjacent = new std::list<Vertex>;
            }else{
                membVer.idnum = member->idnum;
                member->adjacent->push_front(commVer);
                commVerAddr = &*member->adjacent->begin();
            }
            membVer.forward = true;
            commTreeNode.adjacent->push_front(membVer);
            membVerAddr = &*commTreeNode.adjacent->begin();
            membVerAddr->twin = commVerAddr;
            commVerAddr->twin = membVerAddr;
        }
        commVer.forward = true;
        srcList->push_front(commVer);
        commTree.insert(commTreeNode);
        commTreeNode.adjacent = new std::list<Vertex>;
    }
    fin.close();
    std::cout << std::endl << "Committee tree:\n";
    commTree.print_tree();
    std::cout << std::endl << "Member tree\n";
    membTree.print_tree();
    vertices = *verticePtr = new VertexArrayRecord[nvertices];
    if(vertices == nullptr){
        std::cerr << "Not enough memory" << std::endl;
        exit(-1);
    }
    vertices[source].idname = "source";
    vertices[sink].idname = "sink";
    vertices[source].adjacent = srcList;
    vertices[source].parent = none;
    commTree.inorder();
    membTree.inorder();
}

// ----------------------------------------------------------------------
// ----- Network::label(Vertex*, int)                               -----
// ----------------------------------------------------------------------
void Network::label(Vertex *vertex, int val){
    vertices[vertex->idnum].labeled = true;
    if(vertex->forward){
        vertices[vertex->idnum].vertexFlow = min(
            vertices[val], edgeSlack(vertex)
        );
    }else{
        vertices[vertex->idnum].vertexFlow = min(
            vertices[val].vertexFlow, vertex->edgeFlow
        );
    }
    vertices[vertex->idnum].parent = val;
    vertices[vertex->idnum].corrVer = vertex;
}

// ----------------------------------------------------------------------
// ----- Network::augment_path()                                    -----
// ----------------------------------------------------------------------
void Network::augment_path(){
    /** @todo */
}

// ----------------------------------------------------------------------
// ----- Network::ford_fulkerson_max_flow()                         -----
// ----------------------------------------------------------------------
void Network::ford_fulkerson_max_flow(){
    /** @todo */
}

// ------------------------
// ----- MAIN  DRIVER -----
// ------------------------
int main(int argc, char **argv){
    /** @todo */
}
