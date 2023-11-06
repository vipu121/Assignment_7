// Do NOT add any other includes
#include "search.h"
SearchEngine::SearchEngine(){

}

SearchEngine::~SearchEngine(){
   
    if(front!=NULL){delete front;}
    if(head!=NULL){delete head;}
}
char  SearchEngine:: to_lower(char c) {

        if (c >= 'A' && c <= 'Z') {
            return c + ('a' - 'A');
        }
        return c; 
    }


void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
        if(front==NULL){

            LNode* insert=new LNode(book_code,page,paragraph,sentence_no,sentence);
            front=insert;
            end=insert;
        }
        else{
             LNode* insert=new LNode(book_code,page,paragraph,sentence_no,sentence);
             end->next=insert;
             end=insert;
       
             
        }
}

Node* SearchEngine::search(string pattern, int& n_matches){
    LNode*temp=front;
    int m=pattern.length();
    vector<int> LPS(m,0);
    fillLPS(pattern,LPS);
    while(temp!=NULL){
        int book_cde=temp->book_code;
        int pge=temp->page;
        int para=temp->paragraph;
        int sent=temp->sentence_no;
        int n=temp->sentence.length();
        int i=0;
        int j=0;
        char t;
        while((n-i)>=(m-j)){
            t=to_lower(temp->sentence[i]);
            if(t==to_lower(pattern[j])){
                i++;
                j++;
            
                if(j==m){
                    Node* insert=new Node(book_cde,pge,para,sent,i-j); 
                    if(head==NULL){
                        head=insert;
                        tail=insert;
                    }
                    else{
                        tail->right=insert;
                        tail=insert;
                    }
                    n_matches++;
                    j=LPS[j-1];
                
                    
                }
            }
            else if(i<n && t!=to_lower(pattern[j])){
                if(j==0){
                    i++;
                }
                else{
                    j=LPS[j-1];
                }
            }
        }
        temp=temp->next;
    }
        
    return head;
}
void SearchEngine:: fillLPS(string pattern,vector<int> &v){
        int n=pattern.size();
        int len=0;
        int i=1;
        v[0]=0;
        while(i<n){
            if(pattern[i]==pattern[len]){
                len++;
                v[i]=len;
                i++;
            }
            else{
                if(len==0){
                    v[i]=0;
                    i++;
                }else{
                    len=v[len-1];
                }
            }
        }
}
