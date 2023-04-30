#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <fstream>
#include "SHA1.hpp"
#include "SHA1.cpp"

using namespace std;

void add();
void check();
void everything();
void number();
void password();
void integrity();
bool isNum(const string &);



struct Friend{ //define a structure "Friend" for the addition of data 

    string name;
    string student_ID; 
    string email;
    string country;

};


int main(){


    int selection; // integer for user-input-based menu purpose 

    while(cin.fail()|selection!=4|selection>4){ //loop if user input is invalid
    cout<<"----------------------------------------"<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<endl;
    cout<<setw(32)<<right<<"Welcome to Friend Chain!"<<endl;
    cout<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<endl;
    cout<<"What would you like to do today?"<<endl;
    cout<<endl;
    cout<<"1. Add Friend"<<endl;
    cout<<"2. Check Friend"<<endl;
    cout<<"3. Real or Fake"<<endl;
    cout<<"4. Quit"<<endl;
    cout<<endl;
    cout<<"Please select: ";
    cin>>selection;

    if(cin.fail()|selection>4|selection<1){ //condition if user inputted invalid value
    cin.clear();
    cin.ignore(INT_MAX,'\n'); 
    cout<<endl;
    cout<<"Please enter digits or the options provided only!"<<endl;}
    
    if(selection==1){
        add(); //call function add() for the addition of data;
    }else if(selection==2){

        ifstream filechecker("friends.txt"); //open the file to check its presence
            if(filechecker.is_open()){ //condition if file exists

                check(); //call function check to check data
            }
            else{
                cout<<endl;
                cout<<"There is no friend in the chain yet, please add friend before checking!"<<endl; //prompt message if file doesn't exist
                main();//return to main() function
            }
        filechecker.close();

    }else if(selection==3){
        ifstream filechecker("friends.txt");//open the file to check its presence
            if(filechecker.is_open()){//condition if file exists

                integrity();//call function to check integrity
            }
            else{
                cout<<endl;
                cout<<"There is no friend in the chain yet, please add friend before checking!"<<endl;//prompt message if file doesn't exist
                main();//return to main() function
            }
    }
      
    
    
    }


   

    exit(0); //end the program



   
    return 0;
}



void add(){

    fstream data("friends.txt",ios::in | ios::out | ios::app); //create textfile "friends.txt" 
    fstream duplicate("friends_duplicate.txt",ios::in | ios::out|ios::app); //create textfile "friends_duplicate.txt" 

    int line_num = 0; //counter for the line number in textfile

    string test;

    if(duplicate){ //condition if "friends_duplicate.txt" exists


        while  (getline(duplicate,test)){

            line_num++; //get the total line number in file
        }
    }else{
        line_num =0; //if file is empty
    }

    duplicate.close(); //close "friends_duplicate.txt"

    
   
    Friend friends; //create variable "friends" of structure Friend

    line_num = line_num/3; //Get the current friend number(block number) in textfile

    cout<<"You are now entering Friend "<<line_num+1<<"'s info: "<<endl; //Output the addition of next friend  number(block number) message
   
    cout<<"Type your friend's name: ";
    cin.ignore();//ignore whitespace
    getline(cin,friends.name);   //get the user input of friends' name
    
    
    cout<<"Type your friend's Student ID: ";
    getline(cin,friends.student_ID);//get the user input of friends' student ID
           
    cout<<"Type your friend's email: ";
    getline(cin,friends.email);    //get the user input of friends' email
    
            
    cout<<"Type your friend's country: ";
    getline(cin,friends.country);   //get the user input of friends' country


    SHA1 checksum; //declare header file to use its content
    char hash[41]; //create a character array "hash"
    checksum.update(friends.student_ID); //get the value of student ID to get the hash value
    strcpy(hash,checksum.final().c_str()); //copy the hash value string to character array "hash"
    
    string hash_value = ""; //create a new string "hash_value"
    int hash_size = sizeof(hash)/sizeof(hash[0]); //get the total length of character array "hash"
    for(int i=0;i<hash_size-1;i++){
        hash_value = hash_value+hash[i]; //copy "hash" to "hash_value"
    }

    duplicate.open("friends_duplicate.txt"); //open file "friends_duplicate.txt"

    int counter = 0; //setup a counter
    while(getline(duplicate,test)){

              
            if(test==hash_value){ // condition check if "hash_value" is similar to the line got from "friends_duplicate.txt"
                counter++; //increment of counter if condition has met
                
        }
    }

    duplicate.close(); //close "friends_duplicate.txt"

    int width = (friends.name.length()+friends.student_ID.length()+friends.country.length()+friends.email.length())/4+10; //set the width between data
    if(counter==0){ //condition if "hash_value" does not exist in "friends_duplicate.txt" 

        data<<line_num+1<<endl; //output(write) the friend number(block number) to "friends.txt"


        data<<"Name: "<<friends.name<<setw(width)<<right<<"Student ID: "<<friends.student_ID<<setw(width)<<"Email: "<<friends.email<<setw(width)<<"Country: "<<friends.country<<endl;//output(write) the data of friend to "friends.txt"
        
        data<<hash<<endl;//output(write) the hash value to "friends.txt"

        data.close(); //close the file "friends.txt"

        duplicate.open("friends_duplicate.txt",ios::out |ios::app | ios::in); //open "friends_duplicate.txt"

        duplicate<<line_num+1<<endl;//output(write) the friend number(block number) to "friends_duplicate.txt"
        duplicate<<"Name: "<<friends.name<<setw(width)<<right<<"Student ID: "<<friends.student_ID<<setw(width)<<"Email: "<<friends.email<<setw(width)<<"Country: "<<friends.country<<endl;//output(write) the data of friend to "friends_duplicate.txt"
        duplicate<<hash<<endl; //output(write) the hash value to "friends_duplicate.txt"
        duplicate.close(); //close the file "friends_duplicate.txt"
        
        cout<<"----------------------------------------"<<endl;
        cout<<"----------------------------------------"<<endl;
        cout<<endl;

        cout<<"Data saved!"<<endl;
        cout<<"The ""password""(hash value) is: "<<hash<<endl; //output the hash_value



    }else{ //condition if "hash_value" exists in "friends_duplicate.txt"
        cout<<endl;
        cout<<"This friend has existed in the chain!"<<endl;
        cout<<"Please try again!"<<endl;
        cout<<"(Ps: Did you forget about him/her?) "<<endl; 

        cout<<endl;

    }
 
            

}


