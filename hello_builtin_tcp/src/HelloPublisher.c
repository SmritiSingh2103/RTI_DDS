/*****************************************************************************/
/*         (c) Copyright, Real-Time Innovations, All rights reserved.        */
/*                                                                           */
/*         Permission to modify and use for internal purposes granted.       */
/* This software is provided "as is", without warranty, express or implied.  */
/*                                                                           */
/*****************************************************************************/


#include "Hello.h"
#include "HelloPublisher.h"


/* Defines the maximum number of consecutive write errors. */
#define MAX_CONSECUTIVE_WRITE_ERROR         10

int RTI_SNPRINTF (
   char *buffer,
	//int RTI_SNPRINTF(
		//unsigned char *buffer,
   size_t count,
   const unsigned char *format, ...)
{
    int length;
    va_list ap;
    va_start(ap, format);
#ifdef RTI_WIN32
    length = _vsnprintf_s(buffer, count, count, format, ap);
#else
    length = vsnprintf(buffer, count, format, ap);
#endif
     va_end(ap);
     return length;
}

/*****************************************************************************/
/* start_publisher                                                           */
/*                                                                           */
/* Creates the DDS publisher and data writers, then start sending the data.  */
/*                                                                           */
/* Input:                                                                    */
/*   participant: the DDS domain participant to use                          */
/*   topic: the DDS topic to use for publishing                              */
/*   dataSise: size of the payload buffer to send                            */
/*                                                                           */
/* Returns:                                                                  */
/*   The boolean value DDS_BOOLEAN_TRUE if an error occurred.                */
/*                                                                           */
/*****************************************************************************/
DDS_Boolean start_publisher(
                        DDS_DomainParticipant *participant,
                        DDS_Topic *topic,
                        DDS_Boolean verbose,
                        DDS_Long data_size,
                        DDS_Long sampleCount) {
    DDS_DataWriter *data_writer          = NULL;
    DDS_StringDataWriter *hello_writer   = NULL;
   // char *instance                       = NULL;
	/****************edited here**********************/
	
	 char *instance=NULL;
	 //char *ddsmsg=NULL;
	/****************edited here*********************/
    DDS_Boolean return_value             = DDS_BOOLEAN_FALSE;
    DDS_Long i;
    DDS_Long count;
	char *msg = NULL;
    DDS_ReturnCode_t rc;

    /* Creates the DDS Data writer. 
     * Just like before, if you want to customize the writer QoS,
     * use DDS_Publisher_get_default_datawriter_qos() to 
     * initialize a local copy of the default QoS, modify them, then
     * use them in the creation call below instead of 
     * DDS_DATAWRITER_QOS_DEFAULT.
     * For more data writer API info, see:
     *     $NDDSHOME/doc/html/api_c/group__DDSWriterModule.html
     */
    if (verbose) {
        printf("Creating the data writer...\n");
    }
    data_writer = DDS_DomainParticipant_create_datawriter(
                        participant, 
                        topic,
                        &DDS_DATAWRITER_QOS_DEFAULT,
                        NULL,           /* listener */
                        DDS_STATUS_MASK_NONE);
    if (data_writer == NULL) {
        fprintf(stderr, "! Unable to create DDS data writer\n");
        goto exitFn;
    }

    /* The following narrow function should never fail, as it performs 
     * only a safe cast of the generic data writer into a specific
     * DDS_StringDataWriter.
     * In our case the following cast would do the same job:
     *     hello_writer = (DDS_StringDataWriter *)data_writer;
     */
    hello_writer = DDS_StringDataWriter_narrow(data_writer);
    if (hello_writer == NULL) {
        fprintf(stderr, "! Unable to narrow data writer into "
                        "DDS_String writer\n");
        goto exitFn;
    }
    
    /* The string we are sending will have the following form:
     * - 10 characters (padded with spaces) will contain a sequence number,
     *   in ASCII character
     * - the rest of the string (data_size - 10) will contain just 'ABCDEF...'
     * The string buffer is managed by the application.
     */
	//instance = DDS_String_alloc(data_size);
	instance = DDS_String_alloc(1875);
	printf("datasize = %d\n", data_size);
    if (instance == NULL) {
        fprintf(stderr, "! Unable to create an instance of the data\n");
		printf("instance null");
        fprintf(stderr, "! This problem most likely is caused by "
                        "out of memory\n");
        goto exitFn;
    }
   
	

    /* Fill up the buffer with some valid data:
     * The content of the payload buffer is a progressive series of incremental
     * numbers, starting from 0.
     */
	/*****************edited here**********************/
    /*for (i = 0; i < data_size-1; ++i) { 
        instance[i] = (i < 11) ? ' ' : ('A' + (i % 26));
    }
    instance[i] = '\0'; /* write() will use strlen to determine the length */
	/****************edited here*********************/
	/*******************RTI IMAGE FILE******************************************/
	size_t im_size;
	int n, j, newsize;
	pixdata(&im_size);
	newsize = im_size;
	  char *newarr;
	  char *ddsmsg;
	  char newmsg;
	 
	newarr = malloc(im_size);
	ddsmsg = malloc(im_size);
	printf("from pub pixdata size= %d\n", im_size);
	FILE *fp,*fp1; 
	fp = fopen("rti_dds001.bin", "rb");
	fp1 = fopen("rti_dds_wr01.txt", "wb");
	if (fp == NULL) {
		printf("file cannot be opened");
	}
	/*with getc it does not detect correct eof*/
	for (j = 0; (n = getw(fp)) != EOF; j++) {
		newarr[j] = n;
		ddsmsg[j] = n;
		//newarr[j] = instance;
		//printf("from new arr %d\n", newarr[i]);
		fprintf(fp1, "%c", newarr[j]);
	}
	fclose(fp);
	fclose(fp1);
	
	//int k;
	
	//for (k = 0; k < im_size; k++) {
	//	 ddsmsg[k] = newarr[k];
//	}
	/*******************INSTANCE*********************************/
	//for (i = 0; i < data_size-1; ++i) {
		//instance[i] = (i < 11) ? ' ' : ('A' + (i % 26));
	//}
		//instance[i] = '\0'; /* write() will use strlen to determine the length */
	/************************END INSTANCE************************************/
	//instance[0] ='A';
	/*******************RTI IMAGE FILE*****************************************/
    /* Send the data! */
    printf("Sending data...\n");
	printf("new arr=  %d", newarr[0]);
	/*add delay here*/
	struct DDS_Duration_t initSendPeriod = { 2, 0 };
	NDDS_Utility_sleep(&initSendPeriod);
	NDDS_Utility_sleep(&initSendPeriod);
	NDDS_Utility_sleep(&initSendPeriod);
	NDDS_Utility_sleep(&initSendPeriod);
	char msgg[10] = {1,2,3,4,5,6,7,8,9,10};
		i = 0; /* Use 'i' to keep track of consecutive write errors */
		/*begin of for loop*/
   // for (count = 0;count<=7500; count++ ) {
		//for (int count = 0; (sampleCount == 0) || (count < sampleCount); count++){
			for (int count = 0;  (count < 1875); count++) {
        /* Conversion of an integer to a string in snprintf is relatively
         * expensive and could impact the throughput. But since this is
         * just an example, let's keep it simple. */
		//instance = newarr[count];
			//printf("pixel val=%d\n", newarr[count]);
			//instance = newarr[count];
			//strcpy(instance, newarr[count]);
				//printf("ddsmsg=%d\n", ddsmsg[count]);
	RTI_SNPRINTF(instance, 128, "%c",newarr[count]);
	//DDS_String_free(instance);
	//fflush(stdout);
	//fflush(instance);
	//instance = ' ';
	printf("count= %d\n", count);
    //instance[255] = ' '; /* Remove the '\0' introduced by snprintf */
		//printf("from pub pixel instance = %c\n",newarr[count]);
        rc = DDS_StringDataWriter_write(
                        hello_writer, 
                        instance, 
                        &DDS_HANDLE_NIL);
        if (rc != DDS_RETCODE_OK) {
            fprintf(stderr, "! Write error %d\n", rc);
			/*edited here*/
		printf(stderr, "! Write error %d\n", rc);
            if (++i > MAX_CONSECUTIVE_WRITE_ERROR) {
                fprintf(stderr, "! Reached maximum number of failure, "
                       "stopping writer...\n");
				/*edited here*/
			printf(stderr, "! Reached maximum number of failure, "
					"stopping writer...\n");
                goto exitFn;
            }
        } else {
            i = 0;  /* Always clear the error count in case of successful write */
       }
        if (verbose && (count % 10000) == 0) {
			printf("Sent %d samples...\n", newarr[count]);
			//printf("Sent %d samples...\n", mau[count]);
            //printf("Sent %d samples...\n", count);
            fflush(stdout);
        }
        /* Stop after sampleCount sent */
        if (sampleCount != 0 && (count >= sampleCount)) {
			//fprintf(stderr, "\nSent %d samples.\n", mau[count]);
			fprintf(stderr, "\nSent %d samples.\n", newarr[count]);
            //fprintf(stderr, "\nSent %d samples.\n", count);
            break;
        }
		

        //if (count < 20) {
		if (count < im_size) {
			//edited for {1,0}
            struct DDS_Duration_t initialSendPeriod = {0.75, 0};
            /*fprintf(stderr,
                    "\nSending %d out of 20 samples before speeding up...\n",
                    count);*/
			/*fprintf(stderr,
				"\nSending %d out of %d samples before speeding up...\n",
				mau[count],im_size);*/
			fprintf(stderr,
				"\nSending %d th pixel %d out of %d samples before speeding up...\n",
				count,newarr[count], im_size);
            NDDS_Utility_sleep(&initialSendPeriod);
        } 
		//else if (count == 20) {
		else if (count == im_size) {
            fprintf(stderr, "Speeding up now!!\n");
        }
		//DDS_String_free(instance);
		//instance = NULL;
		//fflush(instance);
		//instance = ' ';
		//RTI_SNPRINTF(instance, 255, "%d", newarr[count]);
    }
    /*End of for loop*/
    /* This code is reached only if sampleCount is set */
    return_value = DDS_BOOLEAN_TRUE;

exitFn:
    if (instance != NULL) {
        DDS_String_free(instance);
        instance = NULL;
    }
    
    return return_value;
}
