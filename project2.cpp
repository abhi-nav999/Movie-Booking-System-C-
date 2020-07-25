#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<list>
#include<windows.h>
using namespace std;

int main();
unsigned long hash1(const std::string& str)
{
    unsigned long hash = 5381;
    for (size_t i = 0; i < str.size(); ++i)
        hash = 33 * hash + (unsigned char)str[i];
    return hash;
}

class Hash
{
    int BUCKET;    // No. of buckets

    // Pointer to an array containing buckets
    list<string> *table;
public:
    Hash(int V);  // Constructor

    // inserts a key into hash table
    void insertItem(long long int key, string password);

    // deletes a key from hash table
    void deleteItem(int key, string password);

    // hash function to map values to key
    int hashFunction(long long int x) {
        return (x % BUCKET);
    }

    void displayHash();
    int findHash(int hashedValue, string password);
};

Hash::Hash(int b)
{
    this->BUCKET = b;
    table = new list<string>[BUCKET];
}

void Hash::insertItem(long long int key, string password)
{
    int index = hashFunction(key);
    table[index].push_back(password);
}

void Hash::deleteItem(int key, string password)
{
  // get the hash index of key
  int index = hashFunction(key);

  // find the key in (inex)th list
  list <string> :: iterator i;
  for (i = table[index].begin();
           i != table[index].end(); i++) {
    if (*i == password)
      break;
  }

  // if key is found in hash table, remove it
  if (i != table[index].end())
    table[index].erase(i);
}

