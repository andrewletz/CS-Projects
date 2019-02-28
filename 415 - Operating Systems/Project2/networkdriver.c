/*
	CIS 415 Project 2 networkdriver.c
	Author: Andrew Letz
	Duck ID: aletz
	Apart from
	- Followed instruction from Roscoe Casita in labs
	- Used instructions and auxiliary code from Joe Sventek and Peter Dickman
	, this is my own work
*/

#define UNUSED __attribute__((unused)) /* compiler-dependent */

#include <pthread.h>
#include "diagnostics.h"
#include "networkdriver.h"
#include "BoundedBuffer.h"
#include "freepacketdescriptorstore__full.h"

static NetworkDevice *netDevice;
static BoundedBuffer *pool; /* cache to improve speed */
static BoundedBuffer *send; /* where packetdescriptors are put by the applications */
static BoundedBuffer *apps[11]; /* MAX_PID is 10, so we need 11 buffers for 11 apps */
static FreePacketDescriptorStore *fpds;

void blocking_send_packet(PacketDescriptor *pd) {
	send->blockingWrite(send, (void *)pd);
}

int  nonblocking_send_packet(PacketDescriptor *pd) {
	return send->nonblockingWrite(send, (void *)pd);
}

void blocking_get_packet(PacketDescriptor **pd, PID pid) {
	BoundedBuffer *app = apps[pid]; /* to index into the correct BB */
	app->blockingRead(app, (void **)pd);
}

int  nonblocking_get_packet(PacketDescriptor **pd, PID pid) {
	BoundedBuffer *app = apps[pid];
	return app->nonblockingRead(app, (void **)pd);
}

int nonblocking_put_PD(PacketDescriptor *pd) {
	if (pool->nonblockingWrite(pool, (void *)pd) == 0) {
		if (fpds->nonblockingPut(fpds, pd) == 0) {
			DIAGNOSTICS("[DRIVER> Critical Error: Failed to write to FPDS\n");
			return 0;
		} else {
			DIAGNOSTICS("[DRIVER> Info: Put packet with PID %i back in the FPDS\n", getPID(pd));
		}
	} else {
		DIAGNOSTICS("[DRIVER> Info: Put packet with PID %i back in the pool\n", getPID(pd));
	}
	return 1;
}

int nonblocking_get_PD(PacketDescriptor **pd) {
	if (pool->nonblockingRead(pool, (void **)pd) == 0) {
		if (fpds->nonblockingGet(fpds, pd) == 0) {
			DIAGNOSTICS("[DRIVER> Error: Failed to get a packet from the FPDS or pool\n");
			return 0;
		}
	}
	return 1;
}

void *send_thread(UNUSED void *unused) {
	PacketDescriptor *pd;
	int i;
	int result;
	while (1) {
		result = 0;
		/* need to blocking read the send BB because we can't do anything until we have a packet */
		send->blockingRead(send, (void **)&pd);

		for (i = 0; i < 10; i++) { /* 10 tries before we give up */
			result = netDevice->sendPacket(netDevice, pd);
			if (result == 1) {
				DIAGNOSTICS("[DRIVER> Info: packet with PID %i sent after %i tries\n", getPID(pd), i + 1);
				break;
			}
		}
		if (result == 0) {
			DIAGNOSTICS("[DRIVER> Error: Failed to send packet with PID %i\n", getPID(pd));
		}
	
		
		result = nonblocking_put_PD(pd); /* return pd to pool or FPDS */
		if (result == 1) {			/* this can be nonblocking because it should never fail */
			DIAGNOSTICS("[DRIVER> Info: Send thread: Put back packet with PID %i\n", getPID(pd));
		} else {
			DIAGNOSTICS("[DRIVER> Error: Send thread: Failed to put back packet with PID %i\n", getPID(pd));
		}
	}
}

void *receive_thread(UNUSED void *unused) {
	PacketDescriptor *pd;
	PID pid;
	PacketDescriptor *temp;

	/* get the code started by finding a pd */
	if (pool->nonblockingRead(pool, (void **)&pd) == 0) { /* try to get from the pool */
		fpds->blockingGet(fpds, &pd); /* if there are none in there yet, wait for one from the FPDS */
	}

	initPD(pd);
	netDevice->registerPD(netDevice, pd);
	while (1) {
		netDevice->awaitIncomingPacket(netDevice);
		if (nonblocking_get_PD(&temp) == 1) { /* we have at least 1 other packet to use */
			pid = getPID(pd);
			if (apps[pid]->nonblockingWrite(apps[pid], pd) == 0) { /* couldn't put it into the correct BB */
				DIAGNOSTICS("[DRIVER> Error: Couldn't write packet with PID %i into application bounded buffer\n", getPID(pd));
				nonblocking_put_PD(pd);
			}
			pd = temp;
		} /* this if block would be skipped if we only had 1 packet available, meaning we would reuse it */
		initPD(pd);	
		netDevice->registerPD(netDevice, pd);
	}
}

void init_network_driver(NetworkDevice               *nd, 
                         void                        *mem_start, 
                         unsigned long               mem_length,
                         FreePacketDescriptorStore **fpds_ptr) {
	int i;
	unsigned long fpdsSize;
	pthread_t send_thr;
	pthread_t receive_thr;

	netDevice = nd; /* give ourselves a reference to the network device */
	fpds = FreePacketDescriptorStore_create(mem_start, mem_length);
	fpdsSize = fpds->size(fpds);
	pool = BoundedBuffer_create((int)(fpdsSize / 5)); /* (2/10) of FPDS */
	send = BoundedBuffer_create((int)(fpdsSize / 2.5)); /* (4/10) of FPDS */
	
	for (i = 0; i < 11; i++)
		apps[i] = BoundedBuffer_create((int)(fpdsSize / 10.1)); /* each gets (1/11) of (4/10) of the FPDS */

	/* create threads */
	pthread_create(&send_thr, NULL, &send_thread, NULL);
	pthread_create(&receive_thr, NULL, &receive_thread, NULL);

	*fpds_ptr = fpds; /* give the fpds back to the caller */ 
}
