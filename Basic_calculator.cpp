#include<iostream>
using namespace std;

int addition(){
    cout<<"enter numbers to add.\n";
    int n;
    cin>>n;
    int result=0;
    while(n--){
        int number;
        cin>>number;
        result+=number;
    }
    cout<<"Result: "<<result<<"\n";
    return result;
}
int subtraction(){
    int a,b;
    cout<<"enter two numbers to subtract.\n";
    cin>>a>>b;
    int result=a-b;
    cout<<"Result: "<<result<<"\n";
    return result;
}

int multiplication(){
    cout<<"enter numbers to multiply.\n";
    int n;
    cin>>n;
    int result=1;
    while(n--){
        int number;
        cin>>number;
        result*=number;
    }
    cout<<"Result: "<<result<<"\n";
    return result;
}

int division(){
    int a,b;
    cout<<"enter two numbers to divide.\n";
    cin>>a>>b;
    if(b==0){
        cout<<"Error: Division by zero is not allowed.\n";
        return 0;
    }
    int result=a/b;
    cout<<"Result: "<<result<<"\n";
    return result;
}

int modulo(){
    int a,b;
    cout<<"enter two numbers to find modulo.\n";
    cin>>a>>b;
    if(b==0){
        cout<<"Error: Modulo by zero is not allowed.\n";
        return 0;
    }
    int result=a%b;
    cout<<"Result: "<<result<<"\n";
    return result;
}

int history(){
    cout<<"History feature is not implemented yet.\n";
    return 0;
}


int main(){
    int choice;
    string name;
    cout<<"Enter your Name.\n";
    cin>>name;
    cout<<"Welcome "<<name<<" to the Basic Calculator.\n";
    while(choice!=7){
    cout<<"-----------------------------------------------------\n";
    cout<<"------------------Basic calculator-------------------\n";
    cout<<"|[1].ADDITION                                        |\n";
    cout<<"|[2].SUBTRACTION                                     |\n";
    cout<<"|[3].MULTIPLICATION                                  |\n";
    cout<<"|[4].DIVISION                                        |\n";
    cout<<"|[5].MODULO                                          |\n";
    cout<<"|[6].HISTORY                                         |\n";
    cout<<"|[7].QUITE                                           |\n";
    cout<<"------------------------------------------------------\n";
    cout<<"Enter your choice.\n";
    cin>>choice;
    switch(choice){
        case 1:
            cout<<"You have selected Addition.\n";
            addition();
            break;
        case 2:
            cout<<"You have selected Subtraction.\n";
            subtraction();
            break;
        case 3:
            cout<<"You have selected Multiplication.\n";
            multiplication();
            break;
        case 4:
            cout<<"You have selected Division.\n";
            division();
            break;
        case 5:
            cout<<"You have selected Modulo.\n";
            modulo();
            break;
        case 6:
            cout<<"You have selected History.\n";
            history();
            break;
        case 7:
            cout<<"You have selected Quite.\n";
            break;
        default:
            cout<<"Invalid choice. Please try again.\n";
    }
}
}