// function to display hash table
void Hash::displayHash() {
  for (int i = 0; i < BUCKET; i++) {
    cout << i;
    for (auto x : table[i])
      cout << " --> " << x;
    cout << endl;
  }
}
int Hash::findHash(int hashedValue, string password) {
  for (int i = 0; i < BUCKET; i++) {
    //cout << i;
    if(i == hashedValue && table[i].empty()){
            return 0;
    }
    if(i == hashedValue &&  !table[i].empty()){
            for (auto x : table[i])
            if(x == password){
                return 1;
            }
      //cout << " --> " << x;
    }
    //cout << endl;
  }
}
struct node{
    string city, theater_name, movie;
    int hour,minute,theaterId;
    float basePrice;
};
struct SeatNode{
    string theater_name, movie;
    int theaterId,t1,t2,silver, gold, platinum, diamond,basePrice;
};
class ticket{
public:
    void BookTicket(){
    cout << "1.LOGIN" << "\n";
    cout << "2.SIGNUP" << "\n";
    int input;
    string username;
    string password;
    cin >> input;
    if(input == 1){
        Hash h1(10000);
        ifstream fin("passwords.txt");
        string result;
        while(fin >> result){
            long long int key = hash1(result);
            h1.insertItem(key, result);
        }
        label2:
        cout << "       LOGIN\n";
        cout << "------------------\n";
        cout << "USERNAME: " ;
        cin >> username;
        cout << "\n\nPASSWORD: ";
        cin >> password;
        string res = username + password;
        unsigned long hashed = hash1(res);
        int key = hashed %10000;
        //h1.displayHash();
        if(h1.findHash(key, res)){
            cout << "LOGIN SUCCESSFUL" << "\n" << "PRESS ANY KEY TO CONTINUE" << "\n";
            getch();
        }
        else{
            cout << "INCORRECT USERNAME OR PASSWORD" << "\n" << "PRESS ANY KEY TO RE-ENTER LOGIN CREDINTIALS" << "\n";
            getch();
            system("cls");
            goto label2;
        }
        system("cls");
        cout << "ENTER YOUR CITY" << "\n";
        string city;
        cin >> city;
        /*cout << "SELECT THEATER" << "\n";
        string location;
        cin >> location;*/
        cout << "MOVIES CURRENTLY SCREENING IN " << city <<  "\n";
        ifstream fptr("movies.txt");
        system("cls");
        list<node> l1;
        struct node temp;
        cout << "  CITY  " <<  "  THEATER NAME " <<"  MOVIE  "  << "  TIME  "  << " PRICE " << " THEATER ID " << "\n";
        while(fptr >> temp.city >> temp.theater_name >> temp.movie >> temp.hour >> temp.minute >> temp.basePrice >> temp.theaterId){
            if(temp.city == city ){
                if(temp.hour <= 12)
                cout << temp.city << " " << temp.theater_name << " " << temp.movie << " " << temp.hour <<":" << temp.minute << " AM " << temp.basePrice << " " << temp.theaterId << "\n";
                else{
                cout << temp.city << " " << temp.theater_name << " " << temp.movie << " " << temp.hour <<":" << temp.minute << " PM " << temp.basePrice << " " << temp.theaterId << "\n";
                }
                l1.push_back(temp);
            }
        }
        fptr.close();
        cout << "SELECT THEATER \n";
        string theater, movie;
        int t1,t2,theaterid;
        cin >> theater;
        cout << "ENTER THEATER-ID\n";
        cin >> theaterid;
        cout << "SELECT MOVIE YOU WANT TO WATCH\n";
        cin >> movie;
        cout << "ENTER TIME SLOT\n";
        cin >> t1 >> t2;
        ifstream fptr2("seats.txt");
        list<SeatNode> l2;
        system("cls");
        cout << "__________________AVAILABLE SEATS_____________________ \n";
        cout << "THEATER    THEATER ID   MOVIE   TIME   SILVER   GOLD   PLATINUM   DIAMOND   PRICE\n";
        struct SeatNode temp2;
        while(fptr2 >> temp2.theater_name >> temp2.theaterId >> temp2.movie >> temp2.t1 >> temp2.t2 >> temp2.silver >> temp2.gold >> temp2.platinum >> temp2.diamond >> temp2.basePrice){
            if(temp2.theater_name == theater && temp2.movie == movie && temp2.t1 == t1 && temp2.t2 == t2)
                cout << temp2.theater_name << "  " << temp2.theaterId << "  " << temp2.movie << "  " <<  temp2.t1 <<"  " << temp2.t2 << "  " << temp2.silver << "  " << temp2.gold << "  " << temp2.platinum << "  " << temp2.diamond << "  " << temp2.basePrice <<  "\n";
            l2.push_back(temp2);
        }
         cout << "SELECT TYPE OF SEAT\n";
        int seatType;
        int nofseats;
        cin >> seatType;
        cout << "ENTER NO OF SEATS\n";
        cin >>  nofseats;
        float subtotal;
        list<SeatNode> :: iterator it;
        for(it = l2.begin(); it != l2.end(); it++){
            if(it->theater_name == theater && it->movie == movie && it->theaterId == theaterid && it->t1 == t1 && it->t2 == t2){
                if(seatType == 1 && it->silver > nofseats){
                    cout << it->basePrice;
                    it->silver = it->silver - nofseats;
                    subtotal = nofseats * it->basePrice;
                }
                if(seatType == 2 && it->gold > nofseats){
                    it->gold = it->gold - nofseats;
                    subtotal = nofseats* (it->basePrice + (it->basePrice * 0.15));
                }
                if(seatType == 3 && it->platinum > nofseats){
                    it->platinum = it->platinum - nofseats;
                    subtotal = nofseats * (it->basePrice + (it->basePrice * 0.3));
                }
                if(seatType == 4 && it->diamond > nofseats){
                    it->diamond = it->diamond - nofseats;
                    subtotal = nofseats * (it->basePrice + (it->basePrice * 0.5));
                }
            }
        }
        fptr2.close();
        system("cls");
        cout << "YOUR SUBTOTAL : " << subtotal << " \n" << "BOOKING ID:  " << rand() << "\n";
        cout << "PRESS ANY KEY TO CONFIRM YOUR BOOKING\n";
        getch();
        ofstream fptr4("seats.txt");
        for(it = l2.begin(); it != l2.end(); it++){
            fptr4 << it->theater_name << " " << it->theaterId << " " << it->movie << " " << it->t1 << " " << it->t2 << " " << it->silver << " " << it->gold << " " << it->platinum << " "  << it->diamond << " " << it->basePrice << "\n";
        }
        fptr4.close();
        //ofstream fptr3;


    }
    else{
            label1:
            system("cls");
            cout << "\nUSERNAME: ";
            cin >> username;
            cout << "\n\nPASSWORD: ";
            cin >> password;
            string confirmPassword;
            cout << "\n\nCONFIRM PASSWORD: ";
            cin >> confirmPassword;
            if(password != confirmPassword){
                cout << "PASSWORD DOES NOT MATCHED \n PRESS ANY KEY TO CONTINUE";
                getch();
                goto label1;
            }
            string res = username + password;
            unsigned long hashed = hash1(res);
            //cout << hashed << "\n";
            ofstream fptr;
            fptr.open("passwords.txt", ios:: app);
            fptr << res << " " << "\n";
            fptr.close();
    }
}
    //void ShowMyTicket();
   // void CheckSeat();
   // void ReserveSeat();
    void ShowMovieList() {
        system("cls");

        // Variables
        int choose;
        // Variables End

        cout<<"-------------------------------------------------------------------------------------------------------------\n";
        cout<<"|";

        cout.width(60);
        cout<<"the latest movies:";
        cout.width(48);
        cout<<"|"<<endl;
        cout<<"-------------------------------------------------------------------------------------------------------------\n";
        cout<<"|";
        cout.width(20);
        cout<<"1.BALA";
        cout.width(88);
        cout<<"|"<<endl;
        cout<<"|";
        cout.width(27);
        cout<<"2.HOUSEFULL 4";
        cout.width(81);
        cout<<"|"<<endl;
        cout<<"|";
        cout.width(37);
        cout<<"3.TERMINATOR: DARK FATE";
        cout.width(71);
        cout<<"|"<<endl;
        cout<<"|";
        cout.width(21);
        cout<<"4.JOKER";
        cout.width(83);
        cout<<"|"<<endl;
        cout<<"|";
        cout.width(26);
        cout<<"5.DREAM GIRL";
        cout.width(82);
        cout<<"|"<<endl;
        cout<<"-------------------------------------------------------------------------------------------------------------\n";
        //cout<<"enter your choice:";
    //cin>>choose;
    cout << "PRESS ANY KEY FOR PREVIOUS MENU\n";
    getch();
    main();
    /*ExitMenu:
    if (choose != 0)
    {
        ShowMovieList();
    }
    else
    {
        main();
    }*/
}
};

