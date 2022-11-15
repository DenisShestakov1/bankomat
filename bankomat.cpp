#include <iostream> // для cin cout ......
#include <fstream> // файловая библиотека
#include <ctime> //Включает time.h стандартной с
#include <map> // место куда скидывают данные по типу ключ-значение
#include <limits> // для общих типовов переменных
using namespace std; // облако в котором все функции с std 


int id ,StatusCard;// переменные
void getid()// функция{
	ifstream idFile("id.txt");// файл
	idFile>>id>>StatusCard; // присвоение
	idFile.close(); // закрыть

}


map <int, int> AllUsersBalance; // создаем map с названием  AllUsersBalance
int UserBalance;// переменная
void getbalance()//функция
{
    ifstream balance("balance.txt");//файл
	while(!balance.eof())//цикл
  {
		int Allid, AllBalance; // переменная 
		balance>>Allid>>AllBalance; // присвоение
		AllUsersBalance[Allid] = AllBalance;//одно равно другому
	}
	balance.close();// закрытие
	UserBalance = AllUsersBalance[id]; //одно равно другому
}


void SaveOperation(string OperationType,int UserBalance)// функция
{
    ofstream operation("operation.txt",ios::app);/файл 
    time_t seconds = time(NULL); // одно равно другому
    tm* timeinfo = localtime(&seconds);//одно равно другому
    operation<<id<<"| "<<OperationType<<"| "<<UserBalance<<"| "<<asctime(timeinfo); // запись как будет выглядить операция
    operation.close(); // закрытие
   
}


void OperationWithBalance(int id,int UserBalance) //функция
{
    AllUsersBalance[id] = UserBalance; //одно равно другому
    ofstream BalanceFile("balance.txt"); // файл
    BalanceFile<<""; // открыть  
    BalanceFile.close(); // закрыть
    map<int, int> ::iterator it; 
    ofstream BalanceFile1("balance.txt",ios::app); // файл
    
    for (it = AllUsersBalance.begin(); it != AllUsersBalance.end(); ++it) //цикл с уловием
    {
    BalanceFile1<<it->first<<" "<<it->second<<"\n"; // присваиваем
	} BalanceFile1.close(); //закрыть 
}


int EnterInPersonalMenu() 
{ 
    if(StatusCard == 0) // условие
    {
        printf("You card has been locked\n"); 
        return 1;
    }
    
    int EnterUserPin,UserPin,AttempLimit = 3; // ппеременные
    ifstream PinFile("pins.txt"); // файл
    PinFile>>UserPin; // присвоение
    PinFile.close(); //закрыть
    printf("Enter you pin - "); // вывод на экран
    
    while(!(cin>>EnterUserPin) or cin.get() != '\n' or EnterUserPin!=UserPin) // цикл с уловием
    {
        AttempLimit-=1; 
        if(AttempLimit == 0) return 1;//условие
        printf("Invalid input! Attemps left - %d\n",AttempLimit);// выво на экран
        cin.clear(); // изменение индикатора
        cin.sync(); // очистка потока
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // извличение и пропуск в потоке
        cout<<"Enter you pin - "; // вывод  на экран
    }
    if(EnterUserPin == UserPin); // условие
    return 0;
}


int UserChoiceFunc()
{
    int UserChoiceInFunc; //переменная
    printf("\nUp the balance[1]\nWithdraw money[2]\nPay be phone[3]\nTransfer money[4]\nbalans[5]\nOperation[6]\nExit[7]\n\nSelect operation - "); 
    
    while(!(cin>>UserChoiceInFunc) or cin.get() != '\n' or UserChoiceInFunc < 1 or UserChoiceInFunc > 7) // цикл 
    {
	        printf("\nInvalid input!\n"); 
            cin.clear();// изменение индикатора
            cin.sync();// очистка потока
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // извличение и пропуск в потоке
            cout<<"\nUp the balance[1]\nWithdraw money[2]\nPay be phone[3]\nTransfer money[4]\nbalans[5]\nOperation[6]\nExit[7]\n\nSelect operation - "; //вывод
	}
	cout<<"\n";
	return UserChoiceInFunc;
}


void UpTheBalance() //функция
{
    int UserDeposit;// переменная
    string OperationType = "UpTheBalance"; //одно равно другому 
    printf("\nexit[0]\nbalance - %d\nHow much do you want to put into the account? - ",UserBalance);
    
    while(!(cin>>UserDeposit) or cin.get() != '\n' or UserDeposit < 0) //цикл с уловием
    {
        printf("Invalid input!\n\n");
        cin.clear();// изменение индикатора
        cin.sync();// очистка потока
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// извличение и пропуск в потоке
        cout<<"\nexit[0]\nbalance - %d\nHow much do you want to put into the account? - ",UserBalance; //вывод
    } if(UserDeposit == 0) // условие
    {return;}
    
    UserBalance += UserDeposit; // x+=4 - x= x+4
    OperationWithBalance(id,UserBalance); // что находиться в OperationWithBalance
    printf("Successful!\n");
    SaveOperation(OperationType,UserDeposit);
}


void WithdrawMoney() // функция
{
    int UserDeposit; // переменная
    string OperationType = "WithdrawMoney";//одно равно другому 
    printf("\nexit[0]\nbalance - %d\nHow much do you want to withdraw? - ",UserBalance);
    
    while(!(cin>>UserDeposit) or cin.get() != '\n' or UserDeposit < 0 or UserBalance - UserDeposit < 0)//цикл с уловием
    {
        printf("Invalid input!\n\n");
        cin.clear();// изменение индикатора
        cin.sync();// очистка потока
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// извличение и пропуск в потоке
        printf("\nexit[0]\nbalance - %d\nHow much do you want to withdraw? - ",UserBalance);//вывод
    } if(UserDeposit == 0)  // условие
    {return;}
    
    UserBalance -= UserDeposit;// x-=4 - x = x - 4
    OperationWithBalance(id,UserBalance);// что находиться в OperationWithBalance
    printf("Successful!\n");
    SaveOperation(OperationType,UserDeposit);
}


