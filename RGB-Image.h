#ifndef RGB_IMAGE_H
#define RGB_IMAGE_H

#endif //RGB_IMAGE_H

#include "bmplib.h"
#include "utility.h

// note: SIZE is declared in bmplib.h as 256
// note: RGB = red, green, blue
using namespace std;

//Global Variables
unsigned char RGBImage[SIZE][SIZE][RGB];
unsigned char RGBImage2[SIZE][SIZE][RGB];
unsigned char RGBImageToGS[SIZE][SIZE];


//function prototypes
bool loadImageRGB();
void RGBToGS();
void RGBToBlackAndWhite();
void invertImageRGB();
void RGBList();
void mergeTwoImagesRGB();
void flipVerticalRGB();
void flipHorizontalRGB();
void flipImageRGB();
void rotateImageRGB();
void darkenImageRGB();
void lightenImageRGB();
void lightAdjustmentRGB();
void detectImageEdgesRGB();
void detectImageEdges();
void enlargeImageRGB();
void shrinkHalfRGB();
void shrinkThirdRGB();
void shrinkQuarterRGB();
void shrinkImageRGB();
void leftMirrorRGB();
void rightMirrorRGB();
void upperMirrorRGB();
void lowerMirrorRGB();
void mirrorImageRGB();
void shuffleImageRGB();
void blurImageRGB();
void saveImageRGB();


//_________________________________________
void RGBList()
{
    string userInput;
    system("cls");
    if (!loadImageRGB())
    {
        while (true)
        {

            printMenu();
            userInput = listInput();

            if (userInput == "1")
            {
                RGBToBlackAndWhite();
                system("cls");
                cout << "Black and white Filter applied successfully" << endl;
                ;
            }
            else if (userInput == "2")
            {
                invertImageRGB();
                system("cls");
                cout << "Invert Image Filter applied successfully" << endl;
            }
            else if (userInput == "3")
            {
                mergeTwoImagesRGB();
                system("cls");
                cout << "Merge Filter applied successfully" << endl;
            }
            else if (userInput == "4")
            {
                flipImageRGB();
                system("cls");
                cout << "Flip Image Filter applied successfully" << endl;
            }
            else if (userInput == "5")
            {
                rotateImageRGB();
                system("cls");
                cout << "Rotate Image Filter applied successfully" << endl;
            }
            else if (userInput == "6")
            {
                lightAdjustmentRGB();
            }
            else if (userInput == "7")
            {
                detectImageEdgesRGB();
                system("cls");
                cout << "Detect Image Edges Filter applied successfully" << endl;
            }
            else if (userInput == "8")
            {
                enlargeImageRGB();
                system("cls");
                cout << "Enlarge Image Filter applied successfully" << endl;
            }
            else if (userInput == "9")
            {
                shrinkImageRGB();
            }
            else if (userInput == "a" || userInput == "A")
            {
                mirrorImageRGB();
                system("cls");
                cout << "Mirror half RGBImage Filter applied successfully" << endl;
            }
            else if (userInput == "b" || userInput == "B")
            {
                shuffleImageRGB();
                system("cls");
                cout << "Shuffle Image Filter applied successfully" << endl;
            }
            else if (userInput == "c" || userInput == "C")
            {
                blurImageRGB();
                system("cls");
                cout << "Blur Image Filter applied successfully" << endl;
            }
            else if (userInput == "s" || userInput == "S")
            {
                saveImageRGB();
                system("cls");
                cout << "photo saved successfully" << endl;
                break;
            }
        }
    }
}

//_________________________________________
// load the RGBImage file requested by the user
bool loadImageRGB()
{
    char imageFilename[100];
    cout << "Please enter the source RGBImage file name: ";
    cin.getline(imageFilename, 100);
    strcat(imageFilename, ".bmp");
    return readRGBBMP(imageFilename, RGBImage);
}
// _________________
// converts the RGB source RGBImage into a grayscale(GS) RGBImage using the weighted method
void RGBToGS()
{
    double GSlevel;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            GSlevel = double(0.299) * RGBImage[i][j][0] + double(0.587) * RGBImage[i][j][1] +
                      double(0.114) * RGBImage[i][j][2];
            RGBImageToGS[i][j] = GSlevel;
        }
    }
}

