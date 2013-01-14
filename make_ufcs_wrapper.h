#ifndef MAKE_UFCS_WRAPPER_HEADER
#define MAKE_UFCS_WRAPPER_HEADER

#define MAKE_UFCS_WRAPPER(impl,name) \
	const panlib::ufcs::wrapper<impl> name

#endif