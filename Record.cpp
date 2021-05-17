//implementation of record class

#include "Record.h"
#include <iostream>
#include <string>
using namespace std;


string Record::get_title() const { return this->title; }
string Record::get_author() const { return this->author; }
string Record::get_ISBN() const { return this->ISBN; }
string Record::get_year() const { return this->year; }
string Record::get_edition() const { return this->edition; }

void Record::set_title(string t){ this->title = t; }
void Record::set_author(string a){ this->author = a; }
void Record::set_ISBN(string i){ this->ISBN = i; }
void Record::set_year(string y){ this->year = y; }
void Record::set_edition(string e){ this->edition = e; }

istream& operator>>(istream& is, Record& rec){
    string title, author, ISBN, edition, year,line;

    
    while(getline(is,line)){
        if(!line.empty()){
            title = line;
            getline(is, author);
            getline(is, ISBN);
            getline(is, year);
            getline(is, edition);

            rec.set_title(title);
            rec.set_author(author);
            rec.set_ISBN(ISBN);
            rec.set_edition(edition);
            rec.set_year(year); 
            return is;

        }
    }
    return is;

}
ostream& operator<<(ostream& os, Record& rec){

    os << rec.get_title() << endl;
    os << rec.get_author() << endl;
    os << rec.get_ISBN() << endl;
    os << rec.get_year() << endl;
    os << rec.get_edition();
    return os;
}

bool operator==(const Record&r1, const Record&r2){

    return (r1.get_title() == r2.get_title()) && (r1.get_author() == r2.get_author()) && (r1.get_ISBN() == r2.get_ISBN());
}

