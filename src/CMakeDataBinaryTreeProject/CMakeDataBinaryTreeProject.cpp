// CMakeDataBinaryTreeProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataBinaryTreeProject.h"

#pragma once
#include <algorithm>
#include <list>
#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cassert>
#include <map>
#include <sstream>
using namespace std;
 
//------下面的代码是用来测试你的代码有没有问题的辅助代码，你无需关注------
#include <algorithm>
#include <cstdlib>
#include <iostream> 
#include <vector>
#include <utility>
using namespace std;
struct Record { Record(void* ptr1, size_t count1, const char* location1, int line1, bool is) :ptr(ptr1), count(count1), line(line1), is_array(is) { int i = 0; while ((location[i] = location1[i]) && i < 100) { ++i; } }void* ptr; size_t count; char location[100] = { 0 }; int line; bool is_array = false; bool not_use_right_delete = false; }; bool operator==(const Record& lhs, const Record& rhs) { return lhs.ptr == rhs.ptr; }std::vector<Record> myAllocStatistic; void* newFunctionImpl(std::size_t sz, char const* file, int line, bool is) { void* ptr = std::malloc(sz); myAllocStatistic.push_back({ ptr,sz, file, line , is }); return ptr; }void* operator new(std::size_t sz, char const* file, int line) { return newFunctionImpl(sz, file, line, false); }void* operator new [](std::size_t sz, char const* file, int line)
{
    return newFunctionImpl(sz, file, line, true);
}void operator delete(void* ptr) noexcept { Record item{ ptr, 0, "", 0, false }; auto itr = std::find(myAllocStatistic.begin(), myAllocStatistic.end(), item); if (itr != myAllocStatistic.end()) { auto ind = std::distance(myAllocStatistic.begin(), itr); myAllocStatistic[ind].ptr = nullptr; if (itr->is_array) { myAllocStatistic[ind].not_use_right_delete = true; } else { myAllocStatistic[ind].count = 0; }std::free(ptr); } }void operator delete[](void* ptr) noexcept { Record item{ ptr, 0, "", 0, true }; auto itr = std::find(myAllocStatistic.begin(), myAllocStatistic.end(), item); if (itr != myAllocStatistic.end()) { auto ind = std::distance(myAllocStatistic.begin(), itr); myAllocStatistic[ind].ptr = nullptr; if (!itr->is_array) { myAllocStatistic[ind].not_use_right_delete = true; } else { myAllocStatistic[ind].count = 0; }std::free(ptr); } }
#define new new(__FILE__, __LINE__)
struct MyStruct { void ReportMemoryLeak() { std::cout << "Memory leak report: " << std::endl; bool leak = false; for (auto& i : myAllocStatistic) { if (i.count != 0) { leak = true; std::cout << "leak count " << i.count << " Byte" << ", file " << i.location << ", line " << i.line; if (i.not_use_right_delete) { cout << ", not use right delete. "; }	cout << std::endl; } }if (!leak) { cout << "No memory leak." << endl; } }~MyStruct() { ReportMemoryLeak(); } }; static MyStruct my; void check_do(bool b, int line = __LINE__) { if (b) { cout << "line:" << line << " Pass" << endl; } else { cout << "line:" << line << " Ohh! not passed!!!!!!!!!!!!!!!!!!!!!!!!!!!" << " " << endl; exit(0); } }
#define check(msg)  check_do(msg, __LINE__);
//------上面的代码是用来测试你的代码有没有问题的辅助代码，你无需关注------
 
template<typename T>
class binary_search_tree
{
private:
    struct tree_node
    {
        tree_node() :data(T()){}
        tree_node(const T& t) :data(t){}
        bool exist_parent(void) const { return parent != nullptr; }
        T data;
        tree_node* parent = nullptr;
        tree_node* left = nullptr;
        tree_node* right = nullptr;
    };
public:
    binary_search_tree(void) :m_root(nullptr) {}//默认构造函数：什么也不需要做，因为成员定义的时候就已经初始化了
    binary_search_tree(const T*, const int);//从数组构造一颗二叉树
    binary_search_tree(const binary_search_tree&);//拷贝构造函数
    binary_search_tree& operator = (const binary_search_tree&);
    ~binary_search_tree(void) { clear(); }//析构函数
public:
    int size(void) const;//元素数量
    bool empty(void) const { return size() == 0; }//二叉树是否为空
    bool insert(const T& data);//插入一个元素
 
