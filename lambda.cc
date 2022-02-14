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

int main() {
    int v1[] = { 1, 2, 3, 4, 1, 1, 0, 8 };
    v1 | (x % 2 == 0) | std::cout << x*x + 1 << ' ';
    
    return 0;
}