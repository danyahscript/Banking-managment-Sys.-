#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;



struct customer
{
    int account_Num;
    char name[30];
    int balance;
};




void intro();
void withdraw(struct customer list[], int iter, int number, int amt);
int search(struct customer list[80], int size, int number);
void display(struct customer list[80], int iter);
void deposit(struct customer list[], int size, int number, int amt);
void add(struct customer list[80], int iter);
bool deleteAcc(struct customer list[80], int size, int target);
void sortbyAccNumAsc(struct customer list[80], int size);
void sortbyAccNumDes(struct customer list[80], int size);


int main()
{
    
    int n, ch, accountNum, index, amount, iter = 0;

    struct customer data[80];

    ofstream statFile;
    statFile.open("statisticalReport.txt");
    if (!statFile)
    {
        cout << "There is an error with opening the statisticalReport.txt file" << endl;
    }

    
    ifstream inFile;
    inFile.open("input.txt");

    if (!inFile)
    {
        cout << "There is an error with opening the output.txt file" << endl;
        exit(1);
    }

    inFile >> n;
    for (int i = 0; i < n; i++)
    {
        inFile >> data[i].account_Num >> data[i].name >> data[i].balance;
        iter = i + 1;
    }

    inFile.close();

    

    intro();
    statFile << "- the user started the program.." << endl;


    while (true)
    {

        cout << "\t\t\t\t    ::MAIN MENU::\n";
        cout << "\n\n\t1. DISPLAY RECORDS";
        cout << "\n\n\t2. ADD RECORDS";
        cout << "\n\n\t3. SEARCH RECORDS";
        cout << "\n\n\t4. DEPOSIT AMOUNT";
        cout << "\n\n\t5. WITHDRAW AMOUNT";
        cout << "\n\n\t6. SORT RECORDS";
        cout << "\n\n\t7. DELETE RECORDS";
        cout << "\n\n\t0. EXIT";
        cout << "\n\n\tSelect Your Option: ";
        cin >> ch;
        
        int* p = &iter;

        

        switch (ch)
        {
        case 1:
            
            display(data, iter);
            break;
        case 2:
            add(data, iter);
            iter++;
            statFile << "- the user added an account" << endl;
            break;
        case 3:
            cout << "Enter account number to search : ";
            cin >> accountNum;
            index = search(data, iter, accountNum);
            if (index == -1)
            {
                cout << "Record not found : ";
            }
            else
            {
                cout << "Account Number: " << data[index].account_Num <<
                    endl << "Name: " << data[index].name << endl << "Balance: " << data[index].balance << endl;
                statFile << "- the user searched an account" << endl;

            }

            break;
        case 4:
            cout << "Enter account number : ";
            cin >> accountNum;
            cout << "Enter amount to deposit : ";
            cin >> amount;
            deposit(data, iter, accountNum, amount);
            statFile << "- the user deposited from an account" << endl;

            break;
        case 5:
            cout << "Enter account number : ";
            cin >> accountNum;
            cout << "Enter amount to withdraw : ";
            cin >> amount;
            withdraw(data, iter, accountNum, amount);
            statFile << "- the user withdrawed from an account" << endl;
            break;
        case 6:
            int c2;
            cout << "How do you want the records to be sorted?\n1)By account number - Descending\n2)By account number - Ascending" << endl;
            cin >> c2;
            switch (c2)
            {
            case 1:
                sortbyAccNumDes(data, iter);
                statFile << "- the user sorted all accounts desceningly" << endl;
                break;
            case 2:
                sortbyAccNumAsc(data, iter);
                statFile << "- the user sorted all accounts ascendingly" << endl;
                break;
            }
            break;


        case 7:
            char c;
            cout << "Enter account number : ";
            cin >> accountNum;
            cout << "Are you sure you want to delete account number - " << accountNum << " ? (y or n)" << endl;
            cin >> c;
            if (c == 'y')
            {
                if (deleteAcc(data, iter, accountNum))
                    iter--;
                else
                    cout << "Record not found!" << endl;
                
            }
            statFile << "- the user deleted an account" << endl;
            break;
        case 0:
            ofstream outFile;
            outFile.open("input.txt");

            if (!outFile)
            {
                cout << "There is an error with opening the output.txt file" << endl;
                exit(1);
            }

            outFile << iter << endl;
            for (int i = 0; i < iter; i++)
            {
                outFile << data[i].account_Num << " " << data[i].name << " " << data[i].balance << endl;
            }


            outFile.close();

            statFile << "- the user exited the program" << endl << endl;
 
            const time_t ttime = time(0);

            char* dt = ctime(&ttime);
            statFile << "Updated: " << dt << endl;


            statFile.close();

            exit(0);
        }
    }

    return 0;
}


