#ifndef GRAY_IMAGE_H
#define GRAY_IMAGE_H

#endif //GRAY_IMAGE_H

#include "bmplib.h"
#include "utility.h"

// note: SIZE is declared in bmplib.h as 256
// note: GS = grey scale
using namespace std;

//Global Variables
unsigned char GSImage[SIZE][SIZE];
unsigned char GSImage2[SIZE][SIZE];
unsigned char edited[SIZE][SIZE];


// function's prototypes
bool loadImage();
void GSToBlackAndWhite();
void invertImage();
void GSList();
void mergeTwoImages();
void detectImageEdges();
void flipVertical();
void flipHorizontal();
void flipImage();
void rotateImage();
void darkenImage();
void lightenImage();
void lightAdjustment();
void enlargeImage();
void shrinkHalf();
void shrinkThird();
void shrinkQuarter();
void shrinkImage();
void leftMirror();
void rightMirror();
void upperMirror();
void lowerMirror();
void mirrorImage();
void shuffleImage();
void blurImage();
void saveImage();




//_________________________________________
void GSList()
{
    string userInput;
    system("cls");
    if (!loadImage())
    {
        while (true)
        {
            printMenu();
            userInput = listInput();

            if (userInput == "1")
            {
                GSToBlackAndWhite();
                system("cls");
                cout << "Black and white Filter applied successfully" << endl;
                ;
            }
            else if (userInput == "2")
            {
                invertImage();
                system("cls");
                cout << "Invert Image Filter applied successfully" << endl;
            }
            else if (userInput == "3")
            {
                mergeTwoImages();
                system("cls");
                cout << "Merge Filter applied successfully" << endl;
            }
            else if (userInput == "4")
            {
                flipImage();
                system("cls");
                cout << "Flip Image Filter applied successfully" << endl;
            }
            else if (userInput == "5")
            {
                rotateImage();
                system("cls");
                cout << "Rotate Image Filter applied successfully" << endl;
            }
            else if (userInput == "6")
            {
                lightAdjustment();
            }
            else if (userInput == "7")
            {
                detectImageEdges();
                system("cls");
                cout << "Detect Image Edges Filter applied successfully" << endl;
            }
            else if (userInput == "8")
            {
                enlargeImage();
                system("cls");
                cout << "Enlarge Image Filter applied successfully" << endl;
            }
            else if (userInput == "9")
            {
                shrinkImage();
            }
            else if (userInput == "a" || userInput == "A")
            {
                mirrorImage();
                system("cls");
                cout << "Mirror half RGBImage Filter applied successfully" << endl;
            }
            else if (userInput == "b" || userInput == "B")
            {
                shuffleImage();
                system("cls");
                cout << "Shuffle Image Filter applied successfully" << endl;
            }
            else if (userInput == "c" || userInput == "C")
            {
                blurImage();
                system("cls");
                cout << "Blur Image Filter applied successfully" << endl;
            }
            else if (userInput == "s" || userInput == "S")
            {
                saveImage();
                system("cls");
                cout << "photo saved successfully" << endl;
                break;
            }
        }
    }
}

//_________________________________________
// load the GSImage file requested by the user
bool loadImage()
{
    char imageFilename[100];
    cout << "Please enter the source Image file name: ";
    cin.getline(imageFilename, 100);
    strcat(imageFilename, ".bmp");
    return readGSBMP(imageFilename, GSImage);
}

//_________________________________________
// filter 1: converts the source GSImage into a black and white RGBImage
void GSToBlackAndWhite()
{
    // calculating average number of greyscale intensity in all pixels
    int sumOfGreyscale = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            sumOfGreyscale += GSImage[i][j];
        }
    }
    int averageGreyscale = sumOfGreyscale / (SIZE * SIZE);

    /* converting each pixel to black or white depending on the comparison of
     * the pixels greyscale intensity number to the average greyscale intensity number */
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (GSImage[i][j] >= averageGreyscale)
            {
                GSImage[i][j] = 255;
            }
            else
            {
                GSImage[i][j] = 0;
            }
        }
    }
}

//__________________________________________
// filter 2: inverts the source GSImage
void invertImage()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            GSImage[i][j] = 255 - GSImage[i][j];
        }
    }
}

