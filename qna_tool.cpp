#include <assert.h>
#include <sstream>
#include "qna_tool.h"

using namespace std;

#define FILENAME "mahatma-gandhi-collected-works-volume-1.txt"
Corpus_House::Corpus_House(){
    words_counter=new Dict(); 
    word_house=new SearchEngine();
}
Corpus_House::~Corpus_House(){
    delete word_house;
    delete words_counter;
}
void Corpus_House::corpus_house(){
    int countin = 0;
    std::ifstream inputFile(FILENAME);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file." << std::endl;
        return ;
    }
    // std::ofstream outfile("split.txt" , fstream::app);

    
    std::string tuple;
    std::string sentence;


    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        std::vector<int> metadata;    
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata.push_back(num);
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata.push_back(num);
            }
        }
        word_house->insert_sentence(metadata[0], metadata[1], metadata[2], metadata[3], sentence);
        words_counter->insert_sentence(metadata[0], metadata[1], metadata[2], metadata[3], sentence);
        countin++;
    }

    inputFile.close();
}
QNA_tool::QNA_tool(){
    house=new Corpus_House();
    house->corpus_house();
    general_house=new General_Dict();
     std::ifstream file("unigram_freq.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string word, countStr;

        if (std::getline(lineStream, word, ',') &&
            std::getline(lineStream, countStr, ',')) {
            
            
            long long count = std::stoll(countStr); // Convert count to a long long
            
            general_house->insert(general_house->root,word,count);
        }
    }

}

QNA_tool::~QNA_tool(){
    delete house;
    delete general_house;
    // Implement your function here  
}
void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here  
    return;
}

Node* QNA_tool::get_top_k_para(string question, int k) {
    string s="";
    vector<vector<vector<int>>>scores (98,vector<vector<int>>(600,vector<int>(100,0)));
    for(int i=0;i<question.length();i++){
        if((i==question.length()-1) && (question[i]!=' ' && question[i]!=',' && question[i]!='.' &&question[i]!='(' &&question[i]!=')' &&question[i]!='[' &&question[i]!=']'&&question[i]!=':' &&question[i]!='!' &&question[i]!='\"' &&question[i]!='?' &&question[i]!='-' &&question[i]!='\u2014' && question[i]!='“' && question[i]!='”' && question[i]!='‘' && question[i]!='’' && question[i]!='˙' && question[i]!=';' && question[i]!='@' && question[i]!='\'')){
            s+=question[i];
            update_scores(s,scores);
        }
        if( question[i]==' ' || question[i]==',' || question[i]=='.' ||question[i]=='(' ||question[i]==')' ||question[i]=='[' ||question[i]==']'||question[i]==':' ||question[i]=='!' ||question[i]=='\"' ||question[i]=='?' ||question[i]=='-' ||question[i]=='—' || question[i]=='“' || question[i]=='”' || question[i]=='‘' || question[i]=='’' || question[i]=='˙' || question[i]==';' || question[i]=='@' || question[i]=='\'' ){
            if(s!=""){
                update_scores(s,scores);
                s="";
            }
        }
        else{
            s+=question[i];
        }
    }
    vector<vector<int>> pairs_of_scores;
    for(int i=0;i<98;i++){
        for(int j=0;j<600;j++){
            for(int k=0;k<100;k++){
                if(scores[i][j][k]!=0){
                    vector<int> pairs;
                    pairs.push_back(i);
                    pairs.push_back(j);
                    pairs.push_back(k);
                    pairs.push_back(scores[i][j][k]);
                }
            }
        }
    }
    int i=0;
    Node*root=NULL;
    Node*tail;
    while(k>0){
        if(root==NULL){
            root=new Node();
            root->book_code=pairs_of_scores[i][0];
            root->page=pairs_of_scores[i][1];
            root->paragraph=pairs_of_scores[i][2];
            root=tail;
            i++;
            k--;

        }
        Node* temp=new Node();
        temp->book_code=pairs_of_scores[i][0];
        temp->page=pairs_of_scores[i][1];
        temp->paragraph=pairs_of_scores[i][2];
        tail->left=temp;
        tail=temp;
        k--;
        i++;


    }

    return root;

}
void QNA_tool:: update_scores(string word,vector<vector<vector<int>>>&scores){
    int i=0;
    // vector<vector<vector<int>>>scores (98,vector<vector<int>>(58000,vector<int>(100,0)));
    Node*h=house->word_house->search(word,i);
    float word_score=static_cast<float>(house->words_counter->get_word_count(word)+1)/(general_house->Search(general_house->root,word)+1);
    while(h!=NULL){
        int i=h->book_code;
        int j=h->page;
        int k=h->paragraph;
        scores[i][j][k]+=word_score;
        h=h->left;
    }

}