    T minmum(void) const;//最小值
    T maxmum(void) const;//最大值
 
    bool exists(const T& data) const;//判断元素是否存在
    void clear(void);//非递归清空二叉树
    void erase(const T& data);
 
    template<typename T>
    friend ostream& operator<<(ostream& out, const binary_search_tree<T>& tree);//输出二叉树
    void print_pre_order_nonrecursive(void) const;//非递归:先序遍历输出二叉树
    void print_in_order_nonrecursive(void) const;//非递归:中序遍历输出二叉树
    void print_post_order_nonrecursive(void) const;//非递归:后续遍历输出二叉树
 
    void print_in_order_recursive(std::ostream& os) const;//递归中序遍历输出二叉树
    void print_element_order(void) const;//非递归按元素顺序输出二叉树
    std::string to_string_in_order(void) const;
    int max_length_between_node(void) const;//最大节点距离
    int height(void) const;//树高度
    bool operator==(const binary_search_tree& other) const;//两个树相等：结构相同，对应元素相同
    bool operator!=(const binary_search_tree& other) const { return !equal(other); }//两个树不相等
    bool equal(const binary_search_tree& other) const;//两个树相等：结构相同，对应元素相同
private:
    void print_binary_tree(ostream&, const tree_node* bt, int depth) const;//二叉树形式打印二叉树
    tree_node* find(const T& data);//查找
    tree_node* maxmum(tree_node*) const;//最大节点
    tree_node* minmum(tree_node*) const;//最小节点
    tree_node* successor(tree_node* t) const;//后继节点
    //节点的深度与高度：对于树中相同深度的每个结点来说，它们的高度不一定相同，这取决于每个结点下面的叶结点的深度
    int height(const tree_node* _t) const;
    bool equal(const tree_node* lhs, const tree_node* rhs) const;//两个树相等：结构相同，对应元素相同
    bool is_node_leaf(const tree_node* node) const;
    bool is_left_child(const tree_node* parent, const tree_node* node);
    bool is_leaf_node_equal(const tree_node* lhs, const tree_node* rhs) const;
    void copy(const binary_search_tree& other);
    void copy_node_from(tree_node*& dest, tree_node* dest_parent, const tree_node* from);
    void print_in_order_recursive(std::ostream& os
        , const tree_node* node) const;//递归中序遍历输出二叉树
    void erase_node(tree_node*& pnode);//参数是引用类型，主要是为了：erase_node(m_root) 时，更新m_root;
    void erase_and_reconnect(tree_node*& pnode, tree_node* pnode_child);
    void update_parent(tree_node* pnode);//删除叶子结点后，让父节点指向空指针
private:
    tree_node* left(tree_node* p)
    {
        assert(p != nullptr);
        return p->left;
    }
private:
    tree_node* m_root = nullptr;
    int m_size = 0;
};
template<typename T>
std::string binary_search_tree<T>::to_string_in_order(void) const
{
    std::stringstream oss;
    this->print_in_order_recursive(oss);
    auto str = oss.str();
    return str;
}
template<typename T>
binary_search_tree<T>::binary_search_tree(const T* arr, const int length) : binary_search_tree()
{
    //(4) your code 
    //可以使用成员函数insert(const T& data) 来实现这个函数
}
template<typename T>
binary_search_tree<T>::binary_search_tree(const binary_search_tree & from) :m_root(nullptr)
{
    //(5) your code 
    //可以使用成员函数copy来实现
}
template<typename T>
binary_search_tree<T>& binary_search_tree<T>::operator=(const binary_search_tree & from)
{
    //(5) your code 
    //可以使用成员函数copy来实现。
    //从这里可以看出copy函数应该先用clear成员函数清空自己原有的全部节点
 
 
    return *this;
}
template<typename T>
void binary_search_tree<T>::copy(const binary_search_tree& other)
{
    if (this == &other)//如果拷贝自己，则什么也不做
    {
        return;//直接返回
    }
    clear();//先清空自己的内容
    m_size = other.m_size;//成员变量赋值
    if (other.m_root)//从根节点开始拷贝；递归的拷贝二叉树的每一个节点，照葫芦画瓢
    {
        copy_node_from(m_root/*需要被创建的节点*/, nullptr/*需要被创建的节点的父节点：用户指向孩子*/, other.m_root/*提供节点存储的数据*/);
    }
}
template<typename T>
bool binary_search_tree<T>::insert(const T& data)
{
    if (m_root != nullptr)
    {
        tree_node *fast, *slow, *ptemp;
        fast = slow = ptemp = m_root;
 
        while (fast != 0)
        {
            slow = fast;
            if (data < slow->data)
            {
                fast = slow->left;
            }
            else if (data > slow->data)
            {
                fast = slow->right;
            }
            else
            //esle equal do nothing 元素不允许重复
            //，元素如果已经存在，什么也不做
            {
                fast = 0;
                return false;//直接退出，不再插入相同的元素的
            }
        }
        if (data < slow->data)
        {
            slow->left = new tree_node(data);
            slow->left->parent = slow;
        }
        else if (data > slow->data)
        {
            slow->right = new tree_node(data);
            slow->right->parent = slow;
        }
        else
        {
            return false;
        }
        //esle equal do nothing
    }
    else
    {
        m_root = new tree_node(data);
    }
    ++m_size;
    return true;
}
template<typename T>
int binary_search_tree<T>::height(void) const
{
    return height(m_root);
}
template<typename T>
int binary_search_tree<T>::height(const tree_node* _t) const
{
    //树的高度，也是树的层树，最大层的层数就是树的高度
    //(7) your code 如果没有元素，返回0
    // 如果只有一个根节点，没有孩子节点高度为1
    // 如果有孩子节点，树的高度就 = 1 + 孩子节点的高度（左右子树高度较大的那一个）
 
 
    return -1;
}
template<typename T>
bool binary_search_tree<T>::operator==(const binary_search_tree & other) const
{
    return this->equal(other);//两个二叉树相等，当且仅当两颗树长的一模一样
}
template<typename T>
bool binary_search_tree<T>::equal(const binary_search_tree & other) const
{
    return equal(m_root, other.m_root);
}
template<typename T>
bool binary_search_tree<T>::equal(const tree_node* lhs, const tree_node* rhs) const
{
    // 先判断两个树是否为空
 
    //再判断两个树是否都是叶子节点  可以使用 is_leaf_node_equal 成员函数
 
    //再判断两个树的两个左右子树是否同时相等  可以递归调用当前equal函数
 
    //(8) your code
 
    return false;
}
template<typename T>
bool binary_search_tree<T>::is_leaf_node_equal(const tree_node* lhs
    , const tree_node* rhs) const
{
    if (is_node_leaf(lhs) && is_node_leaf(rhs))
    {
        return lhs->data == rhs->data;
    }
    return false;
}
template<typename T>
bool binary_search_tree<T>::is_node_leaf(const tree_node * node) const
{
    return node != nullptr && node->left == nullptr && node->right == nullptr;
}
 
 
template<typename T>
// dest需要被创建的节点, dest_parent 需要被创建的节点的父亲节点
void binary_search_tree<T>::copy_node_from(tree_node *& dest, tree_node* dest_parent, const tree_node * from)
{
    //(9) your code 深度拷贝from节点，并切递归拷贝，从而完成整棵树的拷贝
 
    //注意dest节点传递的是引用，这意味着你可以非常方便的对这个地址变量赋值，赋值就会修改传进来的外部变量
 
    //改函数使用递归调用自己的方式，完成整棵树的拷贝。注意对左子树和又子树可能需要分别调用一次递归函数才能完成。
 
}
 
