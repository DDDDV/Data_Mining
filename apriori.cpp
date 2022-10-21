#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <windows.h>
using namespace std;

class Apriori{
private:
    string FileName;
    float minSup;
    map< long, set<string> > Database;
    map< string,set<int> > mp;   //string -- 所有行数
    void sub(set<string> &set1, set<string> &set2);
    set<string> add(set<string> &set1, set<string> &set2);
    set<set<string> > notSup;
public:
    Apriori(string FileName, float MinSup){
        this->FileName = FileName;
        this->minSup = MinSup;
    }
    bool buildData();
    map< string, int> getC1();
    map< set<string>, int > getL1();
    set< set<string> > keySet(map<set<string>,int> &Lk);
    set< set<string> > aprioriGen(int m, set< set<string> > &);
    map< set<string>, int > getLk(int k, set<set<string> >);
    int printsetSet(set< set<string> > &);
    friend bool fun1(set<string> &a,set<string> &b);
};
 
int line_num;
 
int Apriori::printsetSet(set<set<string> > &setSet) {//包了两层set
    int cnt=0;
    for(set< set<string> >::iterator it = setSet.begin(); it!=setSet.end(); it++,cnt++){
        set<string>::iterator It = (*it).begin();
        while(It != (*it).end()){
            cout<< *It++ <<" ";
        }
        cout<<endl;
    }
    return cnt;
}
 
//将数据存入Map，产生事务数据库（抄一遍data，形成map<long,set<string>>的数据结构）
bool Apriori::buildData() {
    ifstream inFile;
    inFile.open(FileName.c_str());
    if(!inFile){
        cout<<"文件"<<FileName<<"打开错误，请检查"<<endl;
        return EXIT_FAILURE;
    }
    string textline;
    vector<string> lines_of_text;
    getline(inFile,textline);//多读取一行文本，消除文件开头标号
    while(getline(inFile,textline))
        lines_of_text.push_back(textline);  //产生数据库
    for(line_num=0; line_num != lines_of_text.size(); line_num++){
        istringstream line(lines_of_text[line_num]);
        string word;
        while(line >> word){
            if(word.size()>=1){
                Database[line_num].insert(word);
                mp[word].insert(line_num);//把行号当作word的值，且作为set<int>值
            }
        }
    }
    cout<<"项目总数: "<<Database.size()<<endl;
    return EXIT_SUCCESS;
}

//获取候选1项集：所有元素--个数：map<string,int>
map<string, int> Apriori::getC1() {
    map<string,int> C1;
    for( map< long,set<string> >::iterator mapIt = Database.begin(); mapIt != Database.end();){
        for(set<string>::iterator setIt = mapIt->second.begin(); setIt != mapIt->second.end(); ){
            pair<map<string,int>::iterator,bool> ret = C1.insert(make_pair(*setIt,1));  //没有true，有false
            if(!ret.second) //ans中已有setIt对应的元素
                ret.first->second++;
            setIt++;
        }
        mapIt++;
    }
    return C1;
}

//获取频繁1项集：频繁元素-个数：map<set<string>,int>
map<set<string>, int> Apriori::getL1() {
    if(minSup<1){
        minSup *= line_num;
        minSup = (int)minSup;
    }
    map<set<string>, int> L1;
    map<string, int> C1 = getC1();
    for(map<string,int>::iterator it=C1.begin(); it!=C1.end(); it++){
        if(it->second >= minSup){
            set<string> Key;
            Key.insert(it->first);  //这样写下一步才放得进去
            L1[Key] = it->second;
        }
    }
    return L1;
}

//获取map里所有频繁项集的串已经做成的set，再一起做成set
set< set<string> > Apriori::keySet(map<set<string>,int> &Lk) {
    set< set<string> > ans;
    for( map<set<string>,int>::iterator it = Lk.begin(); it!=Lk.end(); it++)
        ans.insert(it->first);
    return ans;
}

//集合差：set1-set2
void Apriori::sub(set<string> &set1, set<string> &set2) {
    for(set<string>::iterator it = set2.begin(); it != set2.end(); it++){
        set1.erase(*it);
        if(set1.size() == 0) break;
    }
}

//并集：set1+set2
set<string> Apriori::add(set<string> &set1, set<string> &set2) {
    set<string> ans(set1.begin(),set1.end());
    for(set<string>::iterator it = set2.begin(); it != set2.end(); it++)
        ans.insert(*it);
    return ans;
}

bool fun1(set<string> &a,set<string> &b){
    set<string> t = a;
    for(set<string>::iterator it = b.begin();it != b.end();it++){
        t.erase(*it);
    }
    if(t.size() == 1)
        return true;
    else
        return false;
}