//_________________________________________
// filter 1 - converts the RGB source RGBImage into a black and white RGBImage
void RGBToBlackAndWhite()
{
    RGBToGS();
    // calculating average number of greyscale intensity in all pixels
    int sumOfGreyscale = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            sumOfGreyscale += RGBImageToGS[i][j];
        }
    }
    int averageGreyscale = sumOfGreyscale / (SIZE * SIZE);

    /* converting each pixel to black or white depending on the comparison of
     * the pixels greyscale intensity number to the average greyscale intensity number */
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (RGBImageToGS[i][j] >= averageGreyscale)
            {
                RGBImageToGS[i][j] = 255;
            }
            else
            {
                RGBImageToGS[i][j] = 0;
            }
        }
    }

    // copying contents of GSImage to RGB RGBImage

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                RGBImage[i][j][k] = RGBImageToGS[i][j];
            }
        }
    }
}

//__________________________________________
// filter 2 - inverts the RGB source RGBImage
void invertImageRGB()
{
    for (int k = 0; k < RGB; k++)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                RGBImage[i][j][k] = 255 - RGBImage[i][j][k];
            }
        }
    }
}
//_________________________________________
// filter 3 - merges the RGB source RGBImage with another RGBImage
void mergeTwoImagesRGB()
{
    // Second RGBImage
    char imageFileName2[100];

    // Get RGBImage file name
    system("cls");

    while (true)
    {
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
                    for (int k = 0; k < RGB; k++)
                    {
                        if (i % 2 == 0 || j % 2 == 0)
                        {
                            RGBImage[i][j][k] = RGBImage2[i][j][k];
                        }
                    }
                }
            }

            // Rest of your code...

            break; // Exit the loop after successful merge
        }
        else
        {
            system("cls");
            cout << "File doesn't exist." << endl << endl;
        }
    }
}

//_________________________________________
void flipVerticalRGB()
{
    for (int col = 0; col < SIZE; col++)
    { // for every column
        int y = 127;
        int z = 128; // y and z here correspond to the row numbers
        for (int a = 0; a < SIZE / 2; a++)
        { // 128 iterations
            for (int k = 0; k < 3; k++)
            {
                unsigned char tempPixel = RGBImage[y][col][k];
                RGBImage[y][col][k] = RGBImage[z][col][k];
                RGBImage[z][col][k] = tempPixel;
            }
            y--;
            z++;
        }
    }
}
//_________________________________________
void flipHorizontalRGB()
{
    for (int row = 0; row < SIZE; row++)
    { // for every row
        int y = 127;
        int z = 128; // y and z here correspond to the column numbers
        for (int a = 0; a < SIZE / 2; a++)
        { // 128 iterations
            for (int k = 0; k < 3; k++)
            {
                unsigned char tempPixel = RGBImage[row][y][k];
                RGBImage[row][y][k] = RGBImage[row][z][k];
                RGBImage[row][z][k] = tempPixel;
            }
            y--;
            z++;
        }
    }
}
//_________________________________________
// filter 4 flip RGBImage horizontally or vertically
void flipImageRGB()
{
    string flipType;
    system("cls");

    while (true)
    {
        cout << "Flip type::" << endl << endl;
        cout << "1- (v)ertical." << endl;
        cout << "2- (h)orizontal" << endl << endl;
        cout << "choose: ";

        getline(cin, flipType);

        if (flipType == "v" || flipType == "V")
        {
            flipVerticalRGB();
            break; // Exit the loop after a valid choice
        }
        else if (flipType == "h" || flipType == "H")
        {
            flipHorizontalRGB();
            break; // Exit the loop after a valid choice
        }
        else
        {
            system("cls");
            cout << "Invalid Input" << endl << endl;
        }
    }
}

