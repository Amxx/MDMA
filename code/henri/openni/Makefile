CXX=g++
CXXFLAGS=-W -Wall
LDFLAGS=
EXEC=opencv_openni openni openni_class openni_class_nite
ODIR=obj

all: $(EXEC)

openni: $(ODIR)/openni.o
	$(CXX) -o $@ $^ -lOpenNI -lXnVNite_1_5_2
	
openni_class: $(ODIR)/openni_class.o $(ODIR)/NiHandTracker.o
	$(CXX) -o $@ $^ -lOpenNI

openni_class_nite: $(ODIR)/openni_class_nite.o $(ODIR)/kinecttracking.o
	$(CXX) -o $@ $^ -lOpenNI -lXnVNite_1_5_2
	
opencv_openni: $(ODIR)/opencv_openni.o
	$(CXX) -o $@ $^ -lopencv_core -lopencv_highgui
	
$(ODIR)/openni.o: openni.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) -isystem /usr/include/ni -isystem /usr/include/nite
	
$(ODIR)/openni_class.o: openni_class.cpp NiHandTracker.h
	$(CXX) -o $@ -c $< $(CXXFLAGS) -isystem /usr/include/ni
	
$(ODIR)/NiHandTracker.o: NiHandTracker.cpp NiHandTracker.h
	$(CXX) -o $@ -c $< $(CXXFLAGS) -isystem /usr/include/ni
	
$(ODIR)/openni_class_nite.o: openni_class_nite.cpp kinecttracking.h
	$(CXX) -o $@ -c $< $(CXXFLAGS) -isystem /usr/include/ni -isystem /usr/include/nite
	
$(ODIR)/kinecttracking.o: kinecttracking.cpp kinecttracking.h
	$(CXX) -o $@ -c $< $(CXXFLAGS) -isystem /usr/include/ni -isystem /usr/include/nite

$(ODIR)/opencv_openni.o: opencv_openni.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf $(ODIR)/*.o

mrproper: clean
	rm -rf $(EXEC)