void check(){
    int select; //integer for user-based input menu

    while(cin.fail() | select >3 | select<1 |select !=4){ //loop if user input is invalid
    cout<<"----------------------------------------"<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<endl;
    cout<<setw(32)<<right<<"Welcome to Friend Checker!"<<endl;
    cout<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<"Which method do you want to use to check the data?"<<endl;
    cout<<endl;
    cout<<"1. Friend Number (e.g.: 1,2,3,4)"<<endl;
    cout<<"2. Password (Hash Value)"<<endl;
    cout<<"3. I want to read everything!"<<endl;
    cout<<"4. Exit"<<endl;
    cout<<endl;
    cout<<"Please select:";
    cin>>select;
    cout<<endl;

    if(cin.fail()|select>4|select<1){ //condition if user inputted invalid value
    cin.clear();
    cin.ignore(INT_MAX,'\n');
    cout<<endl;
    cout<<"Please enter digits or the options provided only!"<<endl;
    check(); //recall the function

    }

    if(select==1){
        number(); //call the function number() to check data based on block number
    }else if(select==2){
        password(); //call the function password() to check the data based on hash value
    }else if(select==3){
        cout<<"Here are your friends:"<<endl;
        everything();// call the function everything to output every data in file

    }


    break;
    
    }
    
    
}

void number(){

    int line_counter = 0; //counter for line in textfile
    int current_line = 0;//get the current line number
    int password_line = 0;//get the line number of password(hash value)
    int detail_line = 0;//get the line number of data
    string num; 
    string grab_line;
    cout<<"Type the number of your friend: ";
    cin.ignore(); //ignore whitespace
    getline(cin,num); //user input friend number(block number) to check data
    ifstream reader("friends_duplicate.txt");
    while(getline(reader,grab_line)){ //get the line from "friends_duplicate.txt"
        line_counter++; //increment of line counter
        
        if(num==grab_line){ //condtion if user-inputted friend number(block number) exists in "friends_duplicate.txt"

            cout<<endl;
            cout<<"Friend "<<grab_line<<endl; //output friend number(block number)
            current_line = line_counter; //get the current line number
            detail_line = current_line + 1; //get the line number of the details of friend
            password_line = current_line + 2; // get the line number of hash value


        }

        if(line_counter==detail_line){ //condition if the total of line counter is same as the line number of data
            cout<<grab_line<<endl; //output the details of friend 

        }else if(line_counter==password_line){ //condition if the total of line counter is same as the line number of has value
            cout<<"Password (Hash Value): "<<grab_line<<'\n'; //output hash value
        }

        continue;

    }

    if(current_line==0){ //condition if user-inputted friend number(block number) doesn't exist in "friends_duplicate.txt"
        cout<<endl;
        cout<<"This friend doesn't exist in this chain!"<<endl;
        cout<<"Please add him/her into this chain!"<<endl;
        cout<<"(Ps:Perhaps he/she is just your imagaination...)"<<endl;
        cout<<"(Ps:Or maybe it's just the value you entered is not a number)"<<endl;
        cout<<endl;
    }

    reader.close();
    check(); //return(call) to the function check();
}

