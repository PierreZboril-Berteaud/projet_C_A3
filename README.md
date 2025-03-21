# Projet Oxymètre de pouls en C 
### Compiler avec make:
- Pour utiliser le main de la simulation utilisant le fichier log1.dat:
```bash
~/: make main_sim
./main_sim 
```
- Pour utiliser le main de l'USB utilisant les données de la carte de simulation:
```bash
~/: make main_usb
./main_usb
```

### Addendum
- Le fichier contenant les données qui seront lues par `main_sim` doit s'appeler `log1.dat` et doit se situer dans le répertoire courant du projet. Vous pouvez modifier le chemin d'accès ou le nom du fichier à lire dans le fichier `main_sim.c` à la ligne 16.

- Voici les commandes à réaliser afin de connecter la carte de simulation à la WSL à l'aide de l'outil `usbipd`:
Dans le Powershell:

1. Récupérer le busid du périphérique (USB Serial Converter):
```powershell
usbipd list
```

2. Lier le périphérique à l'interface(invite administrateur requis):
```powershell
usbipd bind --busid [BUS_ID_CARTE_SIMU]
```

3. Attacher le périphérique à la WSL:
```powershell
usbipd attach --wsl --busid [BUS_ID_CARTE_SIMU]
```

Dans la WSL:
4. Lister les périphériques USB connectés et vérifier l'apparition de la carte
```bash
lsusb
```

5. Il sera probablement nécessaire d'accorder des permissions de lecture/écriture au périphérique:
```bash
sudo chmod 666 /dev/bus/usb/*/*
```