//_________________________________________
// filter 3: merges the source GSImage with another GSImage
void mergeTwoImages()
{
    // second RGBImage
    char imageFileName2[100];

    // Get gray scale RGBImage file name
    bool validInput = false;
    do
    {
        system("cls");
        cout << "Enter the other source RGBImage file name: ";
        cin >> imageFileName2;
        cin.ignore();

        // Add .bmp extension and load RGBImage
        strcat(imageFileName2, ".bmp");
        if (!readGSBMP(imageFileName2, GSImage2))
        {
            // Looping over the pixels
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    if (i % 2 == 0 || j % 2 == 0)
                    {
                        GSImage[i][j] = GSImage2[i][j];
                    }
                }
            }
            validInput = true; // Set flag to exit the loop
        }
        else
        {
            system("cls");
            cout << "File doesn't exist." << endl
                 << endl;
        }
    } while (!validInput);
}

//_________________________________________
void flipVertical()
{
    for (int col = 0; col < SIZE; col++)
    { // for every column
        int rowNum = 127;
        int rowNum2 = 128; // rowNum and rowNum2 here correspond to the row numbers
        for (int a = 0; a < SIZE / 2; a++)
        { // 128 iterations
            unsigned char tempPixel = GSImage[rowNum][col];
            GSImage[rowNum][col] = GSImage[rowNum2][col];
            GSImage[rowNum2][col] = tempPixel;
            rowNum--;
            rowNum2++;
        }
    }
}
//_________________________________________
void flipHorizontal()
{
    for (int row = 0; row < SIZE; row++)
    { // for every row
        int columnNum = 127;
        int columnNum2 = 128; // columnNum and columnNum2 here correspond to the column numbers
        for (int a = 0; a < SIZE / 2; a++)
        { // 128 iterations
            unsigned char tempPixel = GSImage[row][columnNum];
            GSImage[row][columnNum] = GSImage[row][columnNum2];
            GSImage[row][columnNum2] = tempPixel;
            columnNum--;
            columnNum2++;
        }
    }
}

//_________________________________________
// filter 4 flip GSImage horizontally or vertically
void flipImage()
{
    string flipType;
    bool validInput = false;

    while (!validInput)
    {
        system("cls");
        cout << "Flip type::" << endl
             << endl;
        cout << "1- (v)ertical." << endl;
        cout << "2- (h)orizontal" << endl
             << endl;
        cout << "choose: ";

        getline(cin, flipType);

        if (flipType == "v" || flipType == "V")
        {
            flipVertical();
            validInput = true;
        }
        else if (flipType == "h" || flipType == "H")
        {
            flipHorizontal();
            validInput = true;
        }
        else
        {
            system("cls");
            cout << "Invalid Input" << endl
                 << endl;
        }
    }
}

//_________________________________________
// filter 5 rotate GSImage 90, 180 or 270 degrees
void rotateImage()
{
    string choice;
    system("cls");
    cout << "Please choose which rotate you want." << endl;
    while (true)
    {
        cout << "Rotate::" << endl
             << endl;
        cout << "1- 90" << endl
             << "2- 180" << endl
             << "3- 270" << endl
             << endl;
        cout << "Choose: ";
        getline(cin, choice);
        if (rotateImageInput(choice))
        {
            int x = stoi(choice);
            for (int k = 0; k < x; k++)
            {
                for (int i = 0; i < SIZE; i++)
                {
                    for (int j = 0; j < SIZE; j++)
                    {
                        edited[j][255 - i] = GSImage[i][j];
                    }
                }

                for (int i = 0; i < SIZE; i++)
                {
                    for (int j = 0; j < SIZE; j++)
                    {
                        GSImage[i][j] = edited[i][j];
                    }
                }
            }
            break;
        }
        else
        {
            system("cls");
            cout << "Invalid input please try again." << endl;
        }
    }
}

//_________________________________________
// 6-1-darken function
void darkenImage()
{
    // looping over the pixels
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // subtracting values to darken
            if (GSImage[i][j] >= 85)
            {
                GSImage[i][j] -= 85;
            }
            else if (GSImage[i][j] < 85)
            {
                GSImage[i][j] = 0;
            }
        }
    }
}

//_________________________________________
// 6-2-lighten function
void lightenImage()
{
    // looping over the pixels
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // adding values to lighten
            if (GSImage[i][j] <= 170 && GSImage[i][j] > 0)
            {
                GSImage[i][j] += 85;
            }

            else if (GSImage[i][j] > 170)
            {
                GSImage[i][j] = 255;
            }
            else if (GSImage[i][j] == 0)
            {
                GSImage[i][j] = 85;
            }
        }
    }
}