//_________________________________________
// filter 5 rotate RGBImage 90, 180 or 270 degrees clockwise
void rotateImageRGB()
{
    string choice;
    char edited[SIZE][SIZE][RGB];
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
                for (int k = 0; k < RGB; k++)
                {
                    for (int i = 0; i < SIZE; i++)
                    {
                        for (int j = 0; j < SIZE; j++)
                        {
                            edited[j][255 - i][k] = RGBImage[i][j][k];
                        }
                    }
                }

                for (int k = 0; k < RGB; k++)
                {
                    for (int i = 0; i < SIZE; i++)
                    {
                        for (int j = 0; j < SIZE; j++)
                        {
                            RGBImage[i][j][k] = edited[i][j][k];
                        }
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
// 6-1-Darken function
void darkenImageRGB()
{
    // looping over the pixels
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                // subtracting values to darken
                if (RGBImage[i][j][k] >= 85)
                {
                    RGBImage[i][j][k] -= 85;
                }
                else if (RGBImage[i][j][k] < 85)
                {
                    RGBImage[i][j][k] = 0;
                }
            }
        }
    }
}

//_________________________________________
// 6-2-lighten function
void lightenImageRGB()
{
    // looping over the pixels
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                // adding values to lighten
                if (RGBImage[i][j][k] <= 170 && RGBImage[i][j][k] > 0)
                {
                    RGBImage[i][j][k] += 85;
                }

                else if (RGBImage[i][j][k] > 170)
                {
                    RGBImage[i][j][k] = 255;
                }
                else if (RGBImage[i][j][k] == 0)
                {
                    RGBImage[i][j][k] = 85;
                }
            }
        }
    }
}

//_________________________________________
// filter 6 - darken or lighten the RGBImage
void lightAdjustmentRGB()
{
    string userInput;
    system("cls");
    userInput = lightAdjustmentInput();
    if (userInput == "1")
    {
        darkenImageRGB();
        system("cls");
        cout << "Darken Image Filter applied successfully" << endl;
    }
    else if (userInput == "2")
    {
        lightenImageRGB();
        system("cls");
        cout << "Lighten Image Filter applied successfully" << endl;
    }
}

