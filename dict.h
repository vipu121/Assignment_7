// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
class Nodee
{
public:
    // Nodee* root=NULL;
    Nodee *left = NULL;
    Nodee *right = NULL;
    string str = "";
    int count = 0;
    int height = 0;
  
};

class Dict
{
private:
    // You can add attributes/helper functions here
    Nodee *Search(Nodee *rt, string key);
    Nodee *insert(Nodee *p, string key);
    bool punCheck(char c);
    void inOrderDump(Nodee *rt, std::ofstream &outputFile);
    int nodeeHeight(Nodee *nd);
    int balanceFactor(Nodee *p);
    Nodee *newNodee(string st);
    Nodee *rightRotate(Nodee* p);
    Nodee *leftRotate(Nodee *x);
    int getBalance(Nodee *node);

public:
    Nodee *root;
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};
