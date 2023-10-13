# a build command to build Spline executable from main.cpp
all:Spline.h main.cpp eigen
	g++ -I eigen main.cpp -o Spline.exe
clean:
	$(RM) Spline