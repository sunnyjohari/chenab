
xml: validate_bmd_request.o xml_parser.o select_routes.o check_id_in_transform_config.o check_id_in_transport_config.o
	gcc  -Wall -I/usr/include/libxml2  -I/user/include/mysql -o xml validate_bmd_request.o \
	xml_parser.o  select_routes.o  check_id_in_transform_config.o          \
	check_id_in_transport_config.o -lxml2 -lmysqlclient

validate_bmd_request.o: validate_bmd_request.c xml.h connection.h
	gcc -c validate_bmd_request.c

select_routes.o: select_routes.c connection.h
	gcc -c  select_routes.c connection.h -I/usr/local/mysql/lib -lmysqlclient -lz

xml_parser.o: xml_parser.c xml.h
	gcc -c  -Wall -I/usr/include/libxml2 -lxml2  xml_parser.c xml.h  

check_id_in_transform_config.o : check_id_in_transform_config.c connection.h
		gcc -c  check_id_in_transform_config.c connection.h -I/usr/local/mysql/lib -lmysqlclient -lz

check_id_in_transport_config.o : check_id_in_transport_config.c connection.h
		gcc -c  check_id_in_transport_config.c connection.h -I/usr/local/mysql/lib -lmysqlclient -lz
		




clean:
	rm *.o xml