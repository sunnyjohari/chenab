#include <stdio.h>
#include <stdlib.h>
#include "munit.h"
#include "../bmd_extract/xml.h"
#include "/home/bpavan/nho_work/chenab/esb_app/src/db_access/connection.h"



/* Test setup function creates bmd and returns it */
static void *
esb_request_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_extract/test_files/dum.xml";
  bmd *b = parse_bmd_xml(file);
  return b;
}


/* Test function for esb_request */
static MunitResult
test_esb_request(const MunitParameter params[], void *fixture)
{
  bmd *test_bmd = (bmd *)fixture;
  
 int rc = insert_to_esb_request(test_bmd->envelope->Sender,
    test_bmd->envelope->Destination,test_bmd->envelope->MessageType,
   test_bmd->envelope->ReferenceID,test_bmd->envelope->MessageID,
    "","RECEIVED","",test_bmd->envelope->CreationDateTime);
    
    munit_assert_int(rc,==,-1);


  return MUNIT_OK;
}


/* free of allocated memory*/
static void
 esb_request_tear_down(void *fixture)
{
  bmd *b = (bmd *)fixture;

  free(b->envelope);
  free(b->payload);
  free(b);

}




/* Test setup function creates */
static void *
check_id_in_transform_config_setup(const MunitParameter params[], void *user_data)
{
}


/* Test function for esb_request */
static MunitResult
test_check_id_in_transform_config(const MunitParameter params[], void *fixture)
{

  
 int rc = check_id_in_transform_config(15);
    munit_assert_int(rc,==,1);


  return MUNIT_OK;
}


/* free of allocated memory*/
static void
check_id_in_transform_config_tear_down(void *fixture)
{
  /*NONE*/

}



/* Test setup function creates bmd and returns it */
static void *
check_id_in_transport_config_setup(const MunitParameter params[], void *user_data)
{

}


/* Test function for esb_request */
static MunitResult
test_check_id_in_transport_config(const MunitParameter params[], void *fixture)
{

  
 int rc = check_id_in_transport_config(15);
    munit_assert_int(rc,==,1);


  return MUNIT_OK;
}


/* free of allocated memory*/
static void
check_id_in_transport_config_tear_down(void *fixture)
{
  /*NONE*/

}



/* Test setup function creates bmd and returns it */
static void *
select_active_route_id_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_extract/test_files/dum.xml";
  bmd *b = parse_bmd_xml(file);
  return b;
}


/* Test function for esb_request */
static MunitResult
test_select_active_route_id(const MunitParameter params[], void *fixture)
{
  bmd *test_bmd = (bmd *)fixture;
  
 int rc = active_routes_from_source(test_bmd->envelope->Sender,
    test_bmd->envelope->Destination,test_bmd->envelope->MessageType);
    
    munit_assert_int(rc,==,15);


  return MUNIT_OK;
}


/* free of allocated memory*/
static void
select_active_route_id_tear_down(void *fixture)
{
  bmd *b = (bmd *)fixture;

  free(b->envelope);
  free(b->payload);
  free(b);

}








/* Put all unit tests here. */
MunitTest db_access_functions_tests[] = {
    {
        "/insert_esb_request_test",   /* name */
        test_esb_request,      /* test function */
        esb_request_setup,     /* setup function for the test */
        esb_request_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,  /* options */
        NULL                     /* parameters */
    },


    

    {
        "/check_id_in _transform_config_test",   /* name */
        test_check_id_in_transform_config,      /* test function */
        check_id_in_transform_config_setup,     /* setup function for the test */
        check_id_in_transform_config_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,                  /* options */
        NULL                                     /* parameters */
    },

    {
        "/check_id_in _transport_config_test",   /* name */
        test_check_id_in_transport_config,      /* test function */
        check_id_in_transport_config_setup,     /* setup function for the test */
        check_id_in_transport_config_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,                  /* options */
        NULL                                     /* parameters */
    },

    {
        "/select_active_route_id_test",   /* name */
        test_select_active_route_id,      /* test function */
        select_active_route_id_setup,     /* setup function for the test */
        select_active_route_id_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,                  /* options */
        NULL                                     /* parameters */

    },


    /* Mark the end of the array with an entry where the test
   * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* Arrange the test cases into a test suite. */
static const MunitSuite suite = {
    "/db_access_functions_tests",           /* name */
    db_access_functions_tests,              /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite */
int main(int argc, const char *argv[])
{
  return munit_suite_main(&suite, NULL, argc, NULL);
}
