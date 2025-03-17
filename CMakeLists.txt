cmake_minimum_required(VERSION 3.14)
project(projet_C_A3)

set(CMAKE_C_STANDARD 11)


set(SRCS
	affichage.c
	fichiers.c
	fir.c
	iir.c
	main_sim.c
	mesure.c
)
set(HEADERS
	affichage.h
	fichiers.h
	fir.h
	iir.h
	mesure.h
	define.h
)

add_executable(main_sim ${SRCS} ${HEADERS})

