CXX=g++
CXXFLAGS=-W -Wall
LDFLAGS=
EXEC=opencv_openni openni
ODIR=obj

all: $(EXEC)

openni: $(ODIR)/openni.o
	$(CXX) -o $@ $^ -lOpenNI -lXnVNite_1_5_2
	
opencv_openni: $(ODIR)/opencv_openni.o
	$(CXX) -o $@ $^ -lopencv_core -lopencv_highgui
	
$(ODIR)/openni.o: openni.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) -isystem /usr/include/ni -isystem /usr/include/nite
	
$(ODIR)/opencv_openni.o: opencv_openni.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf $(ODIR)/*.o

mrproper: clean
	rm -rf $(EXEC)
