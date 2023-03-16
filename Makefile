
# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

TARGETS=image_editor

build: $(TARGETS)

image_editor: image_editor.c 
	$(CC) $(CFLAGS) image_editor.c SAVE.c ROTATE.c SELECT.c CROP.c LOAD.c SEPIA.c GRAYSCALE.c -o image_editor
	
clean:
	rm -f $(TARGETS)
