#include <optional>
#include <string>
#include <iostream>
#include <array>

class ListSL
{
#ifdef TESTING
public:
#endif

    struct Node
    {
        int key;
        float data;
        Node *next;
    };

    Node *root;

public:
    ListSL() : root(nullptr) {}
    ~ListSL();

    std::optional<float> get(int key);
    std::optional<float> update(int key, float data);
    std::optional<float> remove(int key);

    void show(std::string title)
    {
        ListSL::Node *p = root;

        std::cout << title << ": ";
        while (p)
        {
            std::cout << p->key << " ";
            p = p->next;
        }
        std::cout << std::endl;
    }
};

class HashMap
{
#ifdef TESTING
public:
#endif

    const static size_t MAP_SIZE = 101;

    std::array<ListSL, MAP_SIZE> map;

public:
    HashMap();
    ~HashMap();

    std::optional<float> get(int key);
    std::optional<float> update(int key, float data);
    std::optional<float> remove(int key);

    void show(std::string title)
    {
        std::cout << title << std::endl;
        for (int i = 0; i < MAP_SIZE; i++)
        {
            char buf[32];
            snprintf(buf, 32, "[%d]", i);
            map[i].show(buf);
        }
    }
};

class BinarySearchTree
{
    struct Node
    {
        int key;
        float data;
        struct Node *left;
        struct Node *right;

        Node(int v, float d) : key(v), data(d)
        {
            left = right = nullptr;
        }
    };

    Node *root;

    Node *traverse(Node *n, int key);
    Node *delete_node(Node *target);
    void destructor_helper(Node *n);

    void BinarySearchTree::print_node(Node *node)
    {
        if (node->left)
            print_node(node->left);

        std::cout << node->key << " ";
        std::cout << node->data << std::endl;

        if (node->right)
            print_node(node->right);
    }

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree();

    std::optional<float> get(int key);
    std::optional<float> update(int key, float data);
    std::optional<float> remove(int key);

    void show()
    {
        std::cout << "BinarySearchTree: ";
        if (root)
            print_node(root);
        std::cout << std::endl;
    }
};

#ifdef ENABLE_DOUBLY_LINKED_LIST

class ListDL
{
#ifdef TESTING
public:
#endif

    struct Node
    {
        int key;
        float data;
        Node *next;
        Node *prev;
    };

    Node *root;

public:
    ListDL() : root(nullptr) {}
    ~ListDL();

    std::optional<float> get(int key);
    std::optional<float> update(int key, float data);
    std::optional<float> remove(int key);

    void show(std::string title)
    {
        ListDL::Node *p = root;

        std::cout << title << ": ";
        while (p)
        {
            std::cout << p->key << " ";
            p = p->next;
        }
        std::cout << std::endl;
    }
};

#endif // ENABLE_DOUBLY_LINKED_LIST

#ifdef ENABLE_AVL_TREE

class AVLTree
{
    struct Node
    {
        int key;
        float data;
        struct Node *left;
        struct Node *right;
        int height;

        Node(int v, float d) : key(v), data(d), height(1)
        {
            left = right = nullptr;
        }
    };

    Node *root;

    Node *traverse(Node *n, int key);
    Node *insert_node(Node *n, int key, float data);
    Node *delete_node(Node *n, int key);
    Node *rotate_right(Node *y);
    Node *rotate_left(Node *x);
    int get_height(Node *n);
    int get_balance(Node *n);
    void destructor_helper(Node *n);

    void print_node(Node *node)
    {
        if (node->left)
            print_node(node->left);

        std::cout << node->key << " ";
        std::cout << node->data << std::endl;

        if (node->right)
            print_node(node->right);
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree();

    std::optional<float> get(int key);
    std::optional<float> update(int key, float data);
    std::optional<float> remove(int key);

    void show()
    {
        std::cout << "AVLTree: ";
        if (root)
            print_node(root);
        std::cout << std::endl;
    }
};

#endif // ENABLE_AVL_TREE
