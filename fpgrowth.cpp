#include<iostream>
#include<set>
#include<map>
#include<fstream>
#include<vector>
#include<cstring>
#include<sstream>
using namespace std;
/**
 * @brief 步骤：
 * 1、降序排列项集
 * 2、删掉不满足最小支持度的项
 * 3、建立一颗n叉树，从一个虚根节点开始
 * 4、树的结构应该包括：孩子、同属性兄弟、父母（需要向上遍历）
 * 5、
 */

class Node{
    public:
        Node *child, *father, *same_bro;
        map<set<string>, int> content;
};

class FP_growth{
private:
    string FileName;
    int minSup;
    Node v_root;
    //保存数据集合data_base
    map< long, set<string> > Database;
public:
    FP_growth(string FileName, int minSup){
        this->FileName = FileName;
        v_root.father = NULL;
        v_root.same_bro = NULL;
        this->minSup = minSup;
    };
    bool buildData();
    map<string, int> pre_process();
    int insert(set<string> &);
    void rm_low(map<string, int> &);
};

int line_num;
bool FP_growth::buildData(){
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
            }
        }
    }
    cout<<"项目总数: "<<Database.size()<<endl;
    return EXIT_SUCCESS;
}

map<string, int> FP_growth::pre_process(){//计算每一个字符串出现的次数，
    map<string, int> result;
    for(auto it = Database.begin(); it != Database.end(); it++){
        for(auto it_second = it->second.begin(); it_second != it->second.end(); it_second++){
            pair<map<string, int>::iterator, int> ret = result.insert(make_pair(*it_second, 1));
            if(!ret.second){
                ret.first->second++;
            }
        }
    }
    //打印测试一下是否正确
    for(auto it = result.begin(); it != result.end(); it++){
        cout << "测试pre_process" << "串:" <<it->first << "量：" << it->second <<endl;
    }//正确

    return result;
}

//删除小于设定支持度的数据
void FP_growth::rm_low(map<string, int> &src){
    for(auto it = src.begin(); it != src.end(); it++){
        if(it->second < minSup){
            src.erase(it->first);
        }
    }
    //测试删除之后的结果
    for(auto it = src.begin(); it != src.end(); it++){
        cout << "rm_low" << ":" <<it->first << ":" << it->second <<endl;
    }
}

int main(){
    string FileName = "file.txt";
    FP_growth fp(FileName, 2);
    fp.buildData();
    map<string, int> ret = fp.pre_process();
    fp.rm_low(ret);
}
