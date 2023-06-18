# Programme des matrices de LEDs pour les olinpiades
Pour cloner ce dépot:
```
git clone --recurse-submodules git@github.com:robotronik/olinpiades.git
```
## Programme du stm32
pré-requis:  
- arm-none-eabi-gcc: pour compiler le programme du stm32 ainsi que ces librairies (arm-none-eabi-**** sur arch linux)
- openocd: pour envoyer le programme au stm32
- meson pour compiler

Pour compiler les programmes:
```
make build
```
Le dossier build est alors créé. Pour envoyer le programme au stm32 (cela nécessite d'avoir installé les règles udev correctement (make install_udev)), depuis le dossier \_build:
```
ninja olinpiades.flash
```

## Programme de génération de frames
Pour tester ce qui va être afficher, depuis le dossier \_build:
```
./frames_generator/display_test
```
Si les frames ont étés modifiées (options de génération ou images d'entrée):
```
ninja regenerate_frames_files
ninja
```
Les frames sont stockées dans le fichier frames_generator/frames_definition.c . Le script python frames_generator/generator.py est en charge de créer ce fichier. Des options sont disponibles en haut de ce fichier (rotation, miroir x, miroir y, affichage du résultat appliqué à chaque image).  

Les frames sont générées à partir des images contenues dans frames_generator/images. L'ordre alphabétique des fichiers donne l'ordre des frames. La convention de nommage à respecter est la suivante: nomimage_durée_seuil.jpg (ou .png). durée est proportionnel à la durée d'apparition de l'image (entre 0 et 255) et le seuil est celui appliqué à l'image (entre 0 et 255).  

Le programme affiche la taille utilisée pour le stockage de frames (en octets). Le stm32f303k8t6 devrait pouvoir en contenir 70 au minimum.
