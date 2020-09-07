XML_HANDLER = ../bmd_extract/xml_parser.c ../bmd_extract/xml.h  ../bmd_extract/validate_bmd_request.c
SQL_API     = ../db_access/insert_to_esb_request.c ../db_access/select_active_route_id.c ../db_access/check_id_in_transform_config.c ../db_access/check_id_in_transport_config.c
XML_LIB     =   `xml2-config --cflags` `xml2-config --libs`
SQL_LIB     =  `mysql_config --cflags --libs`
esb: esb.c
	gcc esb.c ${XML_HANDLER} ${SQL_API} -o esb ${SQL_LIB} ${XML_LIB}

clean:
	rm esb

