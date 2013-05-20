################################################################
################################################################

PROGRAM = Portal

CXX_SRCS = game.cpp level.cpp object.cpp enemy.cpp player.cpp \
	rectangle.cpp

CXXLIBS = -L/usr/x11R6/lib -lX11 -lm

CCC_OBJS = ccc_x11.o ccc_shap.o ccc_time.o

################################################################
################################################################

CCC_FILESDIR = cccfiles

CCC_OBJS2 = $(CCC_OBJS:%=$(CCC_FILESDIR)/%)

CXXINCLUDEPATHS = -I$(CCC_FILESDIR)

CXX = g++
CC = $(CXX)
LDFLAGS = -g -pipe -L/usr/X11R6/lib $(CXX_LIBS)
CXXFLAGS = -g -pipe -Wall $(CXXINCLUDEPATHS)

OBJS = $(CXX_SRCS:.cpp=.o)

DEMANGLER = c++filt

# The following line is included for Eclipse, since it calls "build all" 
all : $(PROGRAM)

$(PROGRAM) : depend $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(CCC_OBJS2) $(CXXLIBS) -o $(PROGRAM) 2>&1 \
             | $(DEMANGLER)

clean:
	/bin/rm -f *.o $(PROGRAM) .nfs* *~ core \#*\#

depend:
	$(CXX) -MM $(CXX_SRCS) $(CXXINCLUDEPATHS) > .depend.mk

###
include .depend.mk