void QNA_tool::query(string question, string filename){
    // Implement your function here 
     
    std::cout << "Q: " << question << std::endl;
    std::cout << "A: Studying COL106 :)" << std::endl;
    return;
}

void get_paragraph(int book_code, int page, int paragraph, int sentence_no, string &res){
    std::ifstream inputFile(FILENAME);
    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file." << std::endl;
        exit(1);
    }

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        int metadata[4];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph) &&
            (metadata[3] == sentence_no)
        ){
            res = sentence;
            return;
        }

        res = "$I$N$V$A$L$I$D$";
        return;
    }

}

void QNA_tool::query_llm(string filename, Node* root, int k, string API_KEY){

    // first write the 3 paragraphs into different files
    Node* traverse = root;
    int num_paragraph = 0;
    while(num_paragraph < k){
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        ofstream outfile(p_file);
        string paragraph;
        get_paragraph(traverse->book_code, traverse->page, traverse->paragraph, traverse->sentence_no, paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "Hey GPT, What is the purpose of life?";
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();
 
    // python3 <filename> API_KEY paragraph_0.txt paragraph_1.txt paragraph_2.txt query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += "paragraph_0.txt";
    command += " ";
    command += "paragraph_1.txt";
    command += " ";
    command += "paragraph_2.txt";
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
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
General_Dict::General_Dict()
{
    root = NULL;
}
General_Dict::~General_Dict()
{
    avldeleter(root);
    // Implement your function here
}
int General_Dict:: nodeeHeight(Nodee *nd)
{
    if(nd==NULL){
        return 0;
    }
    return nd->height;
}

Nodee* General_Dict:: newNodee(string strr){
    Nodee* nod=new Nodee();
    nod->str=strr;
    nod->left=NULL;
    nod->right=NULL;
    nod->height=1;
    nod->count=0;
    return (nod);
}
int General_Dict::balanceFactor(Nodee *p)
{
    return nodeeHeight(p->left) - nodeeHeight(p->right);
}

Nodee *General_Dict::rightRotate(Nodee* y){
    Nodee *x = y->left;
    Nodee *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(nodeeHeight(y->left), nodeeHeight(y->right)) + 1;
    x->height = max(nodeeHeight(x->left), nodeeHeight(x->right)) + 1;

    return x;
}
Nodee *General_Dict::leftRotate(Nodee *x)
{
    Nodee *y = x->right;
    Nodee *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(nodeeHeight(x->left), nodeeHeight(x->right)) + 1;
    y->height = max(nodeeHeight(y->left), nodeeHeight(y->right)) + 1;

    return y;
}
int General_Dict:: getBalance(Nodee *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return nodeeHeight(node->left) - nodeeHeight(node->right);
}
Nodee *General_Dict::insert(Nodee *p, string key,int cnt)
{

  if (p == NULL)
    {
        Nodee * r=newNodee(key);
        r->count=cnt;
        return r;
    }
    if (key < p->str)
    {
        p->left = insert(p->left, key,cnt);
    }
    else if (key > p->str)
    {
        p->right = insert(p->right, key,cnt);
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
long long General_Dict::Search(Nodee *rt, string key)
{
   
      if (rt == NULL )
        return 0;

      if ( rt->str == key)
            return rt->count;  

    if (key < rt->str)
        return Search(rt->left, key);

    return Search(rt->right, key);
}
