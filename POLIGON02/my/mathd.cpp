//---------------------------------------------------------------------------
#include <float.h>
#include <math.h>

#include "mathd.h"

namespace androsor
{
using namespace std;

//---------------------------------------------------------------------------
int froundi(float x)
{
	return static_cast <int>(floor(x + .5));
}

} // namespace androsor
