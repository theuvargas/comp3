#include <iostream>

using namespace std;

template <typename TipoItr, template<typename> class Iteravel, typename Func>
void operator | (Iteravel<TipoItr>& iteravel, Func fn) {
    for (auto elemento : iteravel) {
        fn(elemento);
    }
}

template <typename TipoItr, size_t tam, typename Func>
void operator | (TipoItr (&iteravel)[tam], Func fn) {
    for (auto elemento : iteravel) {
        fn(elemento);
    }
}