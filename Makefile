main_sim : fir.o iir.o affichage.o mesure.o main_sim.o fichiers.o
	gcc -o main_sim fir.o iir.o affichage.o mesure.o main_sim.o fichiers.o -lm

main_usb : fir.o iir.o affichage.o mesure.o lecture.o fichiers.o main_usb.o
	gcc -o main_usb fir.o iir.o affichage.o mesure.o lecture.o fichiers.o main_usb.o -lm ftd2xx

fir.o : fir.c fir.h define.h fichiers.h
	gcc -c fir.c

iir.o : iir.c iir.h define.h fichiers.h
	gcc -c iir.c

affichage.o : affichage.c affichage.h define.h fichiers.h
	gcc -c affichage.c

mesure.o : mesure.c mesure.h define.h fichiers.h
	gcc -c mesure.c

fichiers.o : fichiers.c fichiers.h define.h
	gcc -c fichiers.c

lecture.o : lecture.c ftd2xx.h define.h
	gcc -c lecture.c

main_sim.o : main_sim.c iir.h fir.h fichiers.h affichage.h define.h mesure.h
	gcc -c main_sim.c

main_usb.o : main_usb.c iir.h fir.h affichage.h define.h mesure.h lecture.h
	gcc -c main_usb.c