template<typename T>
int binary_search_tree<T>::max_length_between_node(void) const
{
    int max_length = 0;
 
    const tree_node* ptree = m_root;
 
    list<tree_node*> listNode;
 
    listNode.push_back(m_root);
    while (!listNode.empty())
    {
        auto pnode = listNode.front();
        listNode.pop_front();
        if (pnode->left != nullptr)
        {
            listNode.push_back(pnode->left);
        }
        if (pnode->right != nullptr)
        {
            listNode.push_back(pnode->right);
        }
        int tempBetween = height(pnode->left) + height(pnode->right);
 
        max_length = std::max<int>(tempBetween, max_length);
    }
 
 
    return max_length;
}
template<typename T>
void binary_search_tree<T>::clear(void)
{
    //使用一个辅助队列(或者栈)，层次遍历删除所有节点。
    //遍历到一个节点A就把孩子BC放到队列，并把这个节点A从队列里取出释放
    //(10) your code
 
 
}
template<typename T>
void binary_search_tree<T>::print_binary_tree(ostream& out, const tree_node* bt, int depth) const
{
    //用右左孩子的方式输出一颗树,先输出右孩子后输出左孩子
    if (bt)
    {
        print_binary_tree(out, bt->right, depth + 1);
 
        if (depth == 0)
        {
            out << bt->data << endl;
        }
        else if (depth == 1)
        {
            out << " --" << bt->data << endl;
        }
        else
        {
            int n = depth;
            while (--n)
            {
                cout << "    ";
            }
            out << " --" << bt->data << endl;
        }
 
        print_binary_tree(out, bt->left, depth + 1);
    }
}
template<typename T>
void binary_search_tree<T>::print_in_order_nonrecursive(void) const
{
    cout << "print_in_order_nonrecursive : ";
    stack<tree_node*> tempstack;
    tree_node* t = m_root;
    if (t != NULL)
    {
        do
        {
            tempstack.push(t);
            t = t->left;
        } while (t != NULL);
    }
    while (!tempstack.empty())
    {
        tree_node* p = tempstack.top();
        cout << p->data << " ";
        tempstack.pop();
        if (p->right != NULL)
        {
            p = p->right;
            do
            {
                tempstack.push(p);
                p = p->left;
            } while (p != NULL);
        }
    }
    cout << endl;
}
template<typename T>
void binary_search_tree<T>::print_in_order_recursive(std::ostream & os) const
{
    print_in_order_recursive(os, m_root);
}
template<typename T>
void binary_search_tree<T>::print_in_order_recursive(std::ostream & os, const tree_node * node) const
{
    if (node == nullptr)
    {
        return;
    }
    print_in_order_recursive(os, node->left);
    os << node->data << " ";
    print_in_order_recursive(os, node->right);
}
template<typename T>
ostream& operator<<(ostream& out, const binary_search_tree<T>& tree)
{
    tree.print_binary_tree(out, tree.m_root, 0);
    return out;
}
template<typename T>
void binary_search_tree<T>::print_post_order_nonrecursive(void) const
{
    //后续序序遍历输出一颗树的全部结点值2,3,1
    //广度优先遍历
    cout << "print_post_order_nonrecursive : ";
    typedef pair<tree_node*, bool> multinode;
    stack<multinode> tempstack;
    if (m_root)
    {
        tempstack.push(make_pair(m_root, false));
    }
    while (!tempstack.empty())
    {
        multinode m = tempstack.top(); tempstack.pop();
        if (m.first->left == NULL && m.first->right == NULL)
        {//叶子节点直接输出
            cout << m.first->data << " ";
        }
        else if (m.second == true)
        {//所有孩子都遍历完了才会到这一步
            cout << m.first->data << " ";
        }
        else
        {//非终结点，并且孩子还没遍历完。
            m.second = true; tempstack.push(m);
            if (m.first->right != NULL)
            {
                tempstack.push(make_pair(m.first->right, false));
            }
            if (m.first->left != NULL)
            {
                tempstack.push(make_pair(m.first->left, false));
            }
        }
    }
    cout << endl;
}
template<typename T>
void binary_search_tree<T>::print_pre_order_nonrecursive(void) const
{
    //先序遍历输出一颗树的全部结点值1,2,3,先根遍历
    cout << "print_pre_order_nonrecursive : ";
    stack<tree_node*> node_stack;
    if (m_root)
    {
        node_stack.push(m_root);
        tree_node* t;
        while (!node_stack.empty())
        {
            t = node_stack.top();
            node_stack.pop();
            cout << t->data << " ";
            if (t->right != 0)
            {
                node_stack.push(t->right);
            }
            if (t->left != 0)
            {
                node_stack.push(t->left);
            }
        }
        cout << endl;
    }
}
template<typename T>
bool binary_search_tree<T>::exists(const T& data) const
{
    bool result = false;
    if (m_root)
    {
        tree_node* pfind = m_root;
        while (pfind)
        {
            if (pfind->data == data)
            {
                result = true;
                break;
            }
            else if (data < pfind->data)
            {
                pfind = pfind->left;
            }
            else
                pfind = pfind->right;
        }
    }
    return result;
}
template<typename T>
typename binary_search_tree<T>::tree_node* binary_search_tree<T>::find(const T& data)
{
    //(11) your code 利用find，非递归实现：查找某个值是否存在于树中
    return nullptr;
}
 
