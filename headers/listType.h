#pragma "once"

struct Elem_t {
    const char *data = nullptr;
    
    int hash = 0;
};

const Elem_t POISON = {};

Elem_t listElemCtor(const char *data, int hash) {
    Elem_t res = {};

    res.data = data;
    res.hash = hash;

    return res;
}