

LIBXML_LIBS :=  -I/usr/include/libxml2 -lxml2
SQL_LIBS   :=  -I/usr/local/mysql/lib -lmysqlclient -lz

xml: validate_bmd_request.o xml_parser.o select_routes.o check_id_in_transform_config.o check_id_in_transport_config.o
	gcc  -Wall  -o xml validate_bmd_request.o  xml_parser.o \
	select_routes.o  check_id_in_transform_config.o          \
	check_id_in_transport_config.o  ${LIBXML_LIBS}  ${SQL_LIBS}

validate_bmd_request.o: validate_bmd_request.c xml.h connection.h
	gcc -c validate_bmd_request.c ${SQL_LIBS}

select_routes.o: select_routes.c connection.h
	gcc -c  select_routes.c connection.h 

xml_parser.o: xml_parser.c xml.h
	gcc -c  -Wall ${LIBXML_LIBS}  xml_parser.c xml.h  

check_id_in_transform_config.o : check_id_in_transform_config.c connection.h
		gcc -c  check_id_in_transform_config.c connection.h ${SQL_LIBS}

check_id_in_transport_config.o : check_id_in_transport_config.c connection.h
		gcc -c  check_id_in_transport_config.c connection.h ${SQL_LIBS}
		




clean:
	rm *.o xml