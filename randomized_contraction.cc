#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <sstream>
#include <random>

class Node;

class Edge
{
   public:
    std::array<Node *, 2> nodes_{ { nullptr, nullptr } };
};

class Node
{
   public:
    uint32_t value_;
    std::vector<Edge *> edges_;
};

class Graph
{
   public:
    typedef std::map<uint32_t, Node *> NodeMap;
    typedef std::map<uint32_t, Node *>::iterator NodeMapIt;
    NodeMap nodes_;
    std::set<Edge *> edges_;

    NodeMapIt FindOrCreateNode(const int value) {
        NodeMapIt node_it = nodes_.find(value);
        if(node_it == nodes_.end()) {
            Node *node = new Node();
            node->value_ = value;
            nodes_.emplace(value, node);
            node_it = nodes_.find(value);
        }
        return node_it;
    }

    void InsertNeighbor(Node *node1, Node *node2) {
        for (const auto &edge_it : node1->edges_) {
            for (const auto &node_edge_it : edge_it->nodes_) {
                if (node_edge_it == node2)
                    // There is an edge in common already
                    return;
            }
        }
        // Edge not found, create one
        Edge *edge = new Edge;
        edge->nodes_[0] = node1;
        edge->nodes_[1] = node2;
        node1->edges_.push_back(edge);
        node2->edges_.push_back(edge);
        
        edges_.insert(edge);
    }

    void MergeAndRemoveLoops(Node *node1, Node *node2) {
        for (const auto &edge_it : node2->edges_) {
            std::cout << "Merging vertex " << edge_it->nodes_[0]->value_ << " "
                      << edge_it->nodes_[1]->value_ << std::endl;
            if (edge_it->nodes_[0] == node2) {
                edge_it->nodes_[0] = node1;
            } else {
                edge_it->nodes_[1] = node1;
            }
            node1->edges_.push_back(edge_it);
        }
        //TODO: remove edge in node1 still pointing to node2
        for (std::vector<Edge*>::iterator edge_it = node1->edges_.begin(); edge_it != node1->edges_.end(); ++edge_it) {
            Edge *edge = *edge_it;
            if (edge->nodes_[0] == edge->nodes_[1]) {
                node1->edges_.erase(edge_it);
                edges_.erase(edges_.find(edge));
                std::cout << "Removing loop" << std::endl;
                delete edge;
            }
        }
        delete node2;
    }

    void DumpGraph() {
        for(const auto &node_it : nodes_) {
            std::cout << node_it.second->value_;
            for (const auto &edge_it : node_it.second->edges_) {
                for (const auto &node_edge_it : edge_it->nodes_) {
                    if (node_edge_it != node_it.second)
                        std::cout << "\t" << node_edge_it->value_;
                }
            }
            std::cout << "\t" << std::endl;
        }
    }
};

int KargerCut(Graph &graph)
{
    if (graph.nodes_.size() <= 2) {
        std::cout << "Reached 2 vertex" << std::endl;
        return graph.nodes_.begin()->second->edges_.size();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, graph.edges_.size()); 

    auto edge_it = graph.edges_.begin();
    for (int i = dis(gen); i > 0 ; --i) {
        ++edge_it;
    }
    Edge *edge = *edge_it;
    std::cout << "Will remove edge with vertexes " << edge->nodes_[0]->value_
              << " and " << edge->nodes_[1]->value_ << std::endl;
    graph.MergeAndRemoveLoops(edge->nodes_[0], edge->nodes_[1]);
    
    return KargerCut(graph);
}

int main()
{
    Graph graph;

    std::ifstream file;
    file.open("/tmp/kargerMinCut.txt");
    std::string line;
    if(file.is_open()) {
        while (std::getline(file, line)) {
            //std::cout << line << std::endl;
            std::stringstream ss;
            ss.str(line);
            std::string item;
            std::getline(ss, item, '\t');
            // std::cout << "Vertex: " << item << std::endl;
            uint32_t value = std::stoi(item);
            // Create Node, if not in map
            Graph::NodeMapIt node1 = graph.FindOrCreateNode(value);
            // Creatin edges
            while (std::getline(ss, item, '\t')) {
               // std::cout << item << std::endl;
               try {
                   value = std::stoi(item);
                   Graph::NodeMapIt node2 = graph.FindOrCreateNode(value); 
                   // Insert nodes as neighbors of each other
                   graph.InsertNeighbor(node1->second, node2->second);
               } catch (std::invalid_argument &e) {
               }
            }
        }
        file.close();
    }

    //graph.DumpGraph();

    Graph graph_cut = graph;

    KargerCut(graph_cut);

    graph_cut.DumpGraph();

    return 0;
}
