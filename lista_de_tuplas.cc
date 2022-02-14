#include <initializer_list>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class AbstractPair {
    private:
        
    public:
        AbstractPair() {};

        virtual ostream& imprime(ostream& out) = 0;
        
};

template<typename A, typename B>
class ImplPair: public AbstractPair {
    private:
        A _a;
        B _b;
    public:
        ImplPair(A a, B b): _a(a), _b(b) {}

        A a() {
            return _a;
        }

        B b() {
            return _b;
        }

        ostream& imprime(ostream& out) {
            return out << _a << " = " << _b;
        }
};

class Pair {
    private:
        shared_ptr<AbstractPair> ptr;

    public:
        template <typename A, typename B>
        Pair(A a, B b) {
            ptr = make_shared<ImplPair<A,B>>(a, b);
        }
        
        ostream& imprime(ostream& out) {
            return ptr->imprime(out);
        }
};

void print(ostream& out, initializer_list<Pair> lista) {
    for (Pair par : lista) {
        par.imprime(out);
        out << endl;
    }
}

template<typename Tipo>
ostream& operator << (ostream& out, vector<Tipo> v) {
    out << "[ ";
    for (auto vi : v) {
        out << vi << " ";
    }
    return out << "]";
}