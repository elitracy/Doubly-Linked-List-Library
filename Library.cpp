#include "Library.h"
#include "TemplatedDLList.h"
#include "Record.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<Record> Library::search(string title){

    int letter = (int)tolower(title.at(0)) - 97;


    DLListNode<Record> *node = book_db.at(letter).first_node();
    vector<Record> rec;

    while(node != book_db.at(letter).after_last_node()){
        if(node->obj.get_title() == title){
            rec.push_back(node->obj);
        }
        node = node->next;
    }
    return rec;
}

int Library::import_database(string filename){
    int numRecords = 0;
    Record rec;
    DLListNode<Record> *node;
    int letter = 0;
    bool inserted = false;

    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cout << filename << " not found";
        return 0;
    }

    while(ifs >> rec){

        numRecords++;

        letter = (int)(tolower(rec.get_title().at(0))) - 97; // get first letter of title

        node = book_db.at(letter).first_node(); // get record of type first letter ^^
        
        if(node != book_db.at(letter).after_last_node()){
            while(node != book_db.at(letter).after_last_node()){ // iterate through DLList of records @ letter

                if(node->obj.get_title() == rec.get_title()){
                    // numRecords--; // offset by 1 so it evens out when added later, but don't add title
                }else if(node->obj.get_title() > rec.get_title()){ // if title in DLList > rec title (b > a)
                    book_db.at(letter).insert_before(*node, rec); // we push rec title before DLList title a <=> b
                }else if(node->obj.get_title() == book_db.at(letter).after_last_node()->prev->obj.get_title()){ // if we get to the last valid node and this rec wasn't already pushed
                    book_db.at(letter).insert_last(rec); // insert at back because nothing was greater than it e.g z > anthing
                }

                node = node->next;
            }
        }else{
            book_db.at(letter).insert_first(rec);

        }
    }
    return numRecords;
}

int Library::export_database(string filename){

    ofstream ofs(filename);
    DLListNode<Record> *node;
    int numRecords = 0;

    for(int i = 0; i < book_db.size(); i++){
        node = book_db.at(i).first_node();
        while(node != book_db.at(i).after_last_node()){
            numRecords++;
            ofs << node->obj << endl;
            node = node->next;
        }

        ofs << endl;
    }

    return numRecords;
}

void Library::print_database(){
    DLListNode<Record> *node;

    for(int i = 0; i < book_db.size(); i++){

        node = book_db.at(i).first_node();
        if(node != book_db.at(i).after_last_node()){
            cout << "----------VOLUME: " << (char)(i+65) << "----------" << endl;

            while(node != book_db.at(i).after_last_node()){
                cout << node->obj << endl << endl;
                node = node->next;
            }
            cout << endl << endl;
        }
        
    }
}

bool Library::add_record(Record book){
    int letter = (int)tolower(book.get_title().at(0)) - 97;

    DLListNode<Record> *node = book_db.at(letter).first_node(); // get record of type first letter ^^
    if(node != book_db.at(letter).after_last_node()){
            while(node != book_db.at(letter).after_last_node()){ // iterate through DLList of records @ letter

            if(node->obj.get_title() == book.get_title()){
                return false; 
            }else if(node->obj.get_title() > book.get_title()){ // if title in DLList > rec title (b > a)
                book_db.at(letter).insert_before(*node, book); // we push rec title before DLList title a <=> b
                return true;
            }else if(node == book_db.at(letter).after_last_node()->prev){ // if we get to the last valid node and this rec wasn't already pushed
                book_db.at(letter).insert_last(book); // insert at back because nothing was greater than it e.g z > anthing
                return true;
            }
        }

        node = node->next;
    }else{
            book_db.at(letter).insert_first(book);
            return true;
    }
    return false;
}

void Library::remove_record(Record book){
    int letter = (int)tolower(book.get_title().at(0)) - 97;

    DLListNode<Record> *node = book_db.at(letter).first_node(); // get record of type first letter ^^

    while(node != book_db.at(letter).after_last_node()){ // iterate through DLList of records @ letter

        if(node->obj.get_title() == book.get_title()){ // if title in DLList > rec title (b > a)
            book_db.at(letter).remove_before(*node->next); // we push rec title before DLList title a <=> b
        }

        node = node->next;
    }
}

char Library::prompt_yes_no(){

    string choice;
    cout << "Yes or No [Y/N]: ";

    getline(cin, choice);
    if(choice.at(0) == 'Y' || choice.at(0) == 'y') return 'Y';
    else return 'N';
}

int Library::prompt_menu(vector<string> vect){
    for(int i = 0; i < vect.size(); i++){
        cout << i+1 << ". " <<  vect.at(i) << endl;
    }
    cout << "Please select an option[" << 1 << "..." << vect.size() << "]: ";
    string choice;
    getline(cin, choice);
    return stoi(choice)-1;
}

Record Library::prompt_record(){
    string title, author, ISBN, year, edition;
    Record rec;

    cout << "Author: ";
    getline(cin, author);
    cout << "Edition: ";
    getline(cin, edition);
    cout << "ISBN: ";
    getline(cin, ISBN);
    cout << "Title: ";
    getline(cin, title);
    cout << "Year: ";
    getline(cin, year);
    
    rec.set_title(title);
    rec.set_author(author);
    rec.set_ISBN(ISBN);
    rec.set_year(year);
    rec.set_edition(edition);


    return rec;
}

string Library::prompt_title(){
    string title;
    cout << "Title: ";
    getline(cin,title);
    return title;
}

string Library::prompt_string(string prompt){
    string input;
    cout << prompt << ": ";
    getline(cin, input);
    return input;
}

