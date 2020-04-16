#include <stdexcept>
#include <typeinfo>

template<typename R, typename T>
R narrow_cast(T in) {
    R out = static_cast<R>(in);
    if (out != in) {
        std::cerr << typeid(T).name() << " [" << in << "] to " << typeid(R).name() << " [" << out <<"]" << std::endl; 
        throw std::out_of_range("narrow_cast");
    }
    return out;
}
