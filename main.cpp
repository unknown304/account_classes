#include <iostream>
#include <vector>
#include <memory>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;
using std::make_unique;
using std::ostream;
using std::vector;



class Account{


private:
    string name;
    unique_ptr <double> amount;

public:
    Account(string name_passed="Unnamed Account",double amount_passed=0.0)
       :name{name_passed}
       {
       amount = make_unique<double>(amount_passed);}


    Account(Account &obj){
    name = obj.name;
    amount = make_unique<double>(*(obj.amount));
    }

    Account(Account &&obj){
    name = obj.name;
    amount = move(obj.amount);
    obj.amount = nullptr;

    }


    virtual bool withdraw(double amount_to_withdraw){
    if(amount_to_withdraw > *amount){
        cout<<"Insufficient funds\n";
         return 0;}
    else{*amount = *amount - amount_to_withdraw;
    return 1;}

    }


    virtual bool deposit(double amount_to_deposit){

    if(amount_to_deposit <= 0 )
         return 0;

    else{
        *amount = *amount + amount_to_deposit;
        return 1;}}


    virtual void print_info(ostream &os) {
     os<<"Account name:"<<name<<endl;
     os<<"Account balance:"<<*amount<<endl;}

    virtual ~Account(){
        }



string get_name(){
return name;}

double get_amount(){
return *amount;}






};













class Saving_account : public Account{

private:
  int int_rate;

public:

Saving_account(string passed_name="Unnamed saving account",double passed_amount=0.0,int passed_int_rate=0)
   :Account(passed_name,passed_amount),int_rate{passed_int_rate}{}

Saving_account(Saving_account &obj)
:Account{obj},int_rate{obj.int_rate}{}



Saving_account(Saving_account &&obj)
:Account{obj},int_rate{obj.int_rate}{}


 virtual bool deposit(double amount_to_deposit) override {


  amount_to_deposit=amount_to_deposit + (static_cast<double>(int_rate)/100);

    return Account::deposit(amount_to_deposit);
 }



virtual bool withdraw(double w) override{

return Account::withdraw(w);}


virtual void print_info(ostream &os) override{


os<< "Name: "<<Account::get_name()<<endl<<"Current balance: "<<Account::get_amount()<<endl<<"Intrest rate: "<<int_rate<<endl;
}

virtual ~Saving_account(){};


};












class Checking_account:public Account{

private:
    static constexpr double fee{1.50};

public:

    Checking_account(string passed_name="Unnamed Checking account",double passed_amount=0)
        :Account(passed_name,passed_amount){}

    Checking_account(Checking_account &obj)
:Account{obj}{}


Checking_account(Checking_account &&obj)
:Account{obj}{}




    virtual bool withdraw(double amount_to_withdraw) override{

        return Account::withdraw(amount_to_withdraw+fee);}




    virtual bool deposit(double amount_to_deposit) override{
        return Account::deposit(amount_to_deposit);
        }


   virtual void print_info(ostream &os) override{

os<<"Name: "<<Account::get_name()<<endl<<"Current balance: "<<Account::get_amount()<<endl;
}

virtual ~Checking_account(){};


};








class Trust_account: public Saving_account{


private:
    int number_of_withdraws;
    static constexpr int max_withdraws=3;
    static constexpr int max_allowed_value = 5000;
    static constexpr int bonus =50;

public:

    Trust_account(string passed_name="Unnamed Trust account",int passed_amount=0,int passed_int_rate=0)
         :Saving_account(passed_name,passed_amount,passed_int_rate),number_of_withdraws(0){}


    Trust_account(Trust_account &obj)
:Saving_account{obj}{
number_of_withdraws = obj.number_of_withdraws;}

Trust_account(Trust_account &&obj)
:Saving_account{obj}{
number_of_withdraws = obj.number_of_withdraws;}




    virtual bool deposit(double amount_to_deposit) override{

        if(amount_to_deposit >= 5000){
          return Saving_account::deposit(amount_to_deposit + bonus);}

        else{
          return Saving_account::deposit(amount_to_deposit);}}






   virtual bool withdraw(double amount_to_withdraw) override{

        if(number_of_withdraws >= max_withdraws)
            {return 0;}

        else{
           Saving_account::withdraw(amount_to_withdraw);
           number_of_withdraws++;
           return 1;}
   }

   virtual ~Trust_account(){};



    virtual void print_info(ostream &os) override{

os<< "Name: "<<Account::get_name()<<endl<<"Current balance: "<<Account::get_amount()<<endl<<"Number of withdraws allowed: "<<max_withdraws - number_of_withdraws<<endl;}

};




ostream& operator<<(ostream &os,Account &obj){

obj.print_info(os);

return os;

}






int main()
{

  vector<Account*> vec;
  vec.push_back(new Account);
  vec.push_back(new Trust_account);
  vec.push_back(new Checking_account);
   vec.push_back(new Saving_account);

   for(auto acc:vec){
    cout<<*acc<<endl;
   }








    return 0;
}
