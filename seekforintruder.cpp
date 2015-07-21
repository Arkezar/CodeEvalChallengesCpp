//
// Created by arkezar on 15.07.15.
//

// Incompatible with GDB 4.8.1

#include <iostream>
#include <fstream>
#include <regex>

using namespace std;
namespace sfi{
    namespace data {
        struct expr;
        struct address;
    }
    namespace logic {
        static string toDot(string, int);
        static bool validateAddr(const string&);
        static string dotToDotDec(const string&, int);
        static void searchAddr(const string&, sfi::data::expr, vector<string>&);
        static int elExists(const vector<sfi::data::address>&, const string&);
    }

}

struct sfi::data::expr {
public:
    expr(string s, int b, bool d) : str(s),base(b),dot(d){}
    regex str;
    int base;
    bool dot;
};

struct sfi::data::address {
    address(string addr, int count) : addr(addr), count(count){}
    void increaseCount() {this->count++;}
    string addr;
    int count;
};

static string sfi::logic::toDot(string str, int base){

    if(base == 16){
        for(int i = 4 ; i < str.length(); i+=5){
            str.insert(i,".0x");
        }
    } else if(base == 10) {
        if (str.length() < 9) {
            unsigned long tmp = stoul(str);
            str = bitset<32>(tmp).to_string();
        } else {
            str = "0";
        }
    } else {
        for (int i = str.length() / 4; i < str.length(); i += str.length() / 4 + 1) {
            str.insert(i, ".");
        }
    }

    return str;
}

static bool sfi::logic::validateAddr(const string& addr){
    vector<int>octets;
    istringstream ss(addr);
    string oct;
    while(getline(ss,oct,'.')){
        octets.push_back(stoul(oct));
    }

    if(octets[0] > 255 || octets[0] < 1)
        return false;

    if(octets[octets.size()-1] > 254)
        return false;

    for(int i = 1 ; i < octets.size()-1 ; i++){
        if(octets[i] > 255)
            return false;
    }
    return true;
}

static string sfi::logic::dotToDotDec(const string& str, int base){
    istringstream stream(str);
    string octet;
    string result{""};
    while(getline(stream,octet,'.')){
            long oct = stoul(octet, nullptr, base);
            result += to_string(oct) + ".";
    }
    return result.substr(0,result.length()-1);
}

static void sfi::logic::searchAddr(const string& line, sfi::data::expr e, vector<string>& addrs){
    smatch match;
    string addr;
    regex_search(line,match,e.str);

    for(const auto& x : match) {
        if(e.dot){
            addr = sfi::logic::dotToDotDec(x,e.base);
        } else {
            addr = sfi::logic::dotToDotDec(sfi::logic::toDot(x,e.base), e.base);
        }
        if(sfi::logic::validateAddr(addr)) {
            addrs.push_back(addr);
        }
    }
}

static int sfi::logic::elExists(const vector<sfi::data::address>& addrs, const string& adr){
    for(int i = 0; i < addrs.size(); i++){
        if(addrs[i].addr == adr)
            return i;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    sfi::data::expr dothex("0x[a-fA-F0-9]{2}[.]0x[a-fA-F0-9]{2}[.]0x[a-fA-F0-9]{2}[.]0x[a-fA-F0-9]{2}",16,true);
    sfi::data::expr dotdec("[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}",10,true);
    sfi::data::expr dotoct("[0-7]{4}[.][0-7]{4}[.][0-7]{4}[.][0-7]{4}",8,true);
    sfi::data::expr dotbin("[0-1]{8}[.][0-1]{8}[.][0-1]{8}[.][0-1]{8}",2,true);
    sfi::data::expr bin("[0-1]{32}",2,false);
    sfi::data::expr octa("[0-7]{12}",8,false);
    sfi::data::expr hexa("0x[a-fA-F0-9]{8}",16,false);
    sfi::data::expr decim("[0-9]{8,10}",10,false);
    vector<sfi::data::expr> exprs{dothex,dotdec,dotoct,dotbin,bin,octa,hexa,decim};

//    ifstream stream(argv[1]);
    ifstream stream("/home/arkezar/intruder");
    string line;
    vector<string> addrs;

    vector<sfi::data::address> counts;
    while (getline(stream, line)) {
//        if(line.length() > 0 && line.length() <= 300){
            for(const sfi::data::expr& e : exprs)
                sfi::logic::searchAddr(line,e,addrs);
//        }
    }

    for(string a : addrs){
        int el = sfi::logic::elExists(counts,a);
        if(el != -1) {
            counts[el].increaseCount();
        } else {
            counts.push_back(sfi::data::address(a,1));
        }
    }

    int maxOcc = 0;
    for (const sfi::data::address& a : counts) {
        if(a.count > maxOcc)
            maxOcc = a.count;
    }

    addrs.clear();

    for (const sfi::data::address& a : counts) {
        if(a.count == maxOcc)
            addrs.push_back(a.addr);
    }

    std::sort(addrs.begin(),addrs.end());

    for(const string& a : addrs)
        cout << a << " ";

    return 0;
}