// Do NOT add any other includes
// D:\COL ASSIGNMENT\COL_ASS6\testt\dict.cpp
#include "dict.h"
#include <iostream>
#include <fstream>
using namespace std;
Dict::Dict()
{
    root = NULL;
}
void avldeleter(Nodee* tr){
    if(tr->left==NULL&&tr->right==NULL){
        delete tr;
    }
    else if(tr->left == NULL){
        avldeleter(tr->right);
        delete tr;
    }
    else if(tr->right == NULL){
        avldeleter(tr->left);
        delete tr;
    }
    else{
        avldeleter (tr->right);
        avldeleter(tr->left);
        delete tr;
    }
}

Dict::~Dict()
{
    avldeleter(root);
    // Implement your function here
}
int Dict:: nodeeHeight(Nodee *nd)
{
    if(nd==NULL){
        return 0;
    }
    return nd->height;
}

Nodee* Dict:: newNodee(string strr){
    Nodee* nod=new Nodee();
    nod->str=strr;
    nod->left=NULL;
    nod->right=NULL;
    nod->height=1;
    nod->count=0;
    return (nod);
}
int Dict::balanceFactor(Nodee *p)
{
    return nodeeHeight(p->left) - nodeeHeight(p->right);
}

Nodee *Dict::rightRotate(Nodee* y){
    Nodee *x = y->left;
    Nodee *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(nodeeHeight(y->left), nodeeHeight(y->right)) + 1;
    x->height = max(nodeeHeight(x->left), nodeeHeight(x->right)) + 1;

    return x;
}
Nodee *Dict::leftRotate(Nodee *x)
{
    Nodee *y = x->right;
    Nodee *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(nodeeHeight(x->left), nodeeHeight(x->right)) + 1;
    y->height = max(nodeeHeight(y->left), nodeeHeight(y->right)) + 1;

    return y;
}
int Dict:: getBalance(Nodee *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return nodeeHeight(node->left) - nodeeHeight(node->right);
}
Nodee *Dict::insert(Nodee *p, string key)
{

  if (p == NULL)
    {
        Nodee * r=newNodee(key);
        r->count++;
        return r;
    }
    if (key < p->str)
    {
        p->left = insert(p->left, key);
    }
    else if (key > p->str)
    {
        p->right = insert(p->right, key);
    }
    else
    {
        return p;
    }
    p->height = 1 + max(nodeeHeight(p->left), nodeeHeight(p->right));
    int balance = getBalance(p);
    if (balance > 1 && key < p->left->str)
        return rightRotate(p);

    if (balance < -1 && key > p->right->str)
        return leftRotate(p);

    if (balance > 1 && key > p->left->str)
    {
        p->left = leftRotate(p->left);
        return rightRotate(p);
    }

    if (balance < -1 && key < p->right->str)
    {
        p->right = rightRotate(p->right);
        return leftRotate(p);
    }
    return p;
}
Nodee *Dict::Search(Nodee *rt, string key)
{
   
      if (rt == NULL || rt->str == key)
        return rt;

    if (key < rt->str)
        return Search(rt->left, key);

    return Search(rt->right, key);
}
bool Dict::punCheck(char c)
{
    const char *separators = ".,-:!'\"()?[];@";
    for (const char *p = separators; *p; ++p)
    {
        if (*p == c)
        {
            return true;
        }
    }
    return false;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{

    string word = "";
    for (char l : sentence)
    {
        if (l == ' ' || punCheck(l))
        {
            if (!word.empty())
            {
                string lowercaseWord = word;
                for (char &c : lowercaseWord)
                {
                    c = std::tolower(c);
                }
                Nodee *result = Search(root, lowercaseWord);
                if (result != NULL)
                {
                    result->count++;
                }
                else
                {
                    root= insert(root, lowercaseWord);
                }
                word = "";
            }
        }
        else
        {
            word += l;
        }
    }
    if (!word.empty())
    {
        string lowercaseWord = word;
        for (char &c : lowercaseWord)
        {
            c = std::tolower(c);
        }

        if (Search(root, lowercaseWord) != NULL)
        {
            Nodee *n = Search(root, lowercaseWord);
            n->count++;
        }
        else
        {
            root = insert(root, lowercaseWord);
        }
    }
}

int Dict::get_word_count(string word)
{
    string lowercaseWord = word;
    for (char &c : lowercaseWord)
    {
        c = std::tolower(c);
    }
    Nodee *s = Search(root, lowercaseWord);
    return s ? s->count : 0;
}
void Dict::inOrderDump(Nodee *node1, std::ofstream &outputFile)
{
    if (node1)
    {
        inOrderDump(node1->left, outputFile);
        outputFile << node1->str << ", " << node1->count << std::endl;
        inOrderDump(node1->right, outputFile);
    }
}

void Dict::dump_dictionary(string filename)
{
    // Implement your function here
    std::ofstream outputFile(filename);
    inOrderDump(root, outputFile);
    outputFile.close();
}
