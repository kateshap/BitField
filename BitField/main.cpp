
#include "TBitField.h"
#include "TSet.h"

#include <stdexcept>
#include <locale>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cassert>
#include <iostream>
#include <cmath>
#include <fstream>

typedef unsigned int Uint;
using namespace std;


int main() {


	int n, m, k, count;
	cin >> n;
	TSet s(n + 1);
	for (m = 2; m <= n; m++)
		s.InsElem(m);
	for (m = 2; m * m <= n; m++) {
		if (s.IsMember(m))
			for (k = 2 * m; k <= n; k += m)
				if (s.IsMember(k))
					s.DelElem(n);
	}
}