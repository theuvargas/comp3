#include <iostream>
#include <cmath>

template<typename E, typename Dx>
struct Expr {
    Expr(E e, Dx dx): e(e), dx(dx) {}

    E e;
    Dx dx;
};

auto x = Expr { [](double x) { return x; }, [](double x) { return 1.0; } };

template<typename E1, typename Dx1, typename E2, typename Dx2>
auto operator* (Expr<E1, Dx1> a, Expr<E2, Dx2> b) {
    return Expr{
        [a, b](double v) { return a.e(v) * b.e(v); },
        [a, b](double v) { return a.e(v) * b.dx(v) + a.dx(v) * b.e(v); }
    };
}

template <typename E, typename Dx, typename B>
auto operator* (Expr<E, Dx> a, B b) {
    return Expr{
        [a, b](double v) { return a.e(v) * b; },
        [a, b](double v) { return a.dx(v) * b; }
    };
}

template <typename E, typename Dx, typename A>
auto operator* (A a, Expr<E, Dx> b) {
    return Expr{
        [a, b](double v) { return a * b.e(v); },
        [a, b](double v) { return a * b.dx(v); }
    };
}

template<typename E1, typename Dx1, typename E2, typename Dx2>
auto operator+ (Expr<E1, Dx1> a, Expr<E2, Dx2> b) {
    return Expr{
        [a, b](double v) { return a.e(v) + b.e(v); },
        [a, b](double v) { return a.dx(v) + b.dx(v); }
    };
}

template <typename E, typename Dx, typename B>
auto operator+ (Expr<E, Dx> a, B b) {
    return Expr{
        [a, b](double v) { return a.e(v) + b; },
        [a, b](double v) { return a.dx(v); }
    };
}

template <typename E, typename Dx, typename A>
auto operator+ (A a, Expr<E, Dx> b) {
    return Expr{
        [a, b](double v) { return a + b.e(v); },
        [a, b](double v) { return b.dx(v); }
    };
}

template<typename E1, typename Dx1, typename E2, typename Dx2>
auto operator- (Expr<E1, Dx1> a, Expr<E2, Dx2> b) {
    return Expr{
        [a, b](double v) { return a.e(v) - b.e(v); },
        [a, b](double v) { return a.dx(v) - b.dx(v); }
    };
}

template <typename E, typename Dx, typename B>
auto operator- (Expr<E, Dx> a, B b) {
    return Expr{
        [a, b](double v) { return a.e(v) - b; },
        [a, b](double v) { return a.dx(v); }
    };
}

template <typename E, typename Dx, typename A>
auto operator- (A a, Expr<E, Dx> b) {
    return Expr{
        [a, b](double v) { return a - b.e(v); },
        [a, b](double v) { return b.dx(v); }
    };
}

template<typename E1, typename Dx1, typename E2, typename Dx2>
auto operator/ (Expr<E1, Dx1> a, Expr<E2, Dx2> b) {
    return Expr{
        [a, b](double v) { return a.e(v) / b.e(v); },
        [a, b](double v) { return (b.e(v) * a.dx(v) - a.e(v) * b.dx(v)) / std::pow(b.e(v), 2); }
    };
}

template<typename E, typename Dx, typename B>
auto operator/ (Expr<E, Dx> a, B b) {
    return Expr{
        [a, b](double v) { return a.e(v) / b; },
        [a, b](double v) { return a.dx(v) / b; }
    };
}

template<typename E, typename Dx, typename A>
auto operator/ (A a, Expr<E, Dx> b) {
    return Expr{
        [a, b](double v) { return a / b.e(v); },
        [a, b](double v) { return -((a * b.dx(v)) / std::pow(b.e(v), 2)); }
    };
}

template<typename E, typename Dx, typename B>
auto operator->* (Expr<E, Dx> a, B b) {
    static_assert(std::is_same_v<B, int>, "Operador de potenciação definido apenas para inteiros");
    return Expr {
        [a, b](double v) { return std::pow(a.e(v), b); },
        [a, b](double v) { return b * std::pow(a.e(v), b-1) * a.dx(v); }
    };
}

struct Seno {
    template<typename E, typename Dx>
    auto operator() (Expr<E, Dx> b) const {
        return Expr {
            [*this, b](double v) { return e(b.e(v)); },
            [*this, b](double v) { return b.dx(v) * dx(b.e(v)); }
        };
    }

    double e(double v) const {
        return std::sin(v);
    }

    double dx(double v) const {
        return std::cos(v);
    }
};

template<typename E, typename Dx>
auto sin(Expr<E, Dx> expr) {
    Seno seno;
    return seno(expr);
}

struct Cosseno {
    template<typename E, typename Dx>
    auto operator() (Expr<E, Dx> b) const {
        return Expr {
            [*this, b](double v) { return e(b.e(v)); },
            [*this, b](double v) { return b.dx(v) * dx(b.e(v)); }
        };
    }

    double e(double v) const {
        return std::cos(v);
    }

    double dx(double v) const {
        return -std::sin(v);
    }
};

template<typename E, typename Dx>
auto cos(Expr<E, Dx> expr) {
    Cosseno cosseno;
    return cosseno(expr);
}

struct Exponencial {
    template<typename E, typename Dx>
    auto operator() (Expr<E, Dx> b) const {
        return Expr {
            [*this, b](double v) { return e(b.e(v)); },
            [*this, b](double v) { return b.dx(v) * dx(b.e(v)); }
        };
    }

    double e(double v) const {
        return std::exp(v);
    }

    double dx(double v) const {
        return std::exp(v);
    }
};

template<typename E, typename Dx>
auto exp(Expr<E, Dx> expr) {
    Exponencial exponencial;
    return exponencial(expr);
}

struct Logaritmo {
    template<typename E, typename Dx>
    auto operator() (Expr<E, Dx> b) const {
        return Expr {
            [*this, b](double v) { return e(b.e(v)); },
            [*this, b](double v) { return b.dx(v) * dx(b.e(v)); }
        };
    }

    double e(double v) const {
        return std::log(v);
    }

    double dx(double v) const {
        return 1 / v;
    }
};

template<typename E, typename Dx>
auto log(Expr<E, Dx> expr) {
    Logaritmo logaritmo;
    return logaritmo(expr);
}

int main() {
    double v = 0.1;
    auto f = 1 / (1 + exp( -2*( x - 1 )->*4 ) );
    
    std::cout << "f(" << v << ") = " << f.e(v) << ", f'(" << v << ") = " << f.dx(v) << std::endl;
    

    return 0;
}