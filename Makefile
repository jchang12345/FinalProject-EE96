CC=gcc
LDFLAGS=-lmraa -lfann
CFLAGS=-Wall
SOURCES=collect_neural_net_data.c examine_sensor_data.c test_neural_network.c train_neural_net.c
EXECUTABLES=$(SOURCES:.c=)

all: collect_neural_net_data examine_sensor_data test_neural_network train_neural_net

collect_neural_net_data: collect_neural_net_data.c
	$(CC) $(CFLAGS) -o collect_neural_net_data collect_neural_net_data.c $(LDFLAGS)

examine_sensor_data: examine_sensor_data.c
	$(CC) $(CFLAGS) -o examine_sensor_data examine_sensor_data.c $(LDFLAGS)

test_neural_network: test_neural_network.c
	$(CC) $(CFLAGS) -o test_neural_network test_neural_network.c $(LDFLAGS)

train_neural_net: train_neural_net.c
	$(CC) $(CFLAGS) -o train_neural_net train_neural_net.c $(LDFLAGS)

clean: 
	rm -f collect_neural_net_data examine_sensor_data test_neural_network train_neural_net
	rm -f *~
	rm -f TEST.net
	rm -f test_data.txt
