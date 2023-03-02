#include "save.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
bool isNumber(const std::string& str){
    return !str.empty() && std::find_if(str.begin(),str.end(),[](unsigned char c) {return !std::isdigit(c); }) == str.end() ;
}
int courant(courant c){
    if(c==courant::premier){
        return 1;
    }
    return 2;
}
enum::courant courant(int c){
    if(c==1){
        return courant::premier;
    }
    return courant::deuxième;
}
void noeux(std::ofstream &file, Node arbre){

    file<<arbre._x<<" "<<arbre._y<<" "<<courant(arbre._j)<<" ";
    file<<arbre._score<<" "<<arbre._nbsim<<" "<<arbre._nbcoups<<" "<< arbre._enfant.size()<<"\n";
    if(arbre._enfant.size()!=0){
        for(auto i : arbre._enfant){
            noeux(file,i);
        }
    };
}

Node noeux(std::ifstream &file){
    int c;
    int j;
    Node arbre;
    file>>arbre._x;
    file>>arbre._y;
    file>>c; arbre._j=courant(c);
    file>>arbre._score;
    file>>arbre._nbsim;
    file>>arbre._nbcoups;
    file>>j;
    if(j!=0){
        for(int i(0);i<j;i++){
            arbre._enfant.push_back(noeux(file));
        }
    }
    return arbre;
}
Node save::import(std::string fichier)
{
    Node Racine;
    //ouverture fichier
    //curseur au début
    std::ifstream file(fichier);
    if(file){
        //on veut se placer ligne 2
        std::string s;
        int nbsim;
        file>>s;//deplacement curseur après nombre
        file>>s;//après de
        file>>s;//après "simalation:"
        file>> nbsim;
        //curseur normalement sur la deuxième ligne
        //lecture et deplacement du curseur dans noeux
        Racine=noeux(file);
    }

    return Racine;
}

void save::exporter(Node arbre, std::string fichier)
{
    std::string const monficher(fichier+".txt");
    std::ofstream file(monficher.c_str());

    if(file) {
        //entête
        file << "nombre de simulation: "<<arbre._nbsim << "\n";
        //ecriture de l'arbre de maniere recursive
        // x y joueur(courant) score nbsimulation nbcoups nbrenfant
        // si nbrenfant==0 frère ou rien
        // autrement enfant
        noeux(file, arbre);
    }
}
