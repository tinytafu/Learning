target := second_make
LIBS := -lpthread
$(target): second_make.cc 
	@echo "build begin $(target)"
	@$(CXX) $^ -o $@ $(LIBS)
	@echo "build end"

# 伪目标:执行某些操作而不生成具体的文件
.PHONY: clean
clean:
	rm second_make
