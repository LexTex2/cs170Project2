#include "featureSearch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <map>

using namespace std;

double oneOutVal(vector<vector<double>>, vector<int>, double);

double nnFinder(vector<vector<double>>, vector<int>, double, int);

int main()  {
    cout << "selecting data set for testing... " << endl;
    string dataSetGiven = "tile2Test.txt";
    ifstream fileCont;
    //CS170_Small_Data__55.txt
    fileCont.open("CS170_Small_Data__55.txt");
    //fileCont.open("tile2Test.txt");
    if (!fileCont.is_open())   {
        cout << "File failed to open" << endl;
    }
    vector<vector<double>> dataSet;
    string dataLine;
    bool firstRunDone = false;

    while (getline(fileCont, dataLine))  {
        stringstream s(dataLine);
        double dataVal;
        vector<double> row;
        while (s >> dataVal)   {
            row.push_back(dataVal);
        }
        firstRunDone = true;
        dataSet.push_back(row);
    }

    fileCont.close();
    int numRows = dataSet.size();
    int numFeatures = dataSet[0].size() - 1;    //number of columns of feater data (not including classification)

    vector<double> classClassifications(numRows);
    vector<vector<double>> featureCreatures(numRows, vector<double>(numFeatures));
    for (int i = 0; i < numRows; ++i) {
        classClassifications[i] = dataSet[i][0]; 
        //cout << dataSet[i][0] << endl;        //----for testing----
        for (int j = 1; j < dataSet[i].size(); ++j) {
            featureCreatures[i][j-1] = dataSet[i][j]; 
            //cout << dataSet[i][j] << endl;        //----for testing----
        }
    }
    //cout << featureCreatures.size() << endl;
    //cout << Y.size() << endl;
    cout << "numFeatures: " << numFeatures << endl;
    cout << "total instances: " << numRows << endl;
    double numFileRows = dataSet.size();

    vector<int> onlyFeatureCreatures(numFeatures);
    for (int i = 0; i < numFeatures; i++) {
        onlyFeatureCreatures[i] = i + 1;
    }
    
    double baseAccuracy = oneOutVal(dataSet, onlyFeatureCreatures, numFileRows);  // Use all features for the first run
    cout << "Running nearest neighbor with all " << numFeatures << " features, using 'leaving-one-out' evaluation, I get an accuracy of " << baseAccuracy * 100 << "%" << endl;

    return 0;
}

double oneOutVal(vector<vector<double>> dataSet, vector<int> onlyFeatureCreatures, double numFileRows)   {
    double match = 0.0;
    double neighVal;
    int rowVal;
    for (int i = 0; i < numFileRows; i++)   {
        rowVal = i;
        neighVal = nnFinder(dataSet, onlyFeatureCreatures, numFileRows, rowVal);
        if (dataSet[neighVal][0] == dataSet[rowVal][0])   {
            match++;
        }
    }
        return (match / numFileRows);
}

double nnFinder(vector<vector<double>> dataSet, vector<int> onlyFeatureCreatures, double numFileRows, int rowVal)   {
    double nnDistance = numeric_limits<int>::max(); //inf;
    double nnLocation = numeric_limits<int>::max(); //inf;
    double euclidDistance = 0.0;
    
    for (int i = 0; i < numFileRows; i++)   {
        if (i != rowVal)   {
            //vector<int> = all_[i];
            for (int j = 1; j < onlyFeatureCreatures.size(); j++)   {   
                // cout << "1" << endl;
                euclidDistance += pow((dataSet[i][onlyFeatureCreatures[j]] - dataSet[rowVal][onlyFeatureCreatures[j]]), 2);
            }
        euclidDistance = sqrt(euclidDistance);
        //cout << euclidDistance << endl;
        }
        if (euclidDistance < nnDistance)  {
        nnDistance = euclidDistance;
        nnLocation = i;
        }
    }
    return nnLocation;
}
 