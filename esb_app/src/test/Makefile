DB_ACCESS = ../db_access/select_routes.c ../db_access/check_id_in_transport_config.c ../db_access/check_id_in_transform_config.c
XML_HANDLER = ../bmd_extract/xml_parser.c ../bmd_extract/validate_bmd_request.c
INCLUDE = `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs`
test: ../bmd_extract/xml_parser.c ../bmd_extract/xml.h
	gcc  ${DB_ACCESS} ${XML_HANDLER} test_bmd.c -o test ${INCLUDE} munit.c

clean :
	rm test	