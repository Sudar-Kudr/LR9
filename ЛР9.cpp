#include <iostream>
#include <cmath>
using namespace std;

template<typename T>
struct Node{
    T key;
    unsigned height;
    Node* left;
    Node* right;
    Node(T k){
        key = k;
        left = right = NULL;
        height = 1;
    }
};


template<typename T>
unsigned height(Node<T>* p){
    if(p == NULL)
        return 0;
    return p->height;
}

template<typename T>
int bfactor(Node<T>* p){
    return height(p->right) - height(p->left);
}

template<typename T>
void fixheight(Node<T>* p){
    int hl = height(p->left);
    int hr = height(p->right);
    p->height = max(hl, hr) + 1;
}

//балансировка
template<typename T>
Node<T>* rotateright(Node<T>* p){
    Node<T>* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

template<typename T>
Node<T>* rotateleft(Node<T>* q){
    Node<T>* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

template<typename T>
Node<T>* balance(Node<T>* p){
    fixheight(p);
    if(bfactor(p) == 2){
        if(bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if(bfactor(p) == -2){
        if(bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

template<typename T>
Node<T>* srl(Node<T>* &p1)
{
    Node<T>* p2;
    p2 = p1->left;
    p1->left = p2->right;
    p2->right = p1;
    p1->height = max(height(p1->left),height(p1->right)) + 1;
    p2->height = max(height(p2->left),p1->height) + 1;
    return p2;
}

template<typename T>
Node<T>* srr(Node<T>* &p1)
{
    Node<T>* p2;
    p2 = p1->right;
    p1->right = p2->left;
    p2->left = p1;
    p1->height = max(height(p1->left),height(p1->right)) + 1;
    p2->height = max(p1->height,height(p2->right)) + 1;
    return p2;
}

template<typename T>
Node<T>* drl(Node<T>* &p1)
{
    p1->left=srr(p1->left);
    return srl(p1);
}

template<typename T>
Node<T>* drr(Node<T>* &p1)
{
    p1->right = srl(p1->right);
    return srr(p1);
}

template<typename T>
void insertNode(Node<T>* &p, T value)
{
    if (p == NULL)
    {
        p = new Node<T>(value);
        p->left=NULL;
        p->right = NULL;
        p->height=0;
    }
    else
    {
        if (value <p->key)
        {
            insertNode(p->left, value);
            if (bfactor(p)==2)
            {
                if (value < p->left->key)
                {
                    p=srl(p);
                }
                else
                {
                    p = drl(p);
                }
            }
        }
        else if (value>p->key)
        {
            insertNode(p->right, value);
            if (bfactor(p)==-2)
            {
                if (value > p->right->key)
                {
                    p=srr(p);
                }
                else
                {
                    p = drr(p);
                }
            }
        }
        else
        {
            cout<<"Элемет уже есть\n"<<endl;
        }
    }
}

template<typename T>
void printNode(Node<T>* p){
    if(p != NULL){
        cout << p->key;
        printNode(p->left);
        printNode(p->right);
    }
}

template<typename T>
void deleteNode(Node<T>* p){
    if(p != NULL){
        deleteNode(p->left);
        deleteNode(p->right);
        delete p;
    }
}

template<typename T>
T deletemin(Node<T>* &p)
{
    T c;
    cout<<"Выбрано удаление минимального значения\n"<<endl;
    if (p->left == NULL)
    {
        c=p->key;
        p=p->right;
        return c;
    }
    else
    {
        c=deletemin(p->left);
        return c;
    }
}

template<typename T>
void del(Node<T>* &p, T x)
{
    Node<T>* d;
    if (p==NULL)
    {
        cout<<"Нет элемента\n"<<endl;
    }
    else if ( x < p->key)
    {
        del(p->left, x);
    }
    else if (x > p->key)
    {
        del(p->right, x);
    }
    else if ((p->left == NULL) && (p->right == NULL))
    {
        d=p;
        delete d;
        p=NULL;
        cout<<"Элемент удален\n"<<endl;
    }
    else if (p->left == NULL)
    {
        d=p;
        free(d);
        p=p->right;
        cout<<"Элемент удален\n"<<endl;
    }
    else if (p->right == NULL)
    {
        d=p;
        p=p->left;
        free(d);
        cout<<"Элемент удален\n"<<endl;
    }
    else
    {
        p->key = deletemin(p->right);
    }
}

template<typename T>
void printT(const std::string& prefix, Node<T>* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        std::cout << node->key << std::endl;

        printT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

template<typename T>
struct AVLTree{
    Node<T>* root;
    //конструктор
    AVLTree(){
        root = NULL;
    }
    void insert(T value){
        insertNode(root, value);
    }
    void print(){
        printNode(root);
    }
    
    void remove(int value){
        del(root, value);
    }
    //деструктор
    ~AVLTree(){
        deleteNode(root);
    }
    
    void prettyPrint(){
        printT("", root, false);
        cout << endl;
    }
};


int main()
{
    AVLTree<int> t;
    
    int el=0;
    int stop=INT_MAX;
    
    cout << "Ввод закончится когда вы сделаете два одинаковых значений подряд\n";
    while (el != stop)
    {
        stop = el;
        cout << "Введите элемент\n";
        cin >> el;
        t.insert(el);
        cout << endl;
        t.prettyPrint();
    }
    
    cout << "Введите элемент который хотите удалить\n";
    cin >> el;
    t.remove(el);
    t.prettyPrint();
    return 0;
}
