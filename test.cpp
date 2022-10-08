#include<set>
#include<map>
#include<iostream>
using namespace std;
//测试往set集合中加入set集合，如果第二个set集合内容相同，能否加入成功。
//结论，两个set集合如果相同，那么再加入到一个大的set集合中时，会被认为相同元素而最终只能插入一个
void func1(){
set<set<string> > father;
    set<string> child1;
    child1.insert("a");
    child1.insert("b");
    set<string> child2;
    child2.insert("a");
    child2.insert("c");
    set<string> child3;
    child3.insert("a");
    child3.insert("d");
    father.insert(child1);
    father.insert(child2);
    father.insert(child3);
    set<set<string> > result;
    for(auto it = father.begin(); it != father.end(); it++){
        set<string> child = *it;
        for(auto itr = ++it; itr != father.end(); itr++){
            
        }
        cout << endl;
    }
    cout << father.size() << endl;
}
//测试map为空时，map的访问
void func2(){
    map<string, int> m;
    cout << m["h"] << endl;
    cout << "输出m中的所有元素" << endl;
    for(auto it = m.begin(); it != m.end(); it++){
        cout << it->first << " " << it->second << endl;
    }
}
//测试map
void func3(){
    map<string, set<int> > m;
    m["h"].insert(2);
    m["h"].insert(3);
    for(auto it = m.begin(); it != m.end(); it++){
        cout << it->first << ": ";
        set<int> a = it->second;
        for(auto it_s = a.begin(); it_s != a.end(); it_s++){
            cout << *it_s << " ";
        }
        cout << endl;
    } 
}
int main(){
    // func2();
    func3();
}