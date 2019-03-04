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

int min_support = 5;
int min_conf = 50;

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
           // cout << "token:"<<token<<endl;
            lists.push_back(token);
            //cout <<"Token:"<< token << endl;
            str.erase(0, pos + delimiter.length());
    }
    if(!str.empty()){
        lists.push_back(str);
    }
 
    return lists;
}

string combinationUtil(vector<string> arr, int n, int r, int index, vector<string> data , int i) 
{ 
    // Current cobination is ready, print it 
   
    vector<string> list;
    string ss;
    if (index == r) 
    { 
        string temp;
        for (int j=0; j<r; j++){
           // cout << data[j]<<",";
            if(j!=r-1){
                temp += data[j]+",";
            }
            else{
                temp += data[j]+"||";
            }
            
        } 
        return temp; 
    } 

    // When no more elements are there to put in data[] 
    if (i >= n) 
        return ""; 
  
    // current is included, put next at next location 
    //data[index] = arr[i]; 
    data.insert(data.begin()+ index,arr[i]);
    ss +=combinationUtil(arr, n, r, index+1, data, i+1); 
  
    // current is excluded, replace it with next (Note that 
    // i+1 is passed, but index is not changed) 
    ss +=combinationUtil(arr, n, r, index, data, i+1); 
    return ss;
} 


vector<string> printCombination(vector<string> items, int n, int r) 
{ 
    // A temporary array to store all combination one by one 
    vector<string> data;

    // Print all combination using temprary array 'data[]' 
    vector<string> str;
    string li;

    li = combinationUtil(items, n, r, 0, data, 0);
    str = list(li,"||");
    return str; 
}

void removeElement(vector<string> &arr, map<string,int> map1){
    
    //double min_support = 2;
    //double min_conf = 60;
    for (vector<string>::iterator it=arr.begin(); it!=arr.end();)
    {
    
        vector<string> bb = list(*it,",");
        string prefix =bb[0];
        for(int i=1;i<bb.size()-1;i++)
        {
            prefix+=","+bb[i];
        }
        double conf = (double)map1[*it]/(double)map1[prefix];
       // cout <<"remove :" << *it << ":"<< map1[*it] <<"/"<<(double)map2[prefix] <<":" << (conf*100) <<endl; 
        if(map1[*it]<min_support || (conf*100)<min_conf){
        
        it = arr.erase(it);
        }
        else{
            ++it;
        }   
    }
}
  
