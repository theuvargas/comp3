#include <iostream>
#include <type_traits>
#include <functional>

/*template<typename F, typename... Tipos>
auto bind(F fn, Tipos... args);

template<typename F, typename... Args>
struct Bind {
    F fn;
    std::tuple<Args...> t;

    Bind(F fn, Args... args): fn(fn) {
        t = std::tuple_cat(std::make_tuple(args...));
        //std::cout << std::get<2>(t) << "\n";
    }

    auto operator() (Args... args) {
        auto [ ola ] = std::make_tuple(args...);
        std::cout << ola << "\n";
        return ::bind(fn, t, args...);
    }
};*/


template<typename Functor>
struct Bind;

template<typename Functor>
auto bind(Functor f) {
    return Bind<Functor>{f};
}

template<typename Functor, typename Arg>
auto bind(Functor f, Arg v) {
    return [f, v](auto... resto) mutable { return std::invoke(f, v, resto...);; };
}

template< typename Functor, typename Arg1, typename... Args >
auto bind(Functor f, Arg1 arg1, Args... args) {
    return [f, arg1, args...](auto... resto) { return ::bind(::bind(f, arg1), args...)(resto...); };
}

template<typename Functor>
struct Bind {
    Functor f;

    Bind(Functor f): f(f) {}

    template <typename... Args>
    auto operator() (Args... args) {
        if constexpr (std::is_invocable<Functor, Args...>::value)
            return std::invoke(f, args...);
        else
            return ::bind(f, args...);
    }
};

//int p1 = ::bind([](int i, int j){ return i-j; }, 6)(2);
//int p2 = ::bind([](int i, int j){ return i-j; }, 6, 2)();

/*template<typename Function, typename... Arguments>
auto bind(Function function, Arguments... args) {
    return [=](auto... rest) {
        return function(args..., rest...);
    }; // don't forget semicolumn
}*/


#include <algorithm>
#include <array>

using namespace std;

long mdc( long a, long b ) { return b == 0 ? a : mdc( b, a%b ); }

struct MMC {
    auto operator()( long a, long b ) { return a*b/mdc(a,b); }    
};

struct BarraPesada {
    template <typename A, typename B>
    auto operator()( A a, B b ) {
        return a + b;
    } 
};

string ordena( string a, string b, string c, string d, string e, string f, string g, string h, string i, string j, string k, string l ) {
    std::array<string, 12> tab = { a, b, c, d, e, f, g, h, i, j, k, l };
    string result;
    
    std::sort( tab.begin(), tab.end() );
    for( auto itr = tab.begin(); itr != tab.end(); ++itr )
        result += *itr + " ";
    
    return result;    
}

int main() {
    
    using ::bind;
  
    /*auto f1 = bind( mdc, 12 );
    for( int i = 2; i <= 12; i++ )
        cout << f1( i ) <<  " ";*/

    /*auto f2 = bind( mdc );
    auto f1 = bind( f2, 12 );
    for( int i = 2; i <= 12; i++ )
        cout << f1( i ) <<  " ";*/

    /*auto f2 = bind( mdc );
    auto f1 = f2( 18 );
    for( int i = 2; i <= 18; i++ )
        cout << f1( i ) <<  " ";*/

    /*auto f2 = bind( []( int x, int y, int z ){ cout << x*y << (char) z << " " ; }, 10 );
    for( int i = 0; i < 5; i++ )
        f2( i, ',' );*/

    /*auto f3 = bind( []( int x, int y, int z ){ cout << x*z << (char) y << " " ; } );
    auto f1 = f3( 5, ';' );
    for( int i = 0; i < 5; i++ )
        f1( i );*/

    /*MMC mmc; // erro
    auto f1 = bind( mmc, 6 );
    for( int i = 2; i <= 12; i++ )
        cout << f1( i ) << " ";*/

    /*MMC mmc; // erro
    auto f2 = bind( mmc );
    auto f1 = f2( 6 );
    for( int i = 2; i <= 12; i++ )
        cout << f1( i ) << " ";*/

    /*auto f1 = ::bind( ordena, "a", "b", "9", "6", "s", "2", "1", "0", "c", "d", "e" );
    cout << f1( "@" ) << endl;
    cout << f1( "~" );*/

    auto f2=bind( BarraPesada() ); // erro
    cout << f2( (string) "a", (string) "b" ) << endl;
    cout << f2( 3.1, 4.3 );

    /*BarraPesada barraMaisPesada; // erro
    auto f2=bind( barraMaisPesada );
    auto f1s=f2( (string) "Hello, " );
    auto f1f=f2( 3.14 );
    cout << f1s( "world!" ) << endl;
    cout << f1f( 4.3 );*/

    /*string msg = "uma frase";
    auto prefixo = ::bind( &string::substr, msg, 0 );
    for( int i = 0; i < 5; i++ )
        cout << prefixo( i + 1 ) << endl;*/


    return 0;
}