#include <iostream>
#include <vector>
#include <string>
#include <functional>

template <typename Iteravel, typename Func>
auto operator | (const Iteravel& iteravel, Func fn) {
    if constexpr (std::is_same_v<std::invoke_result_t<Func, decltype(*std::begin(iteravel))>, bool>) {
        auto _ = *std::begin(iteravel);
        std::vector<decltype(_)> vetorRetorno;
    
        for (auto& elemento : iteravel) {
            if (std::invoke(fn, elemento)) {
                vetorRetorno.push_back(elemento);
            }
        }
        
        return vetorRetorno;
    }
    else if constexpr (std::is_same_v<std::invoke_result_t<Func, decltype(*std::begin(iteravel))>, void>) {
        for (auto& elemento : iteravel) {
            std::invoke(fn, elemento);
        }
    }
    else {
        using TipoRet = std::invoke_result_t<Func, decltype(*std::begin(iteravel))>;
        std::vector<TipoRet> vetorRetorno;

        for (auto& elemento : iteravel) {
            vetorRetorno.push_back(std::invoke(fn, elemento));
        }
        
        return vetorRetorno;
    }
}

template<typename F>
struct ExprVetor {
    ExprVetor(size_t indice, F f): indice(indice), f(f) {}

    template<typename Tipo>
    auto operator() (Tipo v) {
        return f(v[indice]);
    }

    template<typename Tipo>
    auto operator() (Tipo v) const {
        return f(v[indice]);
    }

    size_t indice;
    F f;
};

template<typename F>
struct Expr {
    Expr(F f): f(f) {}

    template<typename Tipo>
    auto operator() (Tipo v) const {
        return f(v);
    }

    template<typename Tipo>
    auto operator() (Tipo v) {
        return f(v);
    }

    auto operator[] (size_t indice) {
        return ExprVetor{ indice, f };
    }

    auto operator[] (size_t indice) const {
        return ExprVetor{ indice, f };
    }

    F f;
};

auto x = Expr{ [](auto x) { return x; } };
using X = decltype(x);

auto cte = Expr{ 
    [](auto c) { return [c](auto x) { return c; }; }
};
using Cte = decltype(cte);

template<typename A, typename B>
auto operator* (Expr<A> a, Expr<B> b) {
    return Expr{
        [a, b](auto v) { return a(v) * b(v); }
    };
}

template<typename A, typename B>
auto operator* (Expr<A> a, B b) {
    return Expr{
        [a, b](auto v) { return a(v) * b; }
    };
}

template<typename A, typename B>
auto operator* (A a, Expr<B> b) {
    return Expr{
        [a, b](auto v) { return a * b(v); }
    };
}

template<typename A, typename B>
auto operator+ (Expr<A> a, Expr<B> b) {
    return Expr{
        [a, b](auto v) { return a(v) + b(v); }
    };
}

template<typename A, typename B>
auto operator+ (Expr<A> a, B b) {
    return Expr{
        [a, b](auto v) { return a(v) + b; }
    };
}

template<typename A, typename B>
auto operator+ (A a, Expr<B> b) {
    return Expr{
        [a, b](auto v) { return a + b(v); }
    };
}

template<typename A, typename B>
auto operator- (Expr<A> a, Expr<B> b) {
    return Expr{
        [a, b](auto v) { return a(v) - b(v); }
    };
}

template<typename A, typename B>
auto operator- (Expr<A> a, B b) {
    return Expr{
        [a, b](auto v) { return a(v) - b; }
    };
}

template<typename A, typename B>
auto operator- (A a, Expr<B> b) {
    return Expr{
        [a, b](auto v) { return a - b(v); }
    };
}

template<typename A, typename B>
auto operator/ (Expr<A> a, Expr<B> b) {
    return Expr{
        [a, b](auto v) { return a(v) / b(v); }
    };
}

template<typename A, typename B>
auto operator/ (Expr<A> a, B b) {
    return Expr{
        [a, b](auto v) { return a(v) / b; }
    };
}

template<typename A, typename B>
auto operator/ (A a, Expr<B> b) {
    return Expr{
        [a, b](auto v) { return a / b(v); }
    };
}

template<typename A, typename B>
auto operator% (Expr<A> a, Expr<B> b) {
    return Expr{
        [a, b](auto v) { return a(v) % b(v); }
    };
}

template<typename A, typename B>
auto operator% (Expr<A> a, B b) {
    return Expr{
        [a, b](auto v) { return a(v) % b; }
    };
}

template<typename A, typename B>
auto operator% (A a, Expr<B> b) {
    return Expr{
        [a, b](auto v) { return a % b(v); }
    };
}

template<typename A, typename B>
auto operator== (Expr<A> a, Expr<B> b) {
    return Expr{
        [a, b](auto v) { return a(v) == b(v); }
    };
}

template<typename A, typename B>
auto operator== (Expr<A> a, B b) {
    return Expr{
        [a, b](auto v) { return a(v) == b; }
    };
}

template<typename A, typename B>
auto operator== (A a, Expr<B> b) {
    return Expr{
        [a, b](auto v) { return a == b(v); }
    };
}

template<typename F>
struct PrintExpr {
    PrintExpr(std::ostream& out, Expr<F> expr): out(out), expr(expr) {}

    template<typename T>
    void operator() (T v) {
        out << expr(v) << sufixo;
    }

    template<typename T>
    void operator() (T v) const {
        out << expr(v) << sufixo;
    }

    std::ostream& out;
    Expr<F> expr;
    char sufixo = '\0';
};


template<typename F>
auto operator<< (std::ostream& out, Expr<F> expr) {
    return PrintExpr{ out, expr };
}

template<typename F>
auto operator<< (PrintExpr<F> print, char c) {
    print.sufixo = c;
    return print;
}

auto operator+ (std::vector<int> v, int n) {
    v.push_back(n);
    return v;
}

template <typename A, typename B>
auto operator | (Expr<A> expr, PrintExpr<B> print) {
    return Expr {
        //[x]( auto v ) { v | std::cout << x << ' '; }
        [expr, print](auto v) { return print(expr(v)); }
    };
}

template <typename Tipo>
std::ostream& operator<< (std::ostream& out, std::vector<Tipo> v) {
    for (size_t i = 0; i < v.size(); i++) {
        if (i == v.size()-1)
            out << v[i];
        else
            out << v[i] << " ";
    }
    return out;
}

template <typename F, typename Tipo>
auto operator!= (ExprVetor<F> a, Tipo b) {
    return Expr {
        [a, b] (auto v) { return a(v) != b; }
    };
}

using namespace std;

int main() {
    vector< vector<int> > m{ { 1, 2, 3 }, { 0, 3, 7 }, { 1, 3 } };
        
    //m | []( auto v ) { return v[0] != 0; } | [x]( auto v ) { v + 7 | cout << x << ' '; };

    //m | []( auto v ) { return v[0] != 0; } | ( x | cout << x << ' ' );
    
    //m | x[0] != 0 | ( x | cout << x << ' ' );

    //m | x[0] != 0 | (( x + 7 ) | cout << x << ' ' );

    return 0;
}