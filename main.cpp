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

void forwardSelectionAlgo(vector<vector<double>>, int);

void backwardEliminationAlgo(vector<vector<double>>, int);

double returnAccuracy(vector<vector<double>>, vector<int>, int);    //used 2 determine accuracy/testing

int main()  {
    cout << "Welcome to Alexis Stephens' Feature Selection Algorithm." << endl;
    cout << "Type in the name of the file to test: ";
    string fileName;
    cin >> fileName;
    cout << endl;
    ifstream fileCont;
    fileCont.open(fileName);
    //fileCont.open("CS170_Small_Data__55.txt");
    //fileCont.open("CS170_Large_Data__55.txt");
    //fileCont.open("CS170_Large_Data__12.txt");
    if (!fileCont.is_open())   {
        cout << "File failed to open" << endl;
    }
    vector<vector<double>> dataSet;
    string dataLine;
    bool firstRunDone = false;
    int numColAct = -1;

    while (getline(fileCont, dataLine))   {          //file openned/data pushed into vector fro use + # of features!
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

    vector<int> onlyFeatureCreatures; // = {26, 38};    //row numbers - 26, 38    18, 40        //int newFeat = 0; // - 38   <-- used for testing

    cout << "Type the number of the algorithm you want to run." << endl;
    cout << "1) Forward Selection\n" << "2) Backward Elimination\n";
    int userChoice;
    cin >> userChoice;
    cout << endl;
    cout << "This dataset has " << numColAct << " features (not including the class attribute), with " << dataSet.size() << " instances.\n";
    cout << "Running nearest neighbor with all " << numColAct << " features, using \"leaving-one-out\" evaluation, I get an accuracy of ";
    double firstAcc = returnAccuracy(dataSet, onlyFeatureCreatures, 0);
    cout << firstAcc * 100 << '%' << endl;
    cout << endl;
    cout << "Beginning search.\n";
    if (userChoice == 1)   {
        forwardSelectionAlgo(dataSet, numColAct);
    }
    else if (userChoice == 2)   {
        backwardEliminationAlgo(dataSet, numColAct);
    }
    else   {
        cout << "not valid search option, try again\n";
    }
    return 0;
}

void forwardSelectionAlgo(vector<vector<double>>dataSet, int numCol)   {
    vector<int> endFeatures, featuresCurr;
    double bestAccuracy = 0.0;

    for (int i = 1; i < numCol + 1; i++)   {
        double singleLVLAcc = 0;
        int singleLVLFeature = 0;
        for (int k = 1; k < numCol + 1; k++)   {        //checking if feature is here already
            bool found = false;
            for (int t : featuresCurr)   {
                if (t == k)   {
                    found = true;
                    break;
                }
            }
            if (!found)   {
                double featureAccuracy = returnAccuracy(dataSet, featuresCurr, k);     //k being the feature/cloumn we gotta iterate through
                vector<int> viewFeatures = featuresCurr;
                viewFeatures.push_back(k);
                int printCount = featuresCurr.size() - 1;
                if (featuresCurr.size() != 0)   {
                    cout << "\tUsing feature(s) {";
                    for (int q : featuresCurr)   {
                        if (printCount == 0)   {
                            cout << q << "} ";
                        }
                        else   {
                            cout << q << ",";
                        }
                        printCount--;
                    }
                    cout << "accuracy is " << featureAccuracy * 100 << "%" << endl;
                }
                if (singleLVLAcc < featureAccuracy)   {
                    singleLVLAcc = featureAccuracy;
                    singleLVLFeature = k;
                }
            }
        }
        cout << endl;
        featuresCurr.push_back(singleLVLFeature);               //saving feature for print/in process of finding best Acc, and to note loss of best
        if (featuresCurr.size() != 0)   {
            cout << "Feature set {";
            //bool start = false;
            int printCnt = featuresCurr.size() - 1;

            for (int y : featuresCurr)   {
                if (printCnt == 0)   {
                    cout << y << "} ";
                }
                else   {
                    cout << y << ",";
                }
                printCnt--;
            }
            cout << "was best, accuracy is " << singleLVLAcc * 100 << "%" << endl;
        if (singleLVLAcc > bestAccuracy)   {
            bestAccuracy = singleLVLAcc;
            endFeatures = featuresCurr;
        }
        if (singleLVLAcc < bestAccuracy)   {
            if (featuresCurr.size() != numCol)   {
                cout << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)" << endl;
            }
        }
        cout << endl;
        }
    }
    cout << "Finished search!! The best feature subset is {";       //add  \n to start of FINISH
    int out = endFeatures.size() - 1;
    for (int r : endFeatures)   {
        if (out == 0)   {
            cout << r << "} ";
        }
        else   {
            cout << r << ",";
        }
        out--;
    }
    cout << "which has an accuracy of " << bestAccuracy * 100 << "%" << endl;
}

