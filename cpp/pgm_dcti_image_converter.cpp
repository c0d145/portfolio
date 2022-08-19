/*
 * This program reads takes an input and a output filename from the console input and parses the
 * given pgm image. Images have to satisfy the following format:
 * Line 1: format ("P2"), 
 * line 2: comment, 
 * line 3: pixels per line of image (N), 
 * line 4: number of line in image (M).
 * line 5 is the maximum color / gray value.
 *
 * After parsing the image the program calculates the DCTI (Discrete Cosinus Transformation) and
 * afterwards sets a given percentage to 0. After that it calculates the inverse by using the 
 * DCTIII multiplied by (2/N).
 * As last step it writes the resulting "compressed" image into the filename given by the user
 * at the start of the program.
 *
 * Author: c0d145
 * Created: 2022-06-25
 * Updated: 07.07.2022 - Fixed negative values in output with std::abs() and values over 255 are now set to 255.
*/
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> parseImage(string filename, bool talkative)
{
    std::cout << "Reading image file '" << filename << "':"<< std::endl;

    string line;
    ifstream myfile;
    myfile.open(filename);
    if(!myfile.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    int linepos = 1;
    int M = 0;
    int N = 0;
    int color_values = 0;
    string format;
    string comment;
    vector<vector<int>> image;
    vector<int> imageline;

    while(getline(myfile, line)) {
        // Line 1 is the format "P2".
        if (i==0) format = line;
        // Line 2 is a comment line.
        if (i==1) comment = line;
        // Line 3 is the Number N of pixels per (image) line.
        if (i==2) M = stoi(line);
        // Line 4 is number M of lines the image consists of.
        if (i==3) N = stoi(line);
        // Line 5 maximum color value / bit limit.
        if (i==4) color_values = stoi(line);

        // read N pixel in grayscale.
        if(i>4) {
            imageline.push_back(stoi(line));
            if (talkative && linepos != N) std::cout << line << ",";
            if (talkative && linepos == N) std::cout << line << std::endl;
        }

        if (linepos == N) {
            linepos = 0;
            image.push_back(imageline);
            imageline.clear();
        }
        if(i > 4) { linepos++; } else { i++; }
    }
    std::cout << std::endl;
    myfile.close();
    return image;
}

void saveImage (string filename, vector<vector<int>> *image) {
    ofstream fout;
    string line;

    // Open file und overwrite content.
    fout.open(filename);
    // concat the output to file looks like this:
    // fout.open(filename, ios::app);

    // If file was succesfully opend / created than write...
    while (fout) {
        fout << "P2" << std::endl;
        fout << "# Created by DCT2 + DCT3 algorithm program by c0d145." << std::endl;
        fout << "" << image->size() << std::endl;
        fout << "" << image->data()[0].size() << std::endl;
        fout << "255" << std::endl;

        for(int i = 0; i < image->size(); i++)
        {
            for(int j = 0; j < image->data()[0].size(); j++) {
                // As values greater than 255 could appear within the matrix i replac them with 255.
                if (image->data()[i][j] < 255){
                    fout << std::abs(image->data()[i][j]) << std::endl;
                } else {
                    fout << "255" << std::endl;
                }
            }
        }
        break;
    }

    // Close the file.
    fout.close();
}

vector<vector<int>> calcDCTII(vector<vector<int>> *image, bool inverseDCTIII, int compression_rate)
{
    if (inverseDCTIII) {
        std::cout << "Inverse DCT III: " << std::endl;
    } else {
        std::cout << "DCT II: " << std::endl;
    }

    vector<vector<int>> image_compressed;
    static long double pi = 3.1415926535897932384626433832795028841971693993751058209749445923;
    int rows = image->size();
    int columns = image->data()[0].size();

    std::vector<float> vec (columns, 0.0);
    //vector<long double> vec (columns, 0.0);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            for (int n = 0; n < columns; n++)
            {
                //vec[j] += std::round((*image)[i][n] * std::cos(pi/columns * (n + 0.5) * j));
                vec[j] += (*image)[i][n] * std::cos(pi/columns * (n + 0.5) * j);
                //std::cout << "n:" << n << std::endl;
                //std::cout << "i: " << i << ", j: " << j << ", n:" << n << ", vec[" << j << "] = " << vec[j] <<  std::endl;
            }
            //std::cout << "vec[" << j << "]: " << round(vec[j]) << ", ";
            if (j > round((columns / 100.0) * (100.0 - compression_rate)) - 1) {
                vec[j] = 0.0;
            }
            if (inverseDCTIII) {
                vec[j] = round((2.0 / columns) * vec[j]);
                //std::cout << vec[j] << ",";
            } else {
                vec[j] = round(vec[j]);
                std::cout << vec[j] << ",";
            }
        }
        std::cout << std::endl;
        std::vector<int> intVec(vec.begin(), vec.end());
        image_compressed.push_back(intVec);
        fill(vec.begin(), vec.end(), 0.0);
    }
    return image_compressed;
}

