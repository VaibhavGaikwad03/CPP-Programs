/////////////////////////////////////////////////////////
//
// Function name :  Arithmatic Operations
// Input :          Two integers
// Output :         Addition/Subtraction/Multiplication/Division
// Description :    It is used to perform Arithmatic operations
// Author :         Vaibhav Tukaram Gaikwad
// Date :           08/04/2022
//
////////////////////////////////////////////////////////

#include<iostream>
using namespace std;
class Arithmatic
{
    public:

    void Addition()
    {
        int iA = 0;
        int iB = 0;
        int iRet = 0;

        cout<<"Enter first number :";
        cin>>iA;
        cout<<"Enter second number :";
        cin>>iB;

        iRet = iA + iB;

        cout<<"Addition is :"<<iRet;


    }

    void Subtraction()
    {
        int iA = 0;
        int iB = 0;
        int iRet = 0;

        cout<<"Enter first number :";
        cin>>iA;
        cout<<"Enter second number :";
        cin>>iB;

        iRet = iA - iB;

        cout<<"Subtraction is :"<<iRet;


    }

    void Multiplication()
    {
        int iA = 0;
        int iB = 0;
        int iRet = 0;

        cout<<"Enter first number :";
        cin>>iA;
        cout<<"Enter second number :";
        cin>>iB;

        iRet = iA * iB;

        cout<<"Multiplication is :"<<iRet;


    }

    void Division()
        {
            int iA = 0;
            int iB = 0;
            int iRet = 0;

            cout<<"Enter first number :";
            cin>>iA;
            cout<<"Enter second number :";
            cin>>iB;

            iRet = iA / iB;

            cout<<"Division is :"<<iRet;


        }
};

int main()
{
    int iOption = 0;
    Arithmatic obj;

    cout<<"Enter 1 for Addition \n";
    cout<<"Enter 2 for Subtraction \n";
    cout<<"Enter 3 for Multiplication \n";
    cout<<"Enter 4 for Division \n";
    
    cin>>iOption;

    switch(iOption)
    {
        case 1 :
        obj.Addition();
        break;

        case 2 :
        obj.Subtraction();
        break;

        case 3 :
        obj.Multiplication();
        break;

        case 4 :
        obj.Division();
        break;

        default :
        cout<<"Invalid option selected";
    }
    return 0;
}