template<typename T>
int binary_search_tree<T>::size(void) const
{
    return m_size;
}
template<typename T>
T binary_search_tree<T>::minmum(void) const
{
    //(12) your code 返回最小值 ，请使用成员函数 minmum(tree_node* p) const  来实现
    return T();
}
template<typename T>
typename binary_search_tree<T>::tree_node* binary_search_tree<T>::minmum(tree_node* p) const
{
    //(13) your code 返回最小值：非递归实现
    return nullptr;
}
template<typename T>
T binary_search_tree<T>::maxmum(void) const
{
    //(14) your code 返回最大值 ，请使用成员函数 maxmum(tree_node* p) const  来实现
    return T();
}
template<typename T>
typename binary_search_tree<T>::tree_node* binary_search_tree<T>::maxmum(tree_node* t) const
{
    //(14) your code 返回最大值：非递归实现
    return nullptr;
}
template<typename T>
typename binary_search_tree<T>::tree_node* binary_search_tree<T>::successor(tree_node* t) const
{
    //(15) your code  找到一个节点的后继结点，这个函数是顺序迭代遍历二叉树的关键函数。
    //具体思路为，如果这个节点有右子树，那么右子树的minmum节点就是后继结点。
    //如果，这个节点没有右子树，比该节点大的值，一定是往右上方去的第一个节点。
    //参考《算法导论》
 
 
    return nullptr;
}
template<typename T>
void binary_search_tree<T>::print_element_order(void) const
{
    cout << "print_element_order by order: ";
    if (!empty())
    {
        //(16) your code 使用后继节点成员函数作为顺序迭代的依据，实现顺序遍历一颗二次函数。
        //循环获取后继，只要有后继，就输出这个后继。
 
 
        cout << endl;
    }
}
 
