// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class SearchEngine
{
private:
    class LNode
    {
    public:
        string sentence;
        int book_code;
        int page;
        int paragraph;
        int sentence_no;
        LNode *next = NULL;

        LNode(int b_code, int pg, int para, int s_no,  string chr)
        {
            book_code = b_code;
            page = pg;
            paragraph = para;
            sentence_no = s_no;
            sentence = chr;
        }
        ~LNode()
        {
            if (next != NULL)
            {
                delete next;
            }
        }
    };
    LNode *front=NULL;
    Node*tail=NULL;
    LNode*end=NULL;
    Node *head=NULL;

public:
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();
    char to_lower(char c);
    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node *search(string pattern, int &n_matches);
    void fillLPS(string pattern, vector<int> &v);

    /* -----------------------------------------*/
};
