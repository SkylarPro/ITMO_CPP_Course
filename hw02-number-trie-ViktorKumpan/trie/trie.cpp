#include "trie.h"
// trie
// Created by Виктор Кумпан on 13.04.2021.


trie_t::node_t::node_t(const char _pt[0]) {
    isEnd = false;
    count = 0;
    subtree_count = 0;
    next.emplace(std::make_pair(_pt[0],node_t()));
}



trie_t::trie_t(const trie_t& other): root(other.root)
{
}


trie_t &trie_t::operator=(const trie_t &other) {
    if (this == &other)
        return *this;
    root = other.root;
    return  *this;
}


void trie_t::insert(const std::string &str) {
    size_t pos = 0;
    root.next['\0'].subtree_count++;
    if (str.empty()){
        root.next['\0'].count++;
        root.next['\0'].isEnd= true;
        return;
    }
    ins(str,root.next['\0'], pos);
}

void trie_t::ins(const std::string &str, trie_t::node_t& root, size_t pos) {
    if (pos == str.size()){
        root.count++;
        root.isEnd = true;
        return;
    }else{
        if (root.next.count(str[pos]) == 0){
            root.next.emplace(std::make_pair(str[pos],node_t()));
            root.next[str[pos]].isStart = false;
        }
        root.next[str[pos]].subtree_count++;
        ins(str,root.next[str[pos]],pos+1);
    }
}

bool trie_t::find(const std::string &str) {
    size_t pos = 0;
    if (str.size() == 0){
        if (root.next['\0'].subtree_count > 0){
            return true;
        }else{
            return false;
        }
    }
    return f_search(str,root.next['\0'], pos);

}

bool trie_t::f_search(const std::string &str, trie_t::node_t &root, size_t pos) {
    if (pos == str.size() &&  root.isEnd){
        return true;
    }else if (root.next.count(str[pos]) == 0){
        return false;
    }
    else{
        if (f_search(str,root.next[str[pos]],pos+1)){
            return true;
        }
    }
}



trie_t& trie_t::clear() {
    return (*this = trie_t());
}

size_t trie_t::count_with_prefix(const std::string &prefix)  {
    size_t size = 0;
    size_t pos = 0;
    if (prefix.size() == 0){
        return root.next['\0'].subtree_count;
    }
    cwp(prefix,root.next['\0'],size, pos);
    return size;
}

void trie_t::cwp(const std::string prefix, trie_t::node_t &root, size_t& size, size_t pos) {
    if (pos == prefix.size() ) {
        size = root.subtree_count;
        return;
    }else if(root.next.count(prefix[pos]) == 0){
        size = 0;
        return;
    }else{
        cwp(prefix,root.next[prefix[pos]],size,pos+1);
    }
}

bool trie_t::empty(){
    if (root.next['\0'].subtree_count == 0){
        return true;
    }else{
        return false;
    }
}


bool trie_t::erase(const std::string & str) {
    size_t pos = 0;
    if (erase_inp(root.next['\0'], str, pos)){
        return true;
    }
    return false;
}

bool trie_t::erase_inp(node_t& root, const std::string str, size_t pos){

    if (str.size() == pos && root.isEnd){
        if (root.subtree_count == 1){
            root.subtree_count--;
            root.isEnd = false;
            root.count--;
            return true;
        }
        else if(root.subtree_count > 1){
            root.subtree_count--;
            root.count--;
            return true;
        }
    }
    if (root.next.count(str[pos]) == 0) return false;

    if (erase_inp(root.next[str[pos]],str,pos+1)){
        if (root.subtree_count == 1){
            root.subtree_count--;
            return true;
        }
        else if(root.subtree_count > 1){
            root.subtree_count--;
            return true;
        }
    }
    return false;
}


size_t trie_t::size() {
    return root.next['\0'].subtree_count;
}

void trie_t::swap(trie_t &other) {
    std::swap(root,other.root);
}

std::vector<std::string> trie_t::to_vector() {
    std::vector<std::string> vec;
    size_t start = 0;
    for (int i = 0; i < root.next['\0'].count; i++){
            vec.push_back("");
    }
    form_vec(root.next['\0'], vec,start);
    return vec;
}

void trie_t::form_vec(node_t& root ,std::vector<std::string>& vec, size_t& start){
    if (root.isEnd && root.subtree_count==0){
        return;
    }
    if (root.next.empty()){
        return;
    }
    for(const auto &c: root.next){
        for (int j = 0; j < c.second.subtree_count; ++j){
            if (root.isStart){
                if (j == 0){
                    start = vec.size();
                }
                std::string s{c.first};
                vec.push_back(s);
            }else if (c.second.isEnd){
                std::string s{c.first};
                vec[start + j] += s;

            }else{
                std::string s{c.first};
                vec[start + j] += s;
            }
        }
        start += c.second.count;
        form_vec(root.next[c.first],vec, start);
    }
}


std::string trie_t::operator[](size_t index)  {
    std::string str;
    long long t = root.next['\0'].count - index;
    if (t > 0){
        return str;
    }
    index -= root.next['\0'].count;
    str_with_ind(root.next['\0'], index,str);
    return str;
}

void trie_t::str_with_ind(node_t& root, size_t index, std::string& str) {
    size_t start = 0;
    for(const auto &c: root.next){
        start += c.second.subtree_count;
        if (start <= index){
            continue;
        }else if(c.second.isEnd && c.second.count>index){
            str.push_back(c.first);
            return;
        }else{
            start -= c.second.subtree_count;
            index = index - start - c.second.count;
            str.push_back(c.first);
            str_with_ind(root.next[c.first],index,str);
            return;
        }
    }
    return;
}