template<typename T>
void binary_search_tree<T>::erase(const T& data)
{
    tree_node* itr = find(data);
    assert(itr != nullptr);
    --m_size;
    if (itr == m_root)
    {
        /*删除根节点，可能需要释放根节点本身，这个时候m_root的指向需要更新。
        * 所以erase_node的参数是引用类型，希望可以在erase_node内部对m_root重新
        * 赋值来打到更新根节点指向的目的。
        */
        erase_node(m_root);
        return;
    }
    else
    {
        erase_node(itr);
    }
}
template<typename T>
void binary_search_tree<T>::erase_node(tree_node*& pnode)
{
    //pnode如果没有parent，那么它就是root，这个时候，删除pnode
    // ，无需考虑pnode的parent需要更新的问题。
    //只需要处理其孩子替代自己的问题
 
    if (pnode->left == nullptr && pnode->right == nullptr)
    {
        //叶子结点被删除了的话，被删除节点的父亲应该指向空指针。
        update_parent(pnode);//内部会先判断pnode有没有parent
        delete pnode;
        //这里会更新传进来的引用参数，比如，如果传进来的是m_root的话。
        pnode = nullptr;//如果pnode是m_root的话，这句话就会变得必不可少（更新m_root）
    }
    //如果被删除的节点p只有左孩子：让p的左孩子p_left_child取代自己作为p的parent节点的做孩子
    else if (pnode->left != nullptr && pnode->right == nullptr)
    {
        //让pnode的父亲节点和pnode的孩子建立连接
        erase_and_reconnect(pnode, pnode->left);
    }
    //如果只有右孩子：让右孩子取代自己
    else if (pnode->left == nullptr && pnode->right != nullptr)
    {
        //让pnode的父亲节点和pnode的孩子建立连接
        erase_and_reconnect(pnode, pnode->right);
    }
    else
    {
        //https://zhuanlan.zhihu.com/p/640863892
        //分成下面几个步骤进行：
        //1 找到z的后继，y是z的后继。这时候可以确定y是不可能有左孩子的。
        //2 删除y，让y的右孩子x取代自己的位置。删除只有一个孩子的节点上面已经讨论过。
        //3 让y的值覆盖z的值。
        tree_node* psuccessor = successor(pnode);
        pnode->data = psuccessor->data;//3 让y的值覆盖z的值。
        //2 删除y, y只有一个孩子，只有一个孩子的节点删除此函数的开始部分已经实现了。只需要调用此函数即可。
        //(17) your code
    }
}
template<typename T>
void binary_search_tree<T>::update_parent(tree_node* pnode)
{//删除叶子结点后，让父节点指向空指针
    if (pnode->parent)
    {
        auto parent = pnode->parent;
        is_left_child(parent, pnode) ? (parent->left = nullptr) : (parent->right = nullptr);
    }
}
template<typename T>
void binary_search_tree<T>::erase_and_reconnect(tree_node*& delete_pnode, tree_node* pnode_child)
{
    //让左孩子取代自己，同时考虑parent不存在的情况下取代自己。
    if (delete_pnode->exist_parent())
    {
        //拿到父节点
        auto parent = delete_pnode->parent;
        auto is_left = is_left_child(parent, delete_pnode);
        //先备份地址，将来用于释放内存
        auto pbackup = delete_pnode;
        //指向新节点：自己的左孩子替代自己
        // reconnect1 ->
        delete_pnode = pnode_child;
        // <- reconnect2 
        pnode_child->parent = parent;//指向新的父亲
        //删除自己原来的内存
        delete pbackup;
 
        //父节点和自己的左孩子建立连接
        is_left ? parent->left = delete_pnode : parent->right = delete_pnode;
    }
    else //删除根节点， 删除根节点可不是删除整个树哦
    {
        //先备份地址，将来用于释放内存
        auto pbackup = delete_pnode;
        //指向新节点：自己的左孩子替代自己
        delete_pnode = pnode_child;
        //删除自己原来的内存
        delete pbackup;
    }
}
template<typename T>
bool binary_search_tree<T>::is_left_child(const tree_node* parent, const tree_node* pnode)
{
    assert(parent != nullptr);
    assert(pnode != nullptr);
    return (parent->left == pnode);
}
 
