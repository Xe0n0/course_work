//
//  Created by Chu-Pan,Wong on Dec 3, 2013.
//  Copyright (c) 2013 ChuPan,Wong. All rights reserved.
//


#include <iostream>
using namespace std;

int m[100][100];

void step1(int n){
    int min;
    for (int i=0; i<n; i++) {
        min = m[i][0];
        for (int j=0; j<n; j++) {
            if (m[i][j]<min) {
                min = m[i][j];
            }
        }
        for (int j=0; j<n; j++) {
            m[i][j]-=min;
        }
    }
    for (int j=0; j<n; j++) {
        min = m[0][j];
        for (int i=0; i<n; i++) {
            if (m[i][j]<min) {
                min = m[i][j];
            }
        }
        for (int i=0; i<n; i++) {
            m[i][j]-=min;
        }
    }
}

void step2(int n){
    for (int i=0; i<n; i++) {
        for (int j=1; j<n-1; j++) {
            m[i][j] = m[i][j+1];
        }
    }
    for (int j=0; j<n; j++) {
        for (int i=1; i<n-1; i++) {
            m[i][j] = m[i+1][j];
        }
    }
}

int main(int argc, char** argv){
    int n;
    cin>>n;
    int round = n;
    while (round--) {
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cin>>m[i][j];
            }
        }
        int sum = 0;
        for (int i=n; i>1; i--) {
            step1(i);
            sum+=m[1][1];
            step2(i);
        }
        cout<<sum<<endl;
    }
    return 0;
}