#include<iostream>
#include<string>
#include<vector>
#define MAX_SIZE 80

using namespace std;

void calu(string &src){
    char add = '+';
    char sub = '-';
    bool flag = false;
    vector<int> all_syb_pos;
    vector<string> all_num;
    vector<string> top_num;
    vector<string> bottom_num;
    int symbol[MAX_SIZE];
    int symbol_num = 0;
    string temp = src;
    while(true){
        size_t pos = src.find("+") || src.find("-");
        if(pos == string::npos){
            all_num.push_back(src);
            break;
        }else if(pos == 0){
            flag = true;
            src = src.substr(1, src.size());
            continue;
        }
        all_syb_pos.push_back(pos);
        all_num.push_back(src.substr(0, pos));
        src = src.substr(pos, src.size());
    }


    // size_t pos = src.find("+") || src.find("-");
    // while(pos != string::npos){
    //     symbol[symbol_num++] = src[pos];
    //     pos = src.find("+") || src.find("-");
    // }

    

    // for(int i = 0; i < src.length(); i++){
    //     if(src[i] == add || src[i] == sub){
            
    //     }
    // }
}

int main(){
    string test= "123+254";
    calu(test);
    return 0;
}