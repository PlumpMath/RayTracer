#include "Intersection.h"
#include "Primitive.h"

void Intersection::getBRDF(BRDF & brdf)
{
	primitive -> getBRDF(local,brdf);
}