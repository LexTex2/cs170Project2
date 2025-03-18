#include "featureSearch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;



int main()  {


    cout << "selecting data set for testing... " << endl;
    string dataSetGiven = "tile2Test.txt";
    ifstream fileCont;
    //CS170_Small_Data__55.txt
    //fileCont.open("CS170_Small_Data__55.txt");
    fileCont.open("tile2Test.txt");
    if (!fileCont.is_open())   {
        cout << "File failed to open" << endl;
    }
    vector<vector<double>> dataSet;
    string dataLine;

    while (getline(fileCont, dataLine))  {
        stringstream s(dataLine);
        double dataVal;
        vector<double> row;
        while (s >> dataVal)   {
            row.push_back(dataVal);
            cout << dataVal << endl;
        }
        dataSet.push_back(row);
    }

    fileCont.close();
    int vectorSize = dataSet.size();
    cout << vectorSize << endl;

    // string fileContent((istreambuf_iterator<char>(fileCont)),
    //                    istreambuf_iterator<char>());

    // Close the file (optional here since the file will be
    // closed automatically when file goes out of scope)
    // fileCont.close();

    // // Output the file content to the console
    // cout << "File content:\n" << fileContent << endl;
    // cout << "finished opening/loading data Set successfully" << endl;
    



    return 0;
}



/*
        --------------------------- pseudo code provided by professor Eamonn Keogh



    funtion accuracy = leave_one_out_cross_validation( data, current_set, feature_to_add)   {
    accuracy = rand;

}




function feature_search_demo(data)   {
    current_set_of_features = [];

    for int i = 1; i < size(data,2)-1; i++)   {
        disp(['On the ', num2str(i),'th level of the search tree'])
        feature_to_add_at_this_level = [];
        best_so_far_accuracy = 0;
        for k = 1: size(data,2)-1
            if isempty(intersect(current_set_of_features,k))
                disp(['--considering adding the ', num2str(k), ' feature'])
                accuracy = leave_one_out_cross_validation(data, current_set_of_features, k+1);
                
                if accuracy > best_so_far_accuracy
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level = k;

        disp(['On level ', num2str(i),' i added feature ', num2str(feature_to_add_at_this_level), ' to current set'])
}
    }
}




//         ---------------------------- VALIDATOR FUNCTION -------------------------------

function accuracy = leave_one_out_validation(data,current_set, feature_to_add)

number_correctly_classified = 0;

for i = 1 : size(data,1)
    object_to_classify = data(i,2:end);
    label_object_to_classify = data(i,1);

    nearest_neighbor_distance = numeric_limits<int>::max(); //inf;
    nearest_neighbor_location = numeric_limits<int>::max(); //inf;
    for k = 1 : size(data,1)
        if k != 1
            distance = sqrt(sum((object_to_classify - data(k,2:end)).^2));
            if distance < nearest_neighbor_distance
                nearest_neighbor_distance = distance;
                nearest_neighbor_location = k;
                nearest_neighbor_label = data(nearest_neighbor_location,1);

    if label_object_to_classify == nearest_neighbor_label;
        number_correctly_classified = number_correctly_classified + 1;

accuracy = number_correctly_classified / size(data,1);




*/