int main()
{
    // Initial Load
    system("cls");
    system("MOVIE BOOKING SYSTEM");
    // Initial Load End

    // Call Methods
    // Call Methods End

    // Variables
    int chooseOneFromMenu = 0;
    char exitSurity;
    int num = 1;
    int fin = 0;
    // Variables End
 cout<<"\t\t------------------------------------------------------------------------------------------\n";
        cout<<"\t\t|";
        cout.width(55);
        cout<<"WELCOME TO BOOK MY SHOW";
        cout<<"\t\t\t\t |"<<endl;
cout<<"\t\t------------------------------------------------------------------------------------------\n";
        cout<<"\t\t|";
        cout.width(50);
        cout <<"1. Book Ticket";
        cout<<"\t\t\t\t\t |"<<endl;

        /*cout<<"\t\t|";
        cout.width(53);
        cout <<"2. Show My Ticket";
        cout<<"\t\t\t\t\t |"<<endl;

        cout<<"\t\t|";
        cout.width(49);
        cout <<"3. Check Seat";
        cout<<"\t\t\t\t\t |"<<endl;*/

        cout<<"\t\t|";
        cout.width(54);
        cout <<"2. Show Movie List";
        cout<<"\t\t\t\t\t |"<<endl;

        cout<<"\t\t|";
        cout.width(43);
        cout <<"3. Exit";
        cout<<"\t\t\t\t\t\t |"<<endl;
        cout<<"\t\t------------------------------------------------------------------------------------------\n";

        cout.width(50);
        cout << "Choose One: ";
    cin>>chooseOneFromMenu;
    ticket t1;
    switch (chooseOneFromMenu)
    {
    case 1:
        t1.BookTicket();
        break;
    case 2:
        //ShowMyTicket();
         t1.ShowMovieList();
        break;
    case 3:
        ExitProgram:
        cout << "Program terminating. Are you sure? (y/N): ";
        cin >> exitSurity;
        if (exitSurity == 'y' || exitSurity == 'Y') {
            return 0;
        }else if (exitSurity == 'n' || exitSurity == 'N') {
            system("cls");
            main();
        }else {
            cout << "Next time choose after read the corresponding line." << endl;
            goto ExitProgram;
        }
        break;
    default:
        cout << "Please choose between 1 - 5. Press Enter To Continue...";
        getch();
        system("cls");
        main();
        break;
    }
    return 0;
}