//_________________________________________
// filter 6: darken or lighten GSImage
void lightAdjustment()
{
    string userInput;
    system("cls");
    userInput = lightAdjustmentInput();
    if (userInput == "1")
    {
        darkenImage();
        system("cls");
        cout << "Darken Image Filter applied successfully" << endl;
    }
    else if (userInput == "2")
    {
        lightenImage();
        system("cls");
        cout << "Lighten Image Filter applied successfully" << endl;
    }
}

// _______________________________________
// filter 7: detect edges in GSImage
void detectImageEdges()
{

    // assigning all pixels of RGBImage2 to white
    for (int row = 0; row < SIZE; row++)
    { // for every row
        for (int col = 0; col < SIZE; col++)
        { // for every column
            GSImage2[row][col] = 255;
        }
    }

    // x direction - for detecting vertical edges
    int xDir[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}};
    // y direction - for detecting horizontal edges
    int yDir[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}};

    // row3x3 and col3x3 correspond to the row and column numbers of a 3x3 "slice" taken from the complete photo matrix,
    // such that their values are either 0, 1 or 2.
    // imageRow and imageCol correspond to the row and column numbers of the complete photo matrix
    for (int imageRow = 1; imageRow <= 254; imageRow++)
    {
        for (int imageCol = 1; imageCol <= 254; imageCol++)
        {
            // for the pixel  RGBImage[imageRow][imageCol]
            int Gx = 0, Gy = 0;
            for (int row3x3 = imageRow - 1; row3x3 <= imageRow + 1; row3x3++)
            {
                for (int col3x3 = imageCol - 1; col3x3 <= imageCol + 1; col3x3++)
                {
                    Gx += GSImage[row3x3][col3x3] * xDir[row3x3 - (imageRow - 1)][col3x3 - (imageCol - 1)];
                    Gy += GSImage[row3x3][col3x3] * yDir[row3x3 - (imageRow - 1)][col3x3 - (imageCol - 1)];
                }
            }
            int gradient = sqrt(pow(Gx, 2) + pow(Gy, 2));
            if (gradient >= 255)
            {
                GSImage2[imageRow][imageCol] = 0;
            }
            else
            {
                GSImage2[imageRow][imageCol] = 255 - gradient;
            }
        }
    }

    // copying contents of RGBImage2 to RGBImage
    for (int imageRow = 0; imageRow < SIZE; imageRow++)
    { // for every RGBImage row
        for (int imageCol = 0; imageCol < SIZE; imageCol++)
        { // for every RGBImage column
            GSImage[imageRow][imageCol] = GSImage2[imageRow][imageCol];
        }
    }
}

