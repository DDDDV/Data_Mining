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
    void pre_process();
    int insert(set<string> &);
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

void FP_growth::pre_process(){
    map<set<string>, int> result;
    for(auto it = Database.begin(); it != Database.end(); it++){
        pair<map<set<string>, int>, int> ret = result.insert(make_pair(*it->second, 1));
    }
}
