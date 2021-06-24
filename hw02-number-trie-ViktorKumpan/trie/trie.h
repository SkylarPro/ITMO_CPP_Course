#pragma once

#include <string>
#include <vector>

#include <map>

class trie_t{

private:
    struct node_t{
        node_t() = default;
        node_t(const char _pt[0]);
        bool isEnd{false};
        size_t count{0}; // сколько заканчивается строк в узле
        size_t subtree_count{0}; // сколько строк идет из узла
        bool isStart{true};
        std::map<char,node_t> next;
    };
    node_t root = node_t("");
    bool f_search(const std::string &str,node_t& root, size_t);
    void ins(const std::string &str,node_t& root, size_t);
    void cwp(const std::string prefix,node_t & root, size_t&,size_t);
    bool erase_inp(node_t & root , const std::string, size_t);
    void form_vec(node_t& root ,std::vector<std::string>& , size_t& start);
    void str_with_ind(node_t& root,size_t,std::string&);
public:

    trie_t() = default;
    ~trie_t() = default;
    trie_t(const trie_t& other);
    trie_t & operator=(const trie_t& other);

    void insert(const std::string &str);

    /**
     * @param prefix
     * @return number of strings which starts with specified prefix in your container
     */
    bool find(const std::string &str);

    /**
   * Made your container empty
   */
    trie_t& clear();
    /**
   * @param prefix
   * @return number of strings which starts with specified prefix in your container
   */
    size_t count_with_prefix(const std::string &prefix);

    /**
   * @return true if container is empty :)
   */
    bool empty();
    /**
    * Remove specified string
    * @param str
    * @return return true if specified string was in container
    */
    bool erase(const std::string &);
    /**
    * @return Number of strings in container
    */
    size_t size();
    /**
   * Exchange content of this and other
   * @param other
   */
    void swap(trie_t &other);
    /**
    * @return All strings from your container in lexicographic order.
    */
    std::vector<std::string> to_vector();
    /**
   * IMAGINE that you sort all strings in you container in lexicographic order.
   * You should return string on position index in this order
   * @param index
   */
    std::string operator[](size_t index);

};