vector<vector<int>> calcDCTIII(vector<vector<int>> *image, bool inverseDCTII)
{
    if (inverseDCTII) {
        std::cout << "Inverse DCT II: " << std::endl;
    } else {
        std::cout << "DCT III: " << std::endl;
    }

    vector<vector<int>> image_compressed;
    static long double pi = 3.1415926535897932384626433832795028841971693993751058209749445923;
    int rows = image->size();
    int columns = image->data()[0].size();

    vector<float> vec (columns, 0.0);
    //vector<long double> vec (columns, 0.0);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            vec[j] += round(0.5 * (*image)[i][0]);
            for (int n = 1; n < columns; n++)
            {
                // vec[j] += round((*image)[i][n] * std::cos(pi/columns * n * (j + 0.5)));
                vec[j] += (*image)[i][n] * std::cos(pi/columns * n * (j + 0.5));
            }
            //std::cout << "vec[" << j << "]: " << round(vec[j]) << ", ";
            //std::cout << "vec[" << j << "]: " << round(vec[j]) << ", ";
            if (inverseDCTII) {
                vec[j] = round((2.0 / columns) * vec[j]);
                std::cout << vec[j] << ",";
            } else {
                vec[j] = round(vec[j]);
                std::cout << vec[j] << ",";
            }
        }
        std::cout << std::endl;
        std::vector<int> intVec(vec.begin(), vec.end());
        image_compressed.push_back(intVec);
        fill(vec.begin(), vec.end(), 0.0);
    }
    return image_compressed;
}

void printMatrix(vector<vector<int>> *matrix)
{
    //vector<vector<float>> matrixA = *matrix;
    for(int i = 0; i < matrix->data()[0].size(); i++)
    {
        for(int j = 0; j < matrix->data()[0].size(); j++)
        {
            std::cout << matrix->data()[i][j];
            if(j < matrix->data()[0].size()-1)
            {
                std::cout << ",";
            }
        }
        std::cout << std::endl;
    }
}

/*
 * Function which converts comma sperated strings to a float vector.
 */
vector<float> parseFloats(string str)
{
    stringstream ss(str);
    vector<float> floats;
    char ch;
    float value;
    while(ss >> value >> ch) {
        floats.push_back(value);
    }
    ss >> value;
    floats.push_back(value);
    return floats;
}

// Reads file names for in- and output from stdin.
vector<string> readFilenames() {
    vector<string> filenames;
    std::cout << "Name of input image:";
    string line;
    cin >> line;
    filenames.push_back(line);
    std::cout << "name of output image:";
    cin >> line;
    filenames.push_back(line);

    return filenames;
}

int main() {
    bool talkative = false;
    // If true then data will be read from the files provided through console input
    // otherwise a test vector / image will be used.
    bool interactive = true;
    // string whichExample = "example1";
    vector<vector<int>> image1;
    vector<vector<int>> image2;
    vector<vector<int>> testimage;

	// Test vector / image for testing DCTII calculation.
    vector<int> row1{ 1, 51, 101, 151, 201, 151, 101, 51 };
    // Expectated output.
    // Output DCTII: 808, −181, −446, 63, , 0, −42, −31, 36
    testimage.push_back(row1);

    if (interactive)
    {
        vector<string> filenames = readFilenames();
        image1 = parseImage(filenames[0], talkative);
        vector<vector<int>> image_DT2 = calcDCTII(&image1,false, 80);
        vector<vector<int>> image_compressed = calcDCTIII(&image_DT2,true);
        saveImage(filenames[1], &image_compressed);
    } else {
        vector<vector<int>> image_DT2;
        vector<vector<int>> image_compressed;

        image1 = parseImage("football.pgm", talkative);
        image_DT2 = calcDCTII(&image1,false, 80);
        image_compressed = calcDCTIII(&image_DT2,true);
        saveImage("football-k.pgm", &image_compressed);

        image2 = parseImage("liverleaf.pgm", talkative);
        image_DT2 = calcDCTII(&image2,false, 80);
        image_compressed = calcDCTIII(&image_DT2,true);
        saveImage("liverleaf-k.pgm", &image_compressed);
    }

    //vector<vector<int>> image_DT2 = calcDCTII(&image1,false, 80);
    //vector<vector<int>> image_compressed = calcDCTII(&image_DT2,true, 0);
    vector<vector<int>> vec_DCT2 = calcDCTII(&testimage, false, 0);
    //calcDCTII(&testimage, true, 80);
    //calcDCTIII(&testimage,false);
    calcDCTIII(&vec_DCT2,true);

    //printMatrix(&image_compressed);
    //calcDCTIII(&image_compressed,true);

    testimage.clear();
    //vector<int> row2{ 808, -181, -446, 63, 0, 0, 0, 0 };
    //testimage.push_back(row2);
    //calcDCTIII(&testimage,false);

    //saveImage("football-k.pgm", &image_compressed);

    return 0;
}
