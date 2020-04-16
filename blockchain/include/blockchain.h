#ifndef _BLOCKCHAIN_H_
#define _BLOCKCHAIN_H_

class Blockchain {
    public:
        static Blockchain& getInstance();
    private:
        Blockchain();

        Blockchain(Blockchain const&) = delete;
        Blockchain(Blockchain &&) = delete;

        Blockchain& operator=(Blockchain const&) = delete;
        Blockchain& operator=(Blockchain &&) = delete;
};

#endif
