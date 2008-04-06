//#include <devel/validate/stdafx.h>
#include "GentorProfile.h"

using namespace itl;

GentorProfileSgl* GentorProfileSgl::s_instance = NULL;

GentorProfileSgl* GentorProfileSgl::it()
{
	if(s_instance==NULL) {
		s_instance = new GentorProfileSgl;
	}
	return s_instance;
}

GentorProfileSgl::GentorProfileSgl(){}



GentorProfile::GentorProfile()
{
	set_range_int(0, 10);
	set_range_double(0.0, 1.0);
	set_range_ContainerSize(0,10);

	set_range_interval_int(-10, 10);
	set_maxIntervalLength(8);
}

// -------------------------------------
// (Algebra, Law, Type) -> (testsCount)
// (set, ipAddCommut, itl::set) -> 150

