struct Elem_t {
    const char *data = nullptr;
    
    int hash = 0;
};

const Elem_t POISON = {};