// This is core/vil/tests/test_border.cxx
#include <testlib/testlib_test.h>
#include <vcl_iostream.h>
#include <vcl_sstream.h>
#include <vcl_functional.h>
#include <vxl_config.h> // for vxl_byte
#include <vil/vil_image_view.h>
#include <vil/vil_border.h>
#include <vil/vil_fill.h>

static void test_border_constant_byte()
{
  vil_image_view<vxl_byte> im(64,64);
  vil_fill(im, vxl_byte(0));
  im(0, 10) = 42;
  im(50, 63) = 51;
  im(63, 2) = 58;
  im(5, 0) = 59;
  im(30, 40) = 69;

  vil_border<vil_image_view<vxl_byte> > border = vil_border_create_constant(im, 13);
  vil_border<vil_image_view<vxl_byte> >::accessor 
    accessor = border.image_accessor(im);

  TEST("respect left border", accessor(0,10), 42);
  TEST("respect right border", accessor(63,2), 58);
  TEST("respect bottom border", accessor(50,63), 51);
  TEST("respect top border", accessor(5,0), 59);
  TEST("respect image range", accessor(30,40), 69);
  TEST("outside left edge", accessor(-1,10), 13);
  TEST("outside top edge", accessor(0,-1), 13);
  TEST("outside bottom edge", accessor(1,64), 13);
  TEST("outside right edge", accessor(64,5), 13);
  TEST("outside top-right edge", accessor(64,64), 13);
}

static void test_border_constant_hsv()
{
  vil_image_view<float> im(64,64,3);
  vil_fill(im, float(0));
  im(0, 10, 0) = 41.2;
  im(0, 10, 1) = 42.2;
  im(0, 10, 2) = 43.2;
  im(50, 63, 0) = 50.1;
  im(50, 63, 1) = 51.1;
  im(50, 63, 2) = 52.1;

  vil_border<vil_image_view<float> > border = vil_border_create_constant(im, 13.3);
  vil_border<vil_image_view<float> >::accessor 
    accessor = border.image_accessor(im);

  TEST_NEAR("respect left border plane 0", accessor(0,10), 41.2, 1e-5);
  TEST_NEAR("respect left border plane 1", accessor(0,10,1), 42.2, 1e-5);
  TEST_NEAR("respect left border plane 2", accessor(0,10,2), 43.2, 1e-5);
  
  TEST_NEAR("respect bottom border plane 0", accessor(50,63,0), 50.1, 1e-5);
  TEST_NEAR("respect bottom border plane 1", accessor(50,63,1), 51.1, 1e-5);
  TEST_NEAR("respect bottom border plane 0", accessor(50,63,2), 52.1, 1e-5);
  
  TEST_NEAR("outside left edge plane 0", accessor(-1,10,0), 13.3, 1e-5);
  TEST_NEAR("outside top edge plane 1", accessor(0,-1,1), 13.3, 1e-5);
  TEST_NEAR("outside bottom edge plane 0", accessor(1,64), 13.3, 1e-5);
  TEST_NEAR("outside right edge plane 1", accessor(64,5,1), 13.3, 1e-5);
  TEST_NEAR("outside top-right edge plane 2", accessor(64,64,2), 13.3, 1e-5);
  TEST_NEAR("outside depth edge front", accessor(5,5,-1), 13.3, 1e-5);
  TEST_NEAR("outside depth edge back", accessor(5,5,3), 13.3, 1e-5);
  TEST_NEAR("outside everything", accessor(-1,-1,-1), 13.3, 1e-5);  
}

