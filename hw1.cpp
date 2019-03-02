#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <time.h> 
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip> // setprecision
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

vector<string> list(string str,string delimiter){
    vector<string> lists;
    size_t pos = 0;
    string token;
    str = trim(str);
    while ((pos = str.find(delimiter)) != string::npos) {
        token = str.substr(0, pos);
        lists.push_back(token);
        //cout <<"Token:"<< token << endl;
        str.erase(0, pos + delimiter.length());
    }
    lists.push_back(str);
    // cout <<"Hello:" << s << endl;
    return lists;
}

int main(int argc, char *argv[]) {

    cout << "data mining hw1" << endl;
    string line;
    ifstream myfile ("input.txt");
    vector<string> lineitems;
   
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
           // cout << line << '\n';
            lineitems.push_back(line);
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    /*vector<string> ss = list(lineitems[0]," ");
    int i=1;
    for(string s : ss){
        cout << i <<":"<<s <<endl;
        i++;
    }*/

    vector<vector<string>> alltrans;
    for(string ss: lineitems){
        vector<string> line = list(ss," ");
        alltrans.push_back(line);
    }
    
    vector<string> listitem;
    map<string,int> mapitem; // item & support
    for(vector<string> l1: alltrans)
    {
        
        for(string l2:l1)
        {
            if(find(listitem.begin(),listitem.end(),l2)!=listitem.end()) // found
            {
               mapitem[l2]+=1;
            }
            else{
                listitem.push_back(l2); // not found
                mapitem.insert(make_pair(l2,1));
            }
        }
    }
    for(string s1:listitem){
        cout << s1 <<","<< mapitem[s1] << endl;
    }


    return 0;
}
