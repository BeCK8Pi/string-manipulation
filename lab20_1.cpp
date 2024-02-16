#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &name,vector<int> &score, vector<char> &grade){
    ifstream file(filename);
    char n[100];
    int score1,score2,score3,total;
    string textline;
    while(getline(file,textline)){
        sscanf(textline.c_str(),"%[^:]: %d %d %d",n,&score1,&score2,&score3);
        total = score1 + score2 + score3;
        name.push_back(n);
        score.push_back(total);
        grade.push_back(score2grade(total));
    }
}

void getCommand(string &command, string &key){
    string ans;
    char a[100],b[100];
    cout << "Please input your command: ";
    getline(cin,ans);
    sscanf(ans.c_str(),"%s %[^:]",a,b);
    command = a;
    key = b;
}

void searchName(vector<string> &name, vector<int> &score, vector<char> &grade, string key){
    int found = 0;
    cout << "---------------------------------" << endl;
    for(unsigned int i = 0; i < name.size(); i++){
        if(toUpperStr(key) == toUpperStr(name[i])){
            cout << name[i] << "'s score = " << score[i] << endl;
            cout << name[i] << "'s grade = " << grade[i] << endl;
            found++;
        }
    }
    if(found == 0) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> &name, vector<int> &score, vector<char> &grade, string key){
    int found = 0;
    cout << "---------------------------------" << endl;
    for(unsigned int i = 0; i < grade.size(); i++){
        if(key[0] == grade[i]){
            cout << name[i] << " (" << score[i] << ")" << endl;
            found++;
        }
    }
    if(found == 0) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;

}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