void password(){

    int counter = 0;

    string password; //store hash value that is inputted by user
    string grab_line; //get the current line
    string grab_line_duplicate; //get the previous line
    string grab_line_duplicate2;// get the second previous line
    cout<<"Please enter the password(hash value) : ";
    cin.ignore();
    getline(cin,password);//get the hash value from user

    ifstream reader("friends_duplicate.txt"); //open "friends_duplicate.txt"
    
    while(getline(reader,grab_line)){ 

        
        if(password==grab_line){ //condtion if user-inputted hash value exists in "friends_duplicate.txt"
            counter++;
            if (counter==1){
                cout<<endl;
                cout<<"Here's your friend:"<<endl;
                cout<<endl;
                cout<<"Friend "<<grab_line_duplicate2<<endl;//output the second previous line(friend number[block number])
                cout<<grab_line_duplicate<<endl; //output the previous line(data)
                cout<<"Password (Hash Value): "<<grab_line<<endl;//output the current line (hash value)
            }

        }
        
        grab_line_duplicate2 = grab_line_duplicate; //store the previous line and become the second previous line after loop

        grab_line_duplicate = grab_line; //store the current line and become the previous line after loop

        continue;


    }

    if(counter==0){
        cout<<endl;
        cout<<"This password(hash value) does not exist in the chain!"<<endl;
    }
    reader.close();
    check();

}

bool isNum(const string & grab) //create a boolean function to check if the string contains only digits
{
    for (char const &character : grab) {
        if (isdigit(character) == 0) 
            return false;
    }
    return true;
}

void everything(){

    cout<<endl;
    int line_counter = 0;
    string grab_line;
    ifstream reader("friends_duplicate.txt"); //open "friends_duplicate.txt"
    
    while(getline(reader,grab_line)){
        line_counter++;
        if((line_counter%3)==1){ //condition if the line contains friend number(block number)
            cout<<"Friend "<<grab_line<<endl; //output the friend number line

        }else if(isNum(grab_line)==false && grab_line.length()<41){//condition if the line contains hash value
            cout<<"Hash Value: "<<grab_line<<endl;//output the hash value line
            cout<<endl;
        }else{
            cout<<grab_line<<endl; //output the line of data of friend
        }


    }

    check();//return(call) to the function check()
    

}

void integrity(){

                cout<<endl;


                ifstream reader1("friends.txt"); //open "friends.txt"
                ifstream reader2("friends_duplicate.txt"); //open "friends_duplicate.txt"
                int reader1_counter =0; //counter for reader1
                int reader2_counter =0; // counter for reader2
                string reader1_hashline; //string to store "friends.txt" hash value
                string reader1_detailline;//string to store "friends.txt" details
                string reader2_hashline; //string to store "friends_duplicate.txt" hash value
                string reader2_detailline; //string to store "friends_duplicate.txt" details 
                while(getline(reader1,reader1_hashline)){
                        reader1_counter++; //increment of reader1 for each line gotten

                        if(reader1_counter%3==2){ //condition to check if the line contain details
                            reader1_detailline = reader1_hashline; //assign the line before getting new line 
                        }

                        if(reader1_counter%3==0){ // condition to check if the line contain hash value
                            while(getline(reader2,reader2_hashline)){
                                reader2_counter++; //increment of reader2 for each line gotten
                                if(reader2_counter==reader1_counter){ //condition if reader1_counter is same as reader2_counter

                                    break; //exit loop
                                }

                                reader2_detailline = reader2_hashline; //assign the line before getting new line 

                            }

                            if(reader1_detailline==reader2_detailline){ //condition to check if details is the same in reader1 and reader2s
                                cout<<"Friend "<<reader1_counter/3<<" is real! "<<endl;
                            }
                            else{

                                cout<<"There's a malicious modification!"<<endl;
                                cout<<"Friend "<<reader2_counter/3<<" is fake!"<<endl;
                                break;
                            }

                        reader2_counter = 0; //reset reader2 counter to 0

                            
                        reader2.clear(); 
                        reader2.seekg(0,ios::beg); //return to the beginning line of "friends_duplicate.txt"
                        }




                        

                }





}