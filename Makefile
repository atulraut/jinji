PLATFORM=linux

DIR_INCLUDE=common/include

ifeq ($(PLATFORM), linux)
PKG_CONFIG=`pkg-config --cflags --libs gtk+-3.0 gthread-2.0  glib-2.0 sqlite3 libcurl`
LIBS=-lcurl
INCLUDE=-Imaemo -Icommon/include $(LIBS)
SRC=maemo
LINUX=common/linux
endif

TARGET=jinji

all:
	gcc -Wall -c $(SRC)/view.c -o $(SRC)/view.o $(INCLUDE) $(PKG_CONFIG)
	gcc -Wall -c $(SRC)/controller.c -o $(SRC)/controller.o $(INCLUDE) $(PKG_CONFIG)
#	gcc -Wall -c $(SRC)/gps.c -o $(SRC)/gps.o $(INCLUDE) $(PKG_CONFIG)
	gcc -Wall -c $(SRC)/model.c -o $(SRC)/model.o $(INCLUDE) $(PKG_CONFIG)
	gcc -Wall -c $(SRC)/retail_create.c -o $(SRC)/retail_create.o $(INCLUDE) $(PKG_CONFIG)
	gcc -Wall -c $(LINUX)/gthread.c -o $(LINUX)/gthread.o $(INCLUDE) $(PKG_CONFIG)
#	gcc -Wall -c $(LINUX)/inotify.c -o $(LINUX)/inotify.o $(INCLUDE) $(PKG_CONFIG)
	gcc -Wall -c main.c $(INCLUDE) $(PKG_CONFIG)
	gcc -o $(TARGET) main.o $(SRC)/view.o $(SRC)/controller.o $(SRC)/retail_create.o $(LINUX)/gthread.o $(SRC)/model.o $(INCLUDE) $(PKG_CONFIG)

clean:
	rm -f *~ *.o $(SRC)/*.o $(SRC)/*~ $(DIR_INCLUDE)/*~ $(TARGET) $(LINUX)/*.o $(LINUX)/*~ 
