#include "History.h"
#include <iostream>

using namespace std;

History::History(int nRows, int nCols)
 : h_rows(nRows), h_cols(nCols)
{
	// set the record straight to 0
	int i,j;
	for ( i=1; i<MAXROWS; i++){
		for ( j=1; j<MAXCOLS; j++)
			h_record[i-1][j-1] = 0;
	}
}

bool History::record(int r, int c){
	if ( r<=h_rows && c<=h_cols ){
		h_record[r-1][c-1]++;
		//cout << h_record[r-1][c-1];
		return true;
	}
	return false;
}

void History::display() const{
	clearScreen();
	int i,j;
	for ( i=1; i<h_rows+1; i++){
		for ( j=1; j<h_cols+1; j++){
			//converting 1->A, 2->B etc.
			int tmp = h_record[i-1][j-1];
			if ( tmp == 0 )
				cout << ".";
			else
				if ( tmp>25) cout<<'Z';
				else cout<< static_cast<char>(tmp+64);
	   }
		cout<< endl;
	}
	cout << endl;
}
