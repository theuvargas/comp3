#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

template <typename TipoContainer, template<typename> class Container, typename Func>
auto apply(const Container<TipoContainer>& container, Func fn) -> vector<decltype(fn(*cbegin(container)))> {
    typedef decltype(fn(*cbegin(container))) TipoRetorno;
    
    vector<TipoRetorno> vetorRetorno;
    for (TipoContainer elemento : container) {
        vetorRetorno.push_back(fn(elemento));
    }

    return vetorRetorno;
}

template <typename TipoContainer, typename Func>
auto apply(const initializer_list<TipoContainer>& container, Func fn) -> vector<decltype(fn(*cbegin(container)))> {
    typedef decltype(fn(*cbegin(container))) TipoRetorno;
    
    vector<TipoRetorno> vetorRetorno;
    for (TipoContainer elemento : container) {
        vetorRetorno.push_back(fn(elemento));
    }

    return vetorRetorno;
}

template <typename TipoContainer, size_t tam, typename Func>
auto apply(TipoContainer (&container)[tam], Func fn) -> vector<decltype(fn(*container))> {
    typedef decltype(fn(*container)) TipoRetorno;
    
    vector<TipoRetorno> vetorRetorno;
    for (TipoContainer elemento : container) {
        vetorRetorno.push_back(fn(elemento));
    }

    return vetorRetorno;
}