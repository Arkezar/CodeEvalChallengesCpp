//
// Created by arkezar on 15.07.15.
//

// IP address pattern searching without regex
// Extremely inefficient

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <sstream>
#include <algorithm>

using namespace std;
namespace sfi{
    namespace data {
        struct address;
    }
    namespace logic {
        static string toDot(string, int);
        static bool validateAddr(const string&);
        static string dotToDotDec(const string&, int);
        static void searchAddr(const string&, vector<string>&);
        static void searchAddrSubmethod(const string&, vector<string>&);
        static int elExists(const vector<sfi::data::address>&, const string&);
        static int getBase(const string&);
        static string octetValidation(const string&);
    }

}

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
        unsigned long tmp;
        try {
             tmp = stoul(str);
        } catch (exception e){
            return "0";
        }
        str = dotToDotDec(toDot(bitset<32>(tmp).to_string(),2),2);
    } else {
        for (int i = str.length() / 4; i < str.length(); i += str.length() / 4 + 1) {
            str.insert(i, ".");
        }
    }
    return str;
}

static bool sfi::logic::validateAddr(const string& addr){
    if(addr.length() > 15)
        return false;
    vector<int>octets;
    istringstream ss(addr);
    string oct;
    while(getline(ss,oct,'.')){
        try {
            octets.push_back(stoul(oct));
        } catch (exception e) {
            return false;
        }
    }

    if(octets.size() < 4)
        return false;

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
    long oct;
    while(getline(stream,octet,'.')){
            try {
                oct = stoul(octet, nullptr, base);
            } catch (exception e){
                return "0";
            }
            result += to_string(oct) + ".";
    }
    return result.substr(0,result.length()-1);
}

static void sfi::logic::searchAddrSubmethod(const string& substr, vector<string>& addrs){
    bool valid = true;
    string addr = substr;
    if(addr[0] == '.'){
        addr = addr.substr(1,addr.length()-1);
    }
    if(addr[addr.length()-1] == '.'){
        addr = addr.substr(0,addr.length()-2);
    }
    int badDot = addr.find("..");
    if(badDot != -1){
        valid = false;
    }
    if(valid){
        addrs.push_back(addr);
    }
}

static void sfi::logic::searchAddr(const string& line, vector<string>& addrs){
    bool nodot = true;
    string addr{""};

    int hexStartPos = line.find("0x");

    if(hexStartPos != -1){
        for(int i = hexStartPos; i < line.length(); i++){
            if( (line[i] >= 'a' && line[i] <= 'f') ||
                    (line[i] >= 'A' && line[i] <= 'F') ||
                    (line[i] >= '0' && line[i] <= '9') ||
                    line[i] == 'x'){
                addr += line[i];
            } else if(line[i] == '.'){
                nodot = false;
                addr += line[i];
            }
        }
        if(!nodot) {
            int j = addr.length() - 1;
            while (addr[j] != '.') {
                j--;
            }
            addr = addr.substr(0, j + 5);
            addrs.push_back(addr);
        } else {
            addr = addr.substr(0, 10);

            addrs.push_back(addr);
        }
    } else {
        for(int i = 0; i < line.length(); i++) {
            if(line[i] == '.' || (line[i] >= '0' && line[i] <= '9')){
                addr += line[i];
            } else if(addr.length()>3){
                searchAddrSubmethod(addr,addrs);
                addr = "";
            } else {
                addr = "";
            }
        }
    }
}

static int sfi::logic::getBase(const string& addr) {
    if (addr.find('x') != -1) {
        return 16;
    } else {

        vector<string> octets;
        istringstream ss(addr);
        string octet;
        while (getline(ss, octet, '.')) {
            octets.push_back(octet);
        }
        if (octets.size() > 1) {
//            for (const auto &o : octets) {
                if (octets[0].length() == 8)
                    return 2;
                else if (octets[0].length() == 4)
                    return 8;
                else
                    return 10;

//            }
        } else {
            int max =0 ;
            int digit;
            string tmp = octets[0];
            for (const auto& a : tmp) {
                digit = a - '0';
                if (digit > max) {
                    max = digit;
                }
            }
            if (max < 2 && octets[0].size() > 20){
                return 2;
            } else if (max < 8 && octets[0].size() == 12) {
                return 8;
            } else {
                return 10;
            }
        }
    }
}

static string sfi::logic::octetValidation(const string& addr){
    vector<string>octets;
    istringstream ss(addr);
    string oct;
    while(getline(ss,oct,'.')){
        octets.push_back(oct);
    }
    if(octets.size()>4){
        return octets[0] + "." + octets[1] + "." + octets[2] + "." + octets[3];
    } else if (octets.size() == 1 || octets.size() == 4){
        return addr;
    } else {
        return "0";
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
    ifstream stream(argv[1]);
//    ifstream stream("/home/arkezar/intruder");
    string line;
    vector<string> addrs;
    vector<string> addrsFin;
    vector<sfi::data::address> counts;
//    int lineNo = 0;
    while (getline(stream, line)) {
//        lineNo+=1;
//        if(lineNo<=1200) {
            if (line.length() >= 100 && line.length() <= 300)
                sfi::logic::searchAddr(line, addrs);
//        } else {
//            return 0;
//        }
    }

    for (auto a : addrs) {
        a = sfi::logic::octetValidation(a);
        if(a.find('.')!=-1){
            a = sfi::logic::dotToDotDec(a,sfi::logic::getBase(a));
        } else {
            int base = sfi::logic::getBase(a);
            if(base == 2 && a.length() < 32) {
                a.insert(0, 32 - a.length(), '0');
            }
            a = sfi::logic::toDot(a,base);
            a = sfi::logic::dotToDotDec(a,base);
        }

        if(sfi::logic::validateAddr(a))
            addrsFin.push_back(a);
    }

    for(const auto& a : addrsFin){
        if(sfi::logic::validateAddr(a)) {
            int el = sfi::logic::elExists(counts, a);
            if (el != -1) {
                counts[el].increaseCount();
            } else {
                counts.push_back(sfi::data::address(a, 1));
            }
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
        if(sfi::logic::validateAddr(a))
            cout << a << " ";

    return 0;
}