//_________________________________________
// filter 7 - detects the edges of the RGBImage
void detectImageEdgesRGB()
{
    RGBToGS();

    // assigning all pixels of RGBImage2 to white
    for (int row = 0; row < SIZE; row++)
    { // for every row
        for (int col = 0; col < SIZE; col++)
        { // for every column
            RGBImage2[row][col][0] = 255;
            RGBImage2[row][col][1] = 255;
            RGBImage2[row][col][2] = 255;
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
                    Gx += RGBImageToGS[row3x3][col3x3] * xDir[row3x3 - (imageRow - 1)][col3x3 - (imageCol - 1)];
                    Gy += RGBImageToGS[row3x3][col3x3] * yDir[row3x3 - (imageRow - 1)][col3x3 - (imageCol - 1)];
                }
            }
            int gradient = sqrt(pow(Gx, 2) + pow(Gy, 2));
            if (gradient >= 255)
            {
                RGBImage2[imageRow][imageCol][0] = 0;
                RGBImage2[imageRow][imageCol][1] = 0;
                RGBImage2[imageRow][imageCol][2] = 0;
            }
            else
            {
                RGBImage2[imageRow][imageCol][0] = 255 - gradient;
                RGBImage2[imageRow][imageCol][1] = 255 - gradient;
                RGBImage2[imageRow][imageCol][2] = 255 - gradient;
            }
        }
    }

    // copying contents of RGBImage2 to RGBImage
    for (int imageRow = 0; imageRow < SIZE; imageRow++)
    { // for every RGBImage row
        for (int imageCol = 0; imageCol < SIZE; imageCol++)
        { // for every RGBImage column
            RGBImage[imageRow][imageCol][0] = RGBImage2[imageRow][imageCol][0];
            RGBImage[imageRow][imageCol][1] = RGBImage2[imageRow][imageCol][1];
            RGBImage[imageRow][imageCol][2] = RGBImage2[imageRow][imageCol][2];
        }
    }
}
//_________________________________________
//filter 8 - enlarge the RGBImage
void enlargeImageRGB()
{
    int rowBegin, rowEnd, columnBegin, columnEnd;

    string choice;

    char result[SIZE][SIZE][RGB], temp;
    system("cls");

    while (true)
    {
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
        }
        else if (choice == "2")
        {
            rowBegin = 0;
            rowEnd = 128;
            columnBegin = 128;
            columnEnd = 256;
        }
        else if (choice == "3")
        {
            rowBegin = 128;
            rowEnd = 256;
            columnBegin = 0;
            columnEnd = 128;
        }
        else if (choice == "4")
        {
            rowBegin = 128;
            rowEnd = 256;
            columnBegin = 128;
            columnEnd = 256;
        }
        else
        {
            system("cls");
            cout << "Invalid Input" << endl
                 << endl;
            continue; // Continue the loop if the input is invalid
        }

        // Rest of your code for image enlargement...

        break; // Exit the loop after processing the user's choice
    }
}
//_________________________________________
// 9-1-shrinking by (1/2)
void shrinkHalfRGB()
{
    // truncate some pixls to shrink
    for (int i = 0; i < SIZE / 2; i++)
    {
        for (int j = 0; j < SIZE / 2; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                RGBImage[i][j][k] = RGBImage[i * 2][j * 2][k];
            }
        }
    }
    // replacing the rest of RGBImage with white
    for (int i = 127; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                RGBImage[i][j][k] = 255;
            }
        }
    }
    for (int i = 0; i < SIZE / 2; i++)
    {
        for (int j = 127; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {

                RGBImage[i][j][k] = 255;
            }
        }
    }
}
//_________________________________________
// 9-2-shrinking by (1/3)
void shrinkThirdRGB()
{
    // truncate some pixls to shrink
    for (int i = 0; i < SIZE / 3; i++)
    {
        for (int j = 0; j < SIZE / 3; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                RGBImage[i][j][k] = RGBImage[i * 3][j * 3][k];
            }
        }
    }
    // replacing the rest of RGBImage with white
    for (int i = 85; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                RGBImage[i][j][k] = 255;
            }
        }
    }
    for (int i = 0; i < SIZE / 3; i++)
    {
        for (int j = 85; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {

                RGBImage[i][j][k] = 255;
            }
        }
    }
}
//_________________________________________
// 9-3-shrinking by (1/4)
void shrinkQuarterRGB()
{
    // truncate some pixls to shrink
    for (int i = 0; i < SIZE / 4; i++)
    {
        for (int j = 0; j < SIZE / 4; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                RGBImage[i][j][k] = RGBImage[i * 4][j * 4][k];
            }
        }
    }
    // replacing the rest of RGBImage with white
    for (int i = 64; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                RGBImage[i][j][k] = 255;
            }
        }
    }
    for (int i = 0; i < SIZE / 4; i++)
    {
        for (int j = 64; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {

                RGBImage[i][j][k] = 255;
            }
        }
    }
}
//_________________________________________
// filter 9 - shrink the RGBImage
void shrinkImageRGB()
{
    string userInput;
    system("cls");
    userInput = shrinkImageInput();
    if (userInput == "1")
    {
        shrinkHalfRGB();
        system("cls");
        cout << "Shrink Image Filter by (1/2) applied successfully" << endl;
    }
    else if (userInput == "2")
    {
        shrinkThirdRGB();
        system("cls");
        cout << "Shrink Image Filter by (1/3) applied successfully" << endl;
    }
    else if (userInput == "3")
    {
        shrinkQuarterRGB();
        system("cls");
        cout << "Shrink Image Filter by (1/4) applied successfully" << endl;
    }
}
//_________________________________________
void leftMirrorRGB()
{
    for (int row = 0; row < SIZE; row++)
    { // for every row
        int columnNum = 127;
        int columnNum2 = 128; // columnNum and columnNum2 here correspond to the column numbers
        for (int a = 0; a < SIZE / 2; a++)
        { // 128 iterations
            for (int k = 0; k < 3; k++)
            {
                RGBImage[row][columnNum2][k] = RGBImage[row][columnNum][k];
            }
            columnNum--;
            columnNum2++;
        }
    }
}
//_________________________________________
void rightMirrorRGB()
{
    for (int row = 0; row < SIZE; row++)
    { // for every row
        int columnNum = 127;
        int columnNum2 = 128; // columnNum and columnNum2 here correspond to the column numbers
        for (int a = 0; a < SIZE / 2; a++)
        { // 128 iterations
            for (int k = 0; k < 3; k++)
            {
                RGBImage[row][columnNum][k] = RGBImage[row][columnNum2][k];
            }
            columnNum--;
            columnNum2++;
        }
    }
}
//_________________________________________
void upperMirrorRGB()
{
    for (int col = 0; col < SIZE; col++)
    { // for every column
        int rowNum = 127;
        int rowNum2 = 128; // rowNum and rowNum2 here correspond to the row numbers
        for (int a = 0; a < SIZE / 2; a++)
        { // 128 iterations
            for (int k = 0; k < 3; k++)
            {
                RGBImage[rowNum2][col][k] = RGBImage[rowNum][col][k];
            }
            rowNum--;
            rowNum2++;
        }
    }
}
//_________________________________________
void lowerMirrorRGB()
{
    for (int col = 0; col < SIZE; col++)
    { // for every column
        int rowNum = 127;
        int rowNum2 = 128; // rowNum and rowNum2 here correspond to the row numbers
        for (int a = 0; a < SIZE / 2; a++)
        { // 128 iterations
            for (int k = 0; k < 3; k++)
            {
                RGBImage[rowNum][col][k] = RGBImage[rowNum2][col][k];
            }
            rowNum--;
            rowNum2++;
        }
    }
}

