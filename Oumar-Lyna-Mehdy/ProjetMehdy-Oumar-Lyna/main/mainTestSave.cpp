#include <iostream>
#include "node.hh"
#include "save.hh"

using namespace std;

int main()
{
    //1.1
    Node e11;
    e11._x=1;
    e11._y=3;
    e11._j=courant::premier;
    e11._score=1;
    e11._nbsim=1;
    e11._nbcoups=98;
    //1.2
    Node e12;
    e12._x=1;
    e12._y=0;
    e12._j=courant::premier;
    e12._score=1;
    e12._nbsim=1;
    e12._nbcoups=98;

    //1
    Node e1;
    e1._x=1;
    e1._y=2;
    e1._j=courant::deuxième;
    e1._score=2;
    e1._nbsim=2;
    e1._nbcoups=99;
    e1.ajouter_enfant(e11);
    e1.ajouter_enfant(e12);

    //2
    Node e2;
    e2._x=2;
    e2._y=1;
    e2._j=courant::deuxième;
    e2._score=0;
    e2._nbsim=1;
    e2._nbcoups=99;

    //0
    Node root;
    root._x=1;
    root._y=1;
    root._j=courant::premier;
    root._score=3;
    root._nbsim=4;
    root._nbcoups=100;
    root.ajouter_enfant(e1);
    root.ajouter_enfant(e2);

    std::cout<<e1._enfant.at(0)._y<<"\n";
    save s;
    s.exporter(root,"test");
    std::cout<<e2._y<<"\n";


    Node root1=s.import("exarbre.txt");
    std::cout<<"verif import \n ";
    std::cout<<root1._y<<":1 \n "; //racine 0 attendu 1
    std::cout<<root1._enfant.at(0)._y<<":2\n ";//enfant 1 attendu y=2
    std::cout<<root1._enfant.at(0)._enfant.at(0)._y<<":3 \n ";//enfant 1.1 attendu y=3
    std::cout<<root1._enfant.at(0)._enfant.at(1)._y<<":0 \n ";//enfant 1.2 attendu y=0
    std::cout<<root1._enfant.at(1)._y<<":1 \n ";//enfant 2 attendu y=1
    return 0;
}
