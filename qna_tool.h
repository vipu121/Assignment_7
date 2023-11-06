#include <iostream>
#include <fstream>
#include "Node.h"
#include "dict.h"
#include "search.h"

using namespace std;
class Nodee
{
public:
    // Nodee* root=NULL;
    Nodee *left = NULL;
    Nodee *right = NULL;
    string str = "";
    long long count = 0;
    int height = 0;
};
class General_Dict
{
public:
    Nodee *root;

    long long Search(Nodee *rt, string key);
    Nodee *insert(Nodee *p, string key, int cnt);
    int nodeeHeight(Nodee *nd);
    int balanceFactor(Nodee *p);
    Nodee *newNodee(string strr);
    Nodee *rightRotate(Nodee *y);
    Nodee *leftRotate(Nodee *x);
    int getBalance(Nodee *node);
};

class Corpus_House
{
public:
    Dict *words_counter;
    SearchEngine *word_house;

    Corpus_House();
    ~Corpus_House();
    void corpus_house();
};

class QNA_tool
{

public:
    Corpus_House *house;
    General_Dict *general_house;
    void query_llm(string filename, Node *root, int k, string API_KEY);

    // You can add attributes/helper functions here

public:
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */

    QNA_tool();  // Constructor
    ~QNA_tool(); // Destructor
    void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);
    Node *get_top_k_para(string question, int k);
    // This function takes in a question, preprocess it
    // And returns a list of paragraphs which contain the question
    // In each Node, you must set: book_code, page, paragraph (other parameters won't be checked)
    void QNA_tool::update_scores(string word, vector<vector<vector<int>>> &scores);
    void query(string question, string filename);
    // This function takes in a question and a filename.
    // It should write the final answer to the specified filename.

    /* -----------------------------------------*/
    /* Please do not touch the code above this line */

    // You can add attributes/helper functions here
};