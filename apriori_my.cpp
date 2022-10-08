#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<cstring>
#include<fstream>
#include<sstream>//istringstream需要使用这个头文件
using namespace std;

class Apriori{
private:
    string FileName;
    float minSup;
    map<long, set<string> > Database;//储存所有待处理数据集
    // map< string, set<int> > mp;
    set<string> add(set<string> &, set<string> &);
public:
    Apriori(string FileName, float MinSup){
        this->FileName = FileName;
        this->minSup = MinSup;
    }
    bool buildData();
    map<string, int> getC1();
    map<set<string>, int> getL1();
    set<set<string> > aprioriGen(int m, set<set<string> > &);
    map<set <string>, int> getLk(int k, set<set<string> > Lk0);

};

bool Apriori::buildData(){
    ifstream inFile;
    inFile.open("file.txt");
    if(!inFile){
        return false;
    }
    string textline;
    getline(inFile, textline);
    vector<string> lines;
    while(getline(inFile, textline)){
        lines.push_back(textline);
    };
    for(int line_num = 0; line_num < lines.size(); line_num++){
        istringstream line(lines[line_num]);
        string word;
        while(line >> word){
            if(word.size() >= 1){
                Database[line_num].insert(word);
            }
        }
    }
    //遍历Database检查正确性
    cout << "遍历Database检查正确性" << endl;
    set<string> s;
    for(map<long, set<string> >::iterator it = Database.begin(); it != Database.end(); it++){
        s = it->second;
        cout << "map first " << it->first << " ";
        for (auto it=s.begin(); it != s.end(); it++){
            cout << *it;
        }
        cout << endl;
    }
    return true;
};

map<string,int> Apriori::getC1(){
    map<string, int> C1;
    for(auto it = Database.begin(); it != Database.end(); it++){
        for(auto it_s = it->second.begin(); it_s != it->second.end(); it_s++){
            auto ret = C1.insert(make_pair(*it_s, 1));
            if(!ret.second){
                ret.first->second++;//一项集计数
            }
        }
    }
    //输出检查C1正确性
    cout << "输出检查C1正确性" << endl;
    for(auto it = C1.begin(); it != C1.end(); it++){
        cout << it->first << " " << it->second << endl;
    }
    return C1;
};
//频繁一项集
map<set<string>, int> Apriori::getL1(){
    map<set<string>, int> L1;
    map<string, int> C1 = getC1();
    for(auto it = C1.begin(); it != C1.end(); it++){
        if(it->second >= minSup){
            set<string> key;
            key.insert(it->first);
            L1[key] = it->second;
        }
    }
    return L1;
};

set<string> Apriori::add(set<string> &a, set<string> &b){
    set<string> ret = a;
    for(auto it = b.begin(); it != b.end(); it++){
        ret.insert(*it);
    }
    return ret;
}

bool is_not_same(set<string> &a, set<string> &b){
    set<string> temp = a;
    for(auto it = b.begin(); it != b.end(); it++){
        temp.erase(*it);
    }
    if(temp.size() == 1){
        return true;
    }else{
        return false;
    }
}
//根据频繁k项集生成候选k+1项集
set<set<string> > Apriori::aprioriGen(int m, set<set<string> > &Lk0){
    set<set<string> > Ck;//用于保存候选k+1项集
    for(auto it = Lk0.begin(); it != Lk0.end(); it++){
        set<string> Li = *it;
        for(auto itr = ++it; itr != Lk0.end(); itr++){
            set<string> Lj = *itr;
            if(is_not_same(Li, Lj)){
                set<string> Ci = add(Li, Lj);
                if(Ci.size() == m+1){
                    if(!Lk0.count(Ci)){
                        Ck.insert(Ci);
                    }
                }
            }
        }
    }
    //取出set<string>
    cout << "检查二项集" << endl;
    for(auto it = Ck.begin(); it != Ck.end(); it++){
        set<string> temp = *it;
        for(auto itr = temp.begin(); itr != temp.end(); itr++){
            cout << *itr;
        }
        cout << endl;
    }
    return Ck;
}

map<set<string>, int> Apriori::getLk(int k, set<set<string> > Lk0){
    map<set<string>, int> Lk;
    for(auto it = Lk0.begin(); it != Lk0.end(); it++){
        set<string> elem_grup = *it;
        for(auto itr = Lk0.begin(); itr != Lk0.end(); itr++){
            set<string> elem_grupr = *itr;
            
        }
    }
}

int main(){
    Apriori apri("file.txt", 2);
    apri.buildData();
    // apri.getC1();
    apri.getL1();

    return 0;
}