//_________________________________________
// filter 8: enlarge GSImage
void enlargeImage()
{
    int row = 0, col = 0, rowBegin, rowEnd, columnBegin, columnEnd;
    string choice;
    unsigned char result[SIZE][SIZE], temp;
    bool validInput = false;

    while (!validInput)
    {
        system("cls");
        cout << "Enlarge:: " << endl
             << endl;
        cout << "1- First quarter" << endl;
        cout << "2- Second quarter" << endl;
        cout << "3- Third quarter" << endl;
        cout << "4- Fourth quarter" << endl
             << endl;
        cout << "choose: ";

        getline(cin, choice);

        if (choice == "1")
        {
            rowBegin = 0;
            columnBegin = 0;
            rowEnd = 128;
            columnEnd = 128;
            validInput = true;
        }
        else if (choice == "2")
        {
            rowBegin = 0;
            rowEnd = 128;
            columnBegin = 128;
            columnEnd = 256;
            validInput = true;
        }
        else if (choice == "3")
        {
            rowBegin = 128;
            rowEnd = 256;
            columnBegin = 0;
            columnEnd = 128;
            validInput = true;
        }
        else if (choice == "4")
        {
            rowBegin = 128;
            rowEnd = 256;
            columnBegin = 128;
            columnEnd = 256;
            validInput = true;
        }
        else
        {
            system("cls");
            cout << "Invalid Input" << endl
                 << endl;
        }
    }

    for (int i = rowBegin; i < rowEnd; i++)
    {
        for (int j = columnBegin; j < columnEnd; j++)
        {
            temp = GSImage[i][j];

            for (int k = 1; k < 5; k++)
            {
                result[row][col] = temp;
                if (k == 2)
                {
                    row++;
                    col--;
                }
                else
                {
                    col++;
                }
            }
            if (col == (SIZE))
            {
                col = 0;
            }
            row--;
        }
        row += 2;
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            GSImage[i][j] = result[i][j];
        }
    }
}
//_________________________________________
// 9-1-shrinking by (1/2)
void shrinkHalf()
{
    // truncate some pixls to shrink
    for (int i = 0; i < SIZE / 2; i++)
    {
        for (int j = 0; j < SIZE / 2; j++)
        {

            GSImage[i][j] = GSImage[i * 2][j * 2];
        }
    }
    // replacing the rest of RGBImage with white
    for (int i = 127; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {

            GSImage[i][j] = 255;
        }
    }
    for (int i = 0; i < SIZE / 2; i++)
    {
        for (int j = 127; j < SIZE; j++)
        {

            GSImage[i][j] = 255;
        }
    }
}
//_________________________________________
// 9-2-shrinking by (1/3)
void shrinkThird()
{
    // truncate some pixls to shrink
    for (int i = 0; i < SIZE / 3; i++)
    {
        for (int j = 0; j < SIZE / 3; j++)
        {

            GSImage[i][j] = GSImage[i * 3][j * 3];
        }
    }
    // replacing the rest of RGBImage with white
    for (int i = 85; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {

            GSImage[i][j] = 255;
        }
    }
    for (int i = 0; i < SIZE / 3; i++)
    {
        for (int j = 85; j < SIZE; j++)
        {

            GSImage[i][j] = 255;
        }
    }
}
//_________________________________________
// 9-3-shrinking by (1/4)
void shrinkQuarter()
{
    // truncate some pixls to shrink
    for (int i = 0; i < SIZE / 4; i++)
    {
        for (int j = 0; j < SIZE / 4; j++)
        {

            GSImage[i][j] = GSImage[i * 4][j * 4];
        }
    }
    // replacing the rest of RGBImage with white
    for (int i = 64; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {

            GSImage[i][j] = 255;
        }
    }
    for (int i = 0; i < SIZE / 4; i++)
    {
        for (int j = 64; j < SIZE; j++)
        {

            GSImage[i][j] = 255;
        }
    }
}
//_________________________________________
// filter 9: shrink GSImage by (1/2), (1/3) or (1/4)
void shrinkImage()
{
    string userInput;
    system("cls");
    userInput = shrinkImageInput();
    if (userInput == "1")
    {
        shrinkHalf();
        system("cls");
        cout << "Shrink Image Filter by (1/2) applied successfully" << endl;
    }
    else if (userInput == "2")
    {
        shrinkThird();
        system("cls");
        cout << "Shrink Image Filter by (1/3) applied successfully" << endl;
    }
    else if (userInput == "3")
    {
        shrinkQuarter();
        system("cls");
        cout << "Shrink Image Filter by (1/4) applied successfully" << endl;
    }
}
//_________________________________________
void leftMirror()
{
    for (int row = 0; row < SIZE; row++)
    { // for every row
        int columnNum = 127;
        int columnNum2 = 128; // columnNum and columnNum2 here correspond to the column numbers
        for (int a = 0; a < SIZE / 2; a++)
        { // 128 iterations
            GSImage[row][columnNum2] = GSImage[row][columnNum];
            columnNum--;
            columnNum2++;
        }
    }
}
//_________________________________________
void rightMirror()
{
    for (int row = 0; row < SIZE; row++)
    { // for every row
        int columnNum = 127;
        int columnNum2 = 128; // columnNum and columnNum2 here correspond to the column numbers
        for (int a = 0; a < SIZE / 2; a++)
        { // 128 iterations
            GSImage[row][columnNum] = GSImage[row][columnNum2];
            columnNum--;
            columnNum2++;
        }
    }
}
//_________________________________________
void upperMirror()
{
    for (int col = 0; col < SIZE; col++)
    { // for every column
        int rowNum = 127;
        int rowNum2 = 128; // rowNum and rowNum2 here correspond to the row numbers
        for (int a = 0; a < SIZE / 2; a++)
        { // 128 iterations
            GSImage[rowNum2][col] = GSImage[rowNum][col];
            rowNum--;
            rowNum2++;
        }
    }
}
//_________________________________________
void lowerMirror()
{
    for (int col = 0; col < SIZE; col++)
    { // for every column
        int rowNum = 127;
        int rowNum2 = 128; // rowNum and rowNum2 here correspond to the row numbers
        for (int a = 0; a < SIZE / 2; a++)
        { // 128 iterations
            GSImage[rowNum][col] = GSImage[rowNum2][col];
            rowNum--;
            rowNum2++;
        }
    }
}

