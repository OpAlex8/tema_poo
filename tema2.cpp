#include <iostream>

using namespace std;

int n;

class Nod{
public:
    Nod* next;
    char info;
    friend class Coada;

    Nod& operator=(const Nod& x) {
        this->info = x.info;
        this->next = x.next;
        return *this;
    }

    Nod& operator+(const Nod& x) {
        this->info = this->info + x.info;
        return *this;
    }

    Nod& operator-(const Nod& x) {
        this->info = this->info - x.info;
        return *this;
    }

    bool operator==(const Nod& x) {
        if (this->info == x.info) {
            return 1;
        }
        return 0;
    }

    bool operator<(const Nod& x) {
        if (this->info < x.info) {
            return 1;
        }
        return 0;
    }

    bool operator>(const Nod& x) {
        if (this->info > x.info) {
            return 1;
        }
        return 0;
    }

    Nod& operator+(char x) {
        this->info = this->info + x;
        return *this;
    }

    Nod& operator-(char x) {
        this->info = this->info - x;
        return *this;
    }

    bool operator==(char x) {
        if (this->info == x) {
            return 1;
        }
        return 0;
    }

    bool operator<(char x) {
        if (this->info < x) {
            return 1;
        }
        return 0;
    }

    bool operator>(char x) {
        if (this->info > x) {
            return 1;
        }
        return 0;
    }

    friend istream& operator>>(istream& is, const Nod& nod);
    friend ostream& operator<<(ostream& os, const Nod& nod);
};

ostream& operator<<(ostream& os, const Nod& nod) {
    os << nod.info;
    return os;
}

istream& operator>>(istream& is, Nod& nod) {
    is >> nod.info;
    return is;
}

class Coada {
public:
    int dim_max;
    Nod *prim, *ultim;

    Coada() {
        this->dim_max = 0;
        this->prim = NULL;
        this->ultim = NULL;
    }

    void push(char info) {
        if (this->dim_max == 0) {
            Nod* nod = new Nod();
            nod->info = info;
            nod->next = NULL;
            this->prim = this->ultim = nod;
            this->dim_max = 1;
        } else {
            Nod* nod = new Nod();
            Nod* aux = this->ultim;
            nod->info = info;
            nod->next = NULL;
            aux->next = nod;
            this->ultim = nod;
            this->dim_max++;
        }
    }

    void pop(){
        if (this->prim == NULL) {
            return;
        }
        Nod* aux = this->prim;
        this->prim = aux->next;
        delete aux;
        this->dim_max--;
    }

    void top() {
        Nod* aux = this->ultim;
        cout << "Varful cozii este:" << aux->info << "\n";
    }

    Coada& operator+(const Coada& nod) {
        this->ultim = nod.prim;
    }

    Coada& operator-(Coada& nod) {
        Nod* aux;
        int i = 1;
        while (nod.dim_max > 0) {
            Nod* p = nod.prim;
            while(p){
                if (p == nod.prim) {
                    delete p;
                }
                aux = p;
                p = p->next;
                i++;
                delete aux;
            }
            nod.pop();
        }
    }

    friend istream& operator>>(istream& is, const Coada& nod);
    friend ostream& operator<<(ostream& os, const Coada& nod);

    ~Coada() {
        cout << "LIST DELETED";
    }
};

istream& operator>>(istream& is, Coada& nod) {
    char x;
    while(1) {
        is >> x;
        if (x == '0') {
            return is;
        }
        nod.push(x);
    }
    return is;
}

ostream& operator<<(ostream& os, const Coada& nod) {
    Nod* p = nod.prim;
    Nod* aux;
    int i = 1;
    while(p) {
        os << i << ": " << p->info << "\n";
        aux = p;
        p = p->next;
        i++;
        delete aux;
    }
    return os;
}

class Deque: public Coada{
    public:
    int dim_max;
    Nod *prim, *ultim;

    Deque() {
        this->dim_max = 0;
        this->prim = NULL;
        this->ultim = NULL;
    }

    void pop_front() {
        if (this->prim == NULL) {
            return;
        }
        Nod* aux = this->prim;
        this->prim = aux->next;
        delete aux;
        this->dim_max--;
    }

    void pop_back() {
        Nod* p = this->prim;
        while(p->next->next) {
            p = p->next;
        }
        p->next = NULL;
        delete this->ultim;
        this->ultim = p;
        this->dim_max--;
    }

    void push_back(char x) {
        Nod* nod = new Nod;
        nod->info = x;
        nod->next = NULL;
        if (this->dim_max == 0) {
            this->prim = this->ultim = nod;
            this->dim_max++;
            return;
        }
        this->ultim->next = nod;
        this->ultim = nod;
        this->dim_max++;
    }

    void push_front(char x) {
        Nod* nod = new Nod;
        nod->info = x;
        nod->next = this->prim;
        if (this->dim_max == 0) {
            this->prim = this->ultim = nod;
            this->dim_max++;
            return;
        }
        this->prim = nod;
        this->dim_max++;
    }

    friend ostream& operator<<(ostream& os, const Deque& nod);
};

ostream& operator<<(ostream& os, const Deque& nod) {
    Nod* p = nod.prim;
    Nod* aux;
    int i = 1;
    while(p) {
        os << i << ": " << p->info << "\n";
        aux = p;
        p = p->next;
        i++;
        delete aux;
    }
    return os;
}

class PQ: public Coada  {
    public:
    void push(char x) {
        if (this->dim_max == 0) {
            Nod* nod = new Nod;
            nod->info = x;
            nod->next = NULL;
            this->prim = this->ultim = nod;
            this->dim_max++;
            return;
        }
        if (x < this->prim->info) {
            Nod* nod = new Nod;
            nod->info = x;
            nod->next = this->prim;
            this->prim = nod;
            this->dim_max++;
            return;
        }
        Nod* p = this->prim;
        while(p->next) {
            if (x < p->next->info) {
                Nod* nod = new Nod;
                nod->info = x;
                nod->next = p->next;
                p->next = nod;
                this->dim_max++;
                return;
            }
            p = p->next;
        }
        Nod* nod = new Nod;
        nod->info = x;
        nod->next = NULL;
        this->ultim->next = nod;
        this->ultim = nod;
        this->dim_max++;
    }
    void pop() {
        if (this->dim_max == 0) {
            return;
        } else if (this->dim_max == 1) {
            this->dim_max = 0;
            this->prim = this->ultim = NULL;
            return;
        }
        Nod* aux = this->prim;
        this->prim = this->prim->next;
        delete aux;
        this->dim_max--;
    }

    friend ostream& operator<<(ostream& os, const PQ& nod);
};

ostream& operator<<(ostream& os, const PQ& nod) {
    Nod* p = nod.prim;
    Nod* aux;
    int i = 1;
    while(p) {
        os << i << ": " << p->info << "\n";
        aux = p;
        p = p->next;
        i++;
        delete aux;
    }
    return os;
}


int main() {
    Deque d;
    PQ p;
    d.push_back('B');
    d.push_back('C');
    d.push_front('A');
    d.push_back('D');
    d.pop_front();
    d.pop_front();
    d.pop_back();

    p.push('A');
    p.push('X');
    p.push('B');
    p.pop();
    p.push('D');
    p.push('E');
    p.pop();
    cout << p;
    return 0;
}

