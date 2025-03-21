cmake_minimum_required(VERSION 3.25)
project(projet_C_A3)

set(CMAKE_C_STANDARD 11)


set(SRCS
	affichage.c
	fichiers.c
	fir.c
	iir.c
	mesure.c
        lecture.c
		main_usb.c)
set(HEADERS
	affichage.h
	fichiers.h
	fir.h
	iir.h
	mesure.h
	define.h
	lecture.h
		ftd2xx.h
		WinTypes.h)
add_executable(main ${SRCS} ${HEADERS})
target_link_libraries(main m)
target_link_libraries(main libftd2xx.so)




