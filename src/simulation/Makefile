#
include ../makedefs

LIB = $(MIXR_LIB_DIR)/libmixr_simulation.a

OBJS =  \
	AbstractDataRecorder.o \
	AbstractNetIO.o \
	AbstractNib.o \
	AbstractOtw.o \
	AbstractPlayer.o \
	AbstractRecorderComponent.o \
	SimBgThread.o \
	SimTcThread.o \
	Simulation.o \
	Station.o \
	StationBgThread.o \
	StationNetThread.o \
	StationTcThread.o \
	factory.o

.PHONY: all clean

all: $(LIB)

$(LIB) : $(OBJS)
	ar rs $@ $(OBJS)

clean:
	-rm -f environment/*.o
	-rm -f *.o
	-rm -f $(LIB)