void PayBePhone() // функция
{
    string OperationType = "PayBePhone";//одно равно другому 
    int UserDeposit,phone;// переменная
    
    printf("\nexit[0]\nEnter phone number - ");
    while(!(cin>>phone) or cin.get() != '\n' or phone < 0) // цикл
    { 
        printf("Invalid phone number!\n");
        cin.clear();// изменение индикатора
        cin.sync();// очистка потока
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// извличение и пропуск в потоке
        cout<<"\nexit[0]\nEnter phone number - "; //вывод
    }if(phone == 0) //условие
    {return;}
    
    printf("\nexit[0]\nbalance - %d\npayment amount? - ",UserBalance);
    while(!(cin>>UserDeposit) or cin.get() != '\n' or UserDeposit < 0 or UserBalance - UserDeposit < 0) //цикл
    {
        printf("Invalid input!\n\n");
        cin.clear();// изменение индикатора
        cin.sync();// очистка потока
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// извличение и пропуск в потоке
        printf("\nexit[0]\nbalance - %d\npayment amount? - ",UserBalance);
    }if(UserDeposit == 0) //условие
    {return;}
    
    UserBalance -= UserDeposit; // x-=4 - x = x - 4
    OperationWithBalance(id,UserBalance); // что находиться в OperationWithBalance
    printf("Successful!\n");
    SaveOperation(OperationType,UserDeposit);
}


void transferMoney()//функция 
{
    string OperationType = "transferMoney";
    int UserDeposit, OtherPersonsid,Allid;//переменная
    map<int, int> ::iterator it;
    
    while(true) //цикл
    {
        printf("\nexit[0]\nEnter the account id to which you want to make the transfer? - ");
        while(!(cin>>OtherPersonsid) or cin.get() != '\n' or OtherPersonsid < 0) // цикл
        {
            printf("Invalid id!\n");
            cin.clear();// изменение индикатора
            cin.sync();// очистка потока
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"\nexit[0]\nEnter the account id to which you want to make the transfer? - ";// извличение и пропуск в потоке
        } if(OtherPersonsid == 0)//условие
        {return;}
        
            if(OtherPersonsid == id)//условие
            {printf("you can't send money to yourself!\n");}
            else if(AllUsersBalance.find(OtherPersonsid) == AllUsersBalance.end()) {printf("there is no such id!\n");} //результат условия
            else{break;}
    }
    
    printf("\nexit[0]\nbalance - %d\npayment amount? - ",UserBalance);
    while(!(cin>>UserDeposit) or cin.get() != '\n' or UserDeposit < 0 or UserBalance - UserDeposit < 0) //цикл
    {
        printf("Invalid input!\n\n");
        cin.clear();// изменение индикатора
        cin.sync();// очистка потока
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// извличение и пропуск в потоке
        printf("\nexit[0]\nbalance - %d\npayment amount? - ",UserBalance);
    }if(UserDeposit == 0) //условие
    {return;}
    
    AllUsersBalance[OtherPersonsid] += UserDeposit; // x+= + 4 , x = x + 4 
	UserBalance -= UserDeposit;// x-=4 - x = x - 4
	OperationWithBalance(id,UserBalance);// что находиться в OperationWithBalance
	printf("Successful!\n");
	SaveOperation(OperationType,UserDeposit);
    
}


void CheckBalance() // функция
 {
    printf("Your balance - %d\n",UserBalance);
}


void CheckOperations() //функция
{
    int SizeBuffer = 100; //переменная
    char* buffer = new char[SizeBuffer+1];// массив
    buffer[SizeBuffer]=0;
    
    ifstream operation("operation.txt");//файл
    while(!operation.eof())//цикл
    {
        operation.getline(buffer,SizeBuffer,'\n');// символы из потока выходного потока помещает в строку
        cout<<buffer<<"\n";
    }
    operation.close();//закрыть
}


void CloseCard()//функция
{
	StatusCard = 0;
	ofstream idFile("id.txt");//файл
	idFile<<id<<" "<<StatusCard; //присвоение
	idFile.close();//закрытие
	cout<<"Card has been locked!\n";//вывод на экран
}

int main()//функция
{
	getid();//функция
    int PermissionToEnter = EnterInPersonalMenu();//переменная
    int UserChoice;//переменная
    if(PermissionToEnter == 1)//условие
    {
	printf("number of attempts exceeded! no entry!\n");
	CloseCard();//закрытие
	return 1;
    }
    
    else if(PermissionToEnter == 0)//результат условия
    {
	    printf("Successful entry!\n\n");
	    getbalance();
	
	    while(true)//цикл
      {
	        UserChoice = UserChoiceFunc(); 
	        if(UserChoice == 1) {UpTheBalance();}
	        else if(UserChoice == 2) {WithdrawMoney();} 
	        else if(UserChoice == 3) {PayBePhone();}
	        else if(UserChoice == 4) {transferMoney();}
	        else if(UserChoice == 5) {CheckBalance();}
	        else if(UserChoice == 6) {CheckOperations();}
	        else if(UserChoice == 7) {break;}
	    }
    }
}
