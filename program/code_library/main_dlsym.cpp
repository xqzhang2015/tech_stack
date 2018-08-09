#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

void* getFunctionalPointer(void* lib, const char* funcName)
{
	void* fptr = dlsym(lib, funcName);
	if (!fptr) 
	{
		fprintf(stderr, "Could not get function pointer for %s\n, error is: %s\n\n", funcName, dlerror());
		return NULL;
	}

	return fptr;
}

int main(int argc, char* argv[])
{
	printf("Load shared library by dlopen and dlsym ...\n\n");

	// Declare the function pointers
	typedef void (*_foo_a)();
	typedef void (*_foo_b)();
	typedef void (*_foo_c)();

	// Open the dynamic library
	void* foo_lib = dlopen("./libfoo.so", RTLD_LAZY | RTLD_GLOBAL);
	if (!foo_lib)
	{
		printf("Failed to open the library libfoo.so\n");
		exit(1);
	}

	// Get the func pointers with the library
	void* foo_a = getFunctionalPointer(foo_lib, "foo_a");
	void* foo_b = getFunctionalPointer(foo_lib, "foo_b");
	void* foo_c = getFunctionalPointer(foo_lib, "foo_c");

	// Call the function via the func pointers
	(*(_foo_a)foo_a)();
	(*(_foo_b)foo_b)();
	(*(_foo_c)foo_c)();

	return 0;
}

/*
 * 1. generate shared library: libfoo.so
 *
 * 2. gcc main_dlsym.cpp -ldl -o main_dlsym
 */
