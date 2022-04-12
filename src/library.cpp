#include<iostream>
#include<fstream>
#include<algorithm>
#include<string>
#include<list>

/***********************/
/* Forward declaration */
/***********************/
class Patron;

// ----------------------------------------------------------------
// --- Book class                                               ---
// ----------------------------------------------------------------
class Book{
private:
    std::string title;
    Patron *patron;
    std::ostream& print_book(std::ostream&) const;

    // ---
    friend std::ostream& operator<<(std::ostream& out, const Book& book){
        return book.print_book(out);
    }

    // ---
    friend class CheckedOutBook;
    friend Patron;
    friend void include_book();
    friend void checkout_book();
    friend void return_book();

public:
    Book(){
        patron = nullptr;
    }

    // ---
    bool operator==(const Book& book) const {
        return title == book.title;
    }
};

// ----------------------------------------------------------------
// --- Author class                                             ---
// ----------------------------------------------------------------
class Author{
private:
    std::string name;
    std::list<Book> books;

    // ---
    std::ostream& print_author(std::ostream& ) const;

    // ---
    friend std::ostream& operator<<(std::ostream& out, const Author& author){
        return author.print_author(out);
    }

    // ---
    friend void include_book();
    friend void checkout_book();
    friend void return_book();
    friend class CheckedOutBook;
    friend Patron;

public:
    Author(){}

    bool operator==(const Author& author) const{
        return name == author.name;
    }
};

// ------------------------------------------------------------------
// --- class CheckedOutBook                                       ---
// ------------------------------------------------------------------
class CheckedOutBook {
private:
    std::list<Author>::iterator author;
    std::list<Book>::iterator book;
    friend void checkout_book();
    friend void return_book();
    friend Patron;
    
public:
    CheckedOutBook(
        std::list<Author>::iterator author=nullptr,
        std::list<Book>::iterator book=nullptr
    ){
        this->author = author;
        this->book = book;
    }

    // ---
    bool operator==(const CheckedOutBook& book) const{
        return author->name == book.author->name &&
            book->title == book.book->title;
    }
};

// --------------------------------------------------------------
// ----- Patron                                             -----
// --------------------------------------------------------------
class Patron {
private:
    std::string name;
    std::list<CheckedOutBook> books;

    std::ostream& print_patron(std::ostream&) const;

    friend std::ostream& operator<<(std::ostream& out, const Patron& patron){
        return patron.print_patron(out);
    }

    friend void checkout_book();
    friend void return_book();
    friend Book;

public:
    Patron(){}
    // ---
    bool operator==(const Patron& patron) const {
        return name == patron.name;
    }
};

/*******************************************************************/
/** Global containers                                              */
/*******************************************************************/
std::list<Author> catalog['Z'+1];
std::list<Patron> people['Z'+1];

/***************************/
/** Author::print_author() */
/***************************/
std::ostream& Author::print_author(std::ostream& out) const{
    out << name << std::endl;
    std::list<Book>::const_iterator ref = books.begin();
    for(; ref != books.end(); ref++){
        out << +ref;
    }

    return out;
}

/***************************/
/** Book::print_book()     */
/***************************/
std::ostream& Book::print_book(std::ostream& out) const {
    out << "    * " << title;
    if(patron != nullptr){
        out << " - checked out to " << patron->name;
    }
    out << std::endl;
    return out;
}

/******************************/
/** Patron::print_patron()    */
/******************************/
std::ostream& Patron::print_patron(std::ostream& out) const {
    out << name;
    if(!books.empty()){
        out << " has the following books:\n";
        std::list<CheckedOutBook>::const_iterator ref = books.begin();
        for(; ref != books.end(); ref++){
            out << "    * " << ref->author->name << ", "
                << ref->book->title << std::endl;
        }
    }else{
        out << " has no books" << std::endl;
    }

    return out;
}

// ----- 
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::list<T>& lst){
    for(std::list<T>::const_iterator ref=lst.begin(); ref != lst.end(); ref++){
        out << *ref;
    }
    return out;
}

// -----
std::string get_string(std::string message){
    std::string out;
    std::string line(message.length(), '-');
    const char *cyan = "\x1b[1;36m";
    const char *yellow = "\x1b[1;33";
    const char *green = "\x1b[1;32m";
    const char *reset = "\x1b[m";
    std::cout << std::endl
        << yellow << line << reset << std::endl 
        << cyan << message << cyan << std::endl
        << yellow << line << reset << std::endl << std::endl
        << green << ">> " << reset;
    std::cout.flush();
    std::getline(std::cin, out);
    return out;
}

