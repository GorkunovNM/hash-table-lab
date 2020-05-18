#ifndef $SLIST$H
#define $SLIST$H

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

namespace slist {

typedef char elem_t;

//class slist {private: struct slist_node_t;};

class slist {
private:
    struct slist_node_t {
        slist_node_t *child;
        elem_t *data;
        slist_node_t *parent;
        slist *owner;

        slist_node_t(elem_t *slist_node_data);

        int destruct_node_and_lower();

        ~slist_node_t();
    };

    slist_node_t *root;
    int nodes_cnt;
    char *name;
    slist_node_t *last_visited;
    int last_visited_logic;

public:
    slist(char *slist_name);

    int len();

    int insert_node(slist_node_t *this_, char *data);

    int insert_node_logic(char *data, int itt);

    int delete_node_logic(int itt);

    int get_node_logic(int itt, elem_t *data);

    int dump();

    slist_node_t *visit(int itt);

    ~slist();
};

/////////////////////////////////////////////////////////////////////////

slist::slist(char *slist_name) {
    root = NULL;
    nodes_cnt = 0;
    name = (char *) calloc(strlen(slist_name) + 1, sizeof(char));
    strcpy(name, slist_name);
    last_visited = NULL;
    last_visited_logic = 0;
}
slist::~slist() {
    root->destruct_node_and_lower();
    root = NULL;
    nodes_cnt = 0;
    free(name);
    name = NULL;
    last_visited = NULL;
    last_visited_logic = 0;
}

int slist::len() return this->nodes_cnt;

int slist::insert_node(slist_node_t *this_, char *data) {
    slist_node_t *to_parent = new slist_node_t(data);
    if (root && this_) {
        to_parent -> child = this_ -> child;
        if (to_parent -> child) (to_parent -> child) -> parent = to_parent;
        this_ -> child = to_parent;
        to_parent -> parent = this_;
    }
    else {
        to_parent -> child = root;
        if (to_parent -> child) (to_parent -> child) -> parent = to_parent;
        root = to_parent;
    }
    ++nodes_cnt;
    return 0;
}

int slist::insert_node_logic(char *data, int itt) {
    slist_node_t *this_ = visit(itt);
    insert_node(this_, data);
    return 0;
}

int slist::delete_node_logic(int itt) {
    slist_node_t *this_ = visit(itt);
    delete this_;
    return 0;
}

int slist::get_node_logic(int itt, elem_t *data_to) {
    slist_node_t *this_ = visit(itt);
    strcpy(data_to, this_ -> data);
    return 0;
}

int slist::dump() {
    slist_node_t *this_ = root;
    for (int i = 0; i < nodes_cnt; i++) {
        printf("%s |||", this_ -> data);
        this_ = this_ -> child;
    }
    printf("\n");
    return 0;
}

slist::slist_node_t *slist::visit(int itt) {
    slist_node_t *ans = NULL;
    if (!root) return NULL;
    int itt_cpy = itt;
    if (last_visited == NULL) {
        ans = root;
        while (itt > 0) {
            if (!(ans -> child)) return NULL;
            ans = ans -> child;
            itt--;
        }
    }
    else {
        ans = last_visited;
        while (itt - last_visited_logic > 0) {
            if (!(ans -> child)) return NULL;
            ans = ans -> child;
            itt--;
        }
        while (last_visited_logic - itt > 0) {
            if (!(ans -> parent)) return NULL;
            ans = ans -> parent;
            itt++;
        }
    }
    last_visited = ans;
    last_visited_logic = itt_cpy;
    return ans;
}

slist::slist_node_t::slist_node_t(char *slist_node_data) {
    child = NULL;
    data = (char *) calloc(strlen(slist_node_data) + 1, sizeof(char));//!!! if only elem_t == char
    strcpy(data, slist_node_data);                                    //!!! if only elem_t == char
    parent = NULL;
    owner = NULL;
}

slist::slist_node_t::~slist_node_t(){
    if (parent) parent -> child = child;
    if (child) child -> parent = parent;
    child = NULL;
    free(data);
    data = NULL;
    parent = NULL;
    (owner -> nodes_cnt)--;
    owner = NULL;
}

int slist::slist_node_t::destruct_node_and_lower() {
    if (child != NULL) child->destruct_node_and_lower();
    delete this;
    return 0;//!!!
}

}

#endif