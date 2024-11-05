#include <iostream>
using namespace std;
#include <cmath>
#include <sstream>
#include <bitset>
class Alu {
    int num1;
    float num2, sum;
    string b, c;

public:
    string integerToBinary(int integerPart) {
        string result = "";
        while (integerPart > 0) {
            result = (integerPart % 2 == 0 ? "0" : "1") + result;
            integerPart /= 2;
        }
        return result.empty() ? "0" : result;
    }

// Helper function to convert fractional part to binary
    string fractionalToBinary(float fractionalPart, int precision = 10) {
        string result = "";
        while (precision-- > 0 && fractionalPart > 0) {
            fractionalPart *= 2;
            if (fractionalPart >= 1) {
                result += "1";
                fractionalPart -= 1;
            } else {
                result += "0";
            }
        }
        return result;
    }

    string floatToBinary(float number) {
        int integerPart = static_cast<int>(number);          // Get the integer part
        float fractionalPart = number - integerPart;         // Get the fractional part

        string binaryInteger = integerToBinary(integerPart); // Convert integer part to binary
        string binaryFraction = fractionalToBinary(fractionalPart); // Convert fractional part to binary

        return binaryInteger + "." + binaryFraction;
    }
    string decimalToHexadecimal(int decimalNumber) {

        if (decimalNumber == 0) {
            return "0";
        }

        stringstream ss;

        if (decimalNumber < 0) {
            ss << "-";
            decimalNumber = -decimalNumber;
        }


        ss << hex << uppercase << decimalNumber;


        return ss.str();
    }
    int hexToDecimal(const string &hex) {
        int decimal = 0;
        int base = 1;
        for (int i = hex.size() - 1; i >= 0; i--) {
            char c = toupper(hex[i]);
            if (c >= '0' && c <= '9') {
                decimal += (c - '0') * base;
            } else if (c >= 'A' && c <= 'F') {
                decimal += (c - 'A' + 10) * base;
            }

            base *= 16;
        }

        return decimal;
    }

    int hex_dec(char b) {
        if (b >= '0' && b <= '9') {
            return b - '0';
        } else if (b >= 'A' && b <= 'F') {
            return b - 'A' + 10;
        } else if (b >= 'a' && b <= 'f') {
            return b - 'a' + 10;
        }
        return 0;
    }


    string decimalToBinary(int decimal) {
        if (decimal == 0) return "0";

        string binary;
        while (decimal > 0) {
            binary = (decimal % 2 == 0 ? "0" : "1") + binary;
            decimal /= 2;
        }
        return binary;
    }


    float inst6(string b) {
        int num1 = hexToDecimal(b);
        if (num1 <= 15) {
            string tdel= decimalToBinary(num1);
            while(tdel.length()<4){
                tdel="0"+tdel;
            }
            string binary = "0.0000" + tdel;
            float sum = 0.0;
            int count = -5;


            for (int i = 6; i < binary.length(); i++) {
                if (binary[i] == '1') {
                    sum += pow(2, count);
                }
                count--;
            }
            return sum;
        }
        else {
            char s1 = b[0];
            char s2 = b[1];
            int numm = hex_dec(s1);
            int lamine= hex_dec(s2);
            if (numm <= 7) {
                int lo = numm - 4;
                if (lo <= 0) {
                    lo = -lo;
                    string space = "0.";
                    for (int i = 0; i < lo; i++) {
                        space += "0";
                    }
                    string tdel=decimalToBinary(hex_dec(s2));
                    while(tdel.length()<4){
                        tdel="0"+tdel;
                    }
                    space += tdel;
                    float add = 0;
                    int count = 0;
                    for (int i = 0; i < space.length(); i++) {
                        if (space[i] == '1') {
                            add += pow(2, count);
                            count--;
                        } else if (space[i] == '.') {
                            continue;
                        } else {
                            count--;
                        }
                    }
                    return add;

                } else if (lo == 1) {
                    string tdel=decimalToBinary(lamine);
                    while (tdel.length()<4){
                        tdel="0"+tdel;
                    }
                    string zo = "0." + tdel;
                    int count = 1;
                    float add = 0;
                    for (int i = 0; i < zo.length(); i++) {
                        if (zo[i] == '1') {
                            add += pow(2, count);
                            count--;
                        } else if (zo[i] == '.') {
                            continue;
                        } else {
                            count--;
                        }
                    }
                    return add;

                } else if (lo == 2) {
                    string tdel=decimalToBinary(lamine);
                    while (tdel.length()<4){
                        tdel="0"+tdel;
                    }
                    string zo = "0." + tdel;
                    int count = 2;
                    float add = 0;
                    for (int i = 0; i < zo.length(); i++) {
                        if (zo[i] == '1') {
                            add += pow(2, count);
                            count--;
                        } else if (zo[i] == '.') {
                            continue;
                        } else {
                            count--;
                        }
                    }
                    return add;

                } else {
                    string tdel=decimalToBinary(lamine);
                    while (tdel.length()<4){
                        tdel="0"+tdel;
                    }
                    string zo = "0." + tdel;
                    int count = 3;
                    float add = 0;
                    for (int i = 0; i < zo.length(); i++) {
                        if (zo[i] == '1') {
                            add += pow(2, count);
                            count--;
                        } else if (zo[i] == '.') {
                            continue;
                        } else {
                            count--;
                        }
                    }
                    return add;

                }

            }
            else {
                string corr = decimalToBinary(numm);
                string ri;
                for (int i = 1; i < corr.length(); i++) {
                    ri += corr[i];
                }
                int ll = numm - 8;
                int lo = ll - 4;
                if (lo <= 0) {
                    lo = -lo;
                    string space = "0.";
                    for (int i = 0; i < lo; i++) {
                        space += "0";
                    }
                    string tdel=decimalToBinary(hex_dec(s2));
                    while(tdel.length()<4){
                        tdel="0"+tdel;
                    }
                    space += tdel;
                    float add = 0;
                    int count = 0;
                    for (int i = 0; i < space.length(); i++) {
                        if (space[i] == '1') {
                            add += pow(2, count);
                            count--;
                        } else if (space[i] == '.') {
                            continue;
                        } else {
                            count--;
                        }
                    }
                    return -add;

                } else if (lo == 1) {
                    string tdel=decimalToBinary(lamine);
                    while (tdel.length()<4){
                        tdel="0"+tdel;
                    }
                    string zo = "0." + tdel;
                    int count = 1;
                    float add = 0;
                    for (int i = 0; i < zo.length(); i++) {
                        if (zo[i] == '1') {
                            add += pow(2, count);
                            count--;
                        } else if (zo[i] == '.') {
                            continue;
                        } else {
                            count--;
                        }
                    }
                    return -add;

                } else if (lo == 2) {
                    string tdel=decimalToBinary(lamine);
                    while (tdel.length()<4){
                        tdel="0"+tdel;
                    }
                    string zo = "0." + tdel;
                    int count = 2;
                    float add = 0;
                    for (int i = 0; i < zo.length(); i++) {
                        if (zo[i] == '1') {
                            add += pow(2, count);
                            count--;
                        } else if (zo[i] == '.') {
                            continue;
                        } else {
                            count--;
                        }
                    }
                    return -add;


                }
                else {
                    string tdel=decimalToBinary(lamine);
                    while (tdel.length()<4){
                        tdel="0"+tdel;
                    }
                    string zo = "0." + tdel;
                    int count = 3;
                    float add = 0;
                    for (int i = 0; i < zo.length(); i++) {
                        if (zo[i] == '1') {
                            add += pow(2, count);
                            count--;
                        } else if (zo[i] == '.') {
                            continue;
                        } else {
                            count--;
                        }
                    }
                    return -add;

                }
            }
        }
    }
    int inst5(string b){
        int mo= hexToDecimal(b);
        string binary= decimalToBinary(mo);
        if(mo<=15){
            return mo;
        }
        else{
            char s1=b[0];
            char s2=b[1];
            int g= hex_dec(s1);
            if(g<=7){
                int sum=0;
                int count=binary.length()-1;
                for(int i=0;i<binary.length();i++){
                    if(binary[i]=='1'){
                        sum+= pow(2,count);
                    }
                    count--;
                }
                return sum;
            }
            else{
                int sum=0;
                int count=binary.length()-1;
                for(int i=0;i<binary.length();i++){
                    if(binary[i]=='0'){
                        binary[i]='1';
                    }
                    else{
                        binary[i]=1;
                    }

                }
                for(int i=0;i<binary.length();i++){
                    if(binary[i]=='1'){
                        sum+= pow(2,count);
                    }
                    count--;
                    }
                return -(sum+1);
                }



            }

        }
    string final5(string a,string b){
        int f= inst5(a);
        int g= inst5(b);
        int sum=f+g;
        if(sum>0){
            return decimalToHexadecimal(sum);
        }
        else{
            sum=-sum;
            sum--;
            string ddd= decimalToBinary(sum);
            int ff=8-ddd.length();
            for(int i=0;i<ff;i++){
                ddd="0"+ddd;
            }
            for(int i=0;i<8;i++){
                if(ddd[i]=='1'){
                    ddd[i]='0';
                }
                else{
                    ddd[i]='1';
                }
            }

            int count=7;
            int add=0;
            for(int i=0;i<ddd.length();i++){
                if(ddd[i]=='1'){
                    add+=pow(2,count);
                }
                count--;

            }

            return decimalToHexadecimal(add);

        }
    }
    string final6(string a,string b){
        float rakm= inst6(a)+ inst6(b);
        cout << rakm<< endl;
        int mkan=0;
        if(rakm>=1){
            string oj = floatToBinary(rakm);
            for(int i=0;i<oj.length();i++){
                if(oj[i]=='.'){
                    mkan=i;
                }
            }
            mkan+=4;
            string aa= decimalToHexadecimal(mkan);
            int brk=0;
            int add=0;
            int powe=3;
            for(int i=0;i<oj.length();i++){
                if(brk==4){
                    break;
                }
                else if(oj[i]=='.'){
                    continue;
                }
                else{
                    if(oj[i]=='1'){
                        add+=pow(2,powe);
                    }
                    brk++;
                    powe--;

                }
            }
            aa+= decimalToHexadecimal(add);
            return aa;

        }
        else if(rakm<=-1){
            rakm=-rakm;
            string oj = floatToBinary(rakm);
            for(int i=0;i<oj.length();i++){
                if(oj[i]=='.'){
                    mkan=i;
                }
            }
            mkan+=4;
            string corr= "1"+decimalToBinary(mkan);
            int as=0;
            int ps=3;
            for(int i=0;i<4;i++){
                if(corr[i]=='1'){
                    as+=pow(2,ps);
                }
                ps--;
            }

            string aa= decimalToHexadecimal(as);
            int brk=0;
            int add=0;
            int powe=3;
            for(int i=0;i<oj.length();i++){
                if(brk==4){
                    break;
                }
                else if(oj[i]=='.'){
                    continue;
                }
                else{
                    if(oj[i]=='1'){
                        add+=pow(2,powe);
                    }
                    brk++;
                    powe--;

                }
            }
            aa+= decimalToHexadecimal(add);
            return aa;

        }
        else if ((rakm>0)&&(rakm<1)){
            string oj = floatToBinary(rakm);
            int mkan=0;
            for(int i=0;i<oj.length();i++){
                if(oj[i]=='1'){
                    mkan=i;
                    break;
                }
            }
            int zoo=mkan-2;
            zoo=-zoo;
            zoo+=4;
            if(zoo<0){
                zoo=0;
            }
            string aa= decimalToHexadecimal(zoo);
            int ad=0;
            int pr=3;
            for(int i=mkan;i<(mkan+4);i++){
                if(oj[i]=='1'){
                    ad+=pow(2,pr);
                }
                pr--;
            }
            aa+= decimalToHexadecimal(ad);
            return aa;
        }
        else{
            rakm=-rakm;
            string oj = floatToBinary(rakm);
            int mkan=0;
            for(int i=0;i<oj.length();i++){
                if(oj[i]=='1'){
                    mkan=i;
                    break;
                }
            }
            int zoo=mkan-2;
            zoo=-zoo;
            zoo+=4;
            if(zoo<0){
                zoo=0;
            }
            zoo+=8;
            string aa= decimalToHexadecimal(zoo);
            int ad=0;
            int pr=3;
            for(int i=mkan;i<(mkan+4);i++){
                if(oj[i]=='1'){
                    ad+=pow(2,pr);
                }
                pr--;
            }
            aa+= decimalToHexadecimal(ad);
            return aa;
        }


    }



};


int main() {
    Alu omar;
    char a = '8';
    int b = 5;
    string omarr="0.6";
    cout << omar.final6("25","04");



    return 0;
}