void test_tree(const binary_search_tree<int>& _tree)
{
    cout << "test_tree:\n";
    cout << _tree;
    cout << "tree size : " << _tree.size() << endl;
    cout << "tree max length between node " << _tree.max_length_between_node() << endl;
    _tree.print_in_order_nonrecursive();
    _tree.print_element_order();
    _tree.print_post_order_nonrecursive();
    _tree.print_pre_order_nonrecursive();
    cout << "min element : " << _tree.minmum() << endl;
    cout << "max element : " << _tree.maxmum() << "\n" << endl;
}
void test1()
{
    binary_search_tree<int> tree;
    check(tree.size() == 0);
    check(tree.empty());
    check(tree.height() == 0);
}
void test2()
{
    int arr[1] = { 1 };
    binary_search_tree<int> tree(arr, 1);
    check(tree.size() == 1);
    check(tree.to_string_in_order() == "1 ");
    check(!tree.empty());
}
void test3()
{
    int arr[2] = { 1, 2 };
    binary_search_tree<int> tree(arr, 2);
    check(tree.size() == 2);
    check(tree.to_string_in_order() == "1 2 ");
    check(!tree.empty());
}
void test4()
{
    int arr[2] = { 2, 1 };
    binary_search_tree<int> tree(arr, 2);
    check(tree.size() == 2);
    check(tree.to_string_in_order() == "1 2 ");
    check(!tree.empty());
}
void test5()
{
    constexpr int length = 3;
    int arr[length] = { 1, 2, 3 };
    binary_search_tree<int> tree(arr, length);
    check(tree.size() == length);
    check(tree.to_string_in_order() == "1 2 3 ");
    check(!tree.empty());
}
void test6()
{
    constexpr int length = 3;
    int arr[length] = { 2, 1, 3 };
    binary_search_tree<int> tree(arr, length);
    check(tree.size() == length);
    check(tree.to_string_in_order() == "1 2 3 ");
    check(!tree.empty());
}
void test7()
{
    constexpr int length = 3;
    int arr[length] = { 3, 2, 1, };
    binary_search_tree<int> tree(arr, length);
    check(tree.size() == length);
    check(tree.to_string_in_order() == "1 2 3 ");
    check(!tree.empty());
}
void test8()
{
    constexpr int length = 3;
    int arr[length] = { 3, 1, 2, };
    binary_search_tree<int> tree(arr, length);
    check(tree.size() == length);
    check(tree.to_string_in_order() == "1 2 3 ");
    check(!tree.empty());
}
void test9()
{
    constexpr int length = 10;
    int arr[length] = { 1,3,5,7,9,2,4,6,8,10 };
    binary_search_tree<int> tree(arr, length);
    check(tree.size() == length);
    check(tree.to_string_in_order() ==
        "1 2 3 4 5 6 7 8 9 10 ");
    check(!tree.empty());
}
void test10()
{
    constexpr int length = 10;
    int arr[length] = { 2,4,6,8,10,1,3,5,7,9 };
    binary_search_tree<int> tree(arr, length);
    check(tree.size() == length);
    check(tree.to_string_in_order() ==
        "1 2 3 4 5 6 7 8 9 10 ");
    check(!tree.empty());
}
void test11()
{
    constexpr int length = 10;
    int arr[length] = { 10,9,8,7,6,5,4,3,2,1 };
    binary_search_tree<int> tree(arr, length);
    check(tree.size() == length);
    check(tree.to_string_in_order() ==
        "1 2 3 4 5 6 7 8 9 10 ");
    check(!tree.empty());
    check(tree.height() == 10);
}
void test12()
{
    constexpr int length = 10;
    int arr[length] = { 5,4,3,2,1,10,9,8,7,6 };
    binary_search_tree<int> tree(arr, length);
    check(tree.size() == length);
    check(tree.to_string_in_order() ==
        "1 2 3 4 5 6 7 8 9 10 ");
    check(!tree.empty());
    check(tree.height() == 6);
}
void test13()
{
    constexpr int length = 1;
    int arr[length] = { 1 };
    binary_search_tree<int> tree(arr, length);
    check(tree.minmum() == 1);
    check(tree.maxmum() == 1);
    check(tree.height() == 1);
}
void test14()
{
    constexpr int length = 2;
    int arr[length] = { 1, 2 };
    binary_search_tree<int> tree(arr, length);
    check(tree.minmum() == 1);
    check(tree.maxmum() == 2);
    check(tree.height() == 2);
}
void test15()
{
    constexpr int length = 10;
    int arr[length] = { 5,4,3,2,1,10,9,8,7,6 };
    binary_search_tree<int> tree(arr, length);
    check(tree.minmum() == 1);
    check(tree.maxmum() == 10);
}
void test16()
{
    constexpr int length = 1;
    int arr[length] = { 1 };
    binary_search_tree<int> tree(arr, length);
    check(tree.exists(1));
    tree.erase(1);
    check(!tree.exists(1));
    check(tree.size() == 0);
}
void test17()
{
    int arr[] = { 3,2,1 };
    binary_search_tree<int> tree(arr, sizeof(arr) / sizeof(int));
    check(tree.exists(1));
    cout << tree << endl;
    tree.erase(2);
    cout << tree << endl;
    check(!tree.exists(2));
    check(tree.size() == 2);
    check(!tree.empty());
    check(tree.to_string_in_order() == "1 3 ");
}
void test18()
{
    constexpr int length = 2;
    int arr[length] = { 1, 2 };
    binary_search_tree<int> tree(arr, length);
    check(tree.exists(1));
    check(tree.exists(2));
    tree.erase(1);
    check(!tree.exists(1));
    check(tree.exists(2));
    tree.clear();
    check(tree.empty());
    check(tree.size() == 0);
    check(!tree.exists(2));
}
void test19()
{
    constexpr int length = 10;
    int arr[length] = { 5,3,4,1,2,10,8,9,7,6 };
    binary_search_tree<int> tree(arr, length);
    cout << tree << endl << "-------------------" << endl;
    tree.erase(1);
    cout << tree << endl << "-------------------" << endl;
    check(tree.to_string_in_order() == "2 3 4 5 6 7 8 9 10 ");
    tree.erase(2);
    cout << tree << endl << "-------------------" << endl;
    check(tree.to_string_in_order() == "3 4 5 6 7 8 9 10 ");
    tree.erase(3);
    check(tree.to_string_in_order() == "4 5 6 7 8 9 10 ");
    cout << tree << endl << "-------------------" << endl;
    tree.erase(4);
    cout << tree << endl << "-------------------" << endl;
    check(tree.to_string_in_order() == "5 6 7 8 9 10 ");
    tree.erase(5);
    cout << tree << endl << "-------------------" << endl;
    check(tree.to_string_in_order() == "6 7 8 9 10 ");
    tree.erase(6);
    cout << tree << endl << "-------------------" << endl;
    check(tree.to_string_in_order() == "7 8 9 10 ");
    tree.erase(7);
    cout << tree << endl << "-------------------" << endl;
    check(tree.to_string_in_order() == "8 9 10 ");
    tree.erase(8);
    cout << tree << endl << "-------------------" << endl;
    check(tree.to_string_in_order() == "9 10 ");
    tree.erase(9);
    cout << tree << endl << "-------------------" << endl;
    check(tree.to_string_in_order() == "10 ");
    tree.erase(10);
    cout << tree << endl << "-------------------" << endl;
    check(tree.to_string_in_order() == "");
}
void test20()
{
    constexpr int length = 10;
    int arr[length] = { 5,3,4,1,2,10,8,9,7,6 };
    binary_search_tree<int> tree(arr, length);
    cout << tree << endl << "-------------------" << endl;
    tree.erase(10);
    cout << tree << endl << "-------------------" << endl;
    check(tree.to_string_in_order() == "1 2 3 4 5 6 7 8 9 ");
    tree.erase(8);
    cout << tree << endl << "-------------------" << endl;
    check(tree.to_string_in_order() == "1 2 3 4 5 6 7 9 ");
}
void test21()
{
    constexpr int length = 10;
    int arr[length] = { 5,3,4,1,2,10,8,9,7,6 };
    binary_search_tree<int> tree(arr, length);
    cout << tree << endl << "-------------------" << endl;
    tree.erase(5);
    cout << tree << endl << "-------------------" << endl;
    check(tree.to_string_in_order() == "1 2 3 4 6 7 8 9 10 ");
}
void test22()
{
    constexpr int length = 10;
    int arr[length] = { 2,4,6,8,10,1,3,5,7,9 };
    binary_search_tree<int> tree(arr, length);
    check(tree.height() == 6);
    tree.erase(1);
    check(!tree.exists(1));
    tree.erase(2);
    check(!tree.exists(2));
    tree.erase(3);
    check(!tree.exists(3));
    tree.erase(4);
    check(!tree.exists(4));
    tree.erase(5);
    check(!tree.exists(5));
    check(tree.to_string_in_order() == "6 7 8 9 10 ");
    tree.erase(6);
    check(!tree.exists(6));
    tree.erase(7);
    check(!tree.exists(7));
    tree.erase(8);
    check(!tree.exists(8));
    tree.erase(9);
    check(!tree.exists(9));
    tree.erase(10);
    check(!tree.exists(10));
    check(tree.empty());
}
void test23()
{
    //test equal
    int a[3] = { 15, 12, 14 };
    binary_search_tree<int> tree(a, 3);
    check(tree.height() == 3);
    cout << "tree:\n" << tree << endl;
    auto tree2 = tree;
    cout << "tree2:\n" << tree2 << endl;
    check(tree2.equal(tree));
}
void test24(binary_search_tree<int>& tree)
{
    cout << "tree:\n" << tree << endl;
    auto tree2 = tree;
    cout << "tree2:\n" << tree2 << endl;
    check(tree2.equal(tree));
    check(tree2 == tree);
    tree.clear();
    cout << tree << endl;
    check(tree2.equal(tree) == false);
    check(tree2 != tree);
}
void test25()
{
    int a[3] = { 15, 12, 14 };
    binary_search_tree<int> tree(a, 3);
    tree.print_in_order_recursive(cout);
}
int main()
{
    test1();//empty
    test2();//test create insert empty size
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    test12();
    test13();
    test14();//minmum maxmum
    test15();
    test16();//exists clear erase size empty
    test17();//erase
    test18();//erase
    test19();//erase
    test20();//erase
    test21();//erase
    test22();//erase
    test23();
 
    int maxLength = 0;
    int a[100] = { 15, 12, 14, 13, 16
                 , 34, 23, 24, 22, 21
                 , 20, 19, 18, 17, 35
                 , 36, 37, 38, 39, 40
                 , 41, 0 };
 
    binary_search_tree<int> tree(a, 22);
    check(tree.size() == 22);
    check(tree.empty() == false);
    check(tree.maxmum() == 41);
    check(tree.minmum() == 0);
    test_tree(tree);
 
    binary_search_tree<int> tree1(a, 3);
    test_tree(tree1);
 
    test24(tree);//test copy
    test25();//print
 
    return 0;
}