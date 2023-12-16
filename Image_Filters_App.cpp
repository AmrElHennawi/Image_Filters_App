#include "Gray_Image.h"
#include "RGB_Image.h"

using namespace std;


int main()
{
    string choice;
    system("cls");
    cout << "Welcome to the Image filters program :)" << endl;
    while (true)
    {

        cout << endl
             << "what kind of bitmap photo would you like to apply the filters on" << endl
             << endl;
        cout << "1- RGB" << endl
             << "2- GS" << endl
             << "0- Exit" << endl
             << "Choose: ";
        getline(cin, choice);
        if (choice == "1")
        {
            RGBList();
        }
        else if (choice == "2")
        {
            GSList();
        }
        else if (choice == "0")
        {
            break;
        }
        else
        {
            system("cls");
            cout
                << "input error" << endl;
        }
    }
    cout << "Thanks for using the app";
}