//_________________________________________
// filter a - mirror half RGBImage
void mirrorImageRGB()
{
    string mirrorType;
    system("cls");

    while (true)
    {
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
            leftMirrorRGB();
            break; // Exit the loop after calling leftMirrorRGB()
        }
        else if (mirrorType == "r" || mirrorType == "R")
        {
            rightMirrorRGB();
            break; // Exit the loop after calling rightMirrorRGB()
        }
        else if (mirrorType == "u" || mirrorType == "U")
        {
            upperMirrorRGB();
            break; // Exit the loop after calling upperMirrorRGB()
        }
        else if (mirrorType == "d" || mirrorType == "D")
        {
            lowerMirrorRGB();
            break; // Exit the loop after calling lowerMirrorRGB()
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
// filter b - shuffle the RGBImage
void shuffleImageRGB()
{
    int col = 0, row = 0, rowBegin, rowEnd, columnBegin, columnEnd;

    char result[SIZE][SIZE][RGB], x;

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
            break;
        default:
            break;
        }
        for (int i = rowBegin; i < rowEnd; i++)
        {
            for (int j = columnBegin; j < columnEnd; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    result[row][col][k] = RGBImage[i][j][k];
                }
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
    for (int k = 0; k < RGB; k++)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                RGBImage[i][j][k] = result[i][j][k];
            }
        }
    }
}
//_________________________________________
// filter c - blur the RGBImage
void blurImageRGB()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                // add the volue of the box of pixls around the pixle and divide by 9
                RGBImage[i][j][k] = (RGBImage[i][j][k] + RGBImage[i + 1][j][k] + RGBImage[i][j + 1][k] + RGBImage[i + 1][j + 1][k] + RGBImage[i][j - 1][k] + RGBImage[i - 1][j][k] + RGBImage[i - 1][j - 1][k] + RGBImage[i - 1][j + 1][k] + RGBImage[i + 1][j - 1][k]) / 9;
            }
        }
    }
}
//_________________________________________
// save the new RGBImage according to the target filename entered by user
void saveImageRGB()
{
    char targetFilename[100];
    system("cls");
    cout << "Please enter the target file name to save: ";
    cin.getline(targetFilename, 100);
    strcat(targetFilename, ".bmp");
    writeRGBBMP(targetFilename, RGBImage);
}