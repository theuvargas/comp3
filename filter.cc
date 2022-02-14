#include <iostream>
#include <vector>
#include <functional>
#include <type_traits>
#include <map>

using namespace std;

template <typename Iteravel, typename Func>
auto operator | (const Iteravel& iteravel, Func fn) {
    if constexpr (is_same_v<invoke_result_t<Func, decltype(*begin(iteravel))>, bool>) {
        vector<decay_t<decltype(*begin(iteravel))>> vetorRetorno;
    
        for (auto& elemento : iteravel) {
            if (invoke(fn, elemento)) {
                vetorRetorno.push_back(elemento);
            }
        }
        
        return vetorRetorno;
    }
    else if constexpr (is_same_v<invoke_result_t<Func, decltype(*begin(iteravel))>, void>) {
        for (auto& elemento : iteravel) {
            invoke(fn, elemento);
        }
    }
    else {
        using TipoRet = invoke_result_t<Func, decltype(*begin(iteravel))>;
        vector<TipoRet> vetorRetorno;
    
        for (auto& elemento : iteravel) {
            vetorRetorno.push_back(invoke(fn, elemento));
        }
        
        return vetorRetorno;
    }
}

int main() {
    vector<int> v = {1, 2, 3, 4};
    v | [](int x) { return x%2 == 0; } | [](int x) { cout << x << " "; };

    return 0;
}