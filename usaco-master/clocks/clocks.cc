/*
ID: nissan.po1
LANG: C++
TASK: clocks
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

#define NCLOCKS 9
#define NMOVES 9
#define N 12
#define E 3
#define S 6
#define W 9

typedef vector< int > Clock;

void printClock( Clock &clock ) {
	for( int i=0; i<NCLOCKS; ++i) {
		cout << clock[i] << " ";
		if( (i+1)%3 == 0 ) cout << endl;
	}
	cout << endl;
}

inline void rotate90( int &dir ) {
	switch( dir ) {
		case N: dir = E; break;
		case E: dir = S; break;
		case S: dir = W; break;
		case W: dir = N; break;
	}
}

inline bool done( Clock &clock ) {
	for( int i=0; i<NCLOCKS; ++i ) {
		if( clock[i] != N ) {
			return false;
		}
	}
	return true;
}

inline void turn_dials( Clock &clock, string targets, int ntimes ) {
	for( int j=0; j<ntimes; ++j ) {
		for( int i=0; i<targets.length( ); ++i ) {
			rotate90( clock[ targets.at( i ) - 'A' ] );
		}
	}
}

inline void turn_dials( Clock &clock, int move , int ntimes) {
	switch( move ) {
		case 1: return turn_dials( clock, "ABDE", ntimes );
		case 2: return turn_dials( clock, "ABC", ntimes );
		case 3: return turn_dials( clock, "BCEF", ntimes );
		case 4: return turn_dials( clock, "ADG", ntimes );
		case 5: return turn_dials( clock, "BDEFH", ntimes );
		case 6: return turn_dials( clock, "CFI", ntimes );
		case 7: return turn_dials( clock, "DEGH", ntimes );
		case 8: return turn_dials( clock, "GHI", ntimes );
		case 9: return turn_dials( clock, "EFHI", ntimes );
	}
}

struct pos {
	Clock clock;
	vector< int > moves;
};

int main() {
	ifstream in( "clocks.in" );
	Clock clock( NCLOCKS, N );
	for( int i=0; i<NCLOCKS; ++i ) {
		in >> clock[i];
	}
	in.close( );
	int moves[NMOVES+2];
	for( int i=0; i<NMOVES+2; ++i ) moves[i] = 0;
	Clock cur = clock;
	while( moves[NMOVES+1] != 1 ) {
		moves[0]++;
		turn_dials( cur, 0, 1 );
		for( int i=0;; ++i ) {
			if( moves[i] > 3 ) {
				moves[i] = 0;
				moves[i+1]++;
				turn_dials( cur, i+1, 1 );
			} else {
				break;
			}
		}
#if 0
		for( int i=1; i<=NMOVES; ++i ) {
			if( moves[i] == 0 ) continue;
			turn_dials( cur, i, moves[i] );
		}
#endif
		if( done( cur ) ) {
			ofstream out( "clocks.out" );
			bool flag = true;
			for( int i=1; i<=NMOVES; ++i ) {
				if( moves[i] != 0 ) {
					for( int j=0; j<moves[i]; ++j ) {
						out << (flag ? flag=false,"" : " ") << i;
					}
				}
			}
			out << endl;
			out.close( );
			break;
		}
	}
	return 0;
}
