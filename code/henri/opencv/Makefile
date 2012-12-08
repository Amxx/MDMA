CXX=g++
CXXFLAGS=-W -Wall
LDFLAGS=-lopencv_core -lopencv_highgui
EXEC=opencv_openni

all: $(EXEC)

opencv_openni: opencv_openni.o
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
