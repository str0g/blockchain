template<typename T>
class Finally {
    public:
        explicit Finally(T fun) : fun(fun){}
        ~Finally() {
            fun();
        }
    private:
        T fun;
};

template<typename T>
Finally<T> finally(T fun) {
    return Finally<T>(fun);
}
