#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <assert.h>

#include "nsAPItypes.h"

#define nsAPIReturn ns_RESULT

typedef char* text;

//	ns_GetFileInfo
//	ns_GetEntityInfo
//	ns_GetEventInfo;
//	ns_GetEventData;
//	ns_GetAnalogInfo;
//	ns_GetAnalogData;
//	ns_GetSegmentInfo;
//	ns_GetSegmentSourceInfo;
//	ns_GetSegmentData;
//	ns_GetNeuralInfo;
//	ns_GetNeuralData;
//	ns_GetIndexByTime;
//	ns_GetTimeByIndex;
//	ns_GetLastErrorMsg

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Usage: test lib file\n");
		printf("lib is the Neuroshare shared library *.so\n");
		printf("file is the data file to be examined\n");
		exit(0);
	}

	dlerror(); // Empty previous errors

	void* handle = dlopen(argv[1],RTLD_NOW);
    if (!handle) {
		fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
	printf("Successfully opened: %s\n",argv[1]);
	
	char *error;
	nsAPIReturn ret;

	// ns_GetLibraryInfo
	typedef nsAPIReturn (*tGetLibraryInfo)(ns_LIBRARYINFO*, uint32);
	tGetLibraryInfo ns_GetLibraryInfo = (tGetLibraryInfo)dlsym(handle,"ns_GetLibraryInfo");
	if ((error = dlerror()) != NULL)  {
		 fprintf(stderr, "%s\n", error);
         exit(1);
    } 
	ns_LIBRARYINFO libinfo;
	ret = ns_GetLibraryInfo(&libinfo,sizeof(ns_LIBRARYINFO));
	if (ret != ns_OK)
	{
		fprintf(stderr,"Error calling: ns_GetLibraryInfo %d\n",ret );
		exit(1);
	}
	printf("NSlib Version: %d.%d, implementing API Version %d.%d\n",libinfo.dwLibVersionMaj,libinfo.dwLibVersionMin,libinfo.dwAPIVersionMaj,libinfo.dwAPIVersionMin);
	printf("Description: %s\n",libinfo.szDescription);
	printf("Creator: %s\n",libinfo.szCreator);
	printf("%04d-%02d-%02d",libinfo.dwTime_Year,libinfo.dwTime_Month,libinfo.dwTime_Day);
	if (libinfo.dwFlags == ns_LIBRARY_DEBUG)
		printf(" ns_LIBRARY_DEBUG");
	if (libinfo.dwFlags == ns_LIBRARY_MODIFIED)
		printf(" ns_LIBRARY_MODIFIED");
	if (libinfo.dwFlags == ns_LIBRARY_PRERELEASE)
		printf(" ns_LIBRARY_PRERELEASE");
	if (libinfo.dwFlags == ns_LIBRARY_SPECIALBUILD)
		printf(" ns_LIBRARY_SPECIALBUILD");
	if (libinfo.dwFlags == ns_LIBRARY_MULTITHREADED)
		printf(" ns_LIBRARY_MULTITHREADED");
	printf("\n");
	printf("Max number of open files: %d\n",libinfo.dwMaxFiles);
	for(int i = 0;i < libinfo.dwFileDescCount;i++)
	{
		printf("File types: %s, Extension: %s\n",libinfo.FileDesc[i].szDescription,libinfo.FileDesc[i].szExtension);
	}
	printf("\n");

	// ns_OpenFile
	typedef nsAPIReturn (*tOpenFile)(char*, uint32*);
	tOpenFile ns_OpenFile = (tOpenFile)dlsym(handle,"ns_OpenFile");
	if ((error = dlerror()) != NULL)  {
		 fprintf(stderr, "%s\n", error);
         exit(1);
    } 
	uint32 hFile;
	ret = ns_OpenFile(argv[2],&hFile);
	if (ret != ns_OK)
	{
		fprintf(stderr,"Error calling: ns_OpenFile on %s, error %d\n",argv[2],ret);
		exit(1);
	}
	printf("Successfully opened: %s\n",argv[2]);

	// ns_GetFileInfo
	typedef nsAPIReturn (*tGetFileInfo)(uint32, ns_FILEINFO*, uint32);
	tGetFileInfo ns_GetFileInfo = (tGetFileInfo)dlsym(handle,"ns_GetFileInfo");
	if ((error = dlerror()) != NULL)  {
		 fprintf(stderr, "%s\n", error);
         exit(1);
    } 
	ns_FILEINFO fileinfo;
	ret = ns_GetFileInfo(hFile,&fileinfo,sizeof(ns_FILEINFO));
	if (ret != ns_OK)
	{
		fprintf(stderr,"Error calling: ns_GetFileInfo %d\n",ret);
		exit(1);
	}
	printf("FileType: %s\n",fileinfo.szFileType);
	printf("Entity count: %d\n",fileinfo.dwEntityCount);
	printf("Timestamp resolution: %f\n",fileinfo.dTimeStampResolution);
	printf("Time span of file: %fs\n",fileinfo.dTimeSpan);
	printf("Created with: %s\n",fileinfo.szAppName);
	printf("%04d-%02d-%02d %02d:%02d:%02d.%03d\n",fileinfo.dwTime_Year,fileinfo.dwTime_Month,fileinfo.dwTime_Day,fileinfo.dwTime_Hour,fileinfo.dwTime_Min,fileinfo.dwTime_Sec,fileinfo.dwTime_MilliSec);
	printf("Comment: %s\n",fileinfo.szFileComment);
	printf("\n");

	// ns_GetEntityInfo
	typedef nsAPIReturn (*tGetEntityInfo)(uint32, uint32, ns_ENTITYINFO*, uint32);
	tGetEntityInfo ns_GetEntityInfo = (tGetEntityInfo)dlsym(handle,"ns_GetEntityInfo");
	if ((error = dlerror()) != NULL)  {
		 fprintf(stderr, "%s\n", error);
         exit(1);
    } 
	typedef nsAPIReturn (*tGetEventInfo)(uint32, uint32, ns_EVENTINFO*, uint32);
	tGetEventInfo ns_GetEventInfo = (tGetEventInfo)dlsym(handle,"ns_GetEventInfo");
	if ((error = dlerror()) != NULL)  {
		 fprintf(stderr, "%s\n", error);
         exit(1);
    } 
	typedef nsAPIReturn (*tGetAnalogInfo)(uint32, uint32, ns_ANALOGINFO*, uint32);
	tGetAnalogInfo ns_GetAnalogInfo = (tGetAnalogInfo)dlsym(handle,"ns_GetAnalogInfo");
	if ((error = dlerror()) != NULL)  {
		 fprintf(stderr, "%s\n", error);
         exit(1);
    } 
	typedef nsAPIReturn (*tGetSegmentInfo)(uint32, uint32, ns_SEGMENTINFO*, uint32);
	tGetSegmentInfo ns_GetSegmentInfo = (tGetSegmentInfo)dlsym(handle,"ns_GetSegmentInfo");
	if ((error = dlerror()) != NULL)  {
		 fprintf(stderr, "%s\n", error);
         exit(1);
    } 
	typedef nsAPIReturn (*tGetSegmentSourceInfo)(uint32, uint32, uint32, ns_SEGSOURCEINFO*, uint32);
	tGetSegmentSourceInfo ns_GetSegmentSourceInfo = (tGetSegmentSourceInfo)dlsym(handle,"ns_GetSegmentSourceInfo");
	if ((error = dlerror()) != NULL)  {
		 fprintf(stderr, "%s\n", error);
         exit(1);
    } 

	typedef nsAPIReturn (*tGetEventData)(uint32, uint32, uint32, double*, void*, uint32, uint32*);
	tGetEventData ns_GetEventData = (tGetEventData)dlsym(handle,"ns_GetEventData");
	if ((error = dlerror()) != NULL)  {
		 fprintf(stderr, "%s\n", error);
         exit(1);
    } 
	typedef nsAPIReturn (*tGetAnalogData)(uint32, uint32, uint32, uint32, uint32*, double*);
	tGetAnalogData ns_GetAnalogData = (tGetAnalogData)dlsym(handle,"ns_GetAnalogData");
	if ((error = dlerror()) != NULL)  {
		 fprintf(stderr, "%s\n", error);
         exit(1);
    } 
	typedef nsAPIReturn (*tGetSegmentData)(uint32, uint32, int32, double*, double*, uint32, uint32*, uint32*);
	tGetSegmentData ns_GetSegmentData = (tGetSegmentData)dlsym(handle,"ns_GetSegmentData");
	if ((error = dlerror()) != NULL)  {
		 fprintf(stderr, "%s\n", error);
         exit(1);
    } 

	ns_ENTITYINFO* pEntityInfo = new ns_ENTITYINFO[fileinfo.dwEntityCount];
	for(int i = 0;i < fileinfo.dwEntityCount;i++)
	{
		ret = ns_GetEntityInfo(hFile,i,&pEntityInfo[i],sizeof(ns_ENTITYINFO));
		if (ret != ns_OK)
		{
			fprintf(stderr,"Error calling: ns_GetEntityInfo %d\n",ret);
			exit(1);
		}
		printf("Entity %d: %s ",i,pEntityInfo[i].szEntityLabel);
		switch (pEntityInfo[i].dwEntityType)
		{
		case ns_ENTITY_UNKNOWN: // unknown entity type
			printf("Unknown entity");
			break;
		case ns_ENTITY_EVENT: // Event entity
			printf("Event entity");
			break;
		case ns_ENTITY_ANALOG: // Analog entity
			printf("Analog entity");
			break;
		case ns_ENTITY_SEGMENT: // Segment entity
			printf("Segment entity");
			break;
		case ns_ENTITY_NEURALEVENT:
			printf("Neural Entity");
			break;
		default:
			assert(false);
			printf("Wrong entity type");
		}
		printf(", %d items\n",pEntityInfo[i].dwItemCount);

		switch(pEntityInfo[i].dwEntityType)
		{
		case ns_ENTITY_EVENT: // Event entity
			ns_EVENTINFO pEventInfo;
			ret = ns_GetEventInfo(hFile,i,&pEventInfo,sizeof(ns_EVENTINFO));
			if (ret != ns_OK)
			{
				fprintf(stderr,"Error calling: ns_GetEventInfo %d\n",ret);
				exit(1);
			}
			printf("Event type: ");
			switch (pEventInfo.dwEventType)
			{
			case ns_EVENT_TEXT:
				printf("null-terminated ascii text string");
				break;
			case ns_EVENT_CSV:
				printf("comma separated ascii text values");
				break;
			case ns_EVENT_BYTE:
				printf("8-bit value");
				break;
			case ns_EVENT_WORD:
				printf("16-bit value");
				break;
			case ns_EVENT_DWORD:
				printf("32-bit value");
				break;
			default:
				assert(false);
				printf("unknowsn event type");
			}; 
			printf("\n");
			printf("Min data length: %d, Max data length: %d\n",pEventInfo.dwMinDataLength,pEventInfo.dwMaxDataLength);
			//szCSVDesc[128];

			for(int k = 0;k < pEntityInfo[i].dwItemCount;k++)
			{
				double pdTimeStamp;
				unsigned char* pData = new unsigned char[pEventInfo.dwMaxDataLength];
				uint32 pdwDataRetSize;
				ret = ns_GetEventData (hFile,i,k,&pdTimeStamp,pData,pEventInfo.dwMaxDataLength,&pdwDataRetSize);
				if (ret != ns_OK)
				{
					fprintf(stderr,"Error calling: ns_GetEventData %d\n",ret);
					exit(1);
				}
				printf(" t=%f size=%d ",pdTimeStamp,pdwDataRetSize);
				switch (pEventInfo.dwEventType)
				{
				case ns_EVENT_TEXT:
					printf("Not Implemented");
					break;
				case ns_EVENT_CSV:
					printf("Not Implemented");
					break;
				case ns_EVENT_BYTE:
					for(int l = 0;l < pdwDataRetSize;l+=sizeof(unsigned char))
					{
						printf("%d ",*(unsigned char*)(pData+l));
					}
					break;
				case ns_EVENT_WORD:
					for(int l = 0;l < pdwDataRetSize;l+=sizeof(unsigned short))
					{
						printf("%d ",*(unsigned short*)(pData+l));
					}
					break;
				case ns_EVENT_DWORD:
					printf("Not Implemented");
					break;
				default:
					assert(false);
					printf("unknowsn event type");
			}; 
				printf("\n");
			}
			break;
		case ns_ENTITY_ANALOG: // Analog entity
			ns_ANALOGINFO pAnalogInfo;
			ret = ns_GetAnalogInfo(hFile,i,&pAnalogInfo,sizeof(ns_ANALOGINFO));
			if (ret != ns_OK)
			{
				fprintf(stderr,"Error calling: ns_GetAnalogInfo %d\n",ret);
				exit(1);
			}
			printf("Sampling rate: %fHz\n",pAnalogInfo.dSampleRate);
			printf("Min: %f, Max: %f, Unit: %s, Resolution: %f\n",pAnalogInfo.dMinVal,pAnalogInfo.dMaxVal,pAnalogInfo.szUnits,pAnalogInfo.dResolution);
			//double	dLocationX;            // X coordinate in meters
			//double	dLocationY;            // Y coordinate in meters
			//double	dLocationZ;            // Z coordinate in meters
			//double	dLocationUser;         // Additional position information (e.g. tetrode number)
			//double	dHighFreqCorner;       // High frequency cutoff in Hz of the source signal filtering
			//uint32	dwHighFreqOrder;       // Order of the filter used for high frequency cutoff
			//char	szHighFilterType[16];  // Type of filter used for high frequency cutoff (text format)
			//double	dLowFreqCorner;        // Low frequency cutoff in Hz of the source signal filtering
			//uint32	dwLowFreqOrder;        // Order of the filter used for low frequency cutoff
			//char	szLowFilterType[16];   // Type of filter used for low frequency cutoff (text format)
			//char	szProbeInfo[128];      // Additional text information about the signal source

			for(int k = 0;k < pEntityInfo[i].dwItemCount;)
			{
				double* pData = new double[10000];
				uint32 pdwContCount;
				uint32 dwIndexCount = pEntityInfo[i].dwItemCount - k > 10000 ? 10000 : pEntityInfo[i].dwItemCount - k; 
				ret = ns_GetAnalogData (hFile,i,k, dwIndexCount,&pdwContCount,pData);
				if (ret != ns_OK)
				{
					fprintf(stderr,"Error calling: ns_GetEventData %d\n",ret);
					exit(1);
				}
				printf(" ContCount: %d",pdwContCount);
				for(int l = 0;l < pdwContCount;l++)
					printf(" %f",pData[l]);
				printf("\n");

				k+=pdwContCount;

			}

			break;
		case ns_ENTITY_SEGMENT: // Segment entity
			ns_SEGMENTINFO pSegmentInfo;
			ret = ns_GetSegmentInfo(hFile,i,&pSegmentInfo,sizeof(ns_SEGMENTINFO));
			if (ret != ns_OK)
			{
				fprintf(stderr,"Error calling: ns_GetSegmentInfo %d\n",ret);
				exit(1);
			}
			printf("Min sample count: %d, Max sample count: %d\n",pSegmentInfo.dwMinSampleCount,pSegmentInfo.dwMaxSampleCount);
			printf("Sample rate: %fHz\n",pSegmentInfo.dSampleRate);
			printf("Units: %s\n",pSegmentInfo.szUnits);

			for(int j = 0;j < pSegmentInfo.dwSourceCount;j++)
			{
				ns_SEGSOURCEINFO pSourceInfo;
				ret = ns_GetSegmentSourceInfo(hFile,i,j,&pSourceInfo,sizeof(ns_SEGSOURCEINFO));
				if (ret != ns_OK)
				{
					fprintf(stderr,"Error calling: ns_GetSegmentSourceInfo %d\n",ret);
					exit(1);
				}
				printf("Source %d:\n",j);
				printf(" Min: %f, Max: %f, Resolution: %f, Sample shift: %f\n",pSourceInfo.dMinVal,pSourceInfo.dMaxVal,pSourceInfo.dResolution,pSourceInfo.dSubSampleShift);
				//double dLocationX;            // X coordinate of source in meters
				//double dLocationY;            // Y coordinate of source in meters
				//double dLocationZ;            // Z coordinate of source in meters
				//double dLocationUser;         // Additional position information (e.g tetrode number)
				//double dHighFreqCorner;       // High frequency cutoff in Hz of the source signal filtering
				//uint32 dwHighFreqOrder;       // Order of the filter used for high frequency cutoff
				//char   szHighFilterType[16];  // Type of filter used for high frequency cutoff (text format)
				//double dLowFreqCorner;		  // Low frequency cutoff in Hz of the source signal filtering
				//uint32 dwLowFreqOrder;        // Order of the filter used for low frequency cutoff
				//char   szLowFilterType[16];	  // Type of filter used for low frequency cutoff (text format)
				//char   szProbeInfo[128];      // Additional text information about the signal source

			}

			break;
		}
		printf("\n");
	}

	// cleanup ns_GetEntityInfo
	delete pEntityInfo;

	// ns_CloseFile
	typedef nsAPIReturn (*tCloseFile)(uint32);
	tCloseFile ns_CloseFile = (tCloseFile)dlsym(handle,"ns_CloseFile");
	if ((error = dlerror()) != NULL)  {
		 fprintf(stderr, "%s\n", error);
         exit(1);
    } 
	ret = ns_CloseFile(hFile);
	if (ret != ns_OK)
	{
		fprintf(stderr,"Error calling: ns_CloseFile %d\n",ret);
		exit(1);
	}
	printf("File closed\n");

	ret = dlclose(handle);
	if (ret)
	{
		fprintf(stderr,"%s\n",dlerror());
		exit(1);
	}
	printf("Shared library closed\n");

}
