#ifndef Record_H
#define Record_H

#include <iostream>
#include <string>

class Record {
private:
    //member variables
    std::string title, author, ISBN, edition, year;
public:
    //accessor/mutator functions

    Record(){};
    Record(std::string title, std::string author, std::string ISBN, std::string year, std::string edition) :
        title(title), author(author), ISBN(ISBN), year(year), edition(edition){};
    ~Record(){
        title = "";
        author = "";
        ISBN = "";
        year = "";
        edition = "";
    }
    std::string get_title() const; // getters
    std::string get_author() const;
    std::string get_ISBN() const;
    std::string get_year() const;
    std::string get_edition() const; 

    void set_title(std::string t); // setters
    void set_author(std::string a);
    void set_ISBN(std::string i );
    void set_year(std::string y);
    void set_edition(std::string e);
};

// Stream operators
std::istream& operator>>(std::istream& is, Record& rec);
std::ostream& operator<<(std::ostream& os, Record& rec);

// Comparison operators
bool operator==(const Record& r1, const Record& r2);
#endif