int main(int argc, char *argv[]) {

    cout << "Create Association Rule" << endl;


    if(argc<4){
        cerr << "Usage: " << argv[0] << " <INPUT_FILE> " <<" <MIN_SUPPORT>" <<" <MIN_CONF>"  << endl;
		return 1;
    }

    string line;
    string input_f = argv[1];
    min_support = stoi(argv[2]);
    min_conf = stoi(argv[3]);
    ifstream myfile (input_f);
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

    vector<vector<string>> alltrans;
    vector<vector<string>> listtrans;
    for(string ss: lineitems){
        vector<string> line = list(ss," ");
        alltrans.push_back(line);
    }
    
    vector<string> listitem;
    //map<string,int> mapitem; // item & support
    map<string,int> mapitem;
    vector<map<string,int>> maps; 

     cout <<"1 - itemset is being computed ..... " <<endl;
    // dbscan
    int n_total = 0;
    for(vector<string> l1: alltrans)
    {
        
        for(string l2:l1)
        {
            if(l2!="\r")
            {
                if(find(listitem.begin(),listitem.end(),l2)!=listitem.end()) // found
                {
                    mapitem[l2]+=1;
                }
                else{
                    listitem.push_back(l2); // not found
                    mapitem.insert(make_pair(l2,1));
                }
               n_total++;   
            }
        }       
    }
    maps.push_back(mapitem);

    /*for(string s1:listitem){
            cout << s1 <<","<< mapitem[s1] << endl;
            //n_total+=mapitem[s1];
    }*/

     cout << "total items=" << n_total <<endl;

    //double min_support = 2;
    for (vector<string>::iterator it=listitem.begin(); it!=listitem.end();)
    {
          if(mapitem[*it]<min_support){
            it = listitem.erase(it);
          }
          else{
            ++it;
          }   
    }

    // update
   
    /*for(string s1:listitem){
            cout << s1 <<","<< mapitem[s1] << endl;
            //n_total+=mapitem[s1];
    }*/

    /*vector<string> cc = printCombination(listitem,listitem.size(),2);
    cout << "cc.size = " << cc.size()<<endl;
    for(string aa:cc){
        cout <<aa<<endl;
    }*/

    listtrans.push_back(listitem);
    vector<string> list2seq;
    cout <<"2 - itemset is being computed ..... " <<endl;
    for(int i=0;i<listitem.size();i++)
    {
        for(int j=0;j<listitem.size();j++)
        {
            string key = "";
            if(i!=j)
            {
                //cout << listitem[i]<<"->"<<listitem[j]<<endl;
                key = listitem[i] + "," + listitem[j];
                string dbscan[] = {listitem[i],listitem[j]};
                mapitem.insert(make_pair(key,0));
                list2seq.push_back(key);
                for(vector<string> l1: alltrans)
                {
                    int n_found = 0;
                    for(int x=0;x<2;x++)
                    {
                        if(find(l1.begin(),l1.end(),dbscan[x])!=l1.end()) // found
                        {
                            n_found++;
                        }
                    }
                    if(n_found==2)
                    {
                        mapitem[key]+=1;
                    }
                }
            }
        }
    }
    maps.push_back(mapitem);

   /* for(string aa:list2seq){
        vector<string> bb = list(aa,",");

        double conf = (double)mapitem2[aa]/(double)mapitem[bb[0]];

        cout << aa <<":"<<mapitem2[aa]<<":"<<conf <<endl;
    }*/
    //cout << "after----------" <<endl;
    removeElement(list2seq,mapitem);
    listtrans.push_back(list2seq);
    /*cout << "aa.sizw():" << list2seq.size()<<endl;
    for(string aa:list2seq){

        vector<string> bb = list(aa,",");
        double conf = (double)mapitem2[aa]/(double)mapitem[bb[0]];
        cout << aa <<":"<<mapitem2[aa]<<":"<<conf <<endl;
    }*/
    //map<string,int> mapkey[listitem.size()-1];
     map<string,int> mapkey;
    for(int n=3;n<=listitem.size();n++)
    {
        cout << n <<"-item set is being computed...." << endl;
        
        vector<string> cc = printCombination(listitem,listitem.size(),n);
        //listtrans.push_back(cc);
        //cout << "cc.size = " << cc.size()<<endl;
        int n_total_trans = 0;
        for(string aa:cc)
        {
            
            mapitem.insert(make_pair(aa,0));
            vector<string> listnum = list(aa,",");
            for(vector<string> l1: alltrans)
            {
                int n_found = 0;
                for(int i=0;i<listnum.size();i++)
                {
                    if(find(l1.begin(),l1.end(),listnum[i])!=l1.end()) // found
                    {
                        n_found++;
                    }
                }
                if(n_found==listnum.size())
                {
                    //cout << 
                    mapitem[aa]+=1;
                    n_total_trans++;
                }

            } 
        }
        maps.push_back(mapitem);
        if(n_total_trans!=0){ // there are at least one transaction occur
            //cout << "***************n="<<n<<endl;
           // for(string ab:cc)
            //{
             //   cout << ab <<":"<<mapkey[ab]<<endl;
               
            //}
            removeElement(cc,mapitem); 
            // << "after remove :" << cc.size() <<endl;
            if(cc.size()!=0){
               listtrans.push_back(cc);
            }
            else{ // no transaction in n-item set no need to continue generating rule
                break;
            }
        }
        else{
            cout << "no any rules in "<< n << "-itemset"<<endl;
            break;
        }
        
    }
  
    cout << "Print Output Process"<< endl;
    ofstream outfile;
   // outfile.open("output.txt",ios_base::app); //append
    string output = "Result_"+input_f;
    outfile.open(output); // overwrite
    string content;
    int k=0;
    content = "Min_Support=" + to_string(min_support) + " Min_conf=" + to_string(min_conf)+"%" +"\n";
    for(vector<string> rules:listtrans){
        cout <<(k+1) <<"- itemset"<<endl;
        content += to_string((k+1)) + "- itemset"+"\n";
       // map<string,int> m = maps[k];
        for(string rule:rules){
            
            if(k==0){

                cout << "{" << rule << "} " << "("<< mapitem[rule]<<"/"<< mapitem[rule] <<")"<<endl;
                content += "{" + rule + "} " + "(" + to_string(mapitem[rule]) + "/" + to_string(mapitem[rule]) + ")" +"\n";
            }
            else{
                vector<string> item = list(rule,",");
                string prefix =item[0];
                for(int i=1;i<item.size()-1;i++)
                {
                    prefix+=","+item[i];
                }
                //cout << rule << endl;
               // map<string,int> mp = maps[k-1];
                cout << "{"<< prefix << "}->"<<"{"<< item[item.size()-1]<<"} ("<<mapitem[rule]<<"/"<<mapitem[prefix]<<")"<< endl;
                content +="{" + prefix + "}->" + "{"+ (item[item.size()-1]) +"} (" + to_string(mapitem[rule]) + "/" + to_string(mapitem[prefix]) + ")"+ "\n";
            }
          
            
        }
        k++;
    }
    outfile << content; 
    outfile.close();
        




    return 0;
}