// --------------------
// ----- status() -----
// --------------------
void status(){
    register int i;
    std::cout << "Library has the following books:" << std::endl << std::endl;
    for(i='A'; i <= 'Z'; i++){
        if(!catalog[i].empty()){
            std::cout << catalog[i];
        }
    }
    std::cout << std::endl;
    std::cout << "The following people are using the library"
        << std::endl << std::endl;
    for(i='A'; i <= 'Z'; i++){
        if(!people[i].empty()){
            std::cout << people[i];
        }
    }
    std::cout << std::endl;
}

// --------------------------
// ----- include_book() -----
// --------------------------
void include_book(){
    Author author;
    Book book;
    author.name = get_string("Enter author's name: ");
    book.title = get_string("Enter the title of the book: ");
    std::list<Author>::iterator _author = std::find(
        catalog[author.name[0]].begin(),
        catalog[author.name[0]].end(), author
    );

    if(_author == catalog[author.name[0]].end()){
        author.books.push_front(book);
        catalog[author.name[0]].push_front(author);
    }else{
        _author->books.push_front(book);
    }
}

// ---------------------------
// ----- checkout_book() -----
// ---------------------------
void checkout_book(){
    Patron patron;
    Author author;
    Book book;
    std::list<Author>::iterator iauthor;
    std::list<Book>::iterator ibook;
    patron.name = get_string("Enter patron's name: ");
    while(true){
        author.name = get_string("Enter author's name: ");
        iauthor = std::find(
            catalog[author.name[0]].begin(),
            catalog[author.name[0]].end(),
            author
        );
        if(iauthor == catalog[author.name[0]].end()){
            std::cout << "Misspelled author's name" << std::endl;
        }else{ break; }
    }

    while(true){
        book.title = get_string("Enter the title of the book:");
        ibook = std::find(
            iauthor->books.begin(),
            iauthor->books.end(), end
        );
        if(ibook == iauthor->books.end()){
            std::cout << "Misspelled title\n" << std::endl;
        }else{ break; }
    }
    std::list<Patron>::iterator ipatron;
    ipatron = std::find(
        people[patron.name[0]].begin(),
        people[patron.name[0]].end(),
        patron
    );

    CheckedOutBook checkedOutBook(iauthor, ibook);

    if(ipatron == people[patron.name[0]].end()){ // a new patron
        patron.books.push_front(checkedOutBook);
        people[patron.name[0]].push_front(patron);
        ibook->patron = &*people[patron.name[0]].begin();
    }else{
        ipatron->books.push_front(checkedOutBook);
        ibook->patron = &*ipatron;
    }
}

// -------------------------
// ----- return_book() -----
// -------------------------
void return_book(){
    Patron patron;
    Book book;
    Author author;
    std::list<Patron>::iterator ipatron;
    std::list<Book>::iterator ibook;
    std::list<Author>::iterator iauthor;
    while(true){
        patron.name = get_string("Enter patron's name:");
        ipatron = std::find(
            people[patron.name[0]].begin(),
            people[patron.name[0]].end(),
            patron
        );
        if(ipatron == people[patron.name[0]].end()){
            std::cout << "Patron's name misselled" << std::endl;
        }else{ break; }
    }
    while(true){
        author.name = get_string("Enter author's name:");
        iauthor = std::find(
            catalog[author.name[0]].begin(),
            catalog[author.name[0]].end(),
            author
        );
        if(iauthor == catalog[author.name[0]].end()){
            std::cout << "Misspelled author's name" << std::endl;
        }else{ break; }
    }
    while(true){
        book.title = get_string("Enter the title of the book:");
        ibook = std::find(
            iauthor->books.begin(),
            iauthor->books.end(), book
        );
        if(ibook == iauthor->books.end()){
            std::cout << "Misspelled title" << std::endl;
        }else{ break; }
    }

    CheckedOutBook checkedOutBook(iauthor, ibook);
    ibook->patron = nullptr;
    ipatron->books.remove(checkedOutBook);
}

// ------------------
// ----- menu() -----
// ------------------
int menu(){
    int option;
    std::cout << std::endl
        << "Enter one of the following options" << std::endl
        << "1. Include a book in the catalog "  << std::endl
        << "2. Check out a book " << std::endl
        << "3. Return a book " << std::endl
        << "4. Status " << std::endl
        << "5. Exit " << std::endl
        << std::endl << ">> ";
    std::cout.flush();
    std::cin >> option;
    std::cin.get();     // discard '\n'

    return option;
}

// ----------------------------
// -----    MAIN DRIVER   -----
// ----------------------------
int main(int argc, char **argv){
    while(true){
        switch(menu()){
        case 1:
            include_book();
            break;
        case 2:
            checkout_book();
            break;
        case 3:
            return_book();
            break;
        case 4:
            status();
            break;
        case 5:
            return 0;
        default:
            std::cout << "Wrong option, try again\n";
        }
    }

    return EXIT_SUCCESS;
}