//L(k-1)获取Ck
set< set<string> > Apriori::aprioriGen(int m, set<set<string> > &Lk0) {
    set< set<string> > Ck;
    for(set< set<string> >::iterator it=Lk0.begin(); it != Lk0.end(); ){
        set<string> Li = *it;
        for(set< set<string> >::iterator itr = ++it; itr != Lk0.end(); itr++){
            set<string> Lj = *itr;
            if(fun1(Li, Lj)){
                set<string> Ci = add(Li,Lj);
                if(Ci.size() == m+1)
                    if(!Lk0.count(Ci))
                        Ck.insert(Ci);
            }
        }
    }
    //产生了ck之后 应该进行剪枝工作
    for(auto it = Ck.begin(); it != Ck.end(); ){
        bool flag = false;
        set<string> temp = *it;
        for(auto itr = notSup.begin(); itr != notSup.end(); itr++){//这里可能可以倒序遍历？会更快？
            set<string> t = *itr;
            if(fun1(temp, t)){
                it = Ck.erase(it);
                flag = true;
                break;//如果删除，跳出本次循环。跳出循环
            }
        }
        if(flag != true){//迭代器删除标记，如果删除则无需+1，否则需要+1
            it++;
        }
        
    }
    cout<<"完成"<<endl;
    return Ck;
}
set<int> intersec(set<int> &a,set<int> &b){
    set<int> t;
    set_intersection(a.begin(),a.end(), b.begin(),b.end(), inserter(t,t.begin()));
    return t;
}
 
//根据频繁k-1项集键集，获取频繁k项集
map< set<string>, int > Apriori::getLk(int k, set<set<string> > Lk0) {
    map< set<string>,int> Lk,Ck;
    set< set<string> > CkSet = aprioriGen(k-1, Lk0);    //Ck的set-string，再集合成set
    //剪枝

    for(set< set<string> >::iterator i=CkSet.begin(); i!=CkSet.end(); i++){ //每一个set<string>
        string head = *(*i).begin();
        set<int> temp = mp[head];
        for(set<string>::iterator j = ++(*i).begin(); j!=(*i).end(); j++){
            set<int> t = mp[*j];    //j是set<string>里的每一个string，找到对应的int
            temp=intersec(temp,t);//求两个集合的交集
        }
        if(temp.size()>=minSup)
            Lk[*i]=(int)temp.size();//已经是频繁项集了
        else
            notSup.insert(*i);//不频繁的项集存入到notSup中 以便生成Ck时进行剪枝
    }
    return Lk;
}
 
int main() {
    DWORD time_start, time_end;
    time_start = GetTickCount();
    float min_sup;
    // cout<<"请输入最小支持数/度：";
    // cin>>min_sup;
    min_sup = 1000;
    Apriori apriori("file.txt", min_sup);
    apriori.buildData();
    map<set<string>,int> L1 = apriori.getL1();
    set<set<string> > Set = apriori.keySet(L1); //频繁1项集的所有串，做成set
    map<int,set<set<string> > > L;
    L.insert(make_pair(1,Set));
 
    for(int k=2; ;k++){
        cout<<"k="<<k<<" ";
        map<set<string>,int> setLk = apriori.getLk(k,Set);  //获取频繁k项集的所有string和相应个数
        //map<set<string>,int> setLk = apriori.getLk0(k,Set);
        if(setLk.size()){
            Set = apriori.keySet(setLk);
            L.insert(make_pair(k,Set));
        }
        else break;
    }
    
    ofstream fcout;
    fcout.open("res.txt");
    //fcout.open("res_0.01.txt");
    int cnt=0;
    for(map<int, set<set<string> > >::iterator it = L.begin();it!=L.end();it++){
        cout<<"频繁"<<it->first <<"项集: "<<endl;
        fcout<<"频繁"<<it->first <<"项集: "<<endl;
        int n = apriori.printsetSet(it->second);
        for(set< set<string> >::iterator j = (it->second).begin(); j!=(it->second).end(); j++){
            set<string>::iterator It = (*j).begin();
            while(It != (*j).end()){
                fcout<< *It++ <<" ";
            }
            fcout<<endl;
        }
        cout<<"n="<<n<<endl;
        fcout<<"n="<<n<<endl;
        cnt += n;
    }
    time_end = GetTickCount();
    cout<<"总数="<<cnt<<endl;
    fcout<<"总数="<<cnt<<endl;
    fcout<<"consume time = " << (time_end - time_start) << endl;
    return 0;
}
