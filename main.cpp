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

//void forwardSelectionAlgo(vector<vector<double>>, int, int);
double returnAccuracy(vector<vector<double>>, vector<int>, int);    //will be used 2 determine accuracy/testing

int main()  {
    cout << "selecting data set for testing... " << endl;
    ifstream fileCont;
    //fileCont.open("CS170_Small_Data__55.txt");
    //fileCont.open("CS170_Large_Data__17.txt");
    fileCont.open("CS170_Large_Data__12.txt");
    if (!fileCont.is_open())   {
        cout << "File failed to open" << endl;
    }
    vector<vector<double>> dataSet;
    string dataLine;
    bool firstRunDone = false;
    int numColAct = -1;

    while (getline(fileCont, dataLine))  {
        stringstream s(dataLine);
        double dataVal;
        vector<double> row;
        while (s >> dataVal)   {
            if (!firstRunDone)   {
                numColAct++;
            }
            row.push_back(dataVal);
        }
        firstRunDone = true;
        dataSet.push_back(row);
    }

    fileCont.close();
    int numFileRows = dataSet.size();

    vector<double> classClassifications(numFileRows);
    vector<vector<double>> featureCreatures(numFileRows, vector<double>(numColAct));

    vector<int> onlyFeatureCreatures = {26, 38};    //row numbers - 26, 38    18, 40
    //onlyFeatureCreaturs.push_back(26);
    // for (int i = 0; i < numColAct; i++) {
    //     onlyFeatureCreatures[i] = i + 1;
    // }
    cout << onlyFeatureCreatures.size() << endl;
    int newFeat = 0; // - 38

    double baseAccuracy = returnAccuracy(dataSet, onlyFeatureCreatures, newFeat);  // Use all features for the first run
    cout << "nearest neighbor w/: " << numColAct << " total features, 'leaving-one-out' gives accuracy: " << baseAccuracy * 100 << "%" << endl;

    // cout << "Enter '1' to run forward Selection Algorithm: " << endl;
    // int userChoice;
    // cin >> userChoice;
    // cout << endl;
    // if (userChoice == 1)   {
    //     forwardSelectionAlgo(dataSet, numFeatures, numFileRows);

    // }

    return 0;
}

double returnAccuracy(vector<vector<double>> dataSet, vector<int> onlyFeatureCreatures, int newFeat)   {                                                   
    //used 2 determine accuracy/testing  
    //heavily references pseudo/matlab code given by professor Eamonn Keogh that was provided in video                                                                                       
    double match = 0.0;
    if (newFeat != 0)   {                                           //mainly here for testing, should prolly take out l8tr
        onlyFeatureCreatures.push_back(newFeat);
    }

    for (int i = 0; i < dataSet.size(); i++)   {                    
        vector<double> neighVal;
        int neighLabel = dataSet[i][0]; 
        for (int t : onlyFeatureCreatures)   {                      //comparison point(s) for distance check l8tr
            neighVal.push_back(dataSet[i][t]);
        }

        double nnDistance = numeric_limits<double>::infinity();     //had to make double type
        int nnLocation = numeric_limits<int>::max();
        int nnLabel = 0;                                            //for keeping trak of label of nn
    
        for (int j = 0; j < dataSet.size(); j++)   {
            if (j != i)   {  
                vector<double> nn;
                double euclidDistance = 0.0;
                for (int k : onlyFeatureCreatures)   {              //compare data across feature to find nn in euclidDist
                    nn.push_back(dataSet[j][k]);
                }
                for (int q = 0; q < neighVal.size(); q++) {
                    euclidDistance += pow(neighVal[q] - nn[q], 2);        //euclidDist finder
                }
                euclidDistance = sqrt(euclidDistance);
                if (euclidDistance < nnDistance)   {
                    nnDistance = euclidDistance;
                    nnLocation = j;
                    nnLabel = dataSet[nnLocation][0]; 
                }
            }
        }
        if (neighLabel == nnLabel)   {
            match++;
        }
    }
    return (match / dataSet.size());           //accuracy given as 0.XXX cuz why not
}
