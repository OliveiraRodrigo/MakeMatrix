#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <fstream>
//#include <mutex>
#include <sstream>
//#include <stdio.h>
#include <string>
//#include <thread>
#include <time.h>
#include <typeinfo>

using namespace std;
using namespace std::chrono;

template <typename TYPE>
void fileMatrix (size_t rows, size_t cols, double density, double mini, double maxi, double nullElem) {

	size_t r, c, p, totalElem, nonZeroElem, zeroElem;
	double progress;

	density = min ((double) density, 1.0);
	totalElem = rows * cols;
	nonZeroElem = density * totalElem;
	zeroElem = totalElem - nonZeroElem;

	TYPE** mtr = new (nothrow) TYPE* [rows];
	if (mtr == nullptr) {
		cout << endl << "Nao foi possivel alocar memoria." << endl << endl;
		exit(1);
	}

	cout << "Alocando memoria..." << endl;
	for (r = 0; r < rows; ++r) {
		mtr[r] = new TYPE[cols];
	}

	srand (time(NULL));

  	if (density < 0.5) {
		cout << "Preenchendo com elementos nulos..." << endl;
		for (r = 0; r < rows; ++r) {
			for (c = 0; c < cols; ++c) {
				mtr[r][c] = (TYPE) nullElem;
			}
		}
		cout << "Preenchendo com elementos aleatorios..." << endl;
		for (p = 0; p < nonZeroElem; ++p) {
			do {
				r = rand() % rows;
				c = rand() % cols;
			}
			while (mtr[r][c] != (TYPE) nullElem);
			mtr[r][c] = (TYPE) max (mini, min (maxi, (2 + maxi - mini) * ((double)rand()/(double)RAND_MAX ) + (mini - 1)));
			//mtr[r][c] = (TYPE) max (-(double) maxi, min ((double) maxi, (2 * (maxi+1) * ((double)rand()/RAND_MAX) - maxi - 1)));
		}
	}
	else {
		cout << "Preenchendo com elementos aleatorios..." << endl;
		for (r = 0; r < rows; ++r) {
			for (c = 0; c < cols; ++c) {
				mtr[r][c] = (TYPE) max (mini, min (maxi, (2 + maxi - mini) * ((double)rand()/(double)RAND_MAX ) + (mini - 1)));
				//mtr[r][c] = (TYPE) (-1 + rand() % 2) * (maxi+1) * ((double)rand()/RAND_MAX)
				//mtr[r][c] = (TYPE) max (-(double) maxi, min ((double) maxi, (2 * (maxi+1) * ((double)rand()/RAND_MAX) - maxi - 1)));
			}
		}
		cout << "Preenchendo com elementos nulos..." << endl;
		for (p = 0; p < zeroElem; ++p) {
			do {
				r = rand() % rows;
				c = rand() % cols;
			}
			while (mtr[r][c] == (TYPE) nullElem);
			mtr[r][c] = (TYPE) nullElem;
		}
	}

	ofstream outfile;
	outfile.open ((string)typeid(TYPE).name() + " " + to_string(rows) + "x" + to_string(cols) + ".txt");

	cout << "Gravando arquivo..." << endl;
	outfile << '[' << rows << ',' << cols << ']';
	for (size_t r = 0; r < rows; ++r) {
		progress = 1 + r*100/rows;
		//if ((int)progress % 10 == 0)
			cout << "\rProgresso: " << progress << '%';
		outfile << "\n";
		for (size_t c = 0; c < cols; ++c) {
			if (c > 0)
				outfile << " ";
			outfile << mtr[r][c];
		}
		delete[] mtr[r];
	}

	outfile.close();
	delete[] mtr;
}
	
int main (int argc, char**argv) {
    
	chrono::high_resolution_clock::time_point t1;
	chrono::high_resolution_clock::time_point t2;
	t1 = chrono::high_resolution_clock::now();

    string
    	typeName = "int"
    ;
    size_t
    	rows = atoi(argv[1]),
    	cols = atoi(argv[2])
    ;
    float
    	density = 1.0
    ;
    double
        mini = - (double) RAND_MAX,
        maxi = (double) RAND_MAX
    ;
    double
    	nullElem = 0
    ;

    for (int i = 1; i < argc; ++i) {
        
        if (!(((string)argv[i]).substr(0, 4). compare("type")))
            typeName = typeName.assign((string)argv[i], 5, 10);

        else if (!(((string)argv[i]).substr(0, 4). compare("dens")))
            density = atof(((string)argv[i]).substr(5).c_str());

        else if (!(((string)argv[i]).substr(0, 3). compare("min")))
            mini = atof(((string)argv[i]).substr(4).c_str());

        else if (!(((string)argv[i]).substr(0, 3). compare("max")))
        	maxi = atof(((string)argv[i]).substr(4).c_str());

        else if (!(((string)argv[i]).substr(0, 4). compare("null")))
        	nullElem = atof(((string)argv[i]).substr(5).c_str());
    }

    if (!typeName.compare("double")) {
        fileMatrix<double>(rows, cols, density, mini, maxi, nullElem);
    }
    else {
        fileMatrix<int>(rows, cols, density, mini, maxi, nullElem);
    }

	t2 = chrono::high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(t2 - t1).count();
	cout << endl << "Tempo: " << duration << " ms." << endl << endl;

    return 0;
}