void add(struct customer list[80], int iter)
{
        cout << "\nEnter account number : ";
        cin >> list[iter].account_Num;

        cout << "Enter name : ";
        cin >> list[iter].name;
        list[iter].balance = 0;
        
}

void display(struct customer list[80], int iter)
{
    if (iter >= 0)
    {
        cout << "\n\nAccount Number\tName\tBalance\n";
        cout << "-------------------------------------------------------" << endl;
        for (int i = 0; i < iter; i++)
        {
            cout << "   " << list[i].account_Num << "\t\t" << list[i].name << "   " << list[i].balance << endl << "-------------------------------------------------------" << endl;
        }
    }
    else
        cout << "There are no records to be displayed.."<<endl;
    
}

int search(struct customer list[80], int size, int target)
{
    
    for (int i = 0; i < size; i++)
    {
        if (list[i].account_Num == target)
        {
            return i;
        }
    }

    return  -1;
}

void deposit(struct customer list[], int size, int number, int amount)
{
    int i = search(list, size, number);
    if (i == -1)
    {
        cout << "Record not found";
    }
    else
    {
        list[i].balance += amount;
    }
}

void withdraw(struct customer list[], int s, int number, int amount)
{
    int i = search(list, s, number);
    if (i == -1)
    {
        cout << "Record not found\n";
    }
    else if (list[i].balance < amount)
    {
        cout << "Insufficient balance\n";
    }
    else
    {
        list[i].balance -= amount;
    }
}

bool deleteAcc(struct customer list[80], int size, int target)
{
    int index = search(list,size,target);
    if (index != -1)
    {
        for (int i = index; i < size; i++)
        {
            list[i] = list[i+1];
            
        }
        return true;
    }
    return false;
    
}


void sortbyAccNumAsc(struct customer list[80], int size)
{
    //Bubble Sort - Ascending
    for (int step = 0; step < size - 1; ++step)
    {
        for (int i = 0; i < size - step - 1; ++i)
        {

            if (list[i].account_Num > list[i + 1].account_Num)
            {

                // swap
                struct customer temp = list[i];
                list[i] = list[i + 1];
                list[i + 1] = temp;
            }
        }
    }
    
}

void sortbyAccNumDes(struct customer list[80], int size)
{
    //Bubble Sort - Descending
    for (int step = 0; step < size - 1; ++step)
    {
        for (int i = 0; i < size - step - 1; ++i)
        {

            if (list[i].account_Num < list[i + 1].account_Num)
            {

                // swap
                struct customer temp = list[i];
                list[i] = list[i + 1];
                list[i + 1] = temp;
            }
        }
    }

}

void intro()
{
    cout << "\n\n\t\t\t\t======================\n";
    cout << "\t\t\t\tBANK MANAGEMENT SYSTEM";
    cout << "\n\t\t\t\t======================\n";
    cout << endl << endl;

    cout << "\t\t\tThis project is done by:" << endl << endl;
    cout << "\t\t\tGhadi Riyani - ID: 2190000354" << endl;
    cout << "\t\t\tRaghad Alnahdi - ID: 2190003070" << endl;
    cout << "\t\t\tRawan Almoaibed - ID: 2190003682" << endl;
    cout << "\t\t\tDaniah Alharthi - ID: 2190004427" << endl;
    cout << "\t\t\tAljohara Alshukr - ID: 2180005529" << endl;

    cout << endl << endl;


}