void backwardEliminationAlgo(vector<vector<double>>dataSet, int numCol)   {
    //inverted version of Feature search, with delete/erase function
    vector<int> fullFeature(numCol);

    for (int i = 0; i < numCol; i++)   {                                    //should b filling vector with feature values only
        fullFeature[i] = i + 1;  
    }

    double bestAccuracy = returnAccuracy(dataSet, fullFeature, 0);         //initial accuracy, could be passed in for better runtime, but eh
    vector<int> featuresCurr = fullFeature;
    for (int i = 0; i < numCol; i++)   {
        double singleLVLAcc = 0.0;
        int singLVLBadFeat = numeric_limits<int>::max();

        for (int k = 0; k < featuresCurr.size(); k++)   {
            int yoinkedFeature = featuresCurr[k];
            featuresCurr.erase(featuresCurr.begin() + k);                           //yoink k/feature from set

            double accuracy = returnAccuracy(dataSet, featuresCurr, 0);             //find new accuracy
            if (featuresCurr.size() != 0)   {
            cout << "\tUsing feature(s) {";
            int printCount = featuresCurr.size() - 1;
            for (int q : featuresCurr)   {
                if (printCount == 0)   {
                    cout << q << "} ";
                }
                else   {
                    cout << q << ",";
                }
                printCount--;
            }
            cout << "accuracy is " << accuracy * 100 << "%" << endl;
        }
            featuresCurr.insert(featuresCurr.begin() + k, yoinkedFeature);      //keeping track of deleted bit (yoinkedFeature from above), saving prev incase good
            if (accuracy > singleLVLAcc)   {
                singleLVLAcc = accuracy;
                singLVLBadFeat = yoinkedFeature;
            }
        }
        cout << endl;

        if (singLVLBadFeat != numeric_limits<int>::max())   {
            featuresCurr.erase(remove(featuresCurr.begin(), featuresCurr.end(), singLVLBadFeat), featuresCurr.end());
            cout << "Removing feature {" << singLVLBadFeat << "} from feature set was best, accuracy is " << singleLVLAcc * 100 << "%" << endl;
        }
        if (bestAccuracy < singleLVLAcc)   {
            bestAccuracy = singleLVLAcc;
            fullFeature = featuresCurr;
        } else if (bestAccuracy > singleLVLAcc)   {
            if (featuresCurr.size() > 0)   {
                cout << "(Warning, accuracy has decreased! Continuing search in case of local maxima)" << endl;
            }
        }
    }
    cout << "\nFinished search!! The best feature subset is {";
    int out = fullFeature.size() - 1;
    for (int r : fullFeature)   {
        if (out == 0)   {
            cout << r << "} ";
        }
        else   {
            cout << r << ",";
        }
        out--;
    }
    cout << "with an accuracy of " << bestAccuracy * 100 << "%" << endl;
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
                for (int q = 0; q < neighVal.size(); q++)   {
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
