#include <iostream>

struct Node
{
    int key;
    unsigned int height;
    Node* left;
    Node* right;
    Node(int k)
    {
        key = k;
        left = right = nullptr;
        height = 1;
    }
};

unsigned int height(Node* p)
{
    if (p != nullptr)
        return p->height;
    else
        return 0;
}

int balanceFactor(Node* p)
{
    return height(p->right)-height(p->left);
}

void fixheight(Node* p)
{
    unsigned int hl = height(p->left);
    unsigned int hr = height(p->right);
    if (hl>hr)
        p->height = hl+1;
    else
        p->height = hr+1;
}

Node* rightRotate(Node* p) // правый поворот вокруг p
{
    Node* newP = p->left;
    p->left = newP->right;
    newP->right = p;
    fixheight(p);
    fixheight(newP);
    return newP;
}

Node* leftRotate(Node* p) // левый поворот вокруг p
{
    Node* newP = p->right;
    p->right = newP->left;
    newP->left = p;
    fixheight(p);
    fixheight(newP);
    return newP;
}

Node* balance(Node* p) // балансировка узла
{
    fixheight(p);
    if( balanceFactor(p)==2 )
    {
        if( balanceFactor(p->right) < 0 )
            p->right = rightRotate(p->right);
        return leftRotate(p);
    }
    if( balanceFactor(p)==-2 )
    {
        if( balanceFactor(p->left) > 0  )
            p->left = leftRotate(p->left);
        return rightRotate(p);
    }
    return p;
}

Node* push(Node* p, int k) // вставка
{
    if( !p ) return new Node(k);
    if( k<p->key )
        p->left = push(p->left,k);
    else
        p->right = push(p->right,k);
    return balance(p);
}

Node* findmin(Node* p) // поиск узла с минимальным ключом в дереве
{
    return p->left?findmin(p->left):p;
}

Node* removemin(Node* p) // удаление узла с минимальным ключом из дерева
{
    if( p->left==0 )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

Node* remove(Node* p, int k) // удаление ключа k из дерева p
{
    if( !p ) return 0;
    if( k < p->key )
        p->left = remove(p->left,k);
    else if( k > p->key )
        p->right = remove(p->right,k);
    else {
        Node* q = p->left;
        Node* r = p->right;
        delete p;
        if( !r ) return q;
        Node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

void writeline(int h, Node* p, int k, int rod) {
    if (p == nullptr) {
        for (int i=0; i<=k; i++)
        std::cout << " ";
    }
    else {
        if (k == h) {
            for (int i=0; i< k; i++)
                std::cout << " ";
            std::cout << p->key;
        }
        else if (k > h) {
            writeline(h, p->left, k-1,p->key);
            writeline(h, p->right, k-1,p->key);
        }
    }
}
void writetree(Node* p) {
    if (p != nullptr) {
        for (int i=height(p); i>0; i--) {
            writeline(i, p, height(p), 0);
            std::cout << "\n";
        }
    }
}

void destructor (Node* p){
    if(p != nullptr) {
        destructor (p->left);
        destructor (p->right);
        delete p;
        p = nullptr;
    }
}

int main () {
    Node* avl_tree = nullptr;
    int key;
    int flag = 0;
    while (flag != 5) {
        std::cout << "1) добавление элемента \n2) печать на экран в виде вертикально-ориентированного дерева\n3) удаление элемента\n4) деструктор \n5)конец работы\n";
        std::cin >> flag;
        if (flag == 1){
            std::cout << "Введите значение\n";
            std::cin >> key;
            avl_tree =  push(avl_tree, key);
        }
        if (flag == 2){
            writetree(avl_tree);
        }
        if (flag == 3){
            std::cout << "Введите элемент который хотите удалить\n";
            std::cin >> key;
            avl_tree = remove(avl_tree, key);
        }
        if (flag == 4){
            destructor(avl_tree);
            avl_tree = nullptr;  //изза проблем Xcode
        }
    }
}
