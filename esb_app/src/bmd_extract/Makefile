

LIBXML_LIBS :=  -I/usr/include/libxml2 -lxml2
SQL_LIBS   :=  -I/usr/local/mysql/lib -lmysqlclient -lz

xml: validate_bmd_request.o xml_parser.o select_routes.o insert_esb_request.o  check_id_in_transform_config.o check_id_in_transport_config.o
	gcc  -Wall  -o xml  main.c validate_bmd_request.o  insert_esb_request.o \
	xml_parser.o \
	select_routes.o  check_id_in_transform_config.o          \
	check_id_in_transport_config.o  ${LIBXML_LIBS}  ${SQL_LIBS}


validate_bmd_request.o: validate_bmd_request.c xml.h ../db_access/connection.h
	gcc -c validate_bmd_request.c ${SQL_LIBS}

xml_parser.o : xml_parser.c  xml.h
	gcc -c  -Wall ${LIBXML_LIBS}  xml_parser.c xml.h  
	
insert_esb_request.o : ../db_access/insert_esb_request.c ../db_access/connection.h
	gcc -c  ../db_access/insert_esb_request.c ../db_access/connection.h ${SQL_LIBS}

select_routes.o: ../db_access/select_routes.c  ../db_access/connection.h
	gcc -c  ../db_access/select_routes.c ../db_access/connection.h ${SQL_LIBS}

check_id_in_transform_config.o : ../db_access/check_id_in_transform_config.c ../db_access/connection.h
	gcc -c  ../db_access/check_id_in_transform_config.c ../db_access/connection.h ${SQL_LIBS}

check_id_in_transport_config.o : ../db_access/check_id_in_transport_config.c ../db_access/connection.h
	gcc -c  ../db_access/check_id_in_transport_config.c ../db_access/connection.h ${SQL_LIBS}




clean:
	rm *.o xml