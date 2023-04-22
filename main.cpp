#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

class matrix{
    private:
    std::vector<std::vector<int>> matrix_;
    int x;
    int y;
    public:
    matrix()=default;
    matrix(int y,int x,std::initializer_list<int>&&data){
        this->x=x;
        this->y=y;
        matrix_.resize(y);
        int pos=0;
        for(int i=0;i<y;i++){
            matrix_[i].resize(x);
            std::copy_n(data.begin()+pos,x+1,matrix_[i].begin());
            pos+=x;
        }
    }

    matrix(int y,int x,std::vector<int>&&data){
        this->x=x;
        this->y=y;
        matrix_.resize(y);
        int pos=0;
        for(int i=0;i<y;i++){
            matrix_[i].resize(x);
            std::copy_n(data.begin()+pos,x+1,matrix_[i].begin());
            pos+=x;
        }
    }

    friend std::ostream& operator<<(std::ostream&os,const matrix&matrix);
    friend matrix operator+(const matrix&lhs,const matrix&rhs);
    friend matrix operator*(const matrix&lhs,const matrix&rhs);
    friend matrix operator*(const matrix&lhs,int x);
    friend matrix operator-(const matrix&lhs,const matrix&rhs);
    matrix&operator=(const matrix&rhs){
        x=rhs.x;
        y=rhs.y;
        matrix_.resize(rhs.y);
        for(int i=0;i<y;i++){
            matrix_[i].resize(rhs.x);
            for (int j=0; j<rhs.x;j++) {
                matrix_[i][j]=rhs.matrix_[i][j];
            }
        }
        return *this;
    }
};

inline matrix operator+(const matrix&lhs,const matrix&rhs){
    std::vector<int> buf;
    int pos=0;
    buf.resize(lhs.x*lhs.y);
    for(int i=0;i<lhs.y;i++){
        std::transform(lhs.matrix_[i].begin(),lhs.matrix_[i].end(),rhs.matrix_[i].begin(),buf.begin()+pos,std::plus<int>());
        pos+=lhs.x;
    }
    return matrix(lhs.y,lhs.x,std::move(buf));
}

inline matrix operator-(const matrix&lhs,const matrix&rhs){
    std::vector<int> buf;
    int pos=0;
    buf.resize(lhs.x*lhs.y);
    for(int i=0;i<lhs.y;i++){
        std::transform(lhs.matrix_[i].begin(),lhs.matrix_[i].end(),rhs.matrix_[i].begin(),buf.begin()+pos,std::minus<int>());
        pos+=lhs.x;
    }
    return matrix(lhs.y,lhs.x,std::move(buf));
}

inline matrix operator*(const matrix&lhs,const matrix&rhs){
    std::vector<int> subvec;
    for(int i=0;i<lhs.y;i++){
        for(int j=0;j<rhs.x;j++){
            int sum=0;
            for(int k=0;k<lhs.x;k++){
                sum+=lhs.matrix_[i][k]*rhs.matrix_[k][j];
            }
            subvec.push_back(sum);
        }
    }
    return matrix(lhs.y,rhs.x,std::move(subvec));
}

inline matrix operator*(const matrix&lhs,int x){
    std::vector<int> subvec;
    for(auto i:lhs.matrix_){
        for(int j:i){
            subvec.push_back(j*x);
        }
    }
    return matrix(lhs.x,lhs.y,std::move(subvec));
}

inline std::ostream& operator<<(std::ostream&os,const matrix&matrix){
    for(auto subvec:matrix.matrix_){
        for(int i:subvec){
            os<<i<<" ";
        }
        os<<'\n';
    }
    return os;
}

int main(){
    matrix A(3,3,{4,2,1,3,-2,0,0,-1,2});
    matrix B(3,3,{2,0,2,5,-7,-2,1,0,-1});
    matrix C=(A*A-B*B)*3-A*B*2;
    std::cout<<C<<std::endl;
    return 0;

}
