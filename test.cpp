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

/**
 * @brief
 * 按照k为维度生成排列组合的数据集，比如两个2维数据集生成一个三维数据集
 * 参数3：待生成的数据集的维数
*/
set<set<string> > set_insert(set<string> a, set<string> b, int k){
    set< set<string> > ret;
    set<string> temp = a;
    for(auto it = b.begin(); it != b.end(); it++){
        temp.insert(*it);
        if(temp.size() == k){
            ret.insert(temp);
        }
        temp = a;
    };
    return ret;
}

void b_to_a(set<set<string> > &a, set<set<string> > b){
    for(auto it_b = b.begin(); it_b != b.end(); it_b++){
        a.insert(*it_b);
    }

}

//根据频繁k-1项集生成候选k项集
set<set<string> > genCk(set<set<string> > &Lk_sub_1, int k){
    set<set<string> > ret, temp;
    for(auto it = Lk_sub_1.begin(); it != Lk_sub_1.end(); it++){//此处已经生成了候选k项集合
        set<string> pre = *it;
        for(auto it_r = ++it; it_r != Lk_sub_1.end(); it_r++){
            temp = set_insert(pre, *it_r, k);
            b_to_a(ret, temp);
        }
        it--;
    }
    //从候选k项集中找到频繁k项集
    return ret;
}

//测试一下set_insert这个函数
void func4(){
    set<string> a;
    set<string> b;
    a.insert("a");
    b.insert("b");
    set<set<string> > result = set_insert(a, b, 2);
    for(auto it = result.begin(); it != result.end(); it++){
        set<string> a = *it;
        cout << "将两个二项集合并为一个三项集的结果为"<< endl;
        for(auto it_a = a.begin(); it_a != a.end(); it_a++){
            cout << *it_a ;
        }
        cout << endl;
    }
}

void genCk(set<set<string> > Lk, int k){
    set<set<string> > temp;
    for(auto it = Lk.begin(); it != Lk.end(); it++){
        auto flag = it;
        for(int i = 0; i < k; i++){
            
        }
    }
}

//测试genCk函数
void func5(){
    set<string> a, b, c, d;
    a.insert("a");
    a.insert("b");
    b.insert("a");
    b.insert("c");
    c.insert("b");
    c.insert("c");
    d.insert("e");
    d.insert("f");

    
    set< set<string> > bund;
    bund.insert(a);
    bund.insert(b);
    bund.insert(c);
    bund.insert(d);
    set< set<string> > ret;
    ret = genCk(bund, 3);

    for(auto it = ret.begin(); it != ret.end(); it++){
        set<string> temp = *it;
        cout << "测试genCk函数" << endl;
        for(auto it_s = temp.begin(); it_s != temp.end(); it_s++){
            cout << *it_s;
        }
        cout << endl;
    }

}
int main(){
    // func4();
    func5();
    return 0;
}