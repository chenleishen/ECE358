CC=gcc
CXX=g++

all: lab1_pt1 lab1_pt2 lab1_pt3 run_lab1_pt1 run_lab1_pt2 run_lab1_pt3

lab1_pt1:
	$(CXX) lab1_pt1.cpp generate_exp_distribution.cpp -o lab1_pt1.exe

lab1_pt2:
	$(CXX) lab1_pt2.cpp generate_exp_distribution.cpp -o lab1_pt2.exe

lab1_pt3:
	$(CXX) lab1_pt3.cpp generate_exp_distribution.cpp -o lab1_pt3.exe

run_lab1_pt1:
	./lab1_pt1.exe

run_lab1_pt2:
	./lab1_pt2.exe

run_lab1_pt3:
	./lab1_pt3.exe
