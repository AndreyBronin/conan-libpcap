/**
 * \file
 * \brief List network card and collect information
 *
 * Copyright 2017 Uilian Ries <uilianries@gmail.com>
 */
#include <assert.h>
#include <stdlib.h>
#include <pcap.h>

int main(int argc, char **argv)
{
    char errbuf[PCAP_ERRBUF_SIZE] = {0};
    bpf_u_int32 netp = 0;
    bpf_u_int32 maskp = 0;
    const char* dev = NULL;
    pcap_if_t *devlist = NULL;

    // device lookup
    if (pcap_findalldevs(&devlist, errbuf) == -1)
    {
        fprintf(stderr, "Couldn't get device list: %s\n", errbuf);
        return EXIT_FAILURE;
    }

    if (devlist != NULL) {
        if (pcap_lookupnet(devlist->name, &netp, &maskp, errbuf) == -1) {
            fprintf(stderr, "Couldn't get netmask for device %s: %s\n", dev, errbuf);
        }
    }

    return EXIT_SUCCESS;
}
