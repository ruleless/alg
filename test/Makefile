ROOTDIR:= ..

CFLAGS+= -D_ALG_PROFILER -I../
CXXFLAGS+= -D_ALG_PROFILER -I../
LDFLAGS+= -L $(ROOTDIR)/lib -lalg -lgtest -lpthread

TARGET:= unit_test.out

include $(ROOTDIR)/build.mak
