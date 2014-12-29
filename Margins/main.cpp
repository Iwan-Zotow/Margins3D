#include <cassert>
#include <iostream>

#include "make_cube.h"
#include "make_circle.h"
#include "margins.h"

static void test_circle(bool expcont)
{
	auto c = make_circle(17.1f, 7.5f);

	assert(c != 0);

	c->write_PBM("circle");

	TOK::rvolume* r = TOK::margins(c.get(), 3.1f, 3.2f, 3.3f, 3.3f, 3.2f, 3.1f, expcont, 0.0f, 1);

	r->write_PBM("CIRCLE0");

	delete r;
}

static void test_cube(bool expcont)
{
	auto c = make_cube(3.4f, 4.7f, 7.5f);

	assert(c != 0);

	c->write_PBM("cube");

	TOK::rvolume* r = TOK::margins(c.get(), 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, expcont, 0.0f, 1);

	r->write_PBM("CUBE0");

	delete r;
}

int main()
{
	test_circle(false);
	test_cube(true);

	return 0;
}