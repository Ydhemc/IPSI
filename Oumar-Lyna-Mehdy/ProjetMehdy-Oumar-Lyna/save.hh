#include "node.hh"
#include <string>

class save {
public:
    int courant(enum::courant c);
    enum::courant courant(int c);
    void noeux(std::ofstream &file, Node arbre);
    Node noeux(std::ifstream &file);

    Node import(std::string fichier);
    void exporter(Node arbre, std::string fichier);
};