static void test_border_geodesic()
{
  vil_image_view<vxl_byte> im(64,64);
  vil_fill(im, vxl_byte(13));
  im(0, 10) = 42;
  im(50, 63) = 51;
  im(63, 2) = 58;
  im(5, 0) = 59;
  im(30, 40) = 69;
  im(63, 63) = 25;

  vil_border<vil_image_view<vxl_byte> >::accessor 
    accessor = vil_border_create_geodesic(im).image_accessor(im);

  TEST("respect left border", accessor(0,10), 42);
  TEST("respect right border", accessor(63,2), 58);
  TEST("respect bottom border", accessor(50,63), 51);
  TEST("respect top border", accessor(5,0), 59);
  TEST("respect image range", accessor(30,40), 69);
  TEST("outside left edge", accessor(-1,10), 42);
  TEST("outside left edge (far)", accessor(-10,10), 42);
  TEST("outside top edge", accessor(0,-1), 13);
  TEST("outside bottom edge", accessor(1,64), 13);
  TEST("outside right edge", accessor(64,2), 58);
  TEST("outside top-right edge", accessor(64,64), 25);
}

static void test_border_reflect()
{
  vil_image_view<vxl_byte> im(64,64);
  vil_fill(im, vxl_byte(13));
  im(0, 10) = 42;
  im(9, 10) = 63;
  im(50, 63) = 51;
  im(63, 2) = 58;
  im(5, 0) = 59;
  im(30, 40) = 69;
  im(63, 63) = 25;
  im(1, 61) = 70;

  vil_border<vil_image_view<vxl_byte> >::accessor 
    accessor = vil_border_create_reflect(im).image_accessor(im);

  TEST("respect left border", accessor(0,10), 42);
  TEST("respect right border", accessor(63,2), 58);
  TEST("respect bottom border", accessor(50,63), 51);
  TEST("respect top border", accessor(5,0), 59);
  TEST("respect image range", accessor(30,40), 69);
  TEST("outside left edge", accessor(-1,10), 42);
  TEST("outside left edge (far)", accessor(-10,10), 63);
  TEST("outside top edge", accessor(0,-1), 13);
  TEST("outside bottom edge", accessor(1,66), 70);
  TEST("outside right edge", accessor(64,2), 58);
  TEST("outside top-right edge", accessor(64,64), 25);
}

static void test_border_periodic()
{
  vil_image_view<vxl_byte> im(64,64);
  vil_fill(im, vxl_byte(13));
  im(0, 10) = 42;
  im(50, 63) = 51;
  im(63, 2) = 58;
  im(5, 0) = 59;
  im(30, 40) = 69;
  im(63, 63) = 25;
  im(63,10) = 33;
  im(0,63) = 2;
  im(0,0) = 25;

  vil_border<vil_image_view<vxl_byte> >::accessor 
    accessor = vil_border_create_periodic(im).image_accessor(im);

  TEST("respect left border", accessor(0,10), 42);
  TEST("respect right border", accessor(63,2), 58);
  TEST("respect bottom border", accessor(50,63), 51);
  TEST("respect top border", accessor(5,0), 59);
  TEST("respect image range", accessor(30,40), 69);
  TEST("outside left edge", accessor(-1,10), 33);
  TEST("outside left edge (far)", accessor(-14,63), 51);
  TEST("outside top edge", accessor(0,-1), 2);
  TEST("outside bottom edge", accessor(5,64), 59);
  TEST("outside right edge", accessor(64,63), 2);
  TEST("outside top-right edge", accessor(64,64), 25);
}

static void test_border()
{
  vcl_cout << "******************************************\n"
           << " Testing vil_border_constant (byte image) \n"
           << "******************************************\n";
  test_border_constant_byte();

  vcl_cout << "******************************************\n"
           << " Testing vil_border_constant (hsv image)  \n"
           << "******************************************\n";
  test_border_constant_hsv();

  vcl_cout << "******************************************\n"
           << " Testing vil_border_geodesic              \n"
           << "******************************************\n";
  test_border_geodesic();

  vcl_cout << "******************************************\n"
           << " Testing vil_border_reflect               \n"
           << "******************************************\n";
  test_border_reflect();

  vcl_cout << "******************************************\n"
           << " Testing vil_border_periodic              \n"
           << "******************************************\n";
  test_border_periodic();
}

TESTMAIN(test_border);