//_________________________________________
// filter a: mirror half GSImage
void mirrorImage()
{
    string mirrorType;
    bool validInput = false;

    while (!validInput)
    {
        system("cls");
        cout << "mirror:: " << endl
             << endl;
        cout << "l- left" << endl;
        cout << "r- right" << endl;
        cout << "u- up" << endl;
        cout << "d- down" << endl
             << endl;
        cout << "choose: ";

        getline(cin, mirrorType);

        if (mirrorType == "l" || mirrorType == "L")
        {
            leftMirror();
            validInput = true;
        }
        else if (mirrorType == "r" || mirrorType == "R")
        {
            rightMirror();
            validInput = true;
        }
        else if (mirrorType == "u" || mirrorType == "U")
        {
            upperMirror();
            validInput = true;
        }
        else if (mirrorType == "d" || mirrorType == "D")
        {
            lowerMirror();
            validInput = true;
        }
        else
        {
            system("cls");
            cout << "Invalid Input" << endl
                 << endl;
        }
    }
}
//_________________________________________
// filter b: shuffle GSImage
void shuffleImage()
{
    int col = 0, row = 0, rowBegin, rowEnd, columnBegin, columnEnd;

    unsigned char result[SIZE][SIZE], x;

    string choice;
    system("cls");
    while (true)
    {
        cout << "Shuffle:: " << endl
             << endl;
        cout << "1- First quarter" << endl;
        cout << "2- Second quarter" << endl;
        cout << "3- Third quarter" << endl;
        cout << "4- Forth quarter" << endl
             << endl;
        cout << "Enter the order you want as a series of the four quarters ex::(4132): ";
        getline(cin, choice);
        if (shuffleImageInput(choice))
        {
            choice = removeSpaces(choice);
            break;
        }
        system("cls");
        cout << "Invalid input please try again." << endl
             << endl;
    }

    for (int order = 0; order < 4; order++)
    {
        switch (choice[order])
        {
        case '1':
            rowBegin = 0;
            columnBegin = 0;
            rowEnd = 128;
            columnEnd = 128;
            break;
        case '2':
            rowBegin = 0;
            rowEnd = 128;
            columnBegin = 128;
            columnEnd = 256;
            break;
        case '3':
            rowBegin = 128;
            rowEnd = 256;
            columnBegin = 0;
            columnEnd = 128;
            break;
        case '4':
            rowBegin = 128;
            rowEnd = 256;
            columnBegin = 128;
            columnEnd = 256;
        default:
            break;
        }

        for (int i = rowBegin; i < rowEnd; i++)
        {
            for (int j = columnBegin; j < columnEnd; j++)
            {
                result[row][col] = GSImage[i][j];
                col++;
            }
            col = ((order % 2) == 0) ? 0 : 128;
            row++;
        }
        row = 0;
        if (order >= 1)
        {
            row = 128;
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            GSImage[i][j] = result[i][j];
        }
    }
}


//_________________________________________
// filter c: blur GSImage
void blurImage()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // add the volue of the box of pixls around the pixle and divide by 9
            GSImage[i][j] = (GSImage[i][j] + GSImage[i + 1][j] + GSImage[i][j + 1] + GSImage[i + 1][j + 1] + GSImage[i][j - 1] + GSImage[i - 1][j] + GSImage[i - 1][j - 1] + GSImage[i - 1][j + 1] + GSImage[i + 1][j - 1]) / 9;
        }
    }
}

//_________________________________________
// save the new GSImage according to the target filename entered by user
void saveImage()
{
    char targetFilename[100];
    system("cls");
    cout << "Please enter the target file name to save: ";
    cin.getline(targetFilename, 100);
    strcat(targetFilename, ".bmp");
    writeGSBMP(targetFilename, GSImage);
}