target := 04_four_make
OBJS := 04_four_make.o
LIBS := -lpthread
CXXFLAGS := -I../02_test_gcc/ #但是若头文件出现在其他目录，则需要添加参数，这里需要-I头文件路径
$(target): $(OBJS) #make会进行自动推导,在文件系统中查找与.o文件同名的.cc文件,随后再对.o文件进行链接
	$(CXX) $^ -o $@ $(LIBS)
clean:
	$(RM) $(OBJS) $(target)
.PHONY: clean
