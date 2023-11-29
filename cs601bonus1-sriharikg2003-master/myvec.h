#ifndef MYVEC_H
#define MYVEC_H
//CS601BOnus1: Helper file 
template<typename T>
class MyVec{
	//private attributes
	T* data;
	int vecLen;
public:
	MyVec(int len); //constructor decl.
	MyVec();
	MyVec(const MyVec& rhs); //copy constructor
	int GetVecLen() const; //member function
	T& operator[](int index) const;

	~MyVec(); //destructor decl.
    MyVec<T>& operator--();

    MyVec<T> operator--(int);

    MyVec<T>& operator=(const MyVec<T>& rhs);

friend MyVec<T> operator-(const MyVec<T>& lhs, const MyVec<T>& rhs);

   
};

//defining the constructor
template<typename T>
MyVec<T>::MyVec(int len) {
	vecLen=len;
	data=new T[vecLen];
}

template<typename T>
MyVec<T>::MyVec() {
	vecLen=0;
	data=nullptr;
}

template<typename T>
MyVec<T>::MyVec(const MyVec<T>& rhs) {
	vecLen=rhs.GetVecLen();
	data=new T[vecLen];
	for(int i=0;i<vecLen;i++) {
		data[i] = rhs[i];
	}
}

template<typename T>
int MyVec<T>::GetVecLen() const {
	return vecLen;
}

template<typename T>
T& MyVec<T>::operator[](int index) const {
	return data[index];
}

//defining the destructor
template<typename T>
MyVec<T>::~MyVec() {
	delete [] data;
}
#endif


template<typename T>
MyVec<T>& MyVec<T>::operator--() {
    for (int i = 0; i < vecLen; i++) {
        char* str = data[i];
        while (*str) {
            if (*str != 'A') {
                (*str)--;
            }
            str++;
        }
    }
    return *this;
}



template<typename T>
MyVec<T> MyVec<T>::operator--(int) {
    MyVec<T> copy(*this);
    --(*this);
    return copy;
}

template<typename T>
MyVec<T>& MyVec<T>::operator=(const MyVec<T>& rhs) {
    if (this == &rhs) {
        return *this;
    }
    delete[] data;
    vecLen = rhs.vecLen;
    data = new T[vecLen];
    for (int i = 0; i < vecLen; i++) {
        data[i] = rhs.data[i];
    }
    return *this;
}



template<typename T>
MyVec<T> operator-(const MyVec<T>& lhs, const MyVec<T>& rhs) {
    MyVec<T> result(lhs.GetVecLen());
    int res = 0;
    for (int i = 0; i < lhs.GetVecLen(); i++) {
        bool found = false;
        for (int j = 0; j < rhs.GetVecLen(); j++) {
            if (strcmp(lhs[i], rhs[j]) == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            result[res] = lhs[i];
            res++;
        }
    }

    result.Resize(res);

    return result;
}