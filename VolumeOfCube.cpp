/////////////////////////////////////////////////////////
//
// Function name :  VolumeOfCube
// Input :          Side of Cube
// Output :         Volume of Cube
// Description :    It is used to calculate Volume of cube
// Author :         Vaibhav Tukaram Gaikwad
// Date :           08/04/2022
//
////////////////////////////////////////////////////////


#include<iostream>
using namespace std;

class Volume
{
    public:

int VolumeOfCube(int iS)
{
    int iAns = 0;

    iAns = iS*iS*iS;

    return iAns;

    }

};

int main()
{
    Volume obj;

    int iSide = 0;
    int iRet = 0;

    cout<<"Enter side of Cube :";
    cin>>iSide;

    iRet = obj.VolumeOfCube(iSide);

    cout<<"Volume of Cube is :"<<iRet;

    return 0;
}