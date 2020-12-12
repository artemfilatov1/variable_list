
#ifndef variantA_hpp
#define variantA_hpp

#include <stdio.h>
#include <iostream>

union u{
    bool b;
    char c;
    int i;
    double d;
    char* str;
};

enum t{
    Char, Int, Double, String, Bool
};

class variant{
    u value;
    t type;
public:
    variant() = delete;
    variant(bool b): type(Bool), value{.b = b}{}
    variant(char c): type(Char), value{.c = c}{}
    variant(int i): type(Int), value{.i = i}{}
    variant(double d): type(Double), value{.d = d}{}
    variant(char* str): type(String), value{.str = strdup(str)}{}
    variant(const variant& v){
        operator =(v);
    }
    ~variant(){
        if (type == String){
            free(value.str);
        }
    }
    
    t getType(){
        return type;
    };
    
    bool asBool()throw(char*){
        if (type == Bool){
            return value.b;
        } else {
            throw "incorect type";
        }
    }
    char asChar() throw(char*) {
        if (type == Char){
            return value.c;
        } else {
            throw "incorect type";
        }
    }
    int asInt()throw(char*){
        if (type == Int){
            return value.i;
        } else {
            throw "incorect type";
        }
    }
    double asDouble()throw(char*){
        if (type == Double){
            return value.d;
        } else {
            throw "incorect type";
        }
    }
    char* asString()throw(char*){
        if (type == String){
            return value.str;
        } else {
            throw "incorect type";
        }
    }
    
    operator bool() throw(char*) {
        return asBool();
    }
    operator char() throw(char*) {
        return asChar();
    }
    operator int() throw(char*) {
        return asInt();
    }
    operator double() throw(char*) {
        return asDouble();
    }
    operator char*() throw(char*) {
        return asString();
    }
    
    bool operator == (const variant& v){
        if (v.type != type) return false;
        switch(type){
            case Bool: return v.value.b == value.b;
            case Char: return v.value.c == value.c;
            case Int: return v.value.i == value.i;
            case Double: return v.value.d == value.d;
            case String: return strcmp(v.value.str, value.str) == 0;
        }
    }
    bool operator == (const bool& b){
        return operator == (variant(b));
    }
    bool operator == (const char& c){
        return operator == (variant(c));
    }
    bool operator == (const int& i){
        return operator == (variant(i));
    }
    bool operator == (const double& d){
        return operator == (variant(d));
    }
    bool operator == (const char*& str){
        return operator == (variant(str));
    }
    
    void operator = (const variant& v){
        if(type == String) free(value.str);
        type = v.type;
        switch(type){
            case Bool: value.b = v.value.b; break;
            case Char: value.c = v.value.c; break;
            case Int: value.i = v.value.i; break;
            case Double: value.d = v.value.d; break;
            case String: value.str = strdup(v.value.str); break;
        }
        
    }
    void operator = (const bool& b){
        operator = (variant(b));
    }
    void operator = (const char& c){
        operator = (variant(c));
    }
    void operator = (const int& i){
        operator = (variant(i));
    }
    void operator = (const double& d){
        operator = (variant(d));
    }
    void operator = (const char*& str){
        operator = (variant(str));
    }
};


#endif /* variantA_hpp */
