#include "node.hh"
#include <string>

class save {
public:
    Node import(std::string fichier);
    void exporter(Node arbre, std::string fichier);
};
