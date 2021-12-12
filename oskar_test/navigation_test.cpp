#include "navigation.h"
#include "iostream"
using namespace std;

int main()
{

    Navigator navigator;
    //navigator.setPath(PATH_FIRST_PERSON);
    cout<<"PATH_FIRST_PERSON\n";

    for (int j = 0; j < 2; j++)
    {
        int i = 0;

        cout << "Path #"<<j<<"\n";
        while (navigator.hasNextTurn())
        {
            if (i == 15 && j == 1) // Arbitrary, this is where we find the last person
            {
                cout<<"PATH_HOME\n";
                navigator.setPath(PATH_HOME);
            }

            cout << navigator.nextTurn() << "\n";
            i++;
        }
        cout << "Path complete\n";
        navigator.setPath(PATH_EXPLORE);
        cout<<"PATH_EXPLORE\n";
    }

    cout << "\nNavigation test ended\n";
    return 0;
}