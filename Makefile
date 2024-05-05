##################
##  Vit Pavlik  ##
##   xpavli0a   ##
##    251301    ##
##     2024     ##
##################

TARGET_BINARY=icp
GENERATED_MF=generated_makefile
DOXY_MAINPAGE=mainpage.dox
ZIP_FILENAME=xpavli0a-xxxxxx00.zip
OBSTACLES_FILENAME=icp_obstacles.txt

.PHONY: all
all: $(TARGET_BINARY)

$(TARGET_BINARY):
	qmake -o $(GENERATED_MF)
	make -f $(GENERATED_MF)

.PHONY: doxygen
doxygen:

	echo "" > $(DOXY_MAINPAGE)
	echo "/**" >> $(DOXY_MAINPAGE)
	echo "\mainpage" >> $(DOXY_MAINPAGE)
	echo "\`\`\`md" >> $(DOXY_MAINPAGE)
	cat README.txt >> $(DOXY_MAINPAGE)
	echo "\`\`\`" >> $(DOXY_MAINPAGE)
	echo "*/" >> $(DOXY_MAINPAGE)
	doxygen
	rm mainpage.dox

.PHONY: clean
clean:
	if [ -f $(GENERATED_MF) ]; then make -f $(GENERATED_MF) clean; fi
	rm -rf *.o $(TARGET_BINARY) doc/html *.zip

.PHONY: pack
pack: clean  # notice that zipping is performed only after clean
	zip -r $(ZIP_FILENAME) *

.PHONY: run
run: all
	cp examples/$(OBSTACLES_FILENAME) ./$(OBSTACLES_FILENAME)
	./$(TARGET_BINARY)
	rm ./$(OBSTACLES_FILENAME)
