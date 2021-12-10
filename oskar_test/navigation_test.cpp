#include "navigation.h"
#include "iostream"
using namespace std;

int main()
{

    Navigator navigator;

    int i = 0;

    cout << "Exploring\n";
    while (navigator.hasNextTurn())
    {
        if (i == 20) // Arbitrary, this is where we find the last person
        {
            cout << "Going home\n";
            navigator.goHome();
        }

        cout << navigator.nextTurn() << "\n";
        i++;
    }
    cout << "Home\n";

    cout << "\nNavigation test ended\